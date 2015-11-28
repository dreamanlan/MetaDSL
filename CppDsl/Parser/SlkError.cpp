/*****************************************************************************

    SlkError.cpp

    ******************************************************************************/

#include "Dsl.h"
#include "SlkInc.h"
#include "SlkParse.h"
#include "tsnprintf.h"

//mScanner,mErrorInfo由构造函数的引用参数传入，不会为空。所以使用时不再检查是否为空。

#define GET_SYMBOL_NAME        SlkGetSymbolName

short SlkError::mismatch(short terminal, short token)
{
  if (mErrorBuffer && mTokens) {
    char* p = mErrorBuffer->NewErrorInfo();
    if (p)
      tsnprintf(p, MAX_ERROR_INFO_CAPACITY, "[line:%d last:%s cur:%s] expecting '%s' but found '%s' \n",
      mTokens->getLineNumber(),
      mTokens->getLastToken(),
      mTokens->getCurToken(),
      GET_SYMBOL_NAME(terminal),
      GET_SYMBOL_NAME(token));
  }
  return token;
}

short SlkError::no_entry(short nonterminal, short token, int level)
{
  if (mErrorBuffer && mTokens) {
    char* p = mErrorBuffer->NewErrorInfo();
    if (p)
      tsnprintf(p, MAX_ERROR_INFO_CAPACITY, "[line:%d last:%s cur:%s] syntax error: skipping input '%s' \n",
      mTokens->getLineNumber(),
      mTokens->getLastToken(),
      mTokens->getCurToken(),
      GET_SYMBOL_NAME(token));

    token = mTokens->get();// advance the input
    return token;
  } else {
    return 0;
  }
}

void SlkError::input_left(void)
{
  if (mErrorBuffer && mTokens) {
    char* p = mErrorBuffer->NewErrorInfo();
    if (p)
      tsnprintf(p, MAX_ERROR_INFO_CAPACITY, "[line:%d last:%s cur:%s] syntax completion, skipping left . \n",
      mTokens->getLineNumber(),
      mTokens->getLastToken(),
      mTokens->getCurToken());
  }
}

SlkError::SlkError(SlkToken& tokens, Dsl::ErrorAndStringBuffer& errorBuffer) :mTokens(&tokens), mErrorBuffer(&errorBuffer)
{
  MyAssert(mTokens);
  MyAssert(mErrorBuffer);
}