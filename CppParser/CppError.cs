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
            //To make the lexer generate a matching input symbol that ensures normal parsing.
            cppToken.fake(terminal);
            return terminal;
        }

        internal short no_entry(short productionNumber, short nonterminal, short token, int level, ref CppToken cppToken)
        {
            //Note: For the grammar of cpp.txt, it seems that these types of errors only occur at the beginning of the program
            //when encountering the characters ')' ']' '}'.
            mLog.Error("[error] syntax error: skipping input {0}, last token {1} line {2}, cur token {3} line {4} [production: {5} nonterminal: {6} ]", CppString.GetSymbolName(token), cppToken.getLastToken(), cppToken.getLastLineNumber(), cppToken.getCurToken(), cppToken.getLineNumber(), CppString.GetProductionName(productionNumber), CppString.GetSymbolName(nonterminal));
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