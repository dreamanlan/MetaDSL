
#pragma once
#include <cstddef>

namespace CoroutineWithBoostContext
{
    struct CoroutineData;
    class Coroutine
    {
        friend struct CoroutineData;
        friend bool TryYield();
        friend bool TryInit();
        friend void TryRelease();
    public:
        bool IsTerminated()const;
        void Reset();
        bool TryStart();
    protected:
        Coroutine(int stackSize);
        virtual ~Coroutine();
        virtual void Routine() = 0;
    private:
        void Release();
    private:
        int m_StackSize;
        CoroutineData* m_pData;
    };

    extern bool TryYield();
    extern bool TryInit();
    extern void TryRelease();
    extern Coroutine* CurrentCoroutine();
    extern Coroutine* MainCoroutine();

    extern void FreeStackMemory();
    extern void CleanupPool();
    extern std::size_t StatMemory(std::size_t& count, std::size_t& alloced_size);
}
