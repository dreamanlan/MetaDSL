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

#include "BraceCoroutine.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>

#if defined(_WIN32)
#pragma warning(disable:4611)
#endif

/// Maybe there are two patterns:
/// 1、Call <-> Detach pair, coroutines can be called by Tick(non-coroutine), so coroutines are driven by main logic.
/// 2、Resume <-> Resume tuple, switching between coroutines.

namespace Brace
{
    char* g_StackBottom;

#define Terminated(C) (!(C)->m_StackBuffer && (C)->m_BufferSize)

    static inline void Error(const char* message)
    {
        std::cerr << "Error: " << message << std::endl;
        //exit(0);
    }

    Coroutine* Coroutine::m_ToBeResumed = nullptr;
    static Coroutine* g_Current = nullptr, * g_Next = nullptr;

    class CoroutineMain : public Coroutine
    {
    public:
        CoroutineMain(void) :Coroutine()
        {
            g_Current = this;
        }
        virtual void Routine(void) override
        {
        }
    };

    static CoroutineMain g_Main;

    Coroutine::Coroutine(void) : m_Environment{}
    {
        char x{};
        if (g_StackBottom)
            if (&x < g_StackBottom ? &x <= (char*)this && (char*)this <= g_StackBottom : &x >= (char*)this && (char*)this >= g_StackBottom)
                Error("Attempt to allocate a Coroutine on the stack");
        m_StackBuffer = nullptr;
        m_Low = m_High = nullptr;
        m_BufferSize = 0;
        m_Callee = m_Caller = nullptr;
    }
    Coroutine::~Coroutine(void)
    {
        delete m_StackBuffer;
        m_StackBuffer = nullptr;
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
        delete m_StackBuffer;
        m_StackBuffer = nullptr;
        m_Low = m_High = nullptr;
        m_BufferSize = 0;
        if (nullptr != m_Callee) {
            m_Callee->m_Caller = m_Caller;
        }
        if (nullptr != m_Caller) {
            m_Caller->m_Callee = m_Callee;
        }
        m_Callee = m_Caller = nullptr;
    }
    inline void Coroutine::RestoreStack(void)
    {
        Synchronize;
        char x{};
        if (&x >= m_Low && &x <= m_High)
            RestoreStack();
        g_Current = this;
        memcpy(m_Low, m_StackBuffer, m_High - m_Low);
        longjmp(g_Current->m_Environment, 1);
    }
    inline void Coroutine::StoreStack(void)
    {
        if (nullptr == m_Low) {
            if (nullptr == g_StackBottom) {
                Error("StackBottom is not initialized");
                return;
            }
            m_Low = m_High = g_StackBottom;
        }
        char x{};
        if (&x > g_StackBottom)
            m_High = &x;
        else
            m_Low = &x;
        if (m_High - m_Low > static_cast<int>(m_BufferSize)) {
            delete m_StackBuffer;
            m_BufferSize = m_High - m_Low;
            m_StackBuffer = new char[m_BufferSize];
            if (nullptr == m_StackBuffer) {
                Error("No more space available");
                return;
            }
        }
        Synchronize;
        memcpy(m_StackBuffer, m_Low, m_High - m_Low);
    }
    inline void Coroutine::Enter()
    {
        if (!Terminated(g_Current)) {
            g_Current->StoreStack();
            if (setjmp(g_Current->m_Environment))
                return;
        }
        g_Current = this;
        if (!m_StackBuffer) {
            Routine();
            delete g_Current->m_StackBuffer;
            g_Current->m_StackBuffer = nullptr;
            if (m_ToBeResumed) {
                g_Next = m_ToBeResumed;
                m_ToBeResumed = nullptr;
                Resume(g_Next);
            }
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
        if (next->m_Caller) {
            Error("Attempt to Resume an attached Coroutine");
            return;
        }
        while (next->m_Callee) {
            next = next->m_Callee;
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
        if (next->m_Caller) {
            Error("Attempt to Call an attached Coroutine");
            return;
        }
        g_Current->m_Callee = next;
        next->m_Caller = g_Current;
        while (next->m_Callee) {
            next = next->m_Callee;
        }
        if (next == g_Current) {
            Error("Attempt to Call an operating Coroutine");
            return;
        }
        next->Enter();
    }
    void Detach(void)
    {
        g_Next = g_Current->m_Caller;
        if (g_Next) {
            g_Current->m_Caller = g_Next->m_Callee = nullptr;
        }
        else {
            g_Next = &g_Main;
            while (g_Next->m_Callee) {
                g_Next = g_Next->m_Callee;
            }
        }
        g_Next->Enter();
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
