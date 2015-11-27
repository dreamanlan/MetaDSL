/*************************************************************************

    SlkAction.h

*************************************************************************/

#ifndef _SLKACTION_H
#define _SLKACTION_H

#include "Type.h"

class SlkAction
{
public:
	virtual ~SlkAction(void){}
public:
  virtual void predict(INT production){}
	virtual void execute(INT number)=0;
};

#endif

