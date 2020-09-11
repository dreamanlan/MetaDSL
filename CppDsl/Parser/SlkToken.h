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
	int getCommentNum(int& commentOnNewLine) const
	{
		commentOnNewLine = mCommentOnNewLine;
		return mCommentNum;
	}
	char* getComment(int index) const
	{
		if (index >= 0 && index < mCommentNum) {
			return mComments[index];
		}
		else {
			return 0;
		}
	}
	void resetComments(void)
	{
		mCommentNum = 0;
		mCommentOnNewLine = FALSE;
	}
public:
	void setCanFinish(int val)
	{
		mCanFinish = val;
	}
	void setStringDelimiter(const char* begin, const char* end);
	void setScriptDelimiter(const char* begin, const char* end);
private:
	void getOperatorToken(void);
	short getOperatorTokenValue(void)const;
	int isCanFinish(void)const
	{
		return mCanFinish;
	}
	int isWhiteSpace(char c) const;
	int isDelimiter(char c) const;
	int isBeginParentheses(char c) const;
	int isEndParentheses(char c) const;
	int isOperator(char c) const;
    int isQuote(char c) const;
	int isSpecialChar(char c) const;
private:
    int isBegin(const char* delimiter, int len) const;
	void getBlockString(const char* delimiter, int len);
	void removeFirstAndLastEmptyLine(void);
	void newComment(void);
	void pushCommentChar(char c);
	void endComment(void);
	void newToken(void);
	void pushTokenChar(char c);
	void endToken(void);
	void endTokenWithEof(void);
public:
	SlkToken(Dsl::IScriptSource& source, Dsl::DslFile& dslFile);
private:
	Dsl::IScriptSource* mSource;
	Dsl::IScriptSource::Iterator mIterator;

	char* mCurToken;
	char* mLastToken;
	int mTokenCharIndex;

	char* mCurComment;
	int mCommentCharIndex;

	static const int c_MaxCommentNum = 256;
	char* mComments[c_MaxCommentNum];
	int mCommentNum;
	int mCommentOnNewLine;

	Dsl::DslFile* mDslFile;

	int mLineNumber;
	int mLastLineNumber;
	int mCanFinish;

	const char* mWhiteSpaces;
	const char* mDelimiters;
	const char* mBeginParentheses;
	const char* mEndParentheses;
	const char* mOperators;
    const char* mQuotes;
	const char* mSpecialChars;

	static const int c_MaxDelimiterSize = 1024;
	char mScriptBeginDelimiter[c_MaxDelimiterSize + 1];
	char mScriptEndDelimiter[c_MaxDelimiterSize + 1];
	char mStringBeginDelimiter[c_MaxDelimiterSize + 1];
	char mStringEndDelimiter[c_MaxDelimiterSize + 1];
    int mScriptBeginDelimiterLength = 0;
    int mScriptEndDelimiterLength = 0;
    int mStringBeginDelimiterLength = 0;
    int mStringEndDelimiterLength = 0;
};

#endif

