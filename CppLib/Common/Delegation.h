#ifndef __Delegation_H__
#define __Delegation_H__

#include <string.h>

#define PTR_BUFFER_NUM	4

struct ObjectPlaceHolder
{
public:
	ObjectPlaceHolder()
	{
		clear();
	}
	ObjectPlaceHolder(const ObjectPlaceHolder& other)
	{
		obj=other.obj;
		memcpy(ptrBuffer,other.ptrBuffer,sizeof(ptrBuffer));
	}
	ObjectPlaceHolder& operator=(const ObjectPlaceHolder& other)
	{
		if(&other==this)
			return *this;
		obj=other.obj;
		memcpy(ptrBuffer,other.ptrBuffer,sizeof(ptrBuffer));
		return *this;
	}
	inline bool isNull(void) const
	{
		if(obj!=NULL)
			return false;
		for(int i=0;i<PTR_BUFFER_NUM;++i)
		{
			if(ptrBuffer[i]!=NULL)
				return false;
		}
		return true;
	}
	inline void clear(void)
	{
		obj=NULL;
		memset(ptrBuffer,0,sizeof(ptrBuffer));
	}
private:
	void* obj;
	void* ptrBuffer[PTR_BUFFER_NUM];
};

template<typename Delegation,typename R>
struct FuncInvoker0
{
public:
	typedef FuncInvoker0<Delegation,R> ThisType;
	typedef R (*Fptr)(void);
	FuncInvoker0(Fptr func)
	{
		mFunc=func;
	}
	static inline R invoke(const ObjectPlaceHolder* address)
	{
		const ThisType* pThis=reinterpret_cast<const ThisType*>(address);
		Fptr pFunc=pThis->mFunc;
		return (*pFunc)();
	}
	static inline void* operator new (size_t size,const ObjectPlaceHolder* address,size_t space)
	{
		/*char buf[1025];
		::sprintf(buf,"%d<->%d",size,space);
		::MessageBox(NULL,buf,"",MB_OK);
		Assert(size<=space);*/
		return (void*)address;
	}
	static inline void operator delete(void*,const ObjectPlaceHolder* address,size_t space)
	{}
private:
	Fptr mFunc;
};

template<typename Delegation,typename T,typename R>
struct MemFuncInvoker0
{
public:
	typedef MemFuncInvoker0<Delegation,T,R> ThisType;
	typedef R (T::*Fptr)(void);
	MemFuncInvoker0(T* obj,Fptr func)
	{
		mObj=obj;
		mFunc=func;
	}
	static inline R invoke(const ObjectPlaceHolder* address)
	{
		const ThisType* pThis=reinterpret_cast<const ThisType*>(address);
		T* pObj=pThis->mObj;
		Fptr pFunc=pThis->mFunc;
		return (pObj->*pFunc)();
	}
	static inline void* operator new (size_t size,const ObjectPlaceHolder* address,size_t space)
	{
		/*char buf[1025];
		::sprintf(buf,"%d<->%d",size,space);
		::MessageBox(NULL,buf,"",MB_OK);*/
		/*Assert(size<=space);*/
		return (void*)address;
	}
	static inline void operator delete(void*,const ObjectPlaceHolder* address,size_t space)
	{}
private:
	T* mObj;
	Fptr mFunc;
};

