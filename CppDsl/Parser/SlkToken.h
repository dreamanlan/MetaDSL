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
  void setStringDelimiter(const char* delimiter);
  void setScriptDelimiter(const char* delimiter);
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
  int handleStringOrScriptDelimiter(void);
  void getBlockString(const char* delimiter);
  void removeFirstAndLastEmptyLine(void);
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
  int mCanFinish;

  const char* mWhiteSpaces;
  const char* mDelimiters;
  const char* mOperators;
  
  static const int c_MaxDelimiterSize = 1024;
  char mScriptDelimiter[c_MaxDelimiterSize + 1];
  char mStringDelimiter[c_MaxDelimiterSize + 1];
};

#endif

