#ifndef __SourceCodeScript_H__
#define __SourceCodeScript_H__

#include "Dsl.h"

namespace Dsl
{
  class SourceCodeScript
  {
  public:
    void						                  Parse(const char* buf);
    void						                  Parse(IScriptSource& source);
  public:
    inline DslFile&			  GetDslFile(void){ return mDataFile; }
    inline const DslFile&	GetDslFile(void)const{ return mDataFile; }
  public:
    SourceCodeScript(void){}
    SourceCodeScript(const ParserOptions& options) :mDataFile(options){}
  private:
    DslFile					      mDataFile;
  };
}

using namespace Dsl;

#endif //__SourceCodeScript_H__