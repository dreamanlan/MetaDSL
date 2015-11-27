#ifndef		__CHAIN_H__
#define		__CHAIN_H__

#include "BaseType.h"
#include "Queue.h"

/**	约定CChainNode<DataT,RecyclerT>由数据池分配,Recycle方法用于返还结点给数据池，
*	也就是说Recycle方法调用之后，结点应该不在任何链表上，数据池随后可以将该结点
*	作为新结点分配。
*	@Remarks
*	RecyclerT需要符合：
*	1、有无参数构造或默认构造。
*	2、提供公有方法VOID Recycle(CChainNode<DataT,RecyclerT>* pNode)。
*/
template<typename DataT,typename RecyclerT>
class CChain;

template<typename DataT,typename RecyclerT>
class CChainNode
{
public:
	typedef CChain<DataT,RecyclerT>		ChainType;
	typedef CChainNode<DataT,RecyclerT>	ItemType;
	friend class CChain<DataT,RecyclerT>;
	friend class Iterator;
	/**	一个类似STL中迭代器的东东，但是概念上不严格一样。
	*/
	class Iterator
	{
	public:
		inline ChainType*				GetChain(VOID) const
		{
			if(NULL==m_pItem)
				return NULL;
			return m_pItem->m_pChain;
		}
		inline const Iterator			GetNext(VOID) const
		{
			if(NULL==m_pItem)
				return Iterator();
			return Iterator(m_pItem->m_pNext);
		}
		inline const Iterator			GetPrevious(VOID) const
		{
			if(NULL==m_pItem)
				return Iterator();
			return Iterator(m_pItem->m_pPrevious);
		}
		inline BOOL						IsNull(VOID) const
		{
			return m_pItem==NULL;
		}
	public:
		inline ItemType* GetPtr(VOID) const {return m_pItem;}
		inline VOID Recycle(VOID)
		{
			if(NULL==m_pItem)
				return;
			m_pItem->Recycle();
		}
		inline BOOL						IsAllocated(VOID) const
		{
			if(NULL==m_pItem)
				return FALSE;
			return m_pItem->IsAllocated();
		}
	public:
		inline DataT& operator * (VOID) const {CrashAssert(m_pItem);return m_pItem->m_Data;}
		inline DataT* operator -> (VOID) const {CrashAssert(m_pItem);return &(m_pItem->m_Data);}	
	public:
		inline Iterator& operator++(VOID)
		{
			CrashAssert(m_pItem);
			m_pItem=m_pItem->m_pNext;
			return *this;
		}
		inline const Iterator operator++(INT)
		{
			CrashAssert(m_pItem);
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}
		inline Iterator& operator--(VOID)
		{
			CrashAssert(m_pItem);
			m_pItem=m_pItem->m_pPrevious;
			return *this;
		}
		inline const Iterator operator--(INT)
		{
			CrashAssert(m_pItem);
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}
		inline BOOL operator == (const Iterator& other) const
		{
			return m_pItem==other.m_pItem;
		}
		inline BOOL operator != (const Iterator& other) const
		{
			return !(operator ==(other));
		}
	public:
		Iterator(VOID)
		{
			m_pItem=NULL;
		}
		explicit Iterator(ItemType* ptr)
		{
			m_pItem=ptr;
		}
		Iterator(const Iterator& other)
		{
			m_pItem=other.m_pItem;
		}
		inline Iterator& operator = (const Iterator& other)
		{
			if(this==&other)
				return *this;
			m_pItem=other.m_pItem;
			return *this;
		}
		inline Iterator& operator = (ItemType* pItem)
		{
			m_pItem=pItem;
			return *this;
		}
	private:
		ItemType* m_pItem;
	};
protected:
	ChainType*					m_pChain;
	ItemType*					m_pNext;
	ItemType*					m_pPrevious;
protected:
	DataT						m_Data;
	RecyclerT					m_Recycler;
public:
	CChainNode(VOID)
	{
		m_pChain    = NULL;
		m_pNext     = NULL;
		m_pPrevious = NULL;
		m_Recycler.m_pNode = this;
	}
	virtual ~CChainNode(VOID){}
public:
	DataT& GetData(VOID){return m_Data;}
	const DataT& GetData(VOID) const {return m_Data;}
public:
	inline VOID Recycle(VOID);
	inline BOOL IsAllocated(VOID)const;
public:
	RecyclerT& GetRecycler(VOID){return m_Recycler;}
	const RecyclerT& GetRecycler(VOID)const{return m_Recycler;}
private:
	//使当前结点从链表上脱离并保持链表不断链（前后结点成为邻接），链表上的结点数减少一个
	inline VOID DisConnect(VOID);
};

template<typename DataT,typename RecyclerT>
class CChain
{
public:
	typedef CChain<DataT,RecyclerT>			ChainType;
	typedef CChainNode<DataT,RecyclerT>		ItemType;
	typedef typename ItemType::Iterator		Iterator;
	friend class CChainNode<DataT,RecyclerT>;
private:
	UINT				m_uNum;
	ItemType*			m_pHead;
	ItemType*			m_pTail;
public:
	CChain(VOID)
	{
		m_uNum		= 0;
		m_pHead		= NULL;
		m_pTail     = NULL;
	}
	virtual ~CChain(VOID)
	{
		RemoveAll();
	}
	//获取链表第一个结点
	inline const Iterator	First(VOID) const
	{
		return Iterator(m_pHead);
	}
	//获取链表最后一个结点
	inline const Iterator	Last(VOID) const
	{
		return Iterator(m_pTail);
	}
	//获取链表上结点总数
	inline UINT				GetNum(VOID) const
	{
		return m_uNum;
	}
	//获取第i个结点(从0开始计数)
	inline Iterator			GetIterator(INT i) const;
	//在链表上查找指定结点，返回结点在链表中的位置
	inline INT				IndexOf(const Iterator& it) const;
	//在链表头添加一个结点，此结点将成为新的链表头
	inline BOOL				AddFirst(const Iterator& it);
	//在链表尾添加一个结点，此结点将成为新的链表尾
	inline BOOL				AddLast(const Iterator& it);
	//在指定结点前插入一个结点,指定结点不能为空
	inline BOOL				InsertBefore(const Iterator& pos,const Iterator& it);
	//在指定结点后插入一个结点，指定结点不能为空
	inline BOOL				InsertAfter(const Iterator& pos,const Iterator& it);
	//删除第一个结点，结点返还给数据池，返回删除后链表的第一个结点
	inline const Iterator	RemoveFirst(VOID);
	//删除最后一个结点，结点返还给数据池，返回删除后链表的最后一个结点
	inline const Iterator	RemoveLast(VOID);
	//从链表上删除一个结点，结点返还给数据池，返回被删除结点后面的结点
	inline const Iterator	Remove(const Iterator& it);
	//从链表上删除所有结点，全部结点返还给数据池
	inline BOOL				RemoveAll(VOID);
	//移动指定结点为链的首结点
	inline const Iterator	MoveAsFirst(const Iterator& it);
	//移动指定结点为链的尾结点
	inline const Iterator	MoveAsLast(const Iterator& it);
};

template<typename DataT>
class NodeRecyclerForDataT
{
public:
	typedef NodeRecyclerForDataT<DataT> Recycler;
	typedef CChainNode<DataT,Recycler> DataNode;
	friend class CChainNode<DataT,Recycler>;
public:
	VOID Recycle(VOID)
	{
		if(NULL==m_pNode)
			return;
		m_pNode->GetData().Recycle();
	}
	BOOL IsAllocated(VOID) const
	{
		return m_pNode->GetData().IsAllocated();
	}
private:
	NodeRecyclerForDataT(VOID):m_pNode(NULL)
	{}
private:
	DataNode* m_pNode;
};

#include "Chain.inl"

#endif