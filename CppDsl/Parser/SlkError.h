/**************************************************************************

    SlkError.h

    **************************************************************************/

#ifndef _SLKERROR_H
#define _SLKERROR_H

namespace Dsl
{
  class ErrorAndStringBuffer;
}
class SlkToken;
class SlkError
{
public:
  SlkError(SlkToken& tokens, Dsl::ErrorAndStringBuffer& errorBuffer);
  short mismatch(short symbol, short token);
  short no_entry(short nonterminal, short token, int level);
  void input_left(void);
private:
  SlkToken* mTokens;
  Dsl::ErrorAndStringBuffer* mErrorBuffer;
};

#endif

