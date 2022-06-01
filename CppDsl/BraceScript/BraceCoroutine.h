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

#pragma once
#include <stddef.h>
#include <setjmp.h>

#define DEFINE_SEQUENCING(S)    \
    {                           \
        char _dummy;            \
        Brace::g_StackBottom = &_dummy; \
        S;                      \
    }

namespace Brace
{
    class Coroutine
    {
        friend void Resume(Coroutine*);
        friend void Call(Coroutine*);
        friend void Detach(void);
    public:
        bool IsTerminated(void)const;
        void Reset(void);
    protected:
        Coroutine(void);
        virtual ~Coroutine(void);
        virtual void Routine(void) = 0;
    private:
        void Enter(void);
        void StoreStack(void);
        void RestoreStack(void);
    private:
        char* m_StackBuffer, * m_Low, * m_High;
        size_t m_BufferSize;
        jmp_buf m_Environment;
        Coroutine* m_Caller, * m_Callee;
    private:
        static Coroutine* m_ToBeResumed;
    };

    extern char* g_StackBottom;
    extern void Resume(Coroutine*);
    extern void Call(Coroutine*);
    extern void Detach(void);
    extern Coroutine* CurrentCoroutine(void);
    extern Coroutine* MainCoroutine(void);
}
