// DslFile.js - JavaScript port of MetaDSL Dsl.cs DslFile (text/binary DSL load/save facade).
// Lua/Cpp frontends and Gpp preprocessing are intentionally not ported.

import {
    StrBuf,
    ByteStream,
    DelimiterInfo,
    DslGlobals,
    Utility,
    utf8Encode,
    utf8Decode,
} from './Dsl.js';
import { DslLog } from './DslLog.js';
import { DslToken } from './DslToken.js';
import { DslAction } from './DslAction.js';
import { DslError } from './DslError.js';
import DslParserWrap from './DslParserWrap.js';

async function getNodeFs(apiName) {
    if (typeof process === 'undefined' || !process.versions || !process.versions.node) {
        throw new Error(`DslFile.${apiName} is only available in Node.js.`);
    }
    return import('node:fs');
}

class DslFile {
    constructor() {
        this.mDslInfos = [];
        this.mNameTags = null;
        this.mNullableSyntaxEnabled = true;
        this.mStringBeginDelimiter = '"';
        this.mStringEndDelimiter = '"';
        this.mScriptBeginDelimiter = '{:';
        this.mScriptEndDelimiter = ':}';

        this.onTokenCanEatChar = null;
        this.onGetToken = null;
        this.onBeforeAddFunction = null;
        this.onAddFunction = null;
        this.onBeforeEndStatement = null;
        this.onEndStatement = null;
        this.onBeforeBuildOperator = null;
        this.onBuildOperator = null;
        this.onSetFunctionId = null;
        this.onBeforeBuildHighOrder = null;
        this.onBuildHighOrder = null;
    }

    get DslInfos() { return this.mDslInfos; }
    AddDslInfo(data) { this.mDslInfos.push(data); }

    // Node.js only; browsers reject this Promise before importing node:fs.
    async Load(file, logCallback) {
        const fs = await getNodeFs('Load');
        const content = fs.readFileSync(file, 'utf8');
        return this.LoadFromString(content, logCallback);
    }

    LoadFromString(content, logCallback) {
        content = DslFile.SkipUtf8Bom(content);
        content = DslFile.Mac2Unix(content);

        this.mDslInfos.length = 0;
        const log = new DslLog();
        log.OnLog = logCallback || null;

        const action = new DslAction(log, this.mDslInfos);
        const tokens = new DslToken(action, log, content, this.mNullableSyntaxEnabled);
        const error = new DslError(log, tokens);
        tokens.OnGetToken = this.onGetToken;
        tokens.OnTokenCanEatChar = this.onTokenCanEatChar;

        action.SetNameTags(this.mNameTags);
        action.onGetLastToken = () => tokens.getLastToken();
        action.onGetLastLineNumber = () => tokens.getLastLineNumber();
        action.onGetComments = () => {
            const commentOnNewLine = tokens.IsCommentOnNewLine();
            const ret = tokens.GetComments().slice();
            tokens.ResetComments();
            return { commentOnNewLine, comments: ret };
        };
        action.onSetStringDelimiter = (begin, end) => tokens.setStringDelimiter(begin, end);
        action.onSetScriptDelimiter = (begin, end) => tokens.setScriptDelimiter(begin, end);
        action.onBeforeAddFunction = this.onBeforeAddFunction;
        action.onAddFunction = this.onAddFunction;
        action.onBeforeEndStatement = this.onBeforeEndStatement;
        action.onEndStatement = this.onEndStatement;
        action.onBeforeBuildOperator = this.onBeforeBuildOperator;
        action.onBuildOperator = this.onBuildOperator;
        action.onSetFunctionId = this.onSetFunctionId;
        action.onBeforeBuildHighOrder = this.onBeforeBuildHighOrder;
        action.onBuildHighOrder = this.onBuildHighOrder;

        if (this.mStringBeginDelimiter.length > 0 && this.mStringEndDelimiter.length > 0 &&
            (this.mStringBeginDelimiter !== '"' || this.mStringEndDelimiter !== '"')) {
            tokens.setStringDelimiter(this.mStringBeginDelimiter, this.mStringEndDelimiter);
        }
        if (this.mScriptBeginDelimiter.length > 0 && this.mScriptEndDelimiter.length > 0 &&
            (this.mScriptBeginDelimiter !== '"' || this.mScriptEndDelimiter !== '"')) {
            tokens.setScriptDelimiter(this.mScriptBeginDelimiter, this.mScriptEndDelimiter);
        }

        DslParserWrap.parse(action, tokens, error, 0);
        if (log.HasError) {
            this.mDslInfos.length = 0;
        }
        if (tokens.StringBeginDelimiter.length > 0) this.mStringBeginDelimiter = tokens.StringBeginDelimiter;
        if (tokens.StringEndDelimiter.length > 0) this.mStringEndDelimiter = tokens.StringEndDelimiter;
        if (tokens.ScriptBeginDelimiter.length > 0) this.mScriptBeginDelimiter = tokens.ScriptBeginDelimiter;
        if (tokens.ScriptEndDelimiter.length > 0) this.mScriptEndDelimiter = tokens.ScriptEndDelimiter;
        return !log.HasError;
    }

