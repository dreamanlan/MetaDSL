// DslLog.js - JavaScript port of MetaDSL Common/DslLog.cs.

'use strict';

// Minimal C# string.Format replacement: {0}, {1}, ... placeholders only.
function format(fmt, args) {
    return String(fmt).replace(/\{(\d+)\}/g, (m, ix) => {
        const v = args[Number(ix)];
        return v === undefined || v === null ? '' : String(v);
    });
}

class DslLog {
    constructor() {
        this.OnLog = null;
        this.mHasError = false;
    }
    get HasError() { return this.mHasError; }
    Log(fmt, ...args) {
        if (this.OnLog !== null) this.OnLog(format(fmt, args));
    }
    Error(fmt, ...args) {
        this.mHasError = true;
        if (this.OnLog !== null) this.OnLog(format(fmt, args));
    }
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { DslLog };
}
if (typeof globalThis !== 'undefined') {
    globalThis.DslLog = DslLog;
}
