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
    short get();
    short peek(int level);
    char* getCurToken() const
    {
        return mCurToken;
    }
    char* getLastToken() const
    {
        return mLastToken;
    }
    int getLineNumber() const
    {
        return mLineNumber;
    }
    int getLastLineNumber() const
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
    void resetComments()
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
    const char* getStringBeginDelimiter()const { return mStringBeginDelimiter; }
    const char* getStringEndDelimiter()const { return mStringEndDelimiter; }
    const char* getScriptBeginDelimiter()const { return mScriptBeginDelimiter; }
    const char* getScriptEndDelimiter()const { return mScriptEndDelimiter; }
public:
    void setCurToken(char* tok) { mCurToken = tok; }
    void setLastToken(char* tok) { mLastToken = tok; }
    bool enqueueToken(char* tok, short val, int line);
    char curChar()const;
    char nextChar()const;
    char peekChar(int ix)const;
    char peekNextValidChar(int beginIx)const;
    char peekNextValidChar(int beginIx, int& index)const;
    void getOperatorToken();
    short getOperatorTokenValue()const;
    int isNotIdentifier(char c)const;
    int isNotIdentifierAndBeginParenthesis(char c)const;
    int isNotIdentifierAndNumberAndEndParenthesis(char c)const;
    int isWhiteSpace(char c) const;
    int isDelimiter(char c) const;
    int isBeginParentheses(char c) const;
    int isEndParentheses(char c) const;
    int isOperator(char c) const;
    int isQuote(char c) const;
    int isSpecialChar(char c) const;
private:
    short getImpl();
    int isCanFinish()const
    {
        return mCanFinish;
    }
    int isBegin(const char* delimiter, int len) const;
    void getBlockString(const char* delimiter, int len);
    void removeFirstAndLastEmptyLine();
    void newComment();
    void pushCommentChar(char c);
    void endComment();
    void newToken();
    void pushTokenChar(char c);
    void tempEndToken();
    void endToken();
    void endTokenWithEof();
public:
    SlkToken(DslParser::IScriptSource& source, DslParser::DslFile& dslFile);
    void SetDslActionApi(const DslParser::DslActionApi& api)
    {
        mDslActionApi = &api;
    }
private:
    struct TokenInfo
    {
        char* Token;
        short TokenValue;
        int LineNumber;

        inline TokenInfo() :Token(nullptr), TokenValue(0), LineNumber(0) {}
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

    const DslParser::DslActionApi* mDslActionApi;
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
};

#endif