template<typename R>
struct Delegation0
{
public:
	typedef Delegation0<R> ThisType;
	typedef R (*InvokerType)(const ObjectPlaceHolder*);
public:
	Delegation0()
	{
		detach();
	}
	Delegation0(const Delegation0& other)
	{
		mObj=other.mObj;
		invoker=other.invoker;
	}
	template<typename T>
	Delegation0(T* obj,R (T::*fptr)(void))
	{
		attach(obj,fptr);
	}
	Delegation0(R (*fptr)(void))
	{
		attach(fptr);
	}
	Delegation0& operator=(const Delegation0& other)
	{
		if(&other==this)
			return *this;
		mObj=other.mObj;
		invoker=other.invoker;
		return *this;
	}
	template<typename T>
	inline void attach(T* obj,R (T::*fptr)(void))
	{
		invoker=MemFuncInvoker0<ThisType,T,R>::invoke;
		new(&mObj,sizeof(ObjectPlaceHolder)) MemFuncInvoker0<ThisType,T,R>(obj,fptr);
	}
	inline void attach(R (*fptr)(void))
	{
		invoker=FuncInvoker0<ThisType,R>::invoke;
		new(&mObj,sizeof(ObjectPlaceHolder)) FuncInvoker0<ThisType,R>(fptr);
	}
	inline void detach(void)
	{
		mObj.clear();
		invoker=NULL;
	}
	inline bool isNull(void) const
	{
		return mObj.isNull() || invoker==NULL;
	}
	inline R operator () (void)const
	{
		return invoker(&mObj);
	}
private:
	ObjectPlaceHolder mObj;
	InvokerType invoker;
};

template<typename Delegation,typename R,typename P1>
struct FuncInvoker1
{
public:
	typedef FuncInvoker1<Delegation,R,P1> ThisType;
	typedef R (*Fptr)(P1);
	FuncInvoker1(Fptr func)
	{
		mFunc=func;
	}
	static inline R invoke(const ObjectPlaceHolder* address,P1 p1)
	{
		const ThisType* pThis=reinterpret_cast<const ThisType*>(address);
		Fptr pFunc=pThis->mFunc;
		return (*pFunc)(p1);
	}
	static inline void* operator new (size_t size,const ObjectPlaceHolder* address,size_t space)
	{
		/*Assert(size<=space);*/
		return (void*)address;
	}
	static inline void operator delete(void*,const ObjectPlaceHolder* address,size_t space)
	{}
private:
	Fptr mFunc;
};

template<typename Delegation,typename T,typename R,typename P1>
struct MemFuncInvoker1
{
public:
	typedef MemFuncInvoker1<Delegation,T,R,P1> ThisType;
	typedef R (T::*Fptr)(P1);
	MemFuncInvoker1(T* obj,Fptr func)
	{
		mObj=obj;
		mFunc=func;
	}
	static inline R invoke(const ObjectPlaceHolder* address,P1 p1)
	{
		const ThisType* pThis=reinterpret_cast<const ThisType*>(address);
		T* pObj=pThis->mObj;
		Fptr pFunc=pThis->mFunc;
		return (pObj->*pFunc)(p1);
	}
	static inline void* operator new (size_t size,const ObjectPlaceHolder* address,size_t space)
	{
		/*Assert(size<=space);*/
		return (void*)address;
	}
	static inline void operator delete(void*,const ObjectPlaceHolder* address,size_t space)
	{}
private:
	T* mObj;
	Fptr mFunc;
};

template<typename R,typename P1>
struct Delegation1
{
public:
	typedef Delegation1<R,P1> ThisType;
	typedef R (*InvokerType)(const ObjectPlaceHolder*,P1);
public:
	Delegation1()
	{
		detach();
	}
	Delegation1(const Delegation1& other)
	{
		mObj=other.mObj;
		invoker=other.invoker;
	}
	template<typename T>
	Delegation1(T* obj,R (T::*fptr)(P1))
	{
		attach(obj,fptr);
	}
	Delegation1(R (*fptr)(P1))
	{
		attach(fptr);
	}
	Delegation1& operator=(const Delegation1& other)
	{
		if(&other==this)
			return *this;
		mObj=other.mObj;
		invoker=other.invoker;
		return *this;
	}
	template<typename T>
	inline void attach(T* obj,R (T::*fptr)(P1))
	{
		invoker=MemFuncInvoker1<ThisType,T,R,P1>::invoke;
		new(&mObj,sizeof(ObjectPlaceHolder)) MemFuncInvoker1<ThisType,T,R,P1>(obj,fptr);
	}
	inline void attach(R (*fptr)(P1))
	{
		invoker=FuncInvoker1<ThisType,R,P1>::invoke;
		new(&mObj,sizeof(ObjectPlaceHolder)) FuncInvoker1<ThisType,R,P1>(fptr);
	}
	inline void detach(void)
	{
		mObj.clear();
		invoker=NULL;
	}
	inline bool isNull(void) const
	{
		return mObj.isNull() || invoker==NULL;
	}
	inline R operator () (P1 p1)const
	{
		return invoker(&mObj,p1);
	}
private:
	ObjectPlaceHolder mObj;
	InvokerType invoker;
};

