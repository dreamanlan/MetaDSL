using System;
using System.Collections.Generic;
using System.Text;

namespace Dsl.Common
{
    struct DslLog
    {
        internal DslLogDelegation OnLog;
        internal void Log(string format, params object[] args)
        {
            if (null != OnLog) {
                OnLog(string.Format(format, args));
            }
        }
    }
}
