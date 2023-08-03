#include "BraceCoroutine.h"
#include "boost/context/fiber.hpp"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>

namespace CoroutineWithBoostContext
{
#define Terminated(C) (!(C)->m_pData->Environment)
    
    namespace ctx = boost::context;
    using fiber = ctx::fiber;

    struct my_fixedsize_stack_alloc_pool
    {
        struct my_fixedsize_stack_alloc_record
        {
            ctx::fixedsize_stack allocator;
            std::vector<ctx::stack_context> contexts;

            my_fixedsize_stack_alloc_record(std::size_t size) :allocator(size), contexts()
            {
            }
        };

        std::unordered_map<std::size_t, my_fixedsize_stack_alloc_record> fixedsize_stack_pool_;
        std::size_t total_alloced_size_;

        my_fixedsize_stack_alloc_pool() :fixedsize_stack_pool_(), total_alloced_size_(0)
        {}

        my_fixedsize_stack_alloc_record& get_or_new_alloc_record(std::size_t size)
        {
            auto it = fixedsize_stack_pool_.find(size);
            if (it == fixedsize_stack_pool_.end()) {
                my_fixedsize_stack_alloc_record record(size);
                auto result = fixedsize_stack_pool_.insert(std::make_pair(std::move(size), std::move(record)));
                it = result.first;
                auto& rec = it->second;
                return rec;
            }
            else {
                return it->second;
            }
        }
        ctx::stack_context alloc_stack(std::size_t size)
        {
            total_alloced_size_ += size;

            auto& rec = get_or_new_alloc_record(size);
            if (rec.contexts.empty()) {
                return rec.allocator.allocate();
            }
            else {
                ctx::stack_context r{};
                std::swap(r, rec.contexts.back());
                rec.contexts.pop_back();
                return r;
            }

        }
        void recycle_stack(ctx::stack_context& ctx)
        {
            total_alloced_size_ -= ctx.size;

            auto& rec = get_or_new_alloc_record(ctx.size);
            return rec.contexts.push_back(ctx);
        }
        void free_pooled_stacks()
        {
            for (auto&& pair : fixedsize_stack_pool_) {
                auto& rec = pair.second;
                auto& allocator = rec.allocator;
                for (auto&& context : rec.contexts) {
                    allocator.deallocate(context);
                }
                rec.contexts.clear();
            }
        }
        void cleanup_pool()
        {
            free_pooled_stacks();
            fixedsize_stack_pool_.clear();
        }
        std::size_t stat_memory(std::size_t& count, std::size_t& alloced_size)
        {
            std::size_t size = 0;
            count = 0;
            alloced_size = total_alloced_size_;
            for (auto&& pair : fixedsize_stack_pool_) {
                auto& rec = pair.second;
                count += rec.contexts.size();
                for (auto&& context : rec.contexts) {
                    size += context.size;
                }
            }
            return size;
        }
    };

    thread_local static my_fixedsize_stack_alloc_pool g_fixedsize_stack_alloc_pool{};
    thread_local static std::queue<fiber> g_fiber_queue{};

    void FreeStackMemory()
    {
        g_fixedsize_stack_alloc_pool.free_pooled_stacks();
    }
    void CleanupPool()
    {
        g_fixedsize_stack_alloc_pool.cleanup_pool();
    }
    std::size_t StatMemory(std::size_t& count, std::size_t& alloced_size)
    {
        return g_fixedsize_stack_alloc_pool.stat_memory(count, alloced_size);
    }

    struct my_fixedsize_stack
    {
        using traits_type = ctx::stack_traits;

        my_fixedsize_stack(std::size_t size = traits_type::default_size()) BOOST_NOEXCEPT_OR_NOTHROW :
        size_(size)
        {
        }
        ctx::stack_context allocate()
        {
            return g_fixedsize_stack_alloc_pool.alloc_stack(size_);
        }
        void deallocate(ctx::stack_context& sctx) BOOST_NOEXCEPT_OR_NOTHROW
        {
            g_fixedsize_stack_alloc_pool.recycle_stack(sctx);
        }
    private:
        std::size_t size_;
    };
    
