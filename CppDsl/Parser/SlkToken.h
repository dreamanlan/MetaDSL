/**************************************************************************

    SlkToken.h

    **************************************************************************/

#ifndef _SLK_SLKTOKEN_H
#define _SLK_SLKTOKEN_H

#include "Dsl.h"

class SlkToken
{
public:
  short get(void);
  short peek(int level);
  char* getCurToken(void) const
  {
    return mCurToken;
  }
  char* getLastToken(void) const
  {
    return mLastToken;
  }
  int getLineNumber(void) const
  {
    return mLineNumber;
  }
  int getLastLineNumber(void) const
  {
    return mLastLineNumber;
  }
public:
  void setCanFinish(int val)
  {
    mCanFinish = val;
  }
private:
  void getOperatorToken(void);
  short getOperatorTokenValue(void)const;
  int isCanFinish(void)const
  {
    return mCanFinish;
  }
  int isWhiteSpace(char c) const;
  int isDelimiter(char c) const;
  int isOperator(char c) const;
private:
  void newToken(void);
  void pushTokenChar(char c);
  void endToken(void);
  void endTokenWithEof(void);
public:
  SlkToken(Dsl::IScriptSource& source, Dsl::ErrorAndStringBuffer& errorAndStringBuffer);
private:
  Dsl::IScriptSource* mSource;
  Dsl::IScriptSource::Iterator mIterator;

  char* mCurToken;
  char* mLastToken;
  int mTokenCharIndex;

  Dsl::ErrorAndStringBuffer* mErrorAndStringBuffer;

  int mLineNumber;
  int mLastLineNumber;
  int mIsExternScript;
  int mCanFinish;

  const char* mWhiteSpaces;
  const char* mDelimiters;
  const char* mOperators;
};

#endif

