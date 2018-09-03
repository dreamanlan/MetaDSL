/*************************************************************************

    SlkAction.h

*************************************************************************/

#ifndef _SLKACTION_H
#define _SLKACTION_H

class SlkAction
{
public:
	virtual ~SlkAction(void){}
public:
	virtual void predict(int production){}
	virtual void execute(int number)=0;
};

#endif

