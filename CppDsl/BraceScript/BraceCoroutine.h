
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
        friend bool TryInit(void);
        friend void TryRelease(void);
    public:
        bool IsTerminated(void)const;
        void Reset(void);
        void Call(void);
        void Resume(void);
    protected:
        Coroutine(int stackSize);
        virtual ~Coroutine(void);
        virtual void Routine(void) = 0;
    private:
        void Enter(void);
        void Release(void);
    private:
        int m_StackSize;
        CoroutineData* m_pData;
    };

    extern void Resume(Coroutine*);
    extern void Call(Coroutine*);
    extern void Detach(void);
    extern bool TryInit(void);
    extern void TryRelease(void);
    extern Coroutine* CurrentCoroutine(void);
    extern Coroutine* MainCoroutine(void);

    extern void FreeStackMemory(void);
    extern void CleanupPool(void);
    extern std::size_t StatMemory(std::size_t& count, std::size_t& alloced_size);
}
