/*************************************************************************

    SlkAction.h

*************************************************************************/

#ifndef _SLKACTION_H
#define _SLKACTION_H

class SlkAction
{
public:
    virtual ~SlkAction() {}
public:
    virtual void predict(unsigned short production, unsigned short nonterminal, unsigned short token, int level, const char* lastTok, int lastLine, const char* curTok, int curLine)
    {
        production, nonterminal, token, level, lastTok, lastLine, curTok, curLine;
    }
    virtual void execute(int number) = 0;
};

#endif

