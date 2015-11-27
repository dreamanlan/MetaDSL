/*****************************************************************************

SlkToken.cpp

******************************************************************************/
#include "SlkParse.h"

//mIterator,mErrorInfo由构造函数的引用参数传入，不会为空。所以使用时不再检查是否为空。

static inline BOOL myisdigit(CHAR c, BOOL isHex)
{
  BOOL ret = FALSE;
  if (TRUE == isHex) {
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
      ret = TRUE;
    else
      ret = FALSE;
  } else {
    if ((c >= '0' && c <= '9'))
      ret = TRUE;
    else
      ret = FALSE;
  }
  return ret;
}

void SlkToken::getOperatorToken(void)
{
  switch (*mIterator) {
  case '+':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '+' || *mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    }
  }
    break;
  case '-':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '-' || *mIterator == '=' || *mIterator == '>') {
      pushTokenChar(*mIterator);
      ++mIterator;
    }
  }
    break;
  case '>':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    } else if (*mIterator == '>') {
      pushTokenChar(*mIterator);
      ++mIterator;
      if (*mIterator == '>') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
      if (*mIterator == '=') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
    }
  }
    break;
  case '<':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    } else if (*mIterator == '<') {
      pushTokenChar(*mIterator);
      ++mIterator;
      if (*mIterator == '=') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
    }
  }
    break;
  case '&':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    } else if (*mIterator == '&') {
      pushTokenChar(*mIterator);
      ++mIterator;
      if (*mIterator == '=') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
    }
  }
    break;
  case '|':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    } else if (*mIterator == '|') {
      pushTokenChar(*mIterator);
      ++mIterator;
      if (*mIterator == '=') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
    }
  }
    break;
  case '=':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=' || *mIterator == '>') {
      pushTokenChar(*mIterator);
      ++mIterator;
    }
  }
    break;
  case '!':
  case '^':
  case '*':
  case '/':
  case '%':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    }
  }
    break;
  default:
  {
    pushTokenChar(*mIterator);
    ++mIterator;
  }
    break;
  }
  endToken();
}

SHORT SlkToken::getOperatorTokenValue(void)const
{
  const CHAR* pOperator = mCurToken;
  const CHAR* pLastToken = mLastToken;
  BOOL lastIsOperator = TRUE;
  if (pLastToken && pLastToken[0]) {
    if (isDelimiter(pLastToken[0])) {
      lastIsOperator = TRUE;
    } else {
      lastIsOperator = isOperator(pLastToken[0]);
    }
  }
  SHORT val = OP_TOKEN_0_;
  if (pOperator && pOperator[0]) {
    if ((pOperator[0] == '?' || pOperator[0] == ':') && pOperator[1] == '\0') {
      val = OP_TOKEN_1_;
    } else if (pOperator[0] == '|' && pOperator[1] == '|') {
      val = OP_TOKEN_2_;
    } else if (pOperator[0] == '&' && pOperator[1] == '&') {
      val = OP_TOKEN_3_;
    } else if (pOperator[0] == '|' && pOperator[1] == '\0') {
      val = OP_TOKEN_4_;
    } else if (pOperator[0] == '^' && pOperator[1] == '\0') {
      val = OP_TOKEN_5_;
    } else if (pOperator[0] == '&' && pOperator[1] == '\0') {
      val = OP_TOKEN_6_;
    } else if ((pOperator[0] == '=' || pOperator[0] == '!') && pOperator[1] == '=') {
      val = OP_TOKEN_7_;
    } else if ((pOperator[0] == '<' || pOperator[0] == '>') && (pOperator[1] == '=' || pOperator[1] == '\0')) {
      val = OP_TOKEN_8_;
    } else if ((pOperator[0] == '<' && pOperator[1] == '<') || (pOperator[0] == '>' && pOperator[1] == '>') || (pOperator[0] == '>' && pOperator[1] == '>' && pOperator[2] == '>')) {
      val = OP_TOKEN_9_;
    } else if ((pOperator[0] == '+' || pOperator[0] == '-') && pOperator[1] == '\0') {
      if (lastIsOperator)
        val = OP_TOKEN_12_;
      else
        val = OP_TOKEN_10_;
    } else if ((pOperator[0] == '*' || pOperator[0] == '/' || pOperator[0] == '%') && pOperator[1] == '\0') {
      val = OP_TOKEN_11_;
    } else if ((pOperator[0] == '+' && pOperator[1] == '+') || (pOperator[0] == '-' && pOperator[1] == '-') || (pOperator[0] == '~' && pOperator[1] == '\0') || (pOperator[0] == '!' && pOperator[1] == '\0')) {
      val = OP_TOKEN_12_;
    } else {
      val = OP_TOKEN_0_;
    }
  }
  return val;
}

