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

    static Task main_task; // the main task
    static jmp_buf tmp_jmpb; // temporary jump buffer
    static CoroutineMain g_Main;
    static Coroutine* g_Current = nullptr;

    void Coroutine::InitSequencing(int main_StackSize)
    {
        Task tmp{};
        tmp.size = INT_MAX;
        g_Main.m_pData->StackSize = main_StackSize;
        tmp.next = 0;
        g_Main.m_pData->MyTask = &tmp;
        main_task.pred = main_task.suc = &main_task;
        tmp.MyCoroutine = g_Current = &g_Main;
        if (!setjmp(tmp.jmpb))
            g_Main.Eat();
        tmp.pred = main_task.pred;
        tmp.suc = main_task.suc;
        main_task = tmp;
        main_task.next->prev = &main_task;
        g_Main.m_pData->MyTask = &main_task;
        main_task.used = 1;
        g_Main.m_pData->Ready = 0;
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
        if (nullptr == g_Current) {
            Error("InitSequencing has not been called");
            return;
        }
        if (m_pData->Ready) { // find free block
            for (m_pData->MyTask = main_task.suc;
                m_pData->MyTask != &main_task;
                m_pData->MyTask = m_pData->MyTask->suc)
                if (m_pData->MyTask->size >= m_pData->StackSize + MIN_STACK_SIZE)
                    break;
            if (m_pData->MyTask == &main_task)
                Error("No more space available\n");
            m_pData->MyTask->MyCoroutine = this;
            if (!setjmp(tmp_jmpb))
                longjmp(m_pData->MyTask->jmpb, 1);
            m_pData->Ready = 0;
        }
        if (!setjmp(g_Current->m_pData->MyTask->jmpb)) { // activate control block
            g_Current = this;
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
        t.suc = main_task.suc;
        t.pred = &main_task;
        t.suc->pred = main_task.suc = &t;
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
                longjmp(tmp_jmpb, 1);
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
                t.suc = main_task.suc;
                t.pred = &main_task;
                t.suc->pred = main_task.suc = &t;
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
        if (next == g_Current) {
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
    void Detach()
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
    bool TryInit(int main_StackSize)
    {
        if (g_Main.m_pData->StackSize == 0) {
            g_Main.InitSequencing(main_StackSize);
        }
        return !g_Main.IsTerminated();
    }
    void TryRelease()
    {
        g_Main.Release();
    }
    Coroutine* CurrentCoroutine()
    {
        return g_Current;
    }
    Coroutine* MainCoroutine()
    {
        return &g_Main;
    }
}
