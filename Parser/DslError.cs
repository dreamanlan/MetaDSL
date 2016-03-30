using System;
using System.Collections.Generic;
using System.Text;

namespace Dsl.Parser
{
#if FULL_VERSION
    class DslError
    {
        internal DslError(DslLog log, DslToken tokens)
        {
            mLog = log;
            mToken = tokens;
        }

        internal bool HasError
        {
            get { return mHasError; }
        }

        internal short mismatch(short terminal, short token)
        {
            mHasError = true;
            mLog.Log("[error] expecting {0} but found {1}, last token {2} line {3}, cur token {4} line {5}", DslString.GetSymbolName(terminal), DslString.GetSymbolName(token), mToken.getLastToken(), mToken.getLastLineNumber(), mToken.getCurToken(), mToken.getLineNumber());
            return token;
        }

        internal short no_entry(short nonterminal, short token, int level)
        {
            mHasError = true;
            mLog.Log("[error] syntax error: skipping input {0}, last token {1} line {2}, cur token {3} line {4}", DslString.GetSymbolName(token), mToken.getLastToken(), mToken.getLastLineNumber(), mToken.getCurToken(), mToken.getLineNumber());
            token = mToken.get(); // advance the input
            return token;
        }

        internal void input_left()
        {
            mHasError = true;
            mLog.Log("[error] input left, last token {0} line {1}, cur token {2} line {3}", mToken.getLastToken(), mToken.getLastLineNumber(), mToken.getCurToken(), mToken.getLineNumber());
        }

        internal void message(string message)
        {
            mHasError = true;
            mLog.Log("[info] {0}", message);
        }

        private DslLog mLog;
        private DslToken mToken;
        private bool mHasError;
    }
#endif
}
