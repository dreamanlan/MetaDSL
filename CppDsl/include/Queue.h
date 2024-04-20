#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <memory.h>
#include "BaseType.h"

namespace CollectionMemory
{
    template<typename T, int MaxSizeV>
    class StaticT
    {
    public:
        inline T* Create(int& size)
        {
            if (size > MaxSizeV) {
                size = 1;
                return nullptr;
            }
            return m_Data;
        }
        inline void Clear()
        {
            memset(m_Data, 0, sizeof(m_Data));
        }
        size_t GetMemoryInUsed() const
        {
            return sizeof(T) * MaxSizeV;
        }
    private:
        T	m_Data[MaxSizeV];
    };

    template<typename T>
    class DynamicT
    {
    public:
        inline T* Create(int& size)
        {
            Cleanup();
            m_Data = new T[size];
            if (nullptr == m_Data) {
                size = 1;
                return nullptr;
            }
            m_MaxSize = size;
            return m_Data;
        }
        inline void Clear()
        {
            if (m_MaxSize > 0 && nullptr != m_Data) {
                memset(m_Data, 0, sizeof(T) * m_MaxSize);
            }
        }
        size_t GetMemoryInUsed() const
        {
            return (m_Data == nullptr ? 0 : (sizeof(T) * m_MaxSize));
        }
    public:
        DynamicT() :m_Data(nullptr), m_MaxSize(0)
        {}
        virtual ~DynamicT()
        {
            Cleanup();
        }
    private:
        inline void Cleanup()
        {
            if (nullptr != m_Data) {
                delete[] m_Data;
                m_Data = nullptr;
            }
            m_MaxSize = 0;
        }
    private:
        T* m_Data;
        int	m_MaxSize;
    };
    template<typename T, int MaxSizeV>
    class SelectorT
    {
    public:
        using Type = StaticT<T, MaxSizeV>;
    };
    template<typename T>
    class SelectorT<T, 0>
    {
    public:
        using Type = DynamicT<T>;
    };
}

