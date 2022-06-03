#include "BraceCoroutine.h"
#include "boost/context/fiber.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

namespace CoroutineWithBoostContext
{
#define Terminated(C) (!(C)->m_pData->Environment)
    
    namespace ctx = boost::context;
    using fiber = ctx::fiber;

    struct my_fixedsize_stack_alloc_pool
    {
        struct my_fixedsize_stack_alloc_record
        {
            ctx::fixedsize_stack allocator;
            std::vector<ctx::stack_context> contexts;

            my_fixedsize_stack_alloc_record(std::size_t size) :allocator(size), contexts()
            {
            }
        };

        std::unordered_map<std::size_t, my_fixedsize_stack_alloc_record> fixedsize_stack_pool_{};

        my_fixedsize_stack_alloc_record& get_or_new_alloc_record(std::size_t size)
        {
            auto it = fixedsize_stack_pool_.find(size);
            if (it == fixedsize_stack_pool_.end()) {
                my_fixedsize_stack_alloc_record record(size);
                auto result = fixedsize_stack_pool_.insert(std::make_pair(std::move(size), std::move(record)));
                it = result.first;
                auto& rec = it->second;
                return rec;
            }
            else {
                return it->second;
            }
        }
        ctx::stack_context alloc_stack(std::size_t size)
        {
            auto& rec = get_or_new_alloc_record(size);
            if (rec.contexts.empty()) {
                return rec.allocator.allocate();
            }
            else {
                ctx::stack_context r{};
                std::swap(r, rec.contexts.back());
                rec.contexts.pop_back();
                return r;
            }

        }
        void recycle_stack(ctx::stack_context& ctx)
        {
            auto& rec = get_or_new_alloc_record(ctx.size);
            return rec.contexts.push_back(ctx);
        }
        void free_pooled_stacks(void)
        {
            for (auto& pair : fixedsize_stack_pool_) {
                auto& rec = pair.second;
                auto& allocator = rec.allocator;
                for (auto& context : rec.contexts) {
                    allocator.deallocate(context);
                }
                rec.contexts.clear();
            }
        }
        void cleanup_pool(void)
        {
            free_pooled_stacks();
            fixedsize_stack_pool_.clear();
        }
    };

    static my_fixedsize_stack_alloc_pool g_fixedsize_stack_alloc_pool{};

    void FreeStackMemory(void)
    {
        g_fixedsize_stack_alloc_pool.free_pooled_stacks();
    }
    void CleanupPool(void)
    {
        g_fixedsize_stack_alloc_pool.cleanup_pool();
    }

    struct my_fixedsize_stack
    {
        typedef ctx::stack_traits traits_type;

        my_fixedsize_stack(std::size_t size = traits_type::default_size()) BOOST_NOEXCEPT_OR_NOTHROW :
        size_(size)
        {
        }
        ctx::stack_context allocate(void)
        {
            return g_fixedsize_stack_alloc_pool.alloc_stack(size_);
        }
        void deallocate(ctx::stack_context& sctx) BOOST_NOEXCEPT_OR_NOTHROW
        {
            g_fixedsize_stack_alloc_pool.recycle_stack(sctx);
        }
    private:
        std::size_t size_;
    };
    
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
            my_fixedsize_stack salloc(BufferSize);
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