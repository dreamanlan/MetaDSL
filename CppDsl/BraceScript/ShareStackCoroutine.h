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
        friend void Detach();
        friend bool TryInit(int main_StackSize);
        friend void TryRelease();
    public:
        bool IsTerminated()const;
        void Reset();
        void Call();
        void Resume();
    protected:
        Coroutine(int stackSize = DEFAULT_STACK_SIZE);
        virtual ~Coroutine();
        virtual void Routine() = 0;
    private:
        void Enter();
        void Eat();
        void Release();
    protected:
        CoroutineData* m_pData;
    private:
        static void InitSequencing(int main_StackSize);
    };

    extern void Resume(Coroutine*);
    extern void Call(Coroutine*);
    extern void Detach();
    extern bool TryInit(int main_StackSize);
    extern void TryRelease();
    extern Coroutine* CurrentCoroutine();
    extern Coroutine* MainCoroutine();
}
