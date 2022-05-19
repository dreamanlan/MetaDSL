/**************************************************************************

    SlkToken.h

    **************************************************************************/

#ifndef _SLK_SLKTOKEN_H
#define _SLK_SLKTOKEN_H

#include "DslParser.h"
#include "Queue.h"

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
    const char* getStringBeginDelimiter(void)const { return mStringBeginDelimiter; }
    const char* getStringEndDelimiter(void)const { return mStringEndDelimiter; }
    const char* getScriptBeginDelimiter(void)const { return mScriptBeginDelimiter; }
    const char* getScriptEndDelimiter(void)const { return mScriptEndDelimiter; }
public:
    void setCurToken(char* tok) { mCurToken = tok; }
    void setLastToken(char* tok) { mLastToken = tok; }
    bool enqueueToken(char* tok, short val, int line);
    char curChar(void)const;
    char nextChar(void)const;
    char peekChar(int ix)const;
    void getOperatorToken(void);
    short getOperatorTokenValue(void)const;
    int isWhiteSpace(char c) const;
    int isDelimiter(char c) const;
    int isBeginParentheses(char c) const;
    int isEndParentheses(char c) const;
    int isOperator(char c) const;
    int isQuote(char c) const;
    int isSpecialChar(char c) const;
private:
    short getImpl(void);
    int isCanFinish(void)const
    {
        return mCanFinish;
    }
    int isBegin(const char* delimiter, int len) const;
    void getBlockString(const char* delimiter, int len);
    void removeFirstAndLastEmptyLine(void);
    void newComment(void);
    void pushCommentChar(char c);
    void endComment(void);
    void newToken(void);
    void pushTokenChar(char c);
    void tempEndToken(void);
    void endToken(void);
    void endTokenWithEof(void);
public:
    SlkToken(DslParser::IScriptSource& source, DslParser::DslFile& dslFile);
private:
    struct TokenInfo
    {
        char* Token;
        short TokenValue;
        int LineNumber;

        inline TokenInfo(void) {}
        inline TokenInfo(char* token, short tokenValue, int lineNumber) :Token(token), TokenValue(tokenValue), LineNumber(lineNumber) {}
    };

    DslParser::IScriptSource* mSource;
    DslParser::IScriptSource::Iterator mIterator;

    char* mCurToken;
    char* mLastToken;
    int mTokenCharIndex;

    char* mCurComment;
    int mCommentCharIndex;

    static const int c_MaxCommentNum = 256;
    char* mComments[c_MaxCommentNum];
    int mCommentNum;
    int mCommentOnNewLine;

    DslParser::DslFile* mDslFile;
    DequeT<TokenInfo, 16> mTokenQueue;

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

    const char* mScriptBeginDelimiter;
    const char* mScriptEndDelimiter;
    const char* mStringBeginDelimiter;
    const char* mStringEndDelimiter;
    int mStringBeginDelimiterLength;
    int mStringEndDelimiterLength;
    int mScriptBeginDelimiterLength;
    int mScriptEndDelimiterLength;

    DslParser::EnqueueTokenDelegation mOnEnqueueToken;
};

#endif

