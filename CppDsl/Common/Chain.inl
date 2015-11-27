#ifndef __Chain_Inl__
#define __Chain_Inl__

template<typename DataT,typename RecyclerT>
inline VOID CChainNode<DataT,RecyclerT>::Recycle(VOID)
{
	m_Recycler.Recycle();
}

template<typename DataT,typename RecyclerT>
inline BOOL CChainNode<DataT,RecyclerT>::IsAllocated(VOID) const
{
	return m_Recycler.IsAllocated();
}

template<typename DataT,typename RecyclerT>
inline VOID CChainNode<DataT,RecyclerT>::DisConnect(VOID)
{
	if (m_pChain)
	{
   		--(m_pChain->m_uNum);
		if (m_pChain->GetNum() == 0)
		{
			m_pChain->m_pHead		= NULL;
			m_pChain->m_pTail		= NULL;
		}
		else
		{
			//if first item
   			if ( m_pChain->m_pHead == this )
			{
				m_pChain->m_pHead    = m_pNext;
			}

			//if last item
			if ( m_pChain->m_pTail == this )
			{
				m_pChain->m_pTail	= m_pPrevious;
			}
		}
	}

	//connect previous item and next item
	if (m_pNext)	
		m_pNext->m_pPrevious		= m_pPrevious;
	if (m_pPrevious)
		m_pPrevious->m_pNext		= m_pNext;
   
	m_pNext = NULL;
	m_pPrevious = NULL;
	m_pChain = NULL;
}

template<typename DataT,typename RecyclerT>
inline typename CChain<DataT,RecyclerT>::Iterator	CChain<DataT,RecyclerT>::GetIterator(INT i) const
{
	Iterator it=First();
	for(INT j = 0; j < i; ++j)
	{
		if(it.IsNull())
		{
			return Iterator();
		}
		else
		{
			++it;
		}
	}
	return it;
}

template<typename DataT,typename RecyclerT>
inline BOOL CChain<DataT,RecyclerT>::AddFirst(const typename CChain<DataT,RecyclerT>::Iterator& it)
{
	ItemType* pItem=it.GetPtr();
	if(NULL==pItem)
		return FALSE;
	pItem->DisConnect();
	pItem->m_pChain			= this;

	// first node
	if (0==m_uNum)
	{
		m_pTail					= pItem;
		m_pHead					= pItem;
		pItem->m_pPrevious		= NULL;
		pItem->m_pNext			= NULL;
		m_uNum ++;
	}
	else
	{
		pItem->m_pPrevious		= NULL;
		pItem->m_pNext			= m_pHead;
		m_pHead->m_pPrevious	= pItem;
		m_pHead					= pItem;
		m_uNum ++;
	}

	return TRUE;
}

template<typename DataT,typename RecyclerT>
inline BOOL CChain<DataT,RecyclerT>::AddLast(const typename CChain<DataT,RecyclerT>::Iterator& it)
{
	ItemType* pItem=it.GetPtr();	
	if(NULL==pItem)
		return FALSE;
	pItem->DisConnect();
	pItem->m_pChain			= this;

	// first node
	if (0==m_uNum)
	{
		m_pTail					= pItem;
		m_pHead					= pItem;
		pItem->m_pPrevious		= NULL;
		pItem->m_pNext			= NULL;
		m_uNum ++;
	}
	else
	{
		m_pTail->m_pNext		= pItem;
		pItem->m_pPrevious		= m_pTail;
		pItem->m_pNext			= NULL;
		m_pTail					= pItem;
		m_uNum ++;
	}

	return TRUE;
}

template<typename DataT,typename RecyclerT>
inline BOOL CChain<DataT,RecyclerT>::InsertBefore(const typename CChain<DataT,RecyclerT>::Iterator& pos,const typename CChain<DataT,RecyclerT>::Iterator& it)
{
	ItemType* pItem1	= pos.GetPtr();
	ItemType* pItem2	= it.GetPtr();	
	if(NULL==pItem1)
		return FALSE;
	if(this!=pItem1->m_pChain)
		return FALSE;
	if(NULL!=pItem2)
		return FALSE;

	pItem2->m_pChain	= this;
	
	if (pItem1 == m_pHead)
	{
		m_pHead = pItem2;
	}

	pItem2->m_pNext		= pItem1;
	pItem2->m_pPrevious = pItem1->m_pPrevious;
	pItem1->m_pPrevious->m_pNext = pItem2;
	pItem1->m_pPrevious = pItem2;

	m_uNum ++;

	return TRUE;
}

