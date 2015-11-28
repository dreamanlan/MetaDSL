#ifndef __TSNPRINTF_H__
#define __TSNPRINTF_H__

#include "StringFormat.h"

//#define USE_OLD_SNPRINTF
//
#define USE_OLD_SPRINTF

#ifndef USE_OLD_SPRINTF

#define sprintf cant_use_sprintf_in_our_project_you_should_use_tsnprintf_instead

#endif //USE_OLD_SPRINTF

#ifndef USE_OLD_SNPRINTF

#define DEF_SNPRINTF(X)	\
template<ParserRepeatArg1_##X(typename P)>\
inline INT snprintf_(CHAR* buf, size_t size, CHAR const* msg,ParserRepeatArg2_##X(P,p))\
{\
	if(NULL==buf || NULL==msg || size<1) return 0;\
	StringParser fmt(buf,(INT)size,msg);\
	fmt.Format(ParserRepeatArg1_##X(p));\
	buf[size-1]='\0';\
	return fmt.GetLength();\
}

inline int snprintf_(char* buf, size_t size, char const* msg)
{
	if(NULL==buf || NULL==msg || size<1) return 0;
	StringParser fmt(buf,(int)size,msg);
	fmt.Format();
	buf[size-1]='\0';
	return fmt.GetLength();
}

DEF_SNPRINTF(1)
DEF_SNPRINTF(2)
DEF_SNPRINTF(3)
DEF_SNPRINTF(4)
DEF_SNPRINTF(5)
DEF_SNPRINTF(6)
DEF_SNPRINTF(7)
DEF_SNPRINTF(8)
DEF_SNPRINTF(9)
DEF_SNPRINTF(10)
DEF_SNPRINTF(11)
DEF_SNPRINTF(12)
DEF_SNPRINTF(13)
DEF_SNPRINTF(14)
DEF_SNPRINTF(15)
DEF_SNPRINTF(16)
DEF_SNPRINTF(17)
DEF_SNPRINTF(18)
DEF_SNPRINTF(19)
DEF_SNPRINTF(20)
DEF_SNPRINTF(21)
DEF_SNPRINTF(22)
DEF_SNPRINTF(23)
DEF_SNPRINTF(24)
DEF_SNPRINTF(25)
DEF_SNPRINTF(26)
DEF_SNPRINTF(27)
DEF_SNPRINTF(28)
DEF_SNPRINTF(29)
DEF_SNPRINTF(30)
DEF_SNPRINTF(31)
DEF_SNPRINTF(32)
DEF_SNPRINTF(33)
DEF_SNPRINTF(34)

#undef	tsnprintf
#define	tsnprintf snprintf_

#endif //USE_OLD_SNPRINTF

#define t_strncpy StringFormatUtility::MyStrNCpy

inline void nullprintf(const char*,...){}

#endif //__TSNPRINTF_H__