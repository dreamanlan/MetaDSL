// DslError.js - JavaScript port of MetaDSL DslParser/DslError.cs.
// Signatures follow the JS SLK parser: mismatch(terminal, token), no_entry(nonterminal, token, level).

import { GetSymbolName } from './DslParserWrap.js';

class DslError {
    constructor(log, tokens) {
        this.mLog = log;
        this.mTokens = tokens;
    }
    mismatch(terminal, token) {
        const dslToken = this.mTokens;
        this.mLog.Error('[error] expecting {0} but found {1}, last token {2} line {3}, cur token {4} line {5}',
            GetSymbolName(terminal), GetSymbolName(token), dslToken.getLastToken(), dslToken.getLastLineNumber(), dslToken.getCurToken(), dslToken.getLineNumber());
        return token;
    }
    no_entry(nonterminal, token, level) {
        const dslToken = this.mTokens;
        this.mLog.Error('[error] syntax error: skipping input {0}, last token {1} line {2}, cur token {3} line {4} [nonterminal: {5} ]',
            GetSymbolName(token), dslToken.getLastToken(), dslToken.getLastLineNumber(), dslToken.getCurToken(), dslToken.getLineNumber(), GetSymbolName(nonterminal));
        return dslToken.get(); // advance the input
    }
    input_left() {
        const dslToken = this.mTokens;
        this.mLog.Error('[error] input left, last token {0} line {1}, cur token {2} line {3}',
            dslToken.getLastToken(), dslToken.getLastLineNumber(), dslToken.getCurToken(), dslToken.getLineNumber());
    }
    message(msg) {
        const dslToken = this.mTokens;
        this.mLog.Error('[info] {0}, last token {1} line {2}, cur token {3} line {4}',
            msg, dslToken.getLastToken(), dslToken.getLastLineNumber(), dslToken.getCurToken(), dslToken.getLineNumber());
    }
}

export { DslError };