#define RepeatArg1_1(X) X##1
#define RepeatArg1_2(X) RepeatArg1_1(X),X##2
#define RepeatArg1_3(X) RepeatArg1_2(X),X##3
#define RepeatArg1_4(X) RepeatArg1_3(X),X##4
#define RepeatArg1_5(X) RepeatArg1_4(X),X##5
#define RepeatArg1_6(X) RepeatArg1_5(X),X##6
#define RepeatArg1_7(X) RepeatArg1_6(X),X##7
#define RepeatArg1_8(X) RepeatArg1_7(X),X##8
#define RepeatArg1_9(X) RepeatArg1_8(X),X##9
#define RepeatArg1_10(X) RepeatArg1_9(X),X##10
#define RepeatArg1_11(X) RepeatArg1_10(X),X##11
#define RepeatArg1_12(X) RepeatArg1_11(X),X##12
#define RepeatArg1_13(X) RepeatArg1_12(X),X##13
#define RepeatArg1_14(X) RepeatArg1_13(X),X##14
#define RepeatArg1_15(X) RepeatArg1_14(X),X##15
#define RepeatArg1_16(X) RepeatArg1_15(X),X##16

#define RepeatArg2_1(X,Y) X##1 Y##1
#define RepeatArg2_2(X,Y) RepeatArg2_1(X,Y),X##2 Y##2
#define RepeatArg2_3(X,Y) RepeatArg2_2(X,Y),X##3 Y##3
#define RepeatArg2_4(X,Y) RepeatArg2_3(X,Y),X##4 Y##4
#define RepeatArg2_5(X,Y) RepeatArg2_4(X,Y),X##5 Y##5
#define RepeatArg2_6(X,Y) RepeatArg2_5(X,Y),X##6 Y##6
#define RepeatArg2_7(X,Y) RepeatArg2_6(X,Y),X##7 Y##7
#define RepeatArg2_8(X,Y) RepeatArg2_7(X,Y),X##8 Y##8
#define RepeatArg2_9(X,Y) RepeatArg2_8(X,Y),X##9 Y##9
#define RepeatArg2_10(X,Y) RepeatArg2_9(X,Y),X##10 Y##10
#define RepeatArg2_11(X,Y) RepeatArg2_10(X,Y),X##11 Y##11
#define RepeatArg2_12(X,Y) RepeatArg2_11(X,Y),X##12 Y##12
#define RepeatArg2_13(X,Y) RepeatArg2_12(X,Y),X##13 Y##13
#define RepeatArg2_14(X,Y) RepeatArg2_13(X,Y),X##14 Y##14
#define RepeatArg2_15(X,Y) RepeatArg2_14(X,Y),X##15 Y##15
#define RepeatArg2_16(X,Y) RepeatArg2_15(X,Y),X##16 Y##16

