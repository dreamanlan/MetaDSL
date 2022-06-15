
#pragma once
#include <cstddef>

namespace CoroutineWithBoostContext
{
    struct CoroutineData;
    class Coroutine
    {
        friend struct CoroutineData;
        friend void Resume(Coroutine*);
        friend void Call(Coroutine*);
        friend void Detach(void);
        friend void Release(void);
    public:
        bool IsTerminated(void)const;
        void Reset(void);
        void CallFromMain(void);
    protected:
        Coroutine(int stackSize);
        virtual ~Coroutine(void);
        virtual void Routine(void) = 0;
    private:
        void Enter(void);
        void Exit(void);
        void Release(void);
    private:
        int m_StackSize;
        CoroutineData* m_pData;
    };

    extern void Resume(Coroutine*);
    extern void Call(Coroutine*);
    extern void Detach(void);
    extern void Release(void);
    extern Coroutine* CurrentCoroutine(void);
    extern Coroutine* MainCoroutine(void);

    extern void FreeStackMemory(void);
    extern void CleanupPool(void);
    extern std::size_t StateMemory(std::size_t& count);
}
