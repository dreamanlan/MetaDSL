#ifndef __SourceCodeScript_H__
#define __SourceCodeScript_H__

#include "Dsl.h"

namespace Dsl
{
    void Parse(const char* buf, DslFile& file);
    void Parse(IScriptSource& source, DslFile& file);
    void ParseGpp(const char* buf, DslFile& file, const char* beginDelim, const char* endDelim, char* gppBuf, int& len);
}

using namespace Dsl;

#endif //__SourceCodeScript_H__