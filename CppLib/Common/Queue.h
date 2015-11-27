#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <memory.h>
#include "BaseType.h"

namespace CollectionMemory
{
	template<typename T,INT MaxSizeV>
	class StaticT
	{
	public:
		inline T* Create(INT& size)
		{
			if(size>MaxSizeV)
			{
				size = 1;
				return NULL;
			}
			return m_Data;
		}
		inline VOID Clear(VOID)
		{
			memset(m_Data,0,sizeof(m_Data));
		}
		size_t GetMemoryInUsed(VOID) const
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
		inline T* Create(INT& size)
		{
			Cleanup();
			m_Data = new T[size];
			if(NULL == m_Data)
			{
				size = 1;
				return NULL;
			}
			m_MaxSize = size;
			return m_Data;
		}
		inline VOID Clear(VOID)
		{
			if(m_MaxSize>0 && NULL!=m_Data)
			{
				memset(m_Data,0,sizeof(T)*m_MaxSize);
			}
		}
		size_t GetMemoryInUsed(VOID) const
		{
			return (m_Data == NULL ? 0 : (sizeof(T) * m_MaxSize));	
		}
	public:
		DynamicT(VOID):m_Data(NULL),m_MaxSize(0)
		{}
		virtual ~DynamicT(VOID)
		{
			Cleanup();
		}
	private:
		inline VOID Cleanup(VOID)
		{
			if(NULL!=m_Data)
			{
				delete[] m_Data;
				m_Data=NULL;
			}
			m_MaxSize = 0;
		}
	private:
		T*	m_Data;
		INT	m_MaxSize;
	};
	template<typename T,INT MaxSizeV>
	class SelectorT
	{
	public:
		typedef StaticT<T,MaxSizeV> Type;
	};
	template<typename T>
	class SelectorT<T,0>
	{
	public:
		typedef DynamicT<T> Type;
	};
}

