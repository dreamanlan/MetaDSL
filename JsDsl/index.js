// index.js - JavaScript MetaDSL entry point.
// Usage (Node.js):
//   const { DslFile } = require('./index.js');
//   const file = new DslFile();
//   const ok = file.LoadFromString('foo(1, 2){ bar(); };', console.log);
//   console.log(file.ToScriptString());

'use strict';

const Dsl = require('./Dsl.js');
const { DslLog } = require('./DslLog.js');
const { DslToken } = require('./DslToken.js');
const { DslAction, OperatorCategoryEnum, PairTypeEnum } = require('./DslAction.js');
const { DslError } = require('./DslError.js');
const { DslFile } = require('./DslFile.js');
const DslParserWrap = require('./DslParserWrap.js');

module.exports = Object.assign({}, Dsl, {
    DslLog,
    DslToken,
    DslAction,
    OperatorCategoryEnum,
    PairTypeEnum,
    DslError,
    DslFile,
    DslParserWrap,
});
