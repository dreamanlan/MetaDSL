#include "BraceCoroutine.h"
#include "boost/context/fiber.hpp"
#include <iostream>

namespace CoroutineWithBoostContext
{
#define Terminated(C) (!(C)->m_pData->Environment)
    
    namespace ctx = boost::context;
    using fiber = ctx::fiber;
    
    static inline void Error(const char* message)
    {
        std::cerr << "Error: " << message << std::endl;
        //exit(0);
    }

    static Coroutine* g_Current = nullptr;

    struct CoroutineData final
    {
        fiber Environment;
        size_t BufferSize;
        Coroutine* Caller, * Callee;
        Coroutine* ResumeFrom;
        Coroutine* Current;

        CoroutineData(Coroutine* current, int bufferSize) :Environment{}
        {
            BufferSize = bufferSize;
            Callee = Caller = nullptr;
            ResumeFrom = nullptr;
            Current = current;
        }
        ~CoroutineData(void)
        {
            Callee = Caller = nullptr;
            ResumeFrom = nullptr;
            Current = nullptr;
        }
        void BuildEnv(void)
        {
            ctx::fixedsize_stack salloc(BufferSize);
            ctx::stack_context sctx(salloc.allocate());
            void* sp = static_cast<char*>(sctx.sp);
            std::size_t size = sctx.size;

            Environment = fiber(std::allocator_arg, ctx::preallocated(sp, size, sctx), salloc, [this](fiber&& c) { return Callcc(std::move(c)); });
        }
        fiber Callcc(fiber&& cont)const
        {
            ResumeFrom->m_pData->Environment = std::move(cont);
            Current->Routine();
            if (Current == g_Current) {
                Current->Exit();
            }
            return std::move(ResumeFrom->m_pData->Environment);
        }
    };

    class CoroutineMain : public Coroutine
    {
    public:
        CoroutineMain(void) :Coroutine(1024*1024)
        {
            g_Current = this;
        }
        virtual void Routine(void) override
        {
        }
    };

    static CoroutineMain g_Main;

    Coroutine::Coroutine(int stackSize)
    {
        m_pData = new CoroutineData(this, stackSize);
    }
    Coroutine::~Coroutine(void)
    {
        delete m_pData;
        m_pData = nullptr;
    }
    bool Coroutine::IsTerminated(void)const
    {
        return Terminated(this);
    }
    void Coroutine::Reset(void)
    {
        if (this == g_Current) {
            Error("Attempt to reset current coroutine, you must call Reset in other coroutine or main");
            return;
        }
        if (nullptr != m_pData->Callee) {
            m_pData->Callee->m_pData->Caller = m_pData->Caller;
        }
        if (nullptr != m_pData->Caller) {
            m_pData->Caller->m_pData->Callee = m_pData->Callee;
        }
        m_pData->Callee = m_pData->Caller = nullptr;
        m_pData->ResumeFrom = nullptr;

        m_pData->BuildEnv();
    }
    void Coroutine::CallFromMain(void)
    {
        if (IsTerminated())
            Reset();
        CoroutineWithBoostContext::Call(this);
    }
    inline void Coroutine::Enter()
    {
        Coroutine* pCurrent = g_Current;
        g_Current = this;
        m_pData->ResumeFrom = pCurrent;
        m_pData->Environment = std::move(m_pData->Environment).resume();
    }
    inline void Coroutine::Exit()
    {
        if (g_Current == this)
            g_Current = &g_Main;
    }

    void Resume(Coroutine* next)
    {
        if (nullptr == next) {
            Error("Attempt to Resume a non-existing Coroutine");
            return;
        }
        if (next == g_Current) {
            return;
        }
        if (Terminated(next)) {
            Error("Attempt to Resume a terminated Coroutine");
            return;
        }
        if (next->m_pData->Caller) {
            Error("Attempt to Resume an attached Coroutine");
            return;
        }
        while (next->m_pData->Callee) {
            next = next->m_pData->Callee;
        }
        next->Enter();
    }
    void Call(Coroutine* next)
    {
        if (nullptr == next) {
            Error("Attempt to Call a non-existing Coroutine");
            return;
        }
        if (Terminated(next)) {
            Error("Attempt to Call a terminated Coroutine");
            return;
        }
        if (next->m_pData->Caller) {
            Error("Attempt to Call an attached Coroutine");
            return;
        }
        g_Current->m_pData->Callee = next;
        next->m_pData->Caller = g_Current;
        while (next->m_pData->Callee) {
            next = next->m_pData->Callee;
        }
        if (next == g_Current) {
            Error("Attempt to Call an operating Coroutine");
            return;
        }
        next->Enter();
    }
    void Detach(void)
    {
        Coroutine* next = g_Current->m_pData->Caller;
        if (next) {
            g_Current->m_pData->Caller = next->m_pData->Callee = nullptr;
        }
        else {
            next = &g_Main;
            while (next->m_pData->Callee) {
                next = next->m_pData->Callee;
            }
        }
        next->Enter();
    }
    Coroutine* CurrentCoroutine(void)
    {
        return g_Current;
    }
    Coroutine* MainCoroutine(void)
    {
        return &g_Main;
    }
}