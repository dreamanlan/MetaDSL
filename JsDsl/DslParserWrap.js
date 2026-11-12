// DslParserWrap.js - wraps the SLK generated parser tables (DslConstants.js/DslParser.js/DslString.js).
// Node.js: the generated files declare plain globals, so they are evaluated in a shared vm context.
// Browser: include the three generated files with script tags before this file.

'use strict';

let ctx;
if (typeof module !== 'undefined' && module.exports && typeof require === 'function') {
    const fs = require('fs');
    const path = require('path');
    const vm = require('vm');
    ctx = vm.createContext({ console });
    for (const file of ['DslConstants.js', 'DslParser.js', 'DslString.js']) {
        const code = fs.readFileSync(path.join(__dirname, file), 'utf8');
        vm.runInContext(code, ctx, { filename: file });
    }
}
else {
    ctx = globalThis;
}

// Terminal/nonterminal constants, e.g. DslConstants.IDENTIFIER_ / END_OF_SLK_INPUT_.
const DslConstants = {};
for (const key of Object.keys(ctx)) {
    if (/^[A-Z][A-Z0-9_]*_$/.test(key)) {
        DslConstants[key] = ctx[key];
    }
}

function parse(action, tokens, error, startSymbol) {
    ctx.parse(action, tokens, error, startSymbol || 0);
}

function GetSymbolName(symbol) {
    return ctx.GetSymbolName(symbol);
}

function GetProductionName(productionNumber) {
    return ctx.GetProductionName(productionNumber);
}

const DslParserWrap = { DslConstants, parse, GetSymbolName, GetProductionName };

if (typeof module !== 'undefined' && module.exports) {
    module.exports = DslParserWrap;
}
if (typeof globalThis !== 'undefined') {
    globalThis.DslParserWrap = DslParserWrap;
}