//
//T是队列元素类型，SizeV是所期望的队列的最大元素数目(为0时采用动态内存分配方案)
template<typename T,INT SizeV=0>
class DequeT
{
	typedef typename CollectionMemory::SelectorT<T,(SizeV == 0 ? 0 : SizeV+1)>::Type MemoryType;
public://标准双向队列访问方法
	//队列是否空
	inline BOOL Empty(VOID) const
	{
		return m_Head==m_Tail;
	}
	//队列是否满
	inline BOOL Full(VOID) const
	{
		return m_Head==(m_Tail+1)%m_MaxSize;
	}
	//清空队列
	inline VOID Clear(VOID)
	{
		m_Size=0;
		m_Head=m_Tail=0;
		m_Memory.Clear();
	}
	//当前队列中的元素个数
	inline INT Size(VOID) const
	{
		return m_Size;
	}
	//队列尾加一个元素
	inline INT PushBack(const T& t)
	{
		CrashAssert(m_Data);
		CrashAssert(!Full());

		INT id=m_Tail;
		m_Data[id]=t;
		m_Tail=(m_Tail+1) % m_MaxSize;

		UpdateSize();
		return id;
	}
	//队列头加一个元素
	inline INT PushFront(const T& t)
	{
		CrashAssert(m_Data);
		CrashAssert(!Full());

		m_Head=(m_MaxSize+m_Head-1) % m_MaxSize;
		m_Data[m_Head]=t;

		UpdateSize();
		return m_Head;
	}
	//删除队列尾一个元素
	inline T PopBack(VOID)
	{
		CrashAssert(m_Data);
		CrashAssert(!Empty());

		INT id=BackID();
		m_Tail=id;

		UpdateSize();
		return m_Data[id];
	}
	//删除队列头一个元素
	inline T PopFront(VOID)
	{
		CrashAssert(m_Data);
		CrashAssert(!Empty());

		INT id=m_Head;
		m_Head = (m_Head+1) % m_MaxSize;

		UpdateSize();
		return m_Data[id];
	}
	//读队列尾元素
	inline const T& Back(VOID) const
	{
		return m_Data[BackID()];
	}
	//读队列尾元素可写引用（用于修改队列尾元素）
	inline T& Back(VOID)
	{
		return m_Data[BackID()];
	}
	//读队列头元素
	inline const T& Front(VOID) const
	{
		return m_Data[FrontID()];
	}
	//读队列头元素可写引用（用于修改队列头元素）
	inline T& Front(VOID)
	{
		return m_Data[FrontID()];
	}
public://扩展双向队列访问方法（遍历与读写方法）
	//FrontID是队列头元素的ID
	inline INT FrontID(VOID) const
	{
		return m_Head;
	}
	//BackID是队列尾元素的ID
	inline INT BackID(VOID) const
	{
		if(Empty())
		{			
			return m_Head;
		}
		INT newId = (m_MaxSize+m_Tail-1) % m_MaxSize;
		return newId;
	}
	//取当前ID的前一个ID，如果已经是头元素ID，则返回INVALID_ID
	inline INT PrevID(INT id) const
	{
		if(id==m_Head)
			return INVALID_ID;
		INT newId = (m_MaxSize+id-1) % m_MaxSize;
		return newId;
	}
	//取当前ID的后一个ID，如果已经是尾元素ID，则返回INVALID_ID
	inline INT NextID(INT id) const
	{
		if(id==BackID())
			return INVALID_ID;
		INT newId = (id+1) % m_MaxSize;
		return newId;
	}
	//判断是否是有效的ID，对空队列，头ID与尾ID均属无效ID
	inline BOOL IsValidID(INT id) const
	{
		if(Empty())
		{
			return FALSE;
		}
		if(id<0 || id>=m_MaxSize)
		{
			return FALSE;
		}
		INT idVal=CalcIndex(id);
		INT tailVal=CalcIndex(m_Tail);
		if(idVal>=tailVal)
			return FALSE;
		return TRUE;
	}
	//取指定ID的元素
	inline const T& operator [] (INT id) const
	{
		if(id<0 || id>=m_MaxSize)
		{
			return GetInvalidValueRef();
		}
		else
		{
			return m_Data[id];
		}
	}
	//取指定ID的元素的可写引用（用于修改元素）
	inline T& operator [] (INT id)
	{
		if(id<0 || id>=m_MaxSize)
		{
			return GetInvalidValueRef();
		}
		else
		{
			return m_Data[id];
		}
	}
	//求2个ID的距离（间隔元素个数+1）
	inline INT Distance(INT id1,INT id2) const
	{
		INT val=Difference(id1,id2);
		if(val<0)
			return -val;
		else
			return val;
	}
	//求2个ID之差（按从头到尾的顺序编号元素，编号之差）
	inline INT Difference(INT id1,INT id2) const
	{
		INT id1Val=CalcIndex(id1);
		INT id2Val=CalcIndex(id2);
		CrashAssert(id1Val>=0 && id2Val>=0);
		return id2Val-id1Val;
	}
public:
	DequeT(VOID):m_Size(0),m_MaxSize(1),m_Head(0),m_Tail(0),m_Data(NULL)
	{
		if(SizeV>0)
		{
			Init(SizeV);
		}
	}
	DequeT(INT size):m_Size(0),m_MaxSize(1),m_Head(0),m_Tail(0),m_Data(NULL)
	{
		Init(size);
	}
	virtual ~DequeT(VOID)
	{
		m_Size = 0;
		m_MaxSize = 1;
		m_Head = 0;
		m_Tail = 0;
		m_Data = NULL;	
	}
public:
	DequeT(const DequeT& other)
	{
		Init(other.m_MaxSize-1);
		CopyFrom(other);
	}
	DequeT& operator=(const DequeT& other)
	{
		if(this==&other)
			return *this;
		Clear();
		Init(other.m_MaxSize-1);
		CopyFrom(other);
		return *this;
	}
public:
	inline VOID	Init(INT size)
	{
		Create(size+1);
	}
protected:
	inline VOID Create(INT size)
	{
		m_MaxSize = size;
		m_Data = m_Memory.Create(m_MaxSize);
		CrashAssert(m_Data);
		Clear();
	}
private:
	//计算元素的索引（头元素索引为0）
	inline INT CalcIndex(INT id) const
	{
		if(id<m_Head)
			return id+m_MaxSize-m_Head;
		else
			return id-m_Head;
	}
	//更新队列尺寸
	inline VOID UpdateSize(VOID)
	{
		m_Size=(m_MaxSize+m_Tail-m_Head)%m_MaxSize;
	}
private:
	VOID CopyFrom(const DequeT& other)
	{
		Clear();
		for(INT id=other.FrontID();TRUE==other.IsValidID(id);id=other.NextID(id))
		{
			PushBack(other[id]);
		}
	}
private:
	MemoryType m_Memory;
	T* m_Data;
	INT m_Size;
	INT m_MaxSize;
	//头元素的ID
	INT m_Head;
	//尾元素后面一个位置的ID，它标明队列尾的位置，它的值总是一个无效的ID
	INT m_Tail;
public:
	static T& GetInvalidValueRef(VOID)
	{
		static T s_Temp;
		return s_Temp;
	}
};

#endif //__QUEUE_H__