#ifndef __STRINGFORMAT_H__
#define __STRINGFORMAT_H__

#include "BaseType.h"
#include "StaticCheck.h"

//#define VALUE64_FORMAT_AS_ERROR

#define STRING_PARSER_BUFF_TEMP	4096
#define STRING_PARSER_FMT_TEMP	4096

#define ParserRepeatArg1_1(X) X##1
#define ParserRepeatArg1_2(X) ParserRepeatArg1_1(X),X##2
#define ParserRepeatArg1_3(X) ParserRepeatArg1_2(X),X##3
#define ParserRepeatArg1_4(X) ParserRepeatArg1_3(X),X##4
#define ParserRepeatArg1_5(X) ParserRepeatArg1_4(X),X##5
#define ParserRepeatArg1_6(X) ParserRepeatArg1_5(X),X##6
#define ParserRepeatArg1_7(X) ParserRepeatArg1_6(X),X##7
#define ParserRepeatArg1_8(X) ParserRepeatArg1_7(X),X##8
#define ParserRepeatArg1_9(X) ParserRepeatArg1_8(X),X##9
#define ParserRepeatArg1_10(X) ParserRepeatArg1_9(X),X##10
#define ParserRepeatArg1_11(X) ParserRepeatArg1_10(X),X##11
#define ParserRepeatArg1_12(X) ParserRepeatArg1_11(X),X##12
#define ParserRepeatArg1_13(X) ParserRepeatArg1_12(X),X##13
#define ParserRepeatArg1_14(X) ParserRepeatArg1_13(X),X##14
#define ParserRepeatArg1_15(X) ParserRepeatArg1_14(X),X##15
#define ParserRepeatArg1_16(X) ParserRepeatArg1_15(X),X##16
#define ParserRepeatArg1_17(X) ParserRepeatArg1_16(X),X##17
#define ParserRepeatArg1_18(X) ParserRepeatArg1_17(X),X##18
#define ParserRepeatArg1_19(X) ParserRepeatArg1_18(X),X##19
#define ParserRepeatArg1_20(X) ParserRepeatArg1_19(X),X##20
#define ParserRepeatArg1_21(X) ParserRepeatArg1_20(X),X##21
#define ParserRepeatArg1_22(X) ParserRepeatArg1_21(X),X##22
#define ParserRepeatArg1_23(X) ParserRepeatArg1_22(X),X##23
#define ParserRepeatArg1_24(X) ParserRepeatArg1_23(X),X##24
#define ParserRepeatArg1_25(X) ParserRepeatArg1_24(X),X##25
#define ParserRepeatArg1_26(X) ParserRepeatArg1_25(X),X##26
#define ParserRepeatArg1_27(X) ParserRepeatArg1_26(X),X##27
#define ParserRepeatArg1_28(X) ParserRepeatArg1_27(X),X##28
#define ParserRepeatArg1_29(X) ParserRepeatArg1_28(X),X##29
#define ParserRepeatArg1_30(X) ParserRepeatArg1_29(X),X##30
#define ParserRepeatArg1_31(X) ParserRepeatArg1_30(X),X##31
#define ParserRepeatArg1_32(X) ParserRepeatArg1_31(X),X##32
#define ParserRepeatArg1_33(X) ParserRepeatArg1_32(X),X##33
#define ParserRepeatArg1_34(X) ParserRepeatArg1_33(X),X##34

