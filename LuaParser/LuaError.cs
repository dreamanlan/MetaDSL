using System;
using System.Collections.Generic;
using System.Text;
using Dsl.Common;

namespace Dsl.Parser
{
    struct LuaError
    {
        internal LuaError(DslLog log)
        {
            mLog = log;
        }

        internal short mismatch(short terminal, short token, ref LuaToken luaToken)
        {
            mLog.Error("[error] expecting {0} but found {1}, last token {2} line {3}, cur token {4} line {5}", LuaString.GetSymbolName(terminal), LuaString.GetSymbolName(token), luaToken.getLastToken(), luaToken.getLastLineNumber(), luaToken.getCurToken(), luaToken.getLineNumber());
            return token;
        }

        internal short no_entry(short entry, short nonterminal, short token, int level, ref LuaToken luaToken)
        {
            mLog.Error("[error] syntax error: skipping input {0}, last token {1} line {2}, cur token {3} line {4}", LuaString.GetSymbolName(token), luaToken.getLastToken(), luaToken.getLastLineNumber(), luaToken.getCurToken(), luaToken.getLineNumber());
            token = luaToken.get(); // advance the input
            return token;
        }

        internal void input_left(ref LuaToken luaToken)
        {
            mLog.Error("[error] input left, last token {0} line {1}, cur token {2} line {3}", luaToken.getLastToken(), luaToken.getLastLineNumber(), luaToken.getCurToken(), luaToken.getLineNumber());
        }

        internal void message(string message, ref LuaToken luaToken)
        {
            mLog.Error("[info] {0}, last token {1} line {2}, cur token {3} line {4}", message, luaToken.getLastToken(), luaToken.getLastLineNumber(), luaToken.getCurToken(), luaToken.getLineNumber());
        }

        private DslLog mLog;
    }
}
