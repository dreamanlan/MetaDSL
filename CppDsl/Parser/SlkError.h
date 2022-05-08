/**************************************************************************

    SlkError.h

    **************************************************************************/

#ifndef _SLKERROR_H
#define _SLKERROR_H

namespace Dsl
{
  class DslFile;
}
class SlkToken;
class SlkError
{
public:
  SlkError(Dsl::DslFile& dslFile);
  short mismatch(short symbol, short token, SlkToken& tokens);
  short no_entry(short entry, short nonterminal, short token, int level, SlkToken& tokens);
  void input_left(SlkToken& tokens);
  void message(const char* msg, SlkToken& tokens);
private:
  Dsl::DslFile* mDslFile;
};

#endif

