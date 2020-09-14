using System;
using System.Collections.Generic;
using System.Text;

namespace Dsl.Common
{
    class DslLog
    {
        internal DslLogDelegation OnLog;

        internal bool HasError
        {
            get { return mHasError; }
        }

        internal void Log(string format, params object[] args)
        {
            if (null != OnLog) {
                OnLog(string.Format(format, args));
            }
        }
        internal void Error(string format, params object[] args)
        {
            mHasError = true;
            if (null != OnLog) {
                OnLog(string.Format(format, args));
            }
        }

        private bool mHasError = false;
    }
}
