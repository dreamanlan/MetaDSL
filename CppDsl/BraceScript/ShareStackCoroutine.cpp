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

#include "ShareStackCoroutine.h"
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <setjmp.h>
#include <iostream>

#if defined(_WIN32)
#pragma warning(disable:4611)
#endif

 /// Maybe there are two patterns:
 /// 1、Call <-> Detach pair, coroutines can be called by Tick(non-coroutine), so coroutines are driven by main logic.
 /// 2、Resume <-> Resume tuple, switching between coroutines.

namespace CoroutineWithShareStack
{
#define MIN_STACK_SIZE 512

    static inline void Error(const char* message)
    {
        std::cerr << "Error: " << message << std::endl;
        //exit(0);
    }

    struct Task final
    {
        Coroutine* MyCoroutine;
        jmp_buf jmpb;
        int used;
        int size;
        struct Task* pred, * suc;
        struct Task* prev, * next;
    };

    struct CoroutineData final
    {
        Task* MyTask;
        int StackSize;
        int Ready, Terminated;
        Coroutine* Caller, * Callee;

        CoroutineData(int stackSize)
        {
            MyTask = nullptr;
            StackSize = stackSize;
            Ready = 1;
            Terminated = 0;
            Caller = Callee = nullptr;
        }
        ~CoroutineData()
        {
            MyTask = nullptr;
            StackSize = 0;
            Ready = 0;
            Terminated = 1;
            Caller = Callee = nullptr;
        }
    };

    class CoroutineMain : public Coroutine
    {
    public:
        CoroutineMain() :Coroutine(0)
        {
        }
        virtual void Routine() override
        {
        }
    };

    static Task s_main_task; // the main task
    static jmp_buf s_tmp_jmpb; // temporary jump buffer
    static CoroutineMain s_Main;
    static Coroutine* s_pCurrent = nullptr;

    void Coroutine::InitSequencing(int main_StackSize)
    {
        Task tmp{};
        tmp.size = INT_MAX;
        s_Main.m_pData->StackSize = main_StackSize;
        tmp.next = 0;
        s_Main.m_pData->MyTask = &tmp;
        s_main_task.pred = s_main_task.suc = &s_main_task;
        tmp.MyCoroutine = s_pCurrent = &s_Main;
        if (!setjmp(tmp.jmpb))
            s_Main.Eat();
        tmp.pred = s_main_task.pred;
        tmp.suc = s_main_task.suc;
        s_main_task = tmp;
        s_main_task.next->prev = &s_main_task;
        s_Main.m_pData->MyTask = &s_main_task;
        s_main_task.used = 1;
        s_Main.m_pData->Ready = 0;
    }

    Coroutine::Coroutine(int stackSize)
    {
        m_pData = new CoroutineData(stackSize);
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
        return m_pData->Terminated != 0;
    }
    void Coroutine::Reset()
    {
        if (this == s_pCurrent) {
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

        m_pData->MyTask = nullptr;
        m_pData->Ready = 1;
        m_pData->Terminated = 0;
    }
    void Coroutine::Call()
    {
        if (IsTerminated())
            Reset();
        CoroutineWithShareStack::Call(this);
    }
    void Coroutine::Resume()
    {
        if (IsTerminated())
            Reset();
        CoroutineWithShareStack::Resume(this);
    }
    inline void Coroutine::Enter()
    {
        if (nullptr == s_pCurrent) {
            Error("InitSequencing has not been called");
            return;
        }
        if (m_pData->Ready) { // find free block
            for (m_pData->MyTask = s_main_task.suc;
                m_pData->MyTask != &s_main_task;
                m_pData->MyTask = m_pData->MyTask->suc)
                if (m_pData->MyTask->size >= m_pData->StackSize + MIN_STACK_SIZE)
                    break;
            if (m_pData->MyTask == &s_main_task)
                Error("No more space available\n");
            m_pData->MyTask->MyCoroutine = this;
            if (!setjmp(s_tmp_jmpb))
                longjmp(m_pData->MyTask->jmpb, 1);
            m_pData->Ready = 0;
        }
        if (!setjmp(s_pCurrent->m_pData->MyTask->jmpb)) { // activate control block
            s_pCurrent = this;
            longjmp(m_pData->MyTask->jmpb, 1);
        }
    }
    inline void Coroutine::Eat()
    {
        static int d;
        static Task* p;
        Task t{};
        // eat stack
        if ((d = labs(static_cast<long>((char*)&t - (char*)m_pData->MyTask))) < m_pData->StackSize)
            Eat();
        t.size = m_pData->MyTask->size - d; //set size
        m_pData->MyTask->size = d;
        t.used = 0;
        t.suc = s_main_task.suc;
        t.pred = &s_main_task;
        t.suc->pred = s_main_task.suc = &t;
        if (m_pData->MyTask->next != &t) {
            t.next = m_pData->MyTask->next; // set link pointers
            m_pData->MyTask->next = &t;
            t.prev = m_pData->MyTask;
            if (t.next)
                t.next->prev = &t;
        }
        if (!setjmp(t.jmpb)) // wait
            longjmp(m_pData->MyTask->jmpb, 1);

        for (;;) {
            // test size
            if (m_pData->StackSize + MIN_STACK_SIZE < t.size &&
                !setjmp(t.jmpb))
                t.MyCoroutine->Eat(); // split block
            t.used = 1; // mark as used
            t.pred->suc = t.suc;
            t.suc->pred = t.pred;
            if (!setjmp(t.jmpb)) // wait
                longjmp(s_tmp_jmpb, 1);
            t.MyCoroutine->Routine(); // execute Routine
            t.MyCoroutine->m_pData->Terminated = 1;
            t.used = 0; // mark as free
            p = t.next;
            if (p && !p->used) { // merge with following block
                t.size += p->size;
                t.next = p->next;
                if (t.next)
                    t.next->prev = &t;
                p->pred->suc = p->suc;
                p->suc->pred = p->pred;
            }
            p = t.prev;
            if (!p->used) { // merge with preceding block
                p->size += t.size;
                p->next = t.next;
                if (t.next)
                    t.next->prev = p;
            }
            else {
                t.suc = s_main_task.suc;
                t.pred = &s_main_task;
                t.suc->pred = s_main_task.suc = &t;
            }
            if (!setjmp(t.jmpb)) { // save state
                Detach();
            }
        }
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
        if (next->IsTerminated()) {
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
        if (next->IsTerminated()) {
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
    bool TryInit(int main_StackSize)
    {
        if (s_Main.m_pData->StackSize == 0) {
            s_Main.InitSequencing(main_StackSize);
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
