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

#define DEFAULT_STACK_SIZE 10000

namespace CoroutineWithShareStack
{
    struct CoroutineData;
    class Coroutine
    {
        friend void Resume(Coroutine*);
        friend void Call(Coroutine*);
        friend void Detach(void);
        friend bool TryInit(int main_StackSize);
        friend void TryRelease(void);
    public:
        bool IsTerminated(void)const;
        void Reset(void);
        void Call(void);
        void Resume(void);
    protected:
        Coroutine(int stackSize = DEFAULT_STACK_SIZE);
        virtual ~Coroutine(void);
        virtual void Routine(void) = 0;
    private:
        void Enter(void);
        void Eat(void);
        void Release(void);
    protected:
        CoroutineData* m_pData;
    private:
        static void InitSequencing(int main_StackSize);
    };

    extern void Resume(Coroutine*);
    extern void Call(Coroutine*);
    extern void Detach(void);
    extern bool TryInit(int main_StackSize);
    extern void TryRelease(void);
    extern Coroutine* CurrentCoroutine(void);
    extern Coroutine* MainCoroutine(void);
}