BOOL SlkToken::isWhiteSpace(CHAR c) const
{
  if (0 == c)
    return FALSE;
  else
    return (0 != strchr(mWhiteSpaces, c) ? TRUE : FALSE);
}

BOOL SlkToken::isOperator(CHAR c) const
{
  if (0 == c)
    return FALSE;
  else
    return (0 != strchr(mOperators, c) ? TRUE : FALSE);
}

BOOL SlkToken::isDelimiter(CHAR c) const
{
  if (0 == c)
    return FALSE;
  else
    return (0 != strchr(mDelimiters, c) ? TRUE : FALSE);
}

SHORT SlkToken::get(void)
{
  if (NULL == mSource || NULL == mErrorAndStringBuffer) {
    return END_OF_SLK_INPUT_;
  }
  newToken();

  for (;;) {
    if (*mIterator == '\0') {
      if (isCanFinish()) {
        endTokenWithEof();
        return END_OF_SLK_INPUT_;
      } else {
        if (!mIterator.Load()) {
          endTokenWithEof();
          return END_OF_SLK_INPUT_;
        }
      }
    }

    BOOL isSkip = TRUE;
    //跳过注释与白空格
    for (; isSkip && *mIterator != '\0';) {
      isSkip = FALSE;
      for (; isWhiteSpace(*mIterator); ++mIterator) {
        if (*mIterator == '\n')++mLineNumber;
        isSkip = TRUE;
      }
      //#引导的单行注释
      if (*mIterator == '#') {
        for (; *mIterator != '\0' && *mIterator != '\n'; ++mIterator);
        isSkip = TRUE;
      }
      //C++风格的单行注释与多行注释
      if (*mIterator == '/' && (*(mIterator + 1) == '/' || *(mIterator + 1) == '*')) {
        ++mIterator;
        if (*mIterator == '/') {
          ++mIterator;
          for (; *mIterator != '\0' && *mIterator != '\n'; ++mIterator);
          isSkip = TRUE;
        } else if (*mIterator == '*') {
          ++mIterator;
          for (;;) {
            if (*mIterator != '\0') {
              if (*mIterator == '\n')++mLineNumber;
              if (*mIterator == '*' && *(mIterator + 1) == '/') {
                ++mIterator;
                ++mIterator;
                break;
              }
            } else {
              if (mIterator.Load()) {
                continue;
              } else {
                endTokenWithEof();
                return END_OF_SLK_INPUT_;
              }
            }
            ++mIterator;
          }
          isSkip = TRUE;
        }
      }
    }
    if (*mIterator != '\0')
      break;
  }

  if (isCanFinish())
    setCanFinish(FALSE);

  if (*mIterator == '{' && *(mIterator + 1) == ':') {
    ++mIterator;
    ++mIterator;
    INT line = mLineNumber;
    //搜索脚本结束 :}
    for (; *mIterator != '\0';) {
      while (*mIterator != '\0' && *mIterator != ':') {
        if (*mIterator == '\n')++mLineNumber;

        pushTokenChar(*mIterator);

        ++mIterator;
      }
      if (*mIterator == '\0')
        break;
      IScriptSource::Iterator next = mIterator + 1;
      if (*next == '}') {
        ++mIterator;
        ++mIterator;
        break;
      } else {
        pushTokenChar(*mIterator);

        ++mIterator;
      }
    }
    if (*mIterator == '\0') {
      CHAR* pInfo = mErrorAndStringBuffer->NewErrorInfo();
      if (pInfo)
        tsnprintf(pInfo, MAX_ERROR_INFO_CAPACITY, "[line %d ]:ExternScript can't finish！", line);
    }
    endToken();
    return SCRIPT_CONTENT_;
  } else if (isOperator(*mIterator))//操作符
  {
    getOperatorToken();
    return getOperatorTokenValue();
  } else if (*mIterator == '.' && 0 == myisdigit(*(mIterator + 1), FALSE)) {
    CHAR c = *mIterator;
    ++mIterator;

    pushTokenChar(c);
    endToken();
    return DOT_;
  } else if (isDelimiter(*mIterator))//分隔符
  {
    CHAR c = *mIterator;
    ++mIterator;

    pushTokenChar(c);
    endToken();

    switch (c) {
    case '(':
      return LPAREN_;
    case ')':
      return RPAREN_;
    case '[':
      return LBRACK_;
    case ']':
      return RBRACK_;
    case '{':
      return LBRACE_;
    case '}':
      return RBRACE_;
    case ',':
      return COMMA_;
    case ';':
      return SEMI_;
    default:
      return END_OF_SLK_INPUT_;
    }
  } else//关键字、标识符或常数
  {
    if (*mIterator == '"' || *mIterator == '\'')//引号括起来的名称或关键字
    {
      INT line = mLineNumber;
      CHAR c = *mIterator;
      for (++mIterator; *mIterator != '\0' && *mIterator != c;) {
        if (*mIterator == '\n')++mLineNumber;
        if (*mIterator == '\\') {
          //pushTokenChar(*mIterator);
          ++mIterator;
        }

        pushTokenChar(*mIterator);
        ++mIterator;

        if (*mIterator == '\0') {
          if (mIterator.Load()) {
            continue;
          } else {
            CHAR* pInfo = mErrorAndStringBuffer->NewErrorInfo();
            if (pInfo)
              tsnprintf(pInfo, MAX_ERROR_INFO_CAPACITY, "[line %d ]:String can't finish！", line);
            endTokenWithEof();
            return END_OF_SLK_INPUT_;
          }
        }
      }
      if (*mIterator != '\0') {
        ++mIterator;
      } else {
        CHAR* pInfo = mErrorAndStringBuffer->NewErrorInfo();
        if (pInfo)
          tsnprintf(pInfo, MAX_ERROR_INFO_CAPACITY, "[line %d ]:String can't finish！", line);
      }
      endToken();
      return STRING_;
    } else {
      BOOL isNum = TRUE;
      BOOL isHex = FALSE;
      if (*mIterator == '0' && *(mIterator + 1) == 'x') {
        isHex = TRUE;
        pushTokenChar(*mIterator);
        ++mIterator;
        pushTokenChar(*mIterator);
        ++mIterator;
      }
      for (; *mIterator != '\0' && !isDelimiter(*mIterator) && !isWhiteSpace(*mIterator) && !isOperator(*mIterator); ++mIterator) {
        if (*mIterator == '#')
          break;
        else if (*mIterator == '/') {
          IScriptSource::Iterator next = mIterator + 1;
          if (*next != '\0' && (*next == '/' || *next == '*')) {
            break;
          }
        } else if (*mIterator == '.') {
          if (!isNum) {
            break;
          } else {
            IScriptSource::Iterator next = mIterator + 1;
            if (0 == myisdigit(*next, isHex)) {
              break;
            }
          }
        } else if (0 == myisdigit(*mIterator, isHex)) {
          isNum = FALSE;
        }

        pushTokenChar(*mIterator);
      }
      endToken();
      if (isNum)
        return NUMBER_;
      else
        return IDENTIFIER_;
    }
  }
}

