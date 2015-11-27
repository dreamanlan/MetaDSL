/**************************************************************************

    SlkError.h

**************************************************************************/

#ifndef _SLKERROR_H
#define _SLKERROR_H

#include "Type.h"

namespace Dsl
{
	class ErrorAndStringBuffer;
}
class SlkToken;
class SlkError
{
public:
	SlkError(SlkToken& tokens,Dsl::ErrorAndStringBuffer& errorBuffer);
    SHORT mismatch(SHORT symbol, SHORT token);    
    SHORT no_entry(SHORT nonterminal, SHORT token, INT level);    
    void input_left(void);
private:
    SlkToken* mTokens;
	Dsl::ErrorAndStringBuffer* mErrorBuffer;
 };

#endif

