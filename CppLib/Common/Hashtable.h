#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "BaseType.h"
#include "Chain.h"

//字符串hash值计算
UINT CalcStringHashCode(const CHAR *str);

//包装c字符串作为hash表的key，hashcode的计算采用相对简洁的经典算法，需要
//更换计算算法时，在HashtableT的第三个模板参数提供独立的KeyWorker，其中的
//GetHashCode实现采用新算法，Equal与Clean调用StringKeyT的相应成员即可。
template<INT CapacityV>
struct StringKeyT
{
	static const INT MAX_CHAR_CAPACITY	= CapacityV;
public://用作HashtableT的第3个模板参数所需的接口
	static UINT GetHashCode(const StringKeyT& key)
	{
		return (UINT)CalcStringHashCode(key.m_pString);
	}
	static BOOL Equal(const StringKeyT& key1,const StringKeyT& key2)
	{
		return 0==strcmp(key1.m_pString,key2.m_pString);
	}
	static VOID Clean(StringKeyT& key)
	{
		key.Clean();
	}
public://用作HashtableT第1个模板参数与包装标准c字符串的接口,支持标准c字符串到StringKeyT的隐式转换
	StringKeyT(VOID)
	{
		Clean();
	}
	//用于支持标准c字符串到StringKeyT的隐式转换，此构造不进行字符串内容的拷贝，不要直接使用
	StringKeyT(const char* p)
	{
		//此函数特殊，不使用StringKeyT的内部存储，直接引用外部c字符串，仅用于HashtableT::Add,Get,Remove的参数直接
		//使用c字符串时的隐式转换,StringKeyT的其它构造与赋值操作均使用内部存储，不再依赖外部存储空间。
		m_pString=p;
	}
	StringKeyT(const StringKeyT& other)
	{
		CopyFrom(other);
	}
	StringKeyT& operator= (const StringKeyT& other)
	{
		if(this==&other)
			return *this;
		CopyFrom(other);
		return *this;	
	}
	const CHAR* GetString(VOID)const
	{
		return m_pString;
	}
private:
	VOID Clean(VOID)
	{
		memset(m_String,0,sizeof(m_String));
		m_pString=m_String;
	}
	VOID CopyFrom(const StringKeyT& other)
	{
		Clean();
		strncpy(m_String,other.m_pString,MAX_CHAR_CAPACITY-1);
	}
private:
	CHAR		m_String[MAX_CHAR_CAPACITY];
	const CHAR*	m_pString;
};

//哈希表的基础功能（素数获取, 整数hash计算，冲突处理等）
class HashtableBase
{
protected:
	static const UINT INVALID_HASH_INDEX	= 0xFFFFFFFF;
	static const UINT MAX_HASH_INDEX_VALUE	= 0x7FFFFFFF;
	enum
	{
		IDTS_EMPTY = 0 ,
		IDTS_USED = 1 ,
		IDTS_REMOVED = 2 ,
	};
	class ISlotKey
	{
	public:
		virtual BOOL KeyEqual(UINT index) const = 0;
		virtual UINT GetHashCode(VOID) const = 0;
	};
	class ISlot
	{
	public:
		virtual UINT GetHashCode(VOID) const = 0;
		virtual VOID SetStatus(UINT) = 0;
		virtual UINT GetStatus(VOID) const = 0;
		virtual VOID Cleanup(VOID) = 0;
	public:
		virtual ~ISlot(VOID){}
	};
protected:
	//增加一个表项
	UINT		PrepareAddIndex(const ISlotKey& key);
	//读取信息
	UINT		Find( const ISlotKey& key ) const;
	//删除表项
	UINT		Remove( const ISlotKey& key );
	//清除所有数据
	VOID		Cleanup( VOID );
protected:
	virtual UINT			GetSlotCount(VOID) const = 0;
	virtual ISlot&			GetSlot(UINT index) = 0;
	virtual const ISlot&	GetSlot(UINT index) const = 0;
protected:
	virtual ~HashtableBase(VOID){};
protected:
	//得到一个大于等于指定值的素数,code必须小于0x7FFFFFFF(即有符号32位整数的最大值)
	static UINT	GetPrime(UINT code);
private:
	//计算hash索引值,hashSize--哈希表的最大尺寸，code--用于计算哈希值的原始值，incr--在哈希表中遇到冲突变更哈希值的增量
	static UINT	ToIndex(UINT hashSize,UINT code,UINT& incr);
	//判断某数是否是素数
	static BOOL IsPrime(UINT val);
};