#define ParserRepeatArg2_1(X,Y) X##1 Y##1
#define ParserRepeatArg2_2(X,Y) ParserRepeatArg2_1(X,Y),X##2 Y##2
#define ParserRepeatArg2_3(X,Y) ParserRepeatArg2_2(X,Y),X##3 Y##3
#define ParserRepeatArg2_4(X,Y) ParserRepeatArg2_3(X,Y),X##4 Y##4
#define ParserRepeatArg2_5(X,Y) ParserRepeatArg2_4(X,Y),X##5 Y##5
#define ParserRepeatArg2_6(X,Y) ParserRepeatArg2_5(X,Y),X##6 Y##6
#define ParserRepeatArg2_7(X,Y) ParserRepeatArg2_6(X,Y),X##7 Y##7
#define ParserRepeatArg2_8(X,Y) ParserRepeatArg2_7(X,Y),X##8 Y##8
#define ParserRepeatArg2_9(X,Y) ParserRepeatArg2_8(X,Y),X##9 Y##9
#define ParserRepeatArg2_10(X,Y) ParserRepeatArg2_9(X,Y),X##10 Y##10
#define ParserRepeatArg2_11(X,Y) ParserRepeatArg2_10(X,Y),X##11 Y##11
#define ParserRepeatArg2_12(X,Y) ParserRepeatArg2_11(X,Y),X##12 Y##12
#define ParserRepeatArg2_13(X,Y) ParserRepeatArg2_12(X,Y),X##13 Y##13
#define ParserRepeatArg2_14(X,Y) ParserRepeatArg2_13(X,Y),X##14 Y##14
#define ParserRepeatArg2_15(X,Y) ParserRepeatArg2_14(X,Y),X##15 Y##15
#define ParserRepeatArg2_16(X,Y) ParserRepeatArg2_15(X,Y),X##16 Y##16
#define ParserRepeatArg2_17(X,Y) ParserRepeatArg2_16(X,Y),X##17 Y##17
#define ParserRepeatArg2_18(X,Y) ParserRepeatArg2_17(X,Y),X##18 Y##18
#define ParserRepeatArg2_19(X,Y) ParserRepeatArg2_18(X,Y),X##19 Y##19
#define ParserRepeatArg2_20(X,Y) ParserRepeatArg2_19(X,Y),X##20 Y##20
#define ParserRepeatArg2_21(X,Y) ParserRepeatArg2_20(X,Y),X##21 Y##21
#define ParserRepeatArg2_22(X,Y) ParserRepeatArg2_21(X,Y),X##22 Y##22
#define ParserRepeatArg2_23(X,Y) ParserRepeatArg2_22(X,Y),X##23 Y##23
#define ParserRepeatArg2_24(X,Y) ParserRepeatArg2_23(X,Y),X##24 Y##24
#define ParserRepeatArg2_25(X,Y) ParserRepeatArg2_24(X,Y),X##25 Y##25
#define ParserRepeatArg2_26(X,Y) ParserRepeatArg2_25(X,Y),X##26 Y##26
#define ParserRepeatArg2_27(X,Y) ParserRepeatArg2_26(X,Y),X##27 Y##27
#define ParserRepeatArg2_28(X,Y) ParserRepeatArg2_27(X,Y),X##28 Y##28
#define ParserRepeatArg2_29(X,Y) ParserRepeatArg2_28(X,Y),X##29 Y##29
#define ParserRepeatArg2_30(X,Y) ParserRepeatArg2_29(X,Y),X##30 Y##30
#define ParserRepeatArg2_31(X,Y) ParserRepeatArg2_30(X,Y),X##31 Y##31
#define ParserRepeatArg2_32(X,Y) ParserRepeatArg2_31(X,Y),X##32 Y##32
#define ParserRepeatArg2_33(X,Y) ParserRepeatArg2_32(X,Y),X##33 Y##33
#define ParserRepeatArg2_34(X,Y) ParserRepeatArg2_33(X,Y),X##34 Y##34

