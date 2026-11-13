// index.js - JavaScript MetaDSL ESM entry point for Node.js and browsers.
// Usage:
//   import { DslFile } from './index.js';
//   const file = new DslFile();
//   const ok = file.LoadFromString('foo(1, 2){ bar(); };', console.log);
//   console.log(file.ToScriptString());

import * as Dsl from './Dsl.js';
import { DslLog } from './DslLog.js';
import { DslToken } from './DslToken.js';
import { DslAction, OperatorCategoryEnum, PairTypeEnum } from './DslAction.js';
import { DslError } from './DslError.js';
import { DslFile } from './DslFile.js';
import DslParserWrap from './DslParserWrap.js';

const MetaDSL = Object.assign({}, Dsl, {
    DslLog,
    DslToken,
    DslAction,
    OperatorCategoryEnum,
    PairTypeEnum,
    DslError,
    DslFile,
    DslParserWrap,
});

export * from './Dsl.js';
export { DslLog, DslToken, DslAction, OperatorCategoryEnum, PairTypeEnum, DslError, DslFile, DslParserWrap, MetaDSL };
export default MetaDSL;