    // Node.js only; browsers reject this Promise before importing node:fs.
    async Save(file) {
        const fs = await getNodeFs('Save');
        const sb = new StrBuf();
        if (this.mStringBeginDelimiter !== '"' || this.mStringEndDelimiter !== '"') {
            sb.Append(`@@delimiter(string, "${this.mStringBeginDelimiter}", "${this.mStringEndDelimiter}");`);
            sb.AppendLine();
        }
        if (this.mScriptBeginDelimiter !== '{:' || this.mScriptEndDelimiter !== ':}') {
            sb.Append(`@@delimiter(script, "${this.mScriptBeginDelimiter}", "${this.mScriptEndDelimiter}");`);
            sb.AppendLine();
        }
        for (let i = 0; i < this.mDslInfos.length; i++) {
            Utility.writeSyntaxComponent(sb, this.mDslInfos[i], 0, true, true, this.MakeDelimiterInfo());
        }
        fs.writeFileSync(file, sb.ToString(), 'utf8');
    }

    // Statements are written with their separators (isLastOfStatement=true),
    // matching the fixed C# DslFile.ToScriptString(); the output is reparseable.
    ToScriptString() {
        const sb = new StrBuf();
        for (let i = 0; i < this.mDslInfos.length; i++) {
            Utility.writeSyntaxComponent(sb, this.mDslInfos[i], 0, true, true, this.MakeDelimiterInfo());
        }
        return sb.ToString();
    }

    MakeDelimiterInfo() {
        return new DelimiterInfo(this.mStringBeginDelimiter, this.mStringEndDelimiter, this.mScriptBeginDelimiter, this.mScriptEndDelimiter);
    }

    // Node.js only; browsers reject this Promise before importing node:fs.
    async LoadBinaryFile(file, reuseKeyBuffer, reuseIdBuffer) {
        const fs = await getNodeFs('LoadBinaryFile');
        const code = fs.readFileSync(file);
        return this.LoadBinaryCode(code, reuseKeyBuffer, reuseIdBuffer);
    }

    LoadBinaryCode(binaryCode, reuseKeyBuffer, reuseIdBuffer) {
        this.mDslInfos.length = 0;
        if (binaryCode === null || binaryCode === undefined) return;
        const bytes = binaryCode instanceof Uint8Array ? binaryCode : new Uint8Array(binaryCode);
        let pos = DslFile.c_BinaryIdentity.length;
        const bytesLen = Utility.readInt(bytes, pos);
        pos += 4;
        const bytes2Len = Utility.readInt(bytes, pos);
        pos += 4;
        const keyCount = Utility.readInt(bytes, pos);
        pos += 4;
        const bytesStart = pos;
        const bytes2Start = bytesStart + bytesLen;
        const keyStart = bytes2Start + bytes2Len;
        const keys = reuseKeyBuffer || [];
        keys.length = 0;
        pos = keyStart;
        for (let i = 0; i < keyCount; ++i) {
            const r = Utility.read7BitEncodedInt(bytes, pos);
            const len = r.value;
            if (len >= 0) {
                pos += r.byteCount;
                keys.push(utf8Decode(bytes, pos, len));
                pos += len;
            }
            else {
                break;
            }
        }
        const identifiers = reuseIdBuffer || [];
        identifiers.length = 0;
        for (let i = bytes2Start; i < bytes2Start + bytes2Len && i < bytes.length; ++i) {
            const r = Utility.read7BitEncodedInt(bytes, i);
            const ix = r.value;
            if (ix >= 0) {
                i += r.byteCount - 1;
            }
            else {
                break;
            }
            if (ix >= 0 && ix < keys.length) {
                identifiers.push(keys[ix]);
            }
            else {
                identifiers.push('');
            }
        }
        const infos = Utility.readBinary(bytes, bytesStart, bytesLen, identifiers);
        this.mDslInfos.push(...infos);
    }