#define DEF_PARSER_FORMAT_IMPL(X,decX)	\
template<ParserRepeatArg1_##X(typename P)>	\
inline void _Format(ParserRepeatArg2_##X(P,p))	\
{\
	_Format(ParserRepeatArg1_##decX(p));\
	const char* fmt=ParseToNextFormat();\
	if(nullptr!=fmt)\
		StringFormatUtility::Value2String(m_pBuffer,m_BufPos,m_BufLen,fmt,p##X,decX);\
  	else\
		StringFormatUtility::Value2String(m_pBuffer,m_BufPos,m_BufLen,"",p##X,decX);\
}

#define DEF_PARSER_FORMAT(X)	\
template<ParserRepeatArg1_##X(typename P)>	\
inline void Format(ParserRepeatArg2_##X(P,p))	\
{\
	_Format(ParserRepeatArg1_##X(p));\
	ParseToEnd();\
}

#if defined(__WINDOWS__)
#define		t_vsnprintf		_vsnprintf
#define		t_snprintf		_snprintf
#elif defined(__LINUX__)
#define		t_vsnprintf		vsnprintf
#define		t_snprintf		snprintf
#endif

namespace StringFormatUtility
{
    int CopyBuffer(char* dest, int& pos, int size, const char* src);

    inline void MyTrimRight(char* dest)
    {
        if (nullptr == dest)
            return;
        size_t len = strlen(dest);
        for (int i = (int)len - 1; i >= 0; --i) {
            if (static_cast<unsigned char>(dest[i]) <= 32)
                dest[i] = 0;
            else
                break;
        }
    }

    inline char* MyStrNCpy(char* dest, const char* src, size_t len)
    {
        if (nullptr == dest || nullptr == src)
            return nullptr;
        char* res = strncpy(dest, src, len);
        if (len <= strlen(src)) {
            //发生字符串截断时，补一个空字符
            dest[len] = 0;
        }
        return res;
    }

    template<typename T>
    inline int BasicValue2String(char* dest, int& pos, int size, const char* fmt, T t)
    {
        //基础格式化处理
        if (pos >= size - 1)
            return FALSE;
        int r = t_snprintf(dest + pos, size - pos, fmt, t);
        if (r >= 0 && pos + r < size)
            pos += r;
        else
            pos = size - 1;
        return (r >= 0 ? TRUE : FALSE);
    }

    template<typename T>
    struct _impl_for_format_check
    {
        enum { value = 0 };
        static inline int format(char* dest, int& pos, int size, const char* fmt, T t, int argIndex)
        {
            int len = (int)strlen(fmt);
            if (len <= 0) {
                return BasicValue2String(dest, pos, size, " @format:%d,unexpected_value ", argIndex);
            }
            else if (fmt[len - 1] == 's' || fmt[len - 1] == 'S' || fmt[len - 1] == 'n' || fmt[len - 1] == 'p') {
                return BasicValue2String(dest, pos, size, " @format:%d,value_as_pointer ", argIndex);
            }
            else {
                return BasicValue2String(dest, pos, size, fmt, t);
            }
        }
    };

    template<typename T>
    struct _impl_for_format_check < T* >
    {
        enum { value = 1 };
        static inline int format(char* dest, int& pos, int size, const char* fmt, T* t, int argIndex)
        {
            int len = (int)strlen(fmt);
            if (len <= 0) {
                return BasicValue2String(dest, pos, size, " @format:%d,unexpected_pointer ", argIndex);
            }
            else if (fmt[len - 1] != 's' && fmt[len - 1] != 'S' && fmt[len - 1] != 'n' && fmt[len - 1] != 'p') {
                return BasicValue2String(dest, pos, size, " @format:%d,pointer_as_value ", argIndex);
            }
            else {
                return BasicValue2String(dest, pos, size, fmt, t);
            }
        }
    };

    template<typename T>
    inline int GeneralValue2String(char* dest, int& pos, int size, const char* fmt, T t, int argIndex)
    {
        return _impl_for_format_check<T>::format(dest, pos, size, fmt, t, argIndex);
    }

    template<typename T, int k>
    struct _impl_for_64
    {
        static inline int format(char* dest, int& pos, int size, const char* fmt, T t, int argIndex)
        {
            return GeneralValue2String(dest, pos, size, fmt, t, argIndex);
        }
    };

    template<typename T>
    struct _impl_for_64 < T, 8 >
    {
        static inline int format(char* dest, int& pos, int size, const char* fmt, T t, int argIndex)
        {
            if (pos >= size - 1)
                return FALSE;
            unsigned long long val;
            memcpy(&val, &t, sizeof(val));
            int r = 0;
            int len = (int)strlen(fmt);
            if (len <= 0) {
                return BasicValue2String(dest, pos, size, " @format:%d,unexpected_value ", argIndex);
            }
            else if (fmt[len - 1] == 's' || fmt[len - 1] == 'S' || fmt[len - 1] == 'n' || fmt[len - 1] == 'p') {
                return BasicValue2String(dest, pos, size, " @format:%d,value_as_pointer ", argIndex);
            }
            else if (fmt[len - 1] == 'x' || fmt[len - 1] == 'X') {
                r = t_snprintf(dest + pos, size - pos, "%16.16llX", val);
            }
            else if (fmt[len - 1] == 'u') {
                r = t_snprintf(dest + pos, size - pos, "%llu", val);
            }
            else if (fmt[len - 1] == 'o') {
                r = t_snprintf(dest + pos, size - pos, "%llo", val);
            }
            else if (fmt[len - 1] == 'i') {
                r = t_snprintf(dest + pos, size - pos, "%lli", val);
            }
            else {
                r = t_snprintf(dest + pos, size - pos, "%lld", (long long)val);
            }
            if (r >= 0 && pos + r < size)
                pos += r;
            else
                pos = size - 1;
            return (r >= 0 ? TRUE : FALSE);
        }
    };
    template<typename T>
    struct _impl_for_64 < T*, 8 >
    {
        static inline int format(char* dest, int& pos, int size, const char* fmt, T* t, int argIndex)
        {
            return GeneralValue2String(dest, pos, size, fmt, t, argIndex);
        }
    };

    template<>
    struct _impl_for_64 < double, 8 >
    {
        static inline int format(char* dest, int& pos, int size, const char* fmt, double t, int argIndex)
        {
            int len = (int)strlen(fmt);
            if (len <= 0) {
                return BasicValue2String(dest, pos, size, " @format:%d,unexpected_value ", argIndex);
            }
            else if (fmt[len - 1] == 'f' || fmt[len - 1] == 'e' || fmt[len - 1] == 'E' || fmt[len - 1] == 'g' || fmt[len - 1] == 'G' || fmt[len - 1] == 'a' || fmt[len - 1] == 'A') {
                return BasicValue2String(dest, pos, size, fmt, t);
            }
            else {
                return BasicValue2String(dest, pos, size, "%f", t);
            }
        }
    };

    template<typename T>
    inline int Value2String(char* dest, int& pos, int size, const char* fmt, T t, int argIndex)
    {
#ifdef VALUE64_FORMAT_AS_ERROR
        dest, pos, size, fmt, t, argIndex;
        STATIC_CHECK((sizeof(T) <= 4), cant_use_64bit_value_as_printf_arg);
        return TRUE;
#else
        return _impl_for_64<T, sizeof(T)>::format(dest, pos, size, fmt, t, argIndex);
#endif
    }
}

class StringParser
{
public:
    inline void	Format()
    {
        ParseToEnd();
    }
    DEF_PARSER_FORMAT(1);
    DEF_PARSER_FORMAT(2);
    DEF_PARSER_FORMAT(3);
    DEF_PARSER_FORMAT(4);
    DEF_PARSER_FORMAT(5);
    DEF_PARSER_FORMAT(6);
    DEF_PARSER_FORMAT(7);
    DEF_PARSER_FORMAT(8);
    DEF_PARSER_FORMAT(9);
    DEF_PARSER_FORMAT(10);
    DEF_PARSER_FORMAT(11);
    DEF_PARSER_FORMAT(12);
    DEF_PARSER_FORMAT(13);
    DEF_PARSER_FORMAT(14);
    DEF_PARSER_FORMAT(15);
    DEF_PARSER_FORMAT(16);
    DEF_PARSER_FORMAT(17);
    DEF_PARSER_FORMAT(18);
    DEF_PARSER_FORMAT(19);
    DEF_PARSER_FORMAT(20);
    DEF_PARSER_FORMAT(21);
    DEF_PARSER_FORMAT(22);
    DEF_PARSER_FORMAT(23);
    DEF_PARSER_FORMAT(24);
    DEF_PARSER_FORMAT(25);
    DEF_PARSER_FORMAT(26);
    DEF_PARSER_FORMAT(27);
    DEF_PARSER_FORMAT(28);
    DEF_PARSER_FORMAT(29);
    DEF_PARSER_FORMAT(30);
    DEF_PARSER_FORMAT(31);
    DEF_PARSER_FORMAT(32);
    DEF_PARSER_FORMAT(33);
    DEF_PARSER_FORMAT(34);
public:
    //使用方（snprintf_）保证buf、fmt不会为空，StringFormat类及其实现辅助都不再检查这2个指针是否为空。
    StringParser(char* buf, int size, const char* fmt);
    inline int GetLength()const { return m_BufPos; }
private:
    template<typename P1>
    inline void	_Format(P1 p1)
    {
        const char* fmt = ParseToNextFormat();
        if (nullptr != fmt)
            StringFormatUtility::Value2String(m_pBuffer, m_BufPos, m_BufLen, fmt, p1, 0);
        else
            StringFormatUtility::Value2String(m_pBuffer, m_BufPos, m_BufLen, "", p1, 0);
    };
    DEF_PARSER_FORMAT_IMPL(2, 1);
    DEF_PARSER_FORMAT_IMPL(3, 2);
    DEF_PARSER_FORMAT_IMPL(4, 3);
    DEF_PARSER_FORMAT_IMPL(5, 4);
    DEF_PARSER_FORMAT_IMPL(6, 5);
    DEF_PARSER_FORMAT_IMPL(7, 6);
    DEF_PARSER_FORMAT_IMPL(8, 7);
    DEF_PARSER_FORMAT_IMPL(9, 8);
    DEF_PARSER_FORMAT_IMPL(10, 9);
    DEF_PARSER_FORMAT_IMPL(11, 10);
    DEF_PARSER_FORMAT_IMPL(12, 11);
    DEF_PARSER_FORMAT_IMPL(13, 12);
    DEF_PARSER_FORMAT_IMPL(14, 13);
    DEF_PARSER_FORMAT_IMPL(15, 14);
    DEF_PARSER_FORMAT_IMPL(16, 15);
    DEF_PARSER_FORMAT_IMPL(17, 16);
    DEF_PARSER_FORMAT_IMPL(18, 17);
    DEF_PARSER_FORMAT_IMPL(19, 18);
    DEF_PARSER_FORMAT_IMPL(20, 19);
    DEF_PARSER_FORMAT_IMPL(21, 20);
    DEF_PARSER_FORMAT_IMPL(22, 21);
    DEF_PARSER_FORMAT_IMPL(23, 22);
    DEF_PARSER_FORMAT_IMPL(24, 23);
    DEF_PARSER_FORMAT_IMPL(25, 24);
    DEF_PARSER_FORMAT_IMPL(26, 25);
    DEF_PARSER_FORMAT_IMPL(27, 26);
    DEF_PARSER_FORMAT_IMPL(28, 27);
    DEF_PARSER_FORMAT_IMPL(29, 28);
    DEF_PARSER_FORMAT_IMPL(30, 29);
    DEF_PARSER_FORMAT_IMPL(31, 30);
    DEF_PARSER_FORMAT_IMPL(32, 31);
    DEF_PARSER_FORMAT_IMPL(33, 32);
    DEF_PARSER_FORMAT_IMPL(34, 33);
private:
    const char* ParseToNextFormat();
    void		ParseToEnd();
private:
    char* m_pBuffer;
    const char* m_pFmt;
    char		m_TempFmt[STRING_PARSER_FMT_TEMP];
    int			m_BufPos;
    int			m_FmtPos;
    int			m_FmtIndex;
    int			m_BufLen;
    int			m_FmtLen;
};

#endif //__STRINGFORMAT_H__