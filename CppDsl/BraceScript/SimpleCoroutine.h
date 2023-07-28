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
        friend void Detach(void);
        friend bool TryInit(void);
        friend void TryRelease(void);
    public:
        bool IsTerminated(void)const;
        void Reset(void);
        void Call(void);
        void Resume(void);
    protected:
        Coroutine(int bufferSize);
        virtual ~Coroutine(void);
        virtual void Routine(void) = 0;
    private:
        void Enter(void);
        void StoreStack(void);
        void RestoreStack(void);
        void Release(void);
    private:
        CoroutineData* m_pData;
    };

    extern void Resume(Coroutine*);
    extern void Call(Coroutine*);
    extern void Detach(void);
    extern bool TryInit(void);
    extern void TryRelease(void);
    extern Coroutine* CurrentCoroutine(void);
    extern Coroutine* MainCoroutine(void);
}
