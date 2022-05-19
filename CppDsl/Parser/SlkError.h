/**************************************************************************

    SlkError.h

    **************************************************************************/

#ifndef _SLKERROR_H
#define _SLKERROR_H

namespace DslParser
{
  class DslFile;
}
class SlkToken;
class SlkError
{
public:
  SlkError(DslParser::DslFile& dslFile);
  short mismatch(short terminal, short token, SlkToken& tokens);
  short no_entry(short productionNumber, short nonterminal, short token, int level, SlkToken& tokens);
  void input_left(SlkToken& tokens);
  void message(const char* msg, SlkToken& tokens);
private:
  DslParser::DslFile* mDslFile;
};

#endif

