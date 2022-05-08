using System;
using System.Collections.Generic;
using System.Text;
using Dsl.Common;

namespace Dsl.Parser
{
    struct CppError
    {
        internal CppError(DslLog log)
        {
            mLog = log;
        }

        internal short mismatch(short terminal, short token, ref CppToken cppToken)
        {
            //mLog.Error("[error] expecting {0} but found {1}, last token {2} line {3}, cur token {4} line {5}", CppString.GetSymbolName(terminal), CppString.GetSymbolName(token), cppToken.getLastToken(), cppToken.getLastLineNumber(), cppToken.getCurToken(), cppToken.getLineNumber());
            //return token;
            //让词法伪造一个匹配的输入符号，保证解析正常进行
            return terminal;
        }

        internal short no_entry(int entry, short nonterminal, short token, int level, ref CppToken cppToken)
        {
            mLog.Error("[error] syntax error: skipping input {0}, last token {1} line {2}, cur token {3} line {4}", CppString.GetSymbolName(token), cppToken.getLastToken(), cppToken.getLastLineNumber(), cppToken.getCurToken(), cppToken.getLineNumber());
            token = cppToken.get(); // advance the input
            return token;
        }

        internal void input_left(ref CppToken cppToken)
        {
            mLog.Error("[error] input left, last token {0} line {1}, cur token {2} line {3}", cppToken.getLastToken(), cppToken.getLastLineNumber(), cppToken.getCurToken(), cppToken.getLineNumber());
        }

        internal void message(string message, ref CppToken cppToken)
        {
            mLog.Error("[info] {0}, last token {1} line {2}, cur token {3} line {4}", message, cppToken.getLastToken(), cppToken.getLastLineNumber(), cppToken.getCurToken(), cppToken.getLineNumber());
        }

        private DslLog mLog;
    }
}