    // Returns the BDSL bytes (Uint8Array); C# writes them directly in SaveBinaryFile.
    SaveBinaryCode() {
        const stream = new ByteStream();
        const identifiers = [];
        for (const info of this.mDslInfos) {
            Utility.writeBinary(stream, identifiers, info);
        }
        const bytes = stream.ToBytes();
        // C# MyStringComparer: shorter strings first, then ordinal comparison.
        const comparer = (x, y) => {
            if (x === y) return 0;
            if (x.length !== y.length) return x.length - y.length;
            return x < y ? -1 : 1;
        };
        const keys = [...new Set(identifiers)].sort(comparer);
        const binarySearch = (key) => {
            let lo = 0;
            let hi = keys.length - 1;
            while (lo <= hi) {
                const mid = (lo + hi) >> 1;
                const c = comparer(keys[mid], key);
                if (c === 0) return mid;
                if (c < 0) lo = mid + 1;
                else hi = mid - 1;
            }
            return -1;
        };
        const ms = new ByteStream();
        for (const key of identifiers) {
            Utility.write7BitEncodedInt(ms, binarySearch(key));
        }
        const bytes2 = ms.ToBytes();
        const bdsl = new ByteStream();
        for (const b of DslFile.BinaryIdentity) bdsl.WriteByte(b);
        Utility.writeInt(bdsl, bytes.length);
        Utility.writeInt(bdsl, bytes2.length);
        Utility.writeInt(bdsl, keys.length);
        for (const b of bytes) bdsl.WriteByte(b);
        for (const b of bytes2) bdsl.WriteByte(b);
        for (const str of keys) {
            const bstr = utf8Encode(str);
            Utility.write7BitEncodedInt(bdsl, bstr.length);
            for (const b of bstr) bdsl.WriteByte(b);
        }
        return bdsl.ToBytes();
    }

    // Node.js only; browsers reject this Promise before importing node:fs.
    async SaveBinaryFile(file) {
        const fs = await getNodeFs('SaveBinaryFile');
        fs.writeFileSync(file, this.SaveBinaryCode());
    }

    SetNameTags(tags) { this.mNameTags = tags; }
    get NameTags() { return this.mNameTags; }
    SetStringDelimiter(begin, end) {
        this.mStringBeginDelimiter = begin;
        this.mStringEndDelimiter = end;
    }
    SetScriptDelimiter(begin, end) {
        this.mScriptBeginDelimiter = begin;
        this.mScriptEndDelimiter = end;
    }
    get NullableSyntaxEnabled() { return this.mNullableSyntaxEnabled; }
    set NullableSyntaxEnabled(value) { this.mNullableSyntaxEnabled = value; }
    get StringBeginDelimiter() { return this.mStringBeginDelimiter; }
    get StringEndDelimiter() { return this.mStringEndDelimiter; }
    get ScriptBeginDelimiter() { return this.mScriptBeginDelimiter; }
    get ScriptEndDelimiter() { return this.mScriptEndDelimiter; }

    static SkipUtf8Bom(txt) {
        if (txt !== null && txt !== undefined && txt.length > 0 && txt.charCodeAt(0) === 0xFEFF) {
            return txt.substring(1);
        }
        return txt;
    }
    static Mac2Unix(txt) {
        const ix = txt.indexOf('\r');
        if (ix >= 0 && ix + 1 < txt.length && txt[ix + 1] !== '\n') {
            return txt.replace(/\r/g, '\n');
        }
        return txt;
    }
    static Text2Dos(txt) {
        let ix = txt.indexOf('\n');
        if (ix > 0) {
            if (txt[ix - 1] !== '\r') return txt.replace(/\n/g, '\r\n');
        }
        else {
            ix = txt.indexOf('\r');
            if (ix >= 0) return txt.replace(/\r/g, '\r\n');
        }
        return txt;
    }
    static Text2Unix(txt) {
        const ix = txt.indexOf('\r');
        if (ix >= 0) {
            if (ix + 1 < txt.length && txt[ix + 1] === '\n') return txt.replace(/\r\n/g, '\n');
            return txt.replace(/\r/g, '\n');
        }
        return txt;
    }
    static Text2Mac(txt) {
        const ix = txt.indexOf('\n');
        if (ix > 0) {
            if (txt[ix - 1] !== '\r') return txt.replace(/\n/g, '\r');
            return txt.replace(/\r\n/g, '\r');
        }
        return txt;
    }

    static IsBinaryDsl(data, start) {
        if (data === null || data === undefined || data.length < DslFile.c_BinaryIdentity.length) return false;
        const id = DslFile.BinaryIdentity;
        for (let i = 0; i < id.length && start + i < data.length; ++i) {
            if (id[i] !== data[start + i]) return false;
        }
        return true;
    }

    static get DontLoadComments() { return DslGlobals.DontLoadComments; }
    static set DontLoadComments(value) { DslGlobals.DontLoadComments = value; }
}

DslFile.c_BinaryIdentity = 'BDSL';
DslFile.BinaryIdentity = utf8Encode(DslFile.c_BinaryIdentity);

export { DslFile };
