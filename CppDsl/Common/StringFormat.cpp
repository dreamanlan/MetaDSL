#include "StringFormat.h"

namespace StringFormatUtility
{
	const char* format_string="cCdiouxXeEfgGaAnpsS";

	int CopyBuffer(char* dest,int& pos,int size,const char* src)
	{
		if(NULL==dest || NULL==src)
			return FALSE;
		int len=(int)strlen(src);
		if(pos+len>=size)
			return FALSE;
		memcpy(dest+pos,src,len);
		pos+=len;
		dest[pos]=0;
		return TRUE;
	}
}

//使用方（snprintf_）保证buf、fmt不会为空，StringFormat类及其实现辅助都不再检查这2个指针是否为空。
StringParser::StringParser(char* buf,int size,const char* fmt):m_pBuffer(buf),m_BufLen(size),m_pFmt(fmt)
{
	m_FmtLen=(int)strlen(fmt);
	m_BufPos=0;
	m_FmtPos=0;
	m_FmtIndex=0;
}

const char* StringParser::ParseToNextFormat(void)
{
	int len=m_FmtLen;
	for(int i=m_FmtPos;i<len;++i)
	{
		if(m_pFmt[i]=='%')
		{
			if(i+1<len && m_pFmt[i+1]=='%')
			{
				++i;
				if(m_BufPos<m_BufLen-1)
				{
					m_pBuffer[m_BufPos]=m_pFmt[i];
					++m_BufPos;
				}
				else
				{
					break;
				}
			}
			else
			{
				++m_FmtIndex;
				for(int j=i;j<len;++j)
				{
					m_TempFmt[j-i]=m_pFmt[j];
					const char* p=strchr(StringFormatUtility::format_string,m_pFmt[j]);
					if(NULL!=p)
					{
						m_FmtPos=j+1;
						m_TempFmt[j-i+1]=0;
						return m_TempFmt;
					}
				}
				break;
			}
		}
		else
		{
			if(m_BufPos<m_BufLen-1)
			{
				m_pBuffer[m_BufPos]=m_pFmt[i];
				++m_BufPos;
			}
			else
			{
				break;
			}
		}
	}
	m_FmtPos=len;
	return NULL;
}

void StringParser::ParseToEnd(void)
{
	int len=m_FmtLen;
	for(int i=m_FmtPos;i<len;++i)
	{
		if(m_pFmt[i]=='%')
		{
			if(i+1<len && m_pFmt[i+1]=='%')
			{
				++i;
				if(m_BufPos<m_BufLen-1)
				{
					m_pBuffer[m_BufPos]=m_pFmt[i];
					++m_BufPos;
				}
				else
				{
					break;
				}
			}
			else
			{
				++m_FmtIndex;
				for(int j=i;j<len;++j)
				{
					const char* p=strchr(StringFormatUtility::format_string,m_pFmt[j]);
					if(NULL!=p)
					{
						if(FALSE==StringFormatUtility::BasicValue2String(m_pBuffer,m_BufPos,m_BufLen," @format:%d,unexpected_format ",m_FmtIndex-1))
						{
							m_FmtPos=len;
							return;
						}
						i=j;
						break;
					}
				}
			}
		}
		else
		{
			if(m_BufPos<m_BufLen-1)
			{
				m_pBuffer[m_BufPos]=m_pFmt[i];
				++m_BufPos;
			}
			else
			{
				break;
			}
		}
	}
	m_FmtPos=len;
	if(m_BufPos<m_BufLen-1)
		m_pBuffer[m_BufPos]='\0';
	else if(m_BufLen>0)
		m_pBuffer[m_BufLen-1]='\0';
	else
	{
		//error
	}
}