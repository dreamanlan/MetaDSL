#include "StringFormat.h"

namespace StringFormatUtility
{
    const char* format_string = "cCdiouxXeEfgGaAnpsS";

    int CopyBuffer(char* dest, int& pos, int size, const char* src)
    {
        if (nullptr == dest || nullptr == src)
            return FALSE;
        int len = (int)strlen(src);
        if (pos + len >= size)
            return FALSE;
        memcpy(dest + pos, src, len);
        pos += len;
        dest[pos] = 0;
        return TRUE;
    }
}

//The user (snprintf_) guarantees that buf and fmt will not be empty, and neither
//the StringFormat class nor its implementation assistance will ever check whether
//the two Pointers are empty.
StringParser::StringParser(char* buf, int size, const char* fmt) :m_pBuffer(buf), m_BufLen(size), m_pFmt(fmt)
{
    m_FmtLen = (int)strlen(fmt);
    m_BufPos = 0;
    m_FmtPos = 0;
    m_FmtIndex = 0;
}

const char* StringParser::ParseToNextFormat()
{
    int len = m_FmtLen;
    for (int i = m_FmtPos; i < len; ++i) {
        if (m_pFmt[i] == '%') {
            if (i + 1 < len && m_pFmt[i + 1] == '%') {
                ++i;
                if (m_BufPos < m_BufLen - 1) {
                    m_pBuffer[m_BufPos] = m_pFmt[i];
                    ++m_BufPos;
                }
                else {
                    break;
                }
            }
            else {
                ++m_FmtIndex;
                for (int j = i; j < len; ++j) {
                    m_TempFmt[j - i] = m_pFmt[j];
                    const char* p = strchr(StringFormatUtility::format_string, m_pFmt[j]);
                    if (nullptr != p) {
                        m_FmtPos = j + 1;
                        m_TempFmt[j - i + 1] = 0;
                        return m_TempFmt;
                    }
                }
                break;
            }
        }
        else {
            if (m_BufPos < m_BufLen - 1) {
                m_pBuffer[m_BufPos] = m_pFmt[i];
                ++m_BufPos;
            }
            else {
                break;
            }
        }
    }
    m_FmtPos = len;
    return nullptr;
}

void StringParser::ParseToEnd()
{
    int len = m_FmtLen;
    for (int i = m_FmtPos; i < len; ++i) {
        if (m_pFmt[i] == '%') {
            if (i + 1 < len && m_pFmt[i + 1] == '%') {
                ++i;
                if (m_BufPos < m_BufLen - 1) {
                    m_pBuffer[m_BufPos] = m_pFmt[i];
                    ++m_BufPos;
                }
                else {
                    break;
                }
            }
            else {
                ++m_FmtIndex;
                for (int j = i; j < len; ++j) {
                    const char* p = strchr(StringFormatUtility::format_string, m_pFmt[j]);
                    if (nullptr != p) {
                        if (FALSE == StringFormatUtility::BasicValue2String(m_pBuffer, m_BufPos, m_BufLen, " @format:%d,unexpected_format ", m_FmtIndex - 1)) {
                            m_FmtPos = len;
                            return;
                        }
                        i = j;
                        break;
                    }
                }
            }
        }
        else {
            if (m_BufPos < m_BufLen - 1) {
                m_pBuffer[m_BufPos] = m_pFmt[i];
                ++m_BufPos;
            }
            else {
                break;
            }
        }
    }
    m_FmtPos = len;
    if (m_BufPos < m_BufLen - 1)
        m_pBuffer[m_BufPos] = '\0';
    else if (m_BufLen > 0)
        m_pBuffer[m_BufLen - 1] = '\0';
    else {
        //error
    }
}