//基础数值类型用作hash键时的HashtableT的第三个模板参数
template<typename KeyT>
class DefKeyWorkerT
{
public:
	static UINT GetHashCode(const KeyT& key)
	{
		return (UINT)key;
	}
	static BOOL Equal(const KeyT& key1,const KeyT& key2)
	{
		return key1==key2;
	}
	static VOID Clean(KeyT& key)
	{
		key=(KeyT)INVALID_ID;
	}
};

template<typename KeyT>
class DefKeyWorkerT<KeyT*>
{
public:
	static UINT GetHashCode(const KeyT* key)
	{
		UINT val=0;
		memcpy(&val,&key,sizeof(UINT));
		return val;
	}
	static BOOL Equal(const KeyT* key1,const KeyT* key2)
	{
		return key1==key2;
	}
	static VOID Clean(KeyT*& key)
	{
		key=NULL;
	}
};

//HashtableT的第四个模板参数的默认实现。
template<typename ValT>
class DefValueWorkerT
{
public:
	static VOID Clean(ValT& val)
	{
		val = ValT();
	}
};

template<typename ValT>
class DefValueWorkerT<ValT*>
{
public:
	static VOID Clean(ValT*& val)
	{
		val = NULL;
	}
};

//HashtableT的第四个模板参数的实现，用于以INVALID_ID表示无效值的情形。
template<typename ValT,ValT InvalidVal=INVALID_ID>
class IntegerValueWorkerT
{
public:
	static VOID Clean(ValT& val)
	{
		val = InvalidVal;
	}
};