#define DefineDelegation(X)	\
template<typename Delegation,typename R,RepeatArg1_##X(typename P)>\
struct FuncInvoker##X\
{\
public:\
	typedef FuncInvoker##X<Delegation,R,RepeatArg1_##X(P)> ThisType;\
	typedef R (*Fptr)(RepeatArg1_##X(P));\
	FuncInvoker##X(Fptr func)\
	{\
		mFunc=func;\
	}\
	static inline R invoke(const ObjectPlaceHolder* address,RepeatArg2_##X(P,p))\
	{\
		const ThisType* pThis=reinterpret_cast<const ThisType*>(address);\
		Fptr pFunc=pThis->mFunc;\
		return (*pFunc)(RepeatArg1_##X(p));\
	}\
	static inline void* operator new (size_t size,const ObjectPlaceHolder* address,size_t space)\
	{\
		/*Assert(size<=space);*/\
		return (void*)address;\
	}\
	static inline void operator delete(void*,const ObjectPlaceHolder* address,size_t space)\
	{}\
private:\
	Fptr mFunc;\
};\
\
template<typename Delegation,typename T,typename R,RepeatArg1_##X(typename P)>\
struct MemFuncInvoker##X\
{\
public:\
	typedef MemFuncInvoker##X<Delegation,T,R,RepeatArg1_##X(P)> ThisType;\
	typedef R (T::*Fptr)(RepeatArg1_##X(P));\
	MemFuncInvoker##X(T* obj,Fptr func)\
	{\
		mObj=obj;\
		mFunc=func;\
	}\
	static inline R invoke(const ObjectPlaceHolder* address,RepeatArg2_##X(P,p))\
	{\
		const ThisType* pThis=reinterpret_cast<const ThisType*>(address);\
		T* pObj=pThis->mObj;\
		Fptr pFunc=pThis->mFunc;\
		return (pObj->*pFunc)(RepeatArg1_##X(p));\
	}\
	static inline void* operator new (size_t size,const ObjectPlaceHolder* address,size_t space)\
	{\
		/*Assert(size<=space);*/\
		return (void*)address;\
	}\
	static inline void operator delete(void*,const ObjectPlaceHolder* address,size_t space)\
	{}\
private:\
	T* mObj;\
	Fptr mFunc;\
};\
\
template<typename R,RepeatArg1_##X(typename P)>\
struct Delegation##X\
{\
public:\
	typedef Delegation##X<R,RepeatArg1_##X(P)> ThisType;\
	typedef R (*InvokerType)(const ObjectPlaceHolder*,RepeatArg1_##X(P));\
public:\
	Delegation##X()\
	{\
		detach();\
	}\
	Delegation##X(const Delegation##X& other)\
	{\
		mObj=other.mObj;\
		invoker=other.invoker;\
	}\
	template<typename T>\
	Delegation##X(T* obj,R (T::*fptr)(RepeatArg1_##X(P)))\
	{\
		attach(obj,fptr);\
	}\
	Delegation##X(R (*fptr)(RepeatArg1_##X(P)))\
	{\
		attach(fptr);\
	}\
	Delegation##X& operator=(const Delegation##X& other)\
	{\
		if(&other==this)\
			return *this;\
		mObj=other.mObj;\
		invoker=other.invoker;\
		return *this;\
	}\
	template<typename T>\
	inline void attach(T* obj,R (T::*fptr)(RepeatArg1_##X(P)))\
	{\
		invoker=MemFuncInvoker##X<ThisType,T,R,RepeatArg1_##X(P)>::invoke;\
		new(&mObj,sizeof(ObjectPlaceHolder)) MemFuncInvoker##X<ThisType,T,R,RepeatArg1_##X(P)>(obj,fptr);\
	}\
	inline void attach(R (*fptr)(RepeatArg1_##X(P)))\
	{\
		invoker=FuncInvoker##X<ThisType,R,RepeatArg1_##X(P)>::invoke;\
		new(&mObj,sizeof(ObjectPlaceHolder)) FuncInvoker##X<ThisType,R,RepeatArg1_##X(P)>(fptr);\
	}\
	inline void detach(void)\
	{\
		mObj.clear();\
		invoker=NULL;\
	}\
	inline bool isNull(void) const\
	{\
		return mObj.isNull() || invoker==NULL;\
	}\
	inline R operator () (RepeatArg2_##X(P,p))const\
	{\
		return invoker(&mObj,RepeatArg1_##X(p));\
	}\
private:\
	ObjectPlaceHolder mObj;\
	InvokerType invoker;\
};

DefineDelegation(2)
DefineDelegation(3)
DefineDelegation(4)
DefineDelegation(5)
DefineDelegation(6)
DefineDelegation(7)
DefineDelegation(8)
DefineDelegation(9)
DefineDelegation(10)
DefineDelegation(11)
DefineDelegation(12)
DefineDelegation(13)
DefineDelegation(14)
DefineDelegation(15)
DefineDelegation(16)

#endif //__Delegation_H__