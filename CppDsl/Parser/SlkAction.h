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
    virtual void predict([[maybe_unused]] unsigned short production, [[maybe_unused]] unsigned short nonterminal, [[maybe_unused]] unsigned short token, [[maybe_unused]] int level, [[maybe_unused]] const char* lastTok, [[maybe_unused]] int lastLine, [[maybe_unused]] const char* curTok, [[maybe_unused]] int curLine)
    {
    }
    virtual void execute(int number) = 0;
};

#endif