//用于编译时查找大于等于指定值的素数的代码（实在没别的办法了，所以用了这种比较晦涩的技术，请不要怨我！）
namespace HashtableUtility
{
	template<bool v,int V,
		int K1=0,int K2=0,int K3=0,int K4=0,int K5=0,int K6=0,int K7=0,int K8=0,int K9=0,int K10=0,int K11=0,int K12=0,
		int K13=0,int K14=0,int K15=0,int K16=0,int K17=0,int K18=0,int K19=0,int K20=0,int K21=0,int K22=0,int K23=0,int K24=0,
		int K25=0,int K26=0,int K27=0,int K28=0,int K29=0,int K30=0,int K31=0,int K32=0,int K33=0,int K34=0,int K35=0,int K36=0,
		int K37=0,int K38=0,int K39=0,int K40=0,int K41=0,int K42=0,int K43=0,int K44=0,int K45=0,int K46=0,int K47=0,int K48=0,
		int K49=0,int K50=0,int K51=0,int K52=0,int K53=0,int K54=0,int K55=0,int K56=0,int K57=0,int K58=0,int K59=0,int K60=0,
		int K61=0,int K62=0,int K63=0,int K64=0,int K65=0,int K66=0,int K67=0,int K68=0,int K69=0,int K70=0,int K71=0,int K72=0>
	class FindImpl
	{
	public:
		static const int Value = K1;
	};
	template<int V,
		int K1,int K2,int K3,int K4,int K5,int K6,int K7,int K8,int K9,int K10,int K11,int K12,
		int K13,int K14,int K15,int K16,int K17,int K18,int K19,int K20,int K21,int K22,int K23,int K24,
		int K25,int K26,int K27,int K28,int K29,int K30,int K31,int K32,int K33,int K34,int K35,int K36,
		int K37,int K38,int K39,int K40,int K41,int K42,int K43,int K44,int K45,int K46,int K47,int K48,
		int K49,int K50,int K51,int K52,int K53,int K54,int K55,int K56,int K57,int K58,int K59,int K60,
		int K61,int K62,int K63,int K64,int K65,int K66,int K67,int K68,int K69,int K70,int K71,int K72>
	class FindImpl<false,V,K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K30,K31,K32,K33,K34,K35,K36,K37,K38,K39,K40,K41,K42,K43,K44,K45,K46,K47,K48,K49,K50,K51,K52,K53,K54,K55,K56,K57,K58,K59,K60,K61,K62,K63,K64,K65,K66,K67,K68,K69,K70,K71,K72>
	{
	public:
		static const int Value = FindImpl<(V<=K2),V,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K30,K31,K32,K33,K34,K35,K36,K37,K38,K39,K40,K41,K42,K43,K44,K45,K46,K47,K48,K49,K50,K51,K52,K53,K54,K55,K56,K57,K58,K59,K60,K61,K62,K63,K64,K65,K66,K67,K68,K69,K70,K71,K72>::Value;
	};
	template<int V,
		int K1=0,int K2=0,int K3=0,int K4=0,int K5=0,int K6=0,int K7=0,int K8=0,int K9=0,int K10=0,int K11=0,int K12=0,
		int K13=0,int K14=0,int K15=0,int K16=0,int K17=0,int K18=0,int K19=0,int K20=0,int K21=0,int K22=0,int K23=0,int K24=0,
		int K25=0,int K26=0,int K27=0,int K28=0,int K29=0,int K30=0,int K31=0,int K32=0,int K33=0,int K34=0,int K35=0,int K36=0,
		int K37=0,int K38=0,int K39=0,int K40=0,int K41=0,int K42=0,int K43=0,int K44=0,int K45=0,int K46=0,int K47=0,int K48=0,
		int K49=0,int K50=0,int K51=0,int K52=0,int K53=0,int K54=0,int K55=0,int K56=0,int K57=0,int K58=0,int K59=0,int K60=0,
		int K61=0,int K62=0,int K63=0,int K64=0,int K65=0,int K66=0,int K67=0,int K68=0,int K69=0,int K70=0,int K71=0,int K72=0>
	class Find
	{
	public:
		static const int Value = FindImpl<(V<=K1),V,K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K30,K31,K32,K33,K34,K35,K36,K37,K38,K39,K40,K41,K42,K43,K44,K45,K46,K47,K48,K49,K50,K51,K52,K53,K54,K55,K56,K57,K58,K59,K60,K61,K62,K63,K64,K65,K66,K67,K68,K69,K70,K71,K72>::Value;
	};
	template<int v>
	class Prime
	{
	public:
		static const int Value = Find<v,
			3, 7, 11, 0x11, 0x17, 0x1d, 0x25, 0x2f, 0x3b, 0x47, 0x59, 0x6b, 0x83, 0xa3, 0xc5, 0xef,
			0x125, 0x161, 0x1af, 0x209, 0x277, 0x2f9, 0x397, 0x44f, 0x52f, 0x63d, 0x78b, 0x91d, 0xaf1, 0xd2b, 0xfd1, 0x12fd,
			0x16cf, 0x1b65, 0x20e3, 0x2777, 0x2f6f, 0x38ff, 0x446f, 0x521f, 0x628d, 0x7655, 0x8e01, 0xaa6b, 0xcc89, 0xf583, 0x126a7, 0x1619b,
			0x1a857, 0x1fd3b, 0x26315, 0x2dd67, 0x3701b, 0x42023, 0x4f361, 0x5f0ed, 0x72125, 0x88e31, 0xa443b, 0xc51eb, 0xec8c1, 0x11bdbf, 0x154a3f, 0x198c4f,
			0x1ea867, 0x24ca19, 0x2c25c1, 0x34fa1b, 0x3f928f, 0x4c4987, 0x5b8b6f, 0x6dda89
		>::Value;
	};
}

