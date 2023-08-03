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

namespace CoroutineWithLongJmp
{
    struct CoroutineData;
    class Coroutine
    {
        friend void Resume(Coroutine*);
        friend void Call(Coroutine*);
        friend void Detach();
        friend bool TryInit();
        friend void TryRelease();
    public:
        bool IsTerminated()const;
        void Reset();
        void Call();
        void Resume();
    protected:
        Coroutine(int bufferSize);
        virtual ~Coroutine();
        virtual void Routine() = 0;
    private:
        void Enter();
        void StoreStack();
        void RestoreStack();
        void Release();
    private:
        CoroutineData* m_pData;
    };

    extern void Resume(Coroutine*);
    extern void Call(Coroutine*);
    extern void Detach();
    extern bool TryInit();
    extern void TryRelease();
    extern Coroutine* CurrentCoroutine();
    extern Coroutine* MainCoroutine();
}