SHORT SlkToken::peek(INT level)
{
  SHORT     token = 0;

  printf("peek_token is not called in an LL(1) grammar\n");

  return  token;
}

void SlkToken::newToken(void)
{
  if (mErrorAndStringBuffer) {
    mLastToken = mCurToken;
    mLastLineNumber = mLineNumber;
    mCurToken = mErrorAndStringBuffer->GetUnusedStringPtrRef();

    mTokenCharIndex = 0;
    if (mCurToken) {
      mCurToken[mTokenCharIndex] = '\0';
    }
  }
}

void SlkToken::pushTokenChar(CHAR c)
{
  if (NULL == mErrorAndStringBuffer || mErrorAndStringBuffer->GetUnusedStringLength() <= 1 || NULL == mCurToken)
    return;
  mCurToken[mTokenCharIndex] = c;
  ++mTokenCharIndex;
}

void SlkToken::endToken(void)
{
  if (NULL == mErrorAndStringBuffer || mErrorAndStringBuffer->GetUnusedStringLength() <= 1 || NULL == mCurToken || NULL == mErrorAndStringBuffer->GetUnusedStringPtrRef())
    return;
  mCurToken[mTokenCharIndex] = '\0';
  mErrorAndStringBuffer->GetUnusedStringPtrRef() += mTokenCharIndex + 1;
}

void SlkToken::endTokenWithEof(void)
{
  static const char* s_c_Eof = "<<eof>>";
  if (NULL == mErrorAndStringBuffer || mErrorAndStringBuffer->GetUnusedStringLength() <= (INT)strlen(s_c_Eof) + 1 || NULL == mCurToken || NULL == mErrorAndStringBuffer->GetUnusedStringPtrRef())
    return;
  strcpy(mCurToken, s_c_Eof);
  mErrorAndStringBuffer->GetUnusedStringPtrRef() += strlen(s_c_Eof) + 1;
}

SlkToken::SlkToken(Dsl::IScriptSource& source, Dsl::ErrorAndStringBuffer& errorAndStringBuffer) :mSource(&source), mErrorAndStringBuffer(&errorAndStringBuffer)
{
  CrashAssert(mSource);
  CrashAssert(mErrorAndStringBuffer);

  mIterator = mSource->GetIterator();

  mWhiteSpaces = " \t\r\n";
  mDelimiters = "()[]{},;";
  mOperators = "~`!%^&*-+=|<>/?:";

  mLineNumber = 1;
  mLastLineNumber = 1;
  mIsExternScript = FALSE;

  mCurToken = 0;
  mLastToken = 0;
  mTokenCharIndex = 0;

  setCanFinish(FALSE);
}