    static inline void Error(const char* message)
    {
        std::cerr << "Error: " << message << std::endl;
        //exit(0);
    }

    thread_local static Coroutine* g_Current = nullptr;

    struct CoroutineData final
    {
        fiber StartupFiber;
        fiber ResumeFrom;
        size_t BufferSize;
        bool Started;
        Coroutine* Current;

        CoroutineData(Coroutine* current, int bufferSize) :StartupFiber{}, ResumeFrom{}
        {
            BufferSize = bufferSize;
            Started = false;
            Current = current;
        }
        ~CoroutineData()
        {
            StartupFiber.~fiber();
            ResumeFrom.~fiber();
            Current = nullptr;
        }
        void BuildEnv()
        {
            my_fixedsize_stack salloc(BufferSize);
            ctx::stack_context sctx(salloc.allocate());
            void* sp = static_cast<char*>(sctx.sp);
            std::size_t size = sctx.size;

            StartupFiber = fiber(std::allocator_arg, ctx::preallocated(sp, size, sctx), salloc, [this](fiber&& c) { return Callcc(std::move(c)); });
        }
        fiber Callcc(fiber&& cont)
        {
            ResumeFrom = std::move(cont);
            Started = true;
            Current->Routine();
            Started = false;
            //fiber always gives control to ResumeFrom coroutine
            if (ResumeFrom) {
                return std::move(ResumeFrom);
            }
            else if (g_fiber_queue.size() > 0) {
                fiber tmp;
                std::swap(tmp, g_fiber_queue.front());
                g_fiber_queue.pop();
                return std::move(tmp);
            }
            else {
                fiber tmp{};
                return std::move(tmp);
            }
        }
    };

    class CoroutineMain : public Coroutine
    {
    public:
        CoroutineMain() :Coroutine(1024*1024)
        {
            g_Current = this;
        }
        virtual void Routine() override
        {
        }
    };

    thread_local static CoroutineMain g_Main;
    static std::string g_EmptyId;

    Coroutine::Coroutine(int stackSize) :m_StackSize(stackSize), m_pData(nullptr)
    {
        if (nullptr == m_pData) {
            m_pData = new CoroutineData(this, m_StackSize);
        }
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
        return !m_pData->Started;
    }
    void Coroutine::Reset()
    {
        if (this == g_Current) {
            Error("Attempt to reset current coroutine, you must call Reset in other coroutine or main");
            return;
        }
        m_pData->BuildEnv();
    }
    bool Coroutine::TryStart()
    {
        bool ret = false;
        if (IsTerminated()) {
            Reset();

            Coroutine* pCurrent = g_Current;
            g_Current = this;
            //fiber.resume return suspended fiber, null on exit, or itself or other suspended fiber.
            auto&& suspendedFiber = std::move(m_pData->StartupFiber).resume();
            if (suspendedFiber) {
                g_fiber_queue.push(std::move(suspendedFiber));
            }
            g_Current = pCurrent;
            ret = true;
        }
        return false;
    }

    bool TryYield()
    {
        bool ret = false;
        Coroutine* pCurrent = g_Current;
        if (pCurrent->m_pData->ResumeFrom) {
            auto&& suspendedFiber = std::move(pCurrent->m_pData->ResumeFrom).resume();
            if (suspendedFiber) {
                g_fiber_queue.push(std::move(suspendedFiber));
            }
            g_Current = pCurrent;
            ret = true;
        }
        else if (g_fiber_queue.size() > 0) {
            fiber tmp;
            std::swap(tmp, g_fiber_queue.front());
            g_fiber_queue.pop();
            auto&& suspendedFiber = std::move(tmp).resume();
            if (suspendedFiber) {
                g_fiber_queue.push(std::move(suspendedFiber));
            }
            g_Current = pCurrent;
            ret = true;
        }
        return ret;
    }
    bool TryInit()
    {
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