//
//T is the queue element type, and SizeV is the maximum number of elements
//expected in the queue (0 using dynamic memory allocation scheme).
template<typename T, int SizeV = 0>
class DequeT
{
    using MemoryType = typename CollectionMemory::SelectorT<T, (SizeV == 0 ? 0 : SizeV + 1)>::Type;
public://Standard bidirectional queue access method
    //queue is empty?
    inline int Empty() const
    {
        return m_Head == m_Tail;
    }
    //queue is full?
    inline int Full() const
    {
        return m_Head == (m_Tail + 1) % m_MaxSize;
    }
    //clear queue
    inline void Clear()
    {
        m_Size = 0;
        m_Head = m_Tail = 0;
        m_Memory.Clear();
    }
    //The number of elements in the current queue
    inline int Size() const
    {
        return m_Size;
    }
    //Add an element to the tail of the queue
    inline int PushBack(const T& t)
    {
        MyAssert(m_Data);
        MyAssert(!Full());

        int id = m_Tail;
        m_Data[id] = t;
        m_Tail = (m_Tail + 1) % m_MaxSize;

        UpdateSize();
        return id;
    }
    //Add an element to the head of the queue
    inline int PushFront(const T& t)
    {
        MyAssert(m_Data);
        MyAssert(!Full());

        m_Head = (m_MaxSize + m_Head - 1) % m_MaxSize;
        m_Data[m_Head] = t;

        UpdateSize();
        return m_Head;
    }
    //Delete an element at the tail of the queue
    inline T PopBack()
    {
        MyAssert(m_Data);
        MyAssert(!Empty());

        int id = BackID();
        m_Tail = id;

        UpdateSize();
        return m_Data[id];
    }
    //Delete an element at the head of the queue
    inline T PopFront()
    {
        MyAssert(m_Data);
        MyAssert(!Empty());

        int id = m_Head;
        m_Head = (m_Head + 1) % m_MaxSize;

        UpdateSize();
        return m_Data[id];
    }
    //read the element at the tail of the queue
    inline const T& Back() const
    {
        return m_Data[BackID()];
    }
    //read the element reference at the tail of the queue
    inline T& Back()
    {
        return m_Data[BackID()];
    }
    //read the element at the head of the queue
    inline const T& Front() const
    {
        return m_Data[FrontID()];
    }
    //read the element reference at the head of the queue
    inline T& Front()
    {
        return m_Data[FrontID()];
    }
public://Extended bidirectional queue access methods (traversal and read-write methods)
    //FrontID is the id of the head element
    inline int FrontID() const
    {
        return m_Head;
    }
    //BackID is the id of the tail element
    inline int BackID() const
    {
        if (Empty()) {
            return m_Head;
        }
        int newId = (m_MaxSize + m_Tail - 1) % m_MaxSize;
        return newId;
    }
    //Takes the previous ID of the current ID, and returns INVALID_ID
    //if it is already a header element ID
    inline int PrevID(int id) const
    {
        if (id == m_Head)
            return INVALID_ID;
        int newId = (m_MaxSize + id - 1) % m_MaxSize;
        return newId;
    }
    //Takes the next ID of the current ID, and returns INVALID_ID
    //if it is already a tail element ID
    inline int NextID(int id) const
    {
        if (id == BackID())
            return INVALID_ID;
        int newId = (id + 1) % m_MaxSize;
        return newId;
    }
    //Check whether the ID is valid. For an empty queue,
    //the header ID and tail ID are invalid ids
    inline int IsValidID(int id) const
    {
        if (Empty()) {
            return FALSE;
        }
        if (id < 0 || id >= m_MaxSize) {
            return FALSE;
        }
        int idVal = CalcIndex(id);
        int tailVal = CalcIndex(m_Tail);
        if (idVal >= tailVal)
            return FALSE;
        return TRUE;
    }
    //Gets the element with the specified ID
    inline const T& operator [] (int id) const
    {
        if (id < 0 || id >= m_MaxSize) {
            return GetInvalidValueRef();
        }
        else {
            return m_Data[id];
        }
    }
    //Takes a writable reference to an element with a specified ID
    //(used to modify the element)
    inline T& operator [] (int id)
    {
        if (id < 0 || id >= m_MaxSize) {
            return GetInvalidValueRef();
        }
        else {
            return m_Data[id];
        }
    }
    //Find the distance between 2 ids (number of separated elements +1)
    inline int Distance(int id1, int id2) const
    {
        int val = Difference(id1, id2);
        if (val < 0)
            return -val;
        else
            return val;
    }
    //Find the difference between 2 ids (number the elements from beginning
    //to end, the difference in numbers)
    inline int Difference(int id1, int id2) const
    {
        int id1Val = CalcIndex(id1);
        int id2Val = CalcIndex(id2);
        MyAssert(id1Val >= 0 && id2Val >= 0);
        return id2Val - id1Val;
    }
public:
    DequeT() :m_Size(0), m_MaxSize(1), m_Head(0), m_Tail(0), m_Data(nullptr)
    {
        if constexpr (SizeV > 0) {
            Init(SizeV);
        }
    }
    DequeT(int size) :m_Size(0), m_MaxSize(1), m_Head(0), m_Tail(0), m_Data(nullptr)
    {
        Init(size);
    }
    virtual ~DequeT()
    {
        m_Size = 0;
        m_MaxSize = 1;
        m_Head = 0;
        m_Tail = 0;
        m_Data = nullptr;
    }
public:
    DequeT(const DequeT& other)
    {
        Init(other.m_MaxSize - 1);
        CopyFrom(other);
    }
    DequeT& operator=(const DequeT& other)
    {
        if (this == &other)
            return *this;
        Clear();
        Init(other.m_MaxSize - 1);
        CopyFrom(other);
        return *this;
    }
public:
    inline void	Init(int size)
    {
        Create(size + 1);
    }
protected:
    inline void Create(int size)
    {
        m_MaxSize = size;
        m_Data = m_Memory.Create(m_MaxSize);
        MyAssert(m_Data);
        Clear();
    }
private:
    //calc the index of the element (head element's index is 0)
    inline int CalcIndex(int id) const
    {
        if (id < m_Head)
            return id + m_MaxSize - m_Head;
        else
            return id - m_Head;
    }
    //update the size of the queue
    inline void UpdateSize()
    {
        m_Size = (m_MaxSize + m_Tail - m_Head) % m_MaxSize;
    }
private:
    void CopyFrom(const DequeT& other)
    {
        Clear();
        for (int id = other.FrontID(); TRUE == other.IsValidID(id); id = other.NextID(id)) {
            PushBack(other[id]);
        }
    }
private:
    MemoryType m_Memory;
    T* m_Data;
    int m_Size;
    int m_MaxSize;
    //the ID of the head element
    int m_Head;
    //The ID of a position after the tail element, which indicates
    //the position of the queue tail, and its value is always an invalid ID
    int m_Tail;
public:
    static T& GetInvalidValueRef()
    {
        static T s_Temp;
        return s_Temp;
    }
};

#endif //__QUEUE_H__