/**
 * This code modified from <<A Portable C++ Library for Coroutine Sequencing>>
 * 
 * Keld Helsgaun
 * E-mail: keld@ruc.dk
 * 
 * Department of Computer Science
 * Roskilde University
 * DK-4000 Roskilde, Denmark
 * 
 */

#define Synchronize //{jmp_buf E; if (!setjmp(E)) longjmp(E, 1);}

#include "SimpleCoroutine.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <setjmp.h>
#include <iostream>

#if defined(_WIN32)
#pragma warning(disable:4611)
#endif

/// Maybe there are two patterns:
/// 1、Call <-> Detach pair, coroutines can be called by Tick(non-coroutine), so coroutines are driven by main logic.
/// 2、Resume <-> Resume tuple, switching between coroutines.

namespace CoroutineWithLongJmp
{
#define Terminated(C) ((C)->m_pData->IsTerminated)

    static inline void Error(const char* message)
    {
        std::cerr << "Error: " << message << std::endl;
        //exit(0);
    }

    static char* g_StackBottom = nullptr;
    static Coroutine* g_Current = nullptr;

    struct CoroutineData final
    {
        char* StackBuffer, * Low, * High;
        size_t BufferSize;
        jmp_buf Environment;
        Coroutine* Caller, * Callee;
        bool IsTerminated;

        CoroutineData(int bufferSize) :Environment{}
        {
            StackBuffer = nullptr;
            Low = High = nullptr;
            BufferSize = bufferSize;
            Callee = Caller = nullptr;
            IsTerminated = false;
        }
        ~CoroutineData(void)
        {
            delete StackBuffer;
            StackBuffer = nullptr;
        }
    };

    class CoroutineMain : public Coroutine
    {
    public:
        CoroutineMain(void) :Coroutine(0)
        {
            g_Current = this;
        }
        virtual void Routine(void) override
        {
        }
    };

    static CoroutineMain g_Main;

    Coroutine::Coroutine(int bufferSize)
    {
        char x{};
        if (g_StackBottom)
            if (&x < g_StackBottom ? &x <= (char*)this && (char*)this <= g_StackBottom : &x >= (char*)this && (char*)this >= g_StackBottom)
                Error("Attempt to allocate a Coroutine on the stack");
        m_pData = new CoroutineData(bufferSize);
    }
    Coroutine::~Coroutine(void)
    {
        Release();
    }
    void Coroutine::Release(void)
    {
        if (nullptr == m_pData)
            return;
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
        delete m_pData->StackBuffer;
        m_pData->StackBuffer = nullptr;
        m_pData->Low = m_pData->High = nullptr;
        if (nullptr != m_pData->Callee) {
            m_pData->Callee->m_pData->Caller = m_pData->Caller;
        }
        if (nullptr != m_pData->Caller) {
            m_pData->Caller->m_pData->Callee = m_pData->Callee;
        }
        m_pData->Callee = m_pData->Caller = nullptr;
        m_pData->IsTerminated = false;
    }
    void Coroutine::Call(void)
    {
        if (IsTerminated())
            Reset();
        CoroutineWithLongJmp::Call(this);
    }
    void Coroutine::Resume(void)
    {
        if (IsTerminated())
            Reset();
        CoroutineWithLongJmp::Resume(this);
    }
    inline void Coroutine::RestoreStack(void)
    {
        Synchronize;
        char x{};
        if (&x >= m_pData->Low && &x <= m_pData->High)
            RestoreStack();
        g_Current = this;
        memcpy(m_pData->Low, m_pData->StackBuffer, m_pData->High - m_pData->Low);
        longjmp(g_Current->m_pData->Environment, 1);
    }
    inline void Coroutine::StoreStack(void)
    {
        if (nullptr == m_pData->Low) {
            if (nullptr == g_StackBottom) {
                Error("StackBottom is not initialized");
                return;
            }
            m_pData->Low = m_pData->High = g_StackBottom;
        }
        char x{};
        if (&x > g_StackBottom)
            m_pData->High = &x;
        else
            m_pData->Low = &x;
        if (m_pData->High - m_pData->Low > static_cast<int>(m_pData->BufferSize)) {
            delete m_pData->StackBuffer;
            m_pData->BufferSize = m_pData->High - m_pData->Low;
            m_pData->StackBuffer = new char[m_pData->BufferSize];
            if (nullptr == m_pData->StackBuffer) {
                Error("No more space available");
                return;
            }
        }
        else if (nullptr == m_pData->StackBuffer) {
            m_pData->StackBuffer = new char[m_pData->BufferSize];
            if (nullptr == m_pData->StackBuffer) {
                Error("No more space available");
                return;
            }
        }
        Synchronize;
        memcpy(m_pData->StackBuffer, m_pData->Low, m_pData->High - m_pData->Low);
    }
    inline void Coroutine::Enter(void)
    {
        if (!Terminated(g_Current)) {
            g_Current->StoreStack();
            if (setjmp(g_Current->m_pData->Environment))
                return;
        }
        g_Current = this;
        if (!m_pData->StackBuffer) {
            Routine();
            delete g_Current->m_pData->StackBuffer;
            g_Current->m_pData->StackBuffer = nullptr;
            g_Current->m_pData->IsTerminated = true;
            Detach();
        }
        RestoreStack();
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
    bool TryInit(void)
    {
        if (nullptr == g_StackBottom) {
            char _dummy{};
            g_StackBottom = &_dummy;
        }
        return !g_Main.IsTerminated();
    }
    void TryRelease(void)
    {
        g_Main.Release();
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
