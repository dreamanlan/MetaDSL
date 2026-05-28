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

    static char* s_pStackBottom = nullptr;
    static Coroutine* s_pCurrent = nullptr;

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
        ~CoroutineData()
        {
            delete StackBuffer;
            StackBuffer = nullptr;
        }
    };

    class CoroutineMain : public Coroutine
    {
    public:
        CoroutineMain() :Coroutine(0)
        {
            s_pCurrent = this;
        }
        virtual void Routine() override
        {
        }
    };

    static CoroutineMain s_Main;

    Coroutine::Coroutine(int bufferSize)
    {
        char x{};
        if (s_pStackBottom)
            if (&x < s_pStackBottom ? &x <= (char*)this && (char*)this <= s_pStackBottom : &x >= (char*)this && (char*)this >= s_pStackBottom)
                Error("Attempt to allocate a Coroutine on the stack");
        m_pData = new CoroutineData(bufferSize);
    }
    Coroutine::~Coroutine()
    {
        Release();
    }
    void Coroutine::Release()
    {
        if (nullptr == m_pData)
            return;
        delete m_pData;
        m_pData = nullptr;
    }
    bool Coroutine::IsTerminated()const
    {
        return Terminated(this);
    }
    void Coroutine::Reset()
    {
        if (this == s_pCurrent) {
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
    void Coroutine::Call()
    {
        if (IsTerminated())
            Reset();
        CoroutineWithLongJmp::Call(this);
    }
    void Coroutine::Resume()
    {
        if (IsTerminated())
            Reset();
        CoroutineWithLongJmp::Resume(this);
    }
    inline void Coroutine::RestoreStack()
    {
        Synchronize;
        char x{};
        if (&x >= m_pData->Low && &x <= m_pData->High)
            RestoreStack();
        s_pCurrent = this;
        memcpy(m_pData->Low, m_pData->StackBuffer, m_pData->High - m_pData->Low);
        longjmp(s_pCurrent->m_pData->Environment, 1);
    }
    inline void Coroutine::StoreStack()
    {
        if (nullptr == m_pData->Low) {
            if (nullptr == s_pStackBottom) {
                Error("StackBottom is not initialized");
                return;
            }
            m_pData->Low = m_pData->High = s_pStackBottom;
        }
        char x{};
        if (&x > s_pStackBottom)
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
    inline void Coroutine::Enter()
    {
        if (!Terminated(s_pCurrent)) {
            s_pCurrent->StoreStack();
            if (setjmp(s_pCurrent->m_pData->Environment))
                return;
        }
        s_pCurrent = this;
        if (!m_pData->StackBuffer) {
            Routine();
            delete s_pCurrent->m_pData->StackBuffer;
            s_pCurrent->m_pData->StackBuffer = nullptr;
            s_pCurrent->m_pData->IsTerminated = true;
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
        if (next == s_pCurrent) {
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
        s_pCurrent->m_pData->Callee = next;
        next->m_pData->Caller = s_pCurrent;
        while (next->m_pData->Callee) {
            next = next->m_pData->Callee;
        }
        if (next == s_pCurrent) {
            Error("Attempt to Call an operating Coroutine");
            return;
        }
        next->Enter();
    }
    void Detach()
    {
        Coroutine* next = s_pCurrent->m_pData->Caller;
        if (next) {
            s_pCurrent->m_pData->Caller = next->m_pData->Callee = nullptr;
        }
        else {
            next = &s_Main;
            while (next->m_pData->Callee) {
                next = next->m_pData->Callee;
            }
        }
        next->Enter();
    }
    bool TryInit()
    {
        if (nullptr == s_pStackBottom) {
            char _dummy{};
            s_pStackBottom = &_dummy;
        }
        return !s_Main.IsTerminated();
    }
    void TryRelease()
    {
        s_Main.Release();
    }
    Coroutine* CurrentCoroutine()
    { 
        return s_pCurrent; 
    }
    Coroutine* MainCoroutine() 
    { 
        return &s_Main; 
    }
}