//哈希表模板类(最大支持0x7FFFFFFF个元素)
template<typename KeyT,typename ValT,typename KeyWorkerT=DefKeyWorkerT<KeyT>,typename ValueWorkerT=DefValueWorkerT<ValT>,INT SizeV=0 >
class HashtableT : private HashtableBase
{
	typedef HashtableT<KeyT,ValT,KeyWorkerT,ValueWorkerT,SizeV> HashtableType;
	friend class SlotKey;
	class SlotKey : public ISlotKey
	{
	public:
		virtual BOOL KeyEqual(UINT index) const
		{
			return KeyWorkerT::Equal(m_Key,m_pHashtable->GetSlotImpl(index).m_ID);
		}
		virtual UINT GetHashCode(VOID) const
		{
			return KeyWorkerT::GetHashCode(m_Key);
		}
	public:
		SlotKey(const HashtableType* ptr,const KeyT& key):m_pHashtable(ptr),m_Key(key)
		{
			CrashAssert(m_pHashtable);
		}
	private://禁用拷贝与赋值，此类使用引用包装，只用于受限场合
		SlotKey(const SlotKey&);
		SlotKey& operator= (const SlotKey&);
	private:
		const KeyT&				m_Key;
		const HashtableType*	m_pHashtable;
	};
	class Slot : public ISlot
	{
	public:
		virtual UINT GetHashCode(VOID) const
		{
			return KeyWorkerT::GetHashCode(m_ID);
		}
		virtual VOID SetStatus(UINT status)
		{
			m_Status = status;
		}
		virtual UINT GetStatus(VOID) const
		{
			return m_Status;
		}
		virtual VOID Cleanup(VOID)
		{
			Clear();
		}
	public:
		Slot(VOID)
		{
			Clear();
		}
	private:
		VOID Clear(VOID)
		{
			m_Status= IDTS_EMPTY;
			KeyWorkerT::Clean(m_ID);
			ValueWorkerT::Clean(m_Value);
		}
	public:
		UINT	m_Status;
		KeyT	m_ID;
		ValT	m_Value;
	};
public:
	class KeyValueData
	{
		friend class HashtableT<KeyT,ValT,KeyWorkerT,ValueWorkerT,SizeV>;
	public:
		const KeyT&	GetKey(VOID)const
		{
			return m_Slot.m_ID;
		}
		const ValT& GetValue(VOID)const
		{
			return m_Slot.m_Value;
		}
		ValT& GetValue(VOID)
		{
			return m_Slot.m_Value;
		}
	public:
		VOID		Recycle(VOID){m_Allocated=FALSE;}
		BOOL		IsAllocated(VOID)const{return m_Allocated;}
	public:
		KeyValueData(VOID):m_Allocated(FALSE){}
	private:
		const Slot&	GetSlot(VOID)const{return m_Slot;}
		Slot&		GetSlot(VOID){return m_Slot;}
		VOID		UpdateAllocated(BOOL allocated){m_Allocated=allocated;}
	private:
		Slot		m_Slot;
		BOOL		m_Allocated;
	};
	typedef NodeRecyclerForDataT<KeyValueData> Recycler;
	typedef CChainNode<KeyValueData,Recycler> KeyValueDataNode;
	typedef CChain<KeyValueData,Recycler>	KeyValueDataChain;
	typedef typename KeyValueDataNode::Iterator	Iterator;
	typedef typename CollectionMemory::SelectorT<KeyValueDataNode,(SizeV==0 ? 0 : HashtableUtility::Prime<SizeV>::Value)>::Type MemoryType;
public:
	HashtableT(VOID):m_pTable(NULL),m_Count(0)
	{
        if(SizeV>0)
		{
			InitTable(SizeV);
		}
	}
	HashtableT(UINT maxItem):m_pTable(NULL),m_Count(0)
	{
		InitTable(maxItem);
	}
	virtual ~HashtableT(VOID)
	{
		CleanUp();
		m_pTable = NULL;
		m_Count = 0;
	}
	BOOL IsInited(VOID)const
	{
		return (NULL!=m_pTable && 0<m_Count ? TRUE : FALSE);
	}
public:
	HashtableT(const HashtableT& other)
	{
		InitTable(other.m_Count);
		CopyFrom(other);
	}
	HashtableT& operator=(const HashtableT& other)
	{
		if(this==&other)
			return *this;
		CleanUp();
		InitTable(other.m_Count);
		CopyFrom(other);
		return *this;
	}
public:
	//初始化表
	inline VOID				InitTable( UINT maxItem )
	{		
		UINT maxVal = HashtableBase::GetPrime(maxItem);
		if(maxVal==INVALID_HASH_INDEX)
		{
			CrashAssert(FALSE);
			return;
		}
		Create(maxVal);
	}
	//增加一个表项
	inline BOOL				Add( const KeyT& id, const ValT& val )
	{
		SlotKey key(this,id);
		UINT index=Find(key);
		if(index!=INVALID_HASH_INDEX)
			return FALSE;
		index=PrepareAddIndex(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return FALSE;
		GetSlotImpl(index).m_ID=id;
		GetSlotImpl(index).m_Value=val;
		Iterator it = GetChainIterator(index);
		it->UpdateAllocated(TRUE);
		m_DataChain.AddLast(it);
		return TRUE;
	}
	//读取信息
	inline const ValT&		Get( const KeyT& id ) const
	{		
		SlotKey key(this,id);
		UINT index=HashtableBase::Find(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return GetInvalidValueRef();
		return GetSlotImpl(index).m_Value;
	}
	//读取信息
	inline ValT&			Get( const KeyT& id )
	{		
		SlotKey key(this,id);
		UINT index=HashtableBase::Find(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return GetInvalidValueRef();
		return GetSlotImpl(index).m_Value;
	}
	//删除表项
	inline const Iterator	Remove( const KeyT& id )
	{
		SlotKey key(this,id);
		UINT index=HashtableBase::Remove(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return Iterator();
		return m_DataChain.Remove(GetChainIterator(index));
	}
	//删除表项
	inline const Iterator	Remove( const Iterator& it )
	{
		SlotKey key(this,it->GetKey());
		UINT index=HashtableBase::Remove(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return Iterator();
		return m_DataChain.Remove(GetChainIterator(index));
	}
	//移动指定结点为遍历表的首结点
	inline const Iterator	MoveAsFirst( const Iterator& it )
	{
		return m_DataChain.MoveAsFirst(it);
	}
	//移动指定结点为遍历表的尾结点
	inline const Iterator	MoveAsLast( const Iterator& it )
	{
		return m_DataChain.MoveAsLast(it);
	}
	//清除所有数据
	inline VOID				CleanUp( VOID )
	{
		HashtableBase::Cleanup();
		m_DataChain.RemoveAll();
	}
	//
	inline const Iterator	First(VOID) const
	{
		return m_DataChain.First();
	}
	//
	inline const Iterator	Last(VOID) const
	{
		return m_DataChain.Last();
	}
	//
	inline const Iterator	GetIterator(INT i) const
	{
		return m_DataChain.GetIterator(i);
	}
	//
	inline INT				IndexOf(const KeyT& id) const
	{
		SlotKey key(this,id);
		UINT index=HashtableBase::Find(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return INVALID_INDEX;
        return m_DataChain.IndexOf(GetChainIterator(index));
	}
	//
	inline UINT				GetNum(VOID) const
	{
		return m_DataChain.GetNum();
	}
	//
	inline BOOL				Empty(VOID) const
	{
		if(GetNum()==0)
			return TRUE;
		else
			return FALSE;
	}
	//
	inline BOOL				Full(VOID) const
	{
		if(GetNum()>=m_Count)
			return TRUE;
		else
			return FALSE;
	}
	inline size_t				GetMemoryInUsed(VOID) const
	{
		return m_Memory.GetMemoryInUsed();
	}
protected:
	virtual UINT			GetSlotCount(VOID) const
	{
		return m_Count;
	}
	virtual ISlot&			GetSlot(UINT index)
	{
		return GetSlotImpl(index);
	}
	virtual const ISlot&	GetSlot(UINT index) const
	{
		return GetSlotImpl(index);
	}
protected:
	inline VOID Create(UINT size)
	{
		INT v = (INT)size;
		m_pTable = m_Memory.Create(v);
		m_Count = (UINT)v;
		CrashAssert(m_pTable);
		CleanUp();
	}
private:
	inline Slot&			GetSlotImpl(UINT index)
	{
		return const_cast<Slot&>(static_cast<const HashtableType*>(this)->GetSlotImpl(index));
	}
	inline const Slot&		GetSlotImpl(UINT index)const
	{
		if(index>=m_Count)
		{
			CrashAssert(FALSE);
		}
		CrashAssertEx(m_pTable,"You must call InitTable first!");
		return m_pTable[index].GetData().GetSlot();
	}
	inline const typename KeyValueDataNode::Iterator GetChainIterator(UINT index) const
	{
		if(index>=m_Count)
		{
			CrashAssert(FALSE);
		}
		CrashAssertEx(m_pTable,"You must call InitTable first!");
		return typename KeyValueDataNode::Iterator(&(m_pTable[index]));
	}
private:
	VOID CopyFrom(const HashtableT& other)
	{
//		CleanUp();
		for(Iterator it=other.First();FALSE==it.IsNull();++it)
		{
			Add(it->GetKey(),it->GetValue());
		}
	}
private:
	UINT				m_Count;
	KeyValueDataNode*	m_pTable;
	KeyValueDataChain	m_DataChain;
	MemoryType			m_Memory;
public:
	static inline KeyT&	GetInvalidKeyRef(VOID)
	{
		static KeyT s_Key;
		KeyWorkerT::Clean(s_Key);
		return s_Key;
	}
	static inline ValT&	GetInvalidValueRef(VOID)
	{
		static ValT s_Val;
		ValueWorkerT::Clean(s_Val);
		return s_Val;
	}
};

//哈希集合模板类(最大支持0x7FFFFFFF个元素)
template<typename KeyT,typename KeyWorkerT=DefKeyWorkerT<KeyT>,INT SizeV=0 >
class HashsetT : private HashtableBase
{
	typedef HashsetT<KeyT,KeyWorkerT,SizeV> HashsetType;
	friend class SlotKey;
	class SlotKey : public ISlotKey
	{
	public:
		virtual BOOL KeyEqual(UINT index) const
		{
			return KeyWorkerT::Equal(m_Key,m_pHashset->GetSlotImpl(index).m_ID);
		}
		virtual UINT GetHashCode(VOID) const
		{
			return KeyWorkerT::GetHashCode(m_Key);
		}
	public:
		SlotKey(const HashsetType* ptr,const KeyT& key):m_pHashset(ptr),m_Key(key)
		{
			CrashAssert(m_pHashset);
		}
	private://禁用拷贝与赋值，此类使用引用包装，只用于受限场合
		SlotKey(const SlotKey&);
		SlotKey& operator= (const SlotKey&);
	private:
		const KeyT&				m_Key;
		const HashsetType*		m_pHashset;
	};
	class Slot : public ISlot
	{
	public:
		virtual UINT GetHashCode(VOID) const
		{
			return KeyWorkerT::GetHashCode(m_ID);
		}
		virtual VOID SetStatus(UINT status)
		{
			m_Status = status;
		}
		virtual UINT GetStatus(VOID) const
		{
			return m_Status;
		}
		virtual VOID Cleanup(VOID)
		{
			Clear();
		}
	public:
		Slot(VOID)
		{
			Clear();
		}
	private:
		VOID Clear(VOID)
		{
			m_Status= IDTS_EMPTY;
			KeyWorkerT::Clean(m_ID);
		}
	public:
		UINT	m_Status;
		KeyT	m_ID;
	};
public:
	class KeyData
	{
		friend class HashsetT<KeyT,KeyWorkerT,SizeV>;
	public:
		const KeyT&	GetKey(VOID)const
		{
			return m_Slot.m_ID;
		}
	public:
		VOID		Recycle(VOID){m_Allocated=FALSE;}
		BOOL		IsAllocated(VOID)const{return m_Allocated;}
	public:
		KeyData(VOID):m_Allocated(FALSE){}
	private:
		const Slot&	GetSlot(VOID)const{return m_Slot;}
		Slot&		GetSlot(VOID){return m_Slot;}
		VOID		UpdateAllocated(BOOL allocated){m_Allocated=allocated;}
	private:
		Slot		m_Slot;
		BOOL		m_Allocated;
	};
	typedef NodeRecyclerForDataT<KeyData> Recycler;
	typedef CChainNode<KeyData,Recycler> KeyDataNode;
	typedef CChain<KeyData,Recycler>	KeyDataChain;
	typedef typename KeyDataNode::Iterator	Iterator;
	typedef typename CollectionMemory::SelectorT<KeyDataNode,(SizeV==0 ? 0 : HashtableUtility::Prime<SizeV>::Value)>::Type MemoryType;
public:
	HashsetT(VOID):m_pTable(NULL),m_Count(0)
	{
		if(SizeV>0)
		{
			InitSet(SizeV);
		}
	}
	HashsetT(UINT maxItem):m_pTable(NULL),m_Count(0)
	{
		InitSet(maxItem);
	}
	virtual ~HashsetT(VOID)
	{
		CleanUp();
		m_pTable = NULL;
		m_Count = 0;
	}
	BOOL IsInited(VOID)const
	{
		return (NULL!=m_pTable && 0<m_Count ? TRUE : FALSE);
	}
public:
	HashsetT(const HashsetT& other)
	{
		InitSet(other.m_Count);
		CopyFrom(other);
	}
	HashsetT& operator=(const HashsetT& other)
	{
		if(this==&other)
			return *this;
		CleanUp();
		InitSet(other.m_Count);
		CopyFrom(other);
		return *this;
	}
public:
	//初始化表
	inline VOID				InitSet( UINT maxItem )
	{		
		UINT maxVal = HashtableBase::GetPrime(maxItem);
		if(maxVal==INVALID_HASH_INDEX)
		{
			CrashAssert(FALSE);
			return;
		}
		Create(maxVal);
	}
	//增加一个表项
	inline BOOL				Insert( const KeyT& id )
	{
		SlotKey key(this,id);
		UINT index=Find(key);
		if(index!=INVALID_HASH_INDEX)
			return FALSE;
		index=PrepareAddIndex(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return FALSE;
		GetSlotImpl(index).m_ID=id;
		Iterator it = GetChainIterator(index);
		it->UpdateAllocated(TRUE);
		m_DataChain.AddLast(it);
		return TRUE;
	}
	//读取信息
	inline BOOL				Exist( const KeyT& id ) const
	{		
		SlotKey key(this,id);
		UINT index=HashtableBase::Find(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return FALSE;
		return TRUE;
	}
	//删除表项
	inline const Iterator	Remove( const KeyT& id )
	{
		SlotKey key(this,id);
		UINT index=HashtableBase::Remove(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return Iterator();
		return m_DataChain.Remove(GetChainIterator(index));
	}
	//删除表项
	inline const Iterator	Remove( const Iterator& it )
	{
		SlotKey key(this,it->GetKey());
		UINT index=HashtableBase::Remove(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return Iterator();
		return m_DataChain.Remove(GetChainIterator(index));
	}
	//移动指定结点为遍历表的首结点
	inline const Iterator	MoveAsFirst( const Iterator& it )
	{
		return m_DataChain.MoveAsFirst(it);
	}
	//移动指定结点为遍历表的尾结点
	inline const Iterator	MoveAsLast( const Iterator& it )
	{
		return m_DataChain.MoveAsLast(it);
	}
	//清除所有数据
	inline VOID				CleanUp( VOID )
	{
		HashtableBase::Cleanup();
		m_DataChain.RemoveAll();
	}
	//
	inline const Iterator	First(VOID) const
	{
		return m_DataChain.First();
	}
	//
	inline const Iterator	Last(VOID) const
	{
		return m_DataChain.Last();
	}
	//
	inline const Iterator	GetIterator(INT i) const
	{
		return m_DataChain.GetIterator(i);
	}
	//
	inline INT				IndexOf(const KeyT& id) const
	{
		SlotKey key(this,id);
		UINT index=HashtableBase::Find(key);
		if(index==INVALID_HASH_INDEX || index>=m_Count)
			return INVALID_INDEX;
        return m_DataChain.IndexOf(GetChainIterator(index));
	}
	//
	inline UINT				GetNum(VOID) const
	{
		return m_DataChain.GetNum();
	}
	//
	inline BOOL				Empty(VOID) const
	{
		if(GetNum()==0)
			return TRUE;
		else
			return FALSE;
	}
	//
	inline BOOL				Full(VOID) const
	{
		if(GetNum()>=m_Count)
			return TRUE;
		else
			return FALSE;
	}
protected:
	virtual UINT			GetSlotCount(VOID) const
	{
		return m_Count;
	}
	virtual ISlot&			GetSlot(UINT index)
	{
		return GetSlotImpl(index);
	}
	virtual const ISlot&	GetSlot(UINT index) const
	{
		return GetSlotImpl(index);
	}
protected:
	inline VOID Create(UINT size)
	{
		INT v = (INT)size;
		m_pTable = m_Memory.Create(v);
		m_Count = (UINT)v;
		CrashAssert(m_pTable);
		CleanUp();
	}
private:
	inline Slot&			GetSlotImpl(UINT index)
	{
		return const_cast<Slot&>(static_cast<const HashsetType*>(this)->GetSlotImpl(index));
	}
	inline const Slot&		GetSlotImpl(UINT index)const
	{
		if(index>=m_Count)
		{
			CrashAssert(FALSE);
		}
		CrashAssertEx(m_pTable,"You must call InitSet first!");
		return m_pTable[index].GetData().GetSlot();
	}
	inline const typename KeyDataNode::Iterator GetChainIterator(UINT index) const
	{
		if(index>=m_Count)
		{
			CrashAssert(FALSE);
		}
		CrashAssertEx(m_pTable,"You must call InitSet first!");
		return typename KeyDataNode::Iterator(&(m_pTable[index]));
	}
private:
	VOID CopyFrom(const HashsetT& other)
	{
//		CleanUp();
		for(Iterator it=other.First();FALSE==it.IsNull();++it)
		{
			Insert(it->GetKey());
		}
	}
private:
	UINT			m_Count;
	KeyDataNode*	m_pTable;
	KeyDataChain	m_DataChain;
	MemoryType		m_Memory;
public:
	static inline KeyT&	GetInvalidKeyRef(VOID)
	{
		static KeyT s_Key;
		KeyWorkerT::Clean(s_Key);
		return s_Key;
	}
};

#endif
