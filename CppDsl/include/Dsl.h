#ifndef _DSL_H
#define _DSL_H

#include "DslParser.h"
#include "DslData.h"

namespace Dsl
{
    void Transform(const DslParser::DslFile& parsed, DslData::DslFile& data);
}

#endif