template<typename DataT,typename RecyclerT>
inline BOOL CChain<DataT,RecyclerT>::InsertAfter(const typename CChain<DataT,RecyclerT>::Iterator& pos,const typename CChain<DataT,RecyclerT>::Iterator& it)
{
	ItemType* pItem1	= pos.GetPtr();
	ItemType* pItem2	= it.GetPtr();
	if(NULL==pItem1)
		return FALSE;
	if(this!=pItem1->m_pChain)
		return FALSE;
	if(NULL!=pItem2)
		return FALSE;

	pItem2->m_pChain	= this;
	
	pItem1=pItem1->m_pNext;
	if( NULL!=pItem1 )
	{
		InsertBefore( Iterator(pItem1),it );
	}
	else 
	{
		Add( it );
	}

	return TRUE;
}

template<typename DataT,typename RecyclerT>
inline const typename CChain<DataT,RecyclerT>::Iterator CChain<DataT,RecyclerT>::RemoveFirst(VOID)
{
	if(GetNum()<=0)
		return Iterator();
	return Remove(First());
}

template<typename DataT,typename RecyclerT>
inline const typename CChain<DataT,RecyclerT>::Iterator CChain<DataT,RecyclerT>::RemoveLast(VOID)
{
	if(GetNum()<=0)
		return Iterator();
	Remove(Last());
	return Last();
}

template<typename DataT,typename RecyclerT>
inline const typename CChain<DataT,RecyclerT>::Iterator CChain<DataT,RecyclerT>::Remove(const typename CChain<DataT,RecyclerT>::Iterator& it)
{
	if(FALSE==it.IsNull() && this==it.GetChain())
	{
		Iterator ret = it.GetNext();
		ItemType* pItem = it.GetPtr();
		if(NULL==pItem)
			return ret;
		//从当前链表脱离
		pItem->DisConnect();		
		//结点数据返还给数据池
		it.GetPtr()->Recycle();
		return ret;
	}
	else
	{
		return Iterator();
	}
}

template<typename DataT,typename RecyclerT>
inline BOOL CChain<DataT,RecyclerT>::RemoveAll(VOID)
{
	Iterator it=First();
	for(;FALSE==it.IsNull();)
	{
		it=Remove(it);
	}
	m_uNum = 0;
	return TRUE;
}

template<typename DataT,typename RecyclerT>
inline const typename CChain<DataT,RecyclerT>::Iterator CChain<DataT,RecyclerT>::MoveAsFirst(const Iterator& it)
{
	if(FALSE==it.IsNull() && this==it.GetChain())
	{
		Iterator ret = it.GetNext();
		ItemType* pItem = it.GetPtr();
		if(NULL==pItem)
			return ret;
		//从当前链表脱离
		pItem->DisConnect();
		AddFirst(it);
		return ret;
	}
	else
	{
		return Iterator();
	}
}

template<typename DataT,typename RecyclerT>
inline const typename CChain<DataT,RecyclerT>::Iterator CChain<DataT,RecyclerT>::MoveAsLast(const Iterator& it)
{
	if(FALSE==it.IsNull() && this==it.GetChain())
	{
		Iterator ret = it.GetPrevious();
		ItemType* pItem = it.GetPtr();
		if(NULL==pItem)
			return ret;
		//从当前链表脱离
		pItem->DisConnect();		
		AddLast(it);
		return ret;
	}
	else
	{
		return Iterator();
	}
}

template<typename DataT,typename RecyclerT>
inline INT	CChain<DataT,RecyclerT>::IndexOf(const typename CChain<DataT,RecyclerT>::Iterator& target) const
{
	 UINT	uNum = 0;

	 Iterator it = First();
	 while(FALSE==it.IsNull())
	 {
		if(it==target)
			return uNum;
		++it;
		++uNum;
	 }
	 return -1;
}

#endif //__Chain_Inl__