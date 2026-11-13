// DslParserWrap.js - wraps the SLK generated parser modules.

import * as DslConstants from './DslConstants.js';
import { parse as parseImpl } from './DslParser.js';
import { GetSymbolName, GetProductionName } from './DslString.js';

function parse(action, tokens, error, startSymbol) {
    parseImpl(action, tokens, error, startSymbol || 0);
}

const DslParserWrap = { DslConstants, parse, GetSymbolName, GetProductionName };

export { DslConstants, parse, GetSymbolName, GetProductionName, DslParserWrap };
export default DslParserWrap;
