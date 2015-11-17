using System;
using System.Collections.Generic;
using System.Text;

namespace Dsl.Parser
{
#if FULL_VERSION
  class DslError
  {
    internal DslError(DslToken tokens)
    {
      this.tokens = tokens;
    }

    internal bool HasError
    {
      get { return mHasError; }
    }

    internal short mismatch(short terminal, short token)
    {
      mHasError = true;
      //Console.WriteLine(" expecting {0} but found {1}, last token {2} line {3}, cur token {4} line {5}", DslString.GetSymbolName(terminal), DslString.GetSymbolName(token), tokens.getLastToken(), tokens.getLastLineNumber(), tokens.getCurToken(), tokens.getLineNumber());
      return token;
    }

    internal short no_entry(short nonterminal, short token, int level)
    {
      mHasError = true;
      //Console.WriteLine(" syntax error: skipping input {0}, last token {1} line {2}, cur token {3} line {4}", DslString.GetSymbolName(token), tokens.getLastToken(), tokens.getLastLineNumber(), tokens.getCurToken(), tokens.getLineNumber());
      token = tokens.get(); // advance the input
      return token;
    }

    internal void input_left()
    {
      mHasError = true;
      //Console.WriteLine("input left, last token {0} line {1}, cur token {2} line {3}", tokens.getLastToken(), tokens.getLastLineNumber(), tokens.getCurToken(), tokens.getLineNumber());
    }

    internal void message(string message)
    {
      mHasError = true;
      throw new Exception(string.Format("{0}", message));
    }

    private DslToken tokens;
    private bool mHasError;
  }
#endif
}
