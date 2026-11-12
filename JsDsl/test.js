// test.js - standalone tests for the JavaScript MetaDSL port (no C# reference needed).
// Run: node test.js
// Differential tests against the C# implementation live outside the library (e:/tmp).

'use strict';

const Dsl = require('./index.js');

let failures = 0;
let checks = 0;
function check(cond, name, detail) {
    ++checks;
    if (!cond) {
        ++failures;
        console.log('FAIL', name, detail === undefined ? '' : detail);
    }
}

const samples = [
    'foo(1,2);',
    'foo(1, "str", 0x1f, 3.14, -5, +6);',
    'if($a > 1 && $b <= 2){ foo($a); }else{ bar(); };',
    'script(test)params($a,$b)params2($c);',
    'a = b ? c : d;',
    'x = -y * 2 + 3 % 4;',
    'obj.method(1).field::other->ptr;',
    'foo?(1,2);',
    'bar!(3);',
    'var x = $"hello";',
    'foo(){: echo "hi"; :};',
    'for(;;){ break; };',
    'foo(1,2)(3,4){ bar(); };',
    '// line comment\nfoo(1); // trailing\n/* block */\nbar(2);',
    '@@delimiter(string, "[[", "]]");\nfoo([[raw string]]);',
    'a = `infix` b;',
    'foo[: a; b :];',
    'foo(: a; b :);',
    'foo<: a; b :>;',
    'foo{% a; b %};',
    'foo[% a; b %];',
    'foo(% a; b %);',
    'foo<% a; b %>;',
    'v = a?.b;',
    'v = a?[1];',
    'v = a?(1);',
    'v = a?->b;',
    's = "esc\\n\\t\\u0041\\x42";',
    't = @"no""escape";',
    'u = $@"dollar""raw";',
    'for(i=0;i<10;++i){ x += i; };',
    'a && b || c ?? d;',
    'v = o.p->*q.*r;',
    'f(1,2,)(3);',
    'empty();;',
    'x = 1e+3 + 0x1p-2;',
];

function load(src) {
    const file = new Dsl.DslFile();
    const logs = [];
    const ok = file.LoadFromString(src, m => logs.push(m));
    return { file, ok, logs };
}

// Text parse + ToScriptString roundtrip (ToScriptString emits statement separators).
for (const src of samples) {
    const r1 = load(src);
    check(r1.ok, 'parse: ' + src, r1.logs.join('|'));
    if (!r1.ok) continue;
    const out1 = r1.file.ToScriptString();
    const r2 = load(out1);
    check(r2.ok, 'reparse: ' + src, r2.logs.join('|'));
    if (!r2.ok) continue;
    check(r2.file.ToScriptString() === out1, 'roundtrip: ' + src,
        JSON.stringify(out1) + ' != ' + JSON.stringify(r2.file.ToScriptString()));
    check(r2.file.DslInfos.length === r1.file.DslInfos.length, 'roundtrip count: ' + src);
}

// Structural checks (top-level single-call statements are simplified to FunctionData).
{
    const r = load('foo(1,2);');
    const func = r.file.DslInfos[0];
    check(func.GetId() === 'foo', 'statement id');
    check(func.GetParamNum() === 2, 'param num');
    check(func.GetParamId(0) === '1' && func.GetParamId(1) === '2', 'param ids');
    check(func.IsSemiColonSeparator(), 'semicolon separator');
}
{
    const r = load('a = b ? c : d;');
    const assign = r.file.DslInfos[0];
    check(assign.GetId() === '=' && assign.GetParamNum() === 2, 'assignment shape');
    // The ternary operator is represented as op1(cond)(true_val)op2(false_val).
    const ternary = assign.GetParam(1);
    check(ternary instanceof Dsl.StatementData && ternary.Functions.length === 2, 'ternary statement');
    const first = ternary.First.AsFunction;
    check(first !== null && first.IsTernaryOperatorParamClass(), 'ternary param class');
    check(first.LowerOrderFunction.GetId() === '?', 'ternary first op');
    check(ternary.Functions[1].GetId() === ':', 'ternary second op');
}
{
    const r = load('x = -5;');
    // unary minus on a number literal is folded into the literal
    const assign = r.file.DslInfos[0];
    check(assign.GetParam(1).GetId() === '-5', 'negative number folding', assign.GetParam(1).GetId());
}
{
    const r = load('foo(){: echo "hi"; :};');
    const func = r.file.DslInfos[0];
    check(func.HaveExternScript() && func.GetParamId(0) === ' echo "hi"; ', 'extern script',
        JSON.stringify(func.GetParamId(0)));
}
{
    const r = load('v = a?.b;');
    const nullable = r.file.DslInfos[0].GetParam(1).AsFunction;
    check(nullable !== null && nullable.IsHighOrder &&
        nullable.LowerOrderFunction.IsQuestionNullableOperatorParamClass(), 'nullable operator class');
}

// Binary BDSL roundtrip: bytes are stable and the info counts survive.
for (const src of samples) {
    const r1 = load(src);
    if (!r1.ok) continue;
    const bin1 = r1.file.SaveBinaryCode();
    check(Dsl.DslFile.IsBinaryDsl(bin1, 0), 'binary identity: ' + src);
    const file2 = new Dsl.DslFile();
    file2.LoadBinaryCode(bin1);
    check(file2.DslInfos.length === r1.file.DslInfos.length, 'binary count: ' + src);
    const bin2 = file2.SaveBinaryCode();
    check(Buffer.from(bin1).equals(Buffer.from(bin2)), 'binary roundtrip: ' + src);
}

// Syntax errors must be reported and clear the infos.
for (const src of ['foo(1', 'foo){', 'foo(1,2))']) {
    const r = load(src);
    check(!r.ok, 'error expected: ' + src);
    check(r.file.DslInfos.length === 0, 'error clears infos: ' + src);
    check(r.logs.length > 0, 'error logged: ' + src);
}

console.log(failures === 0 ? `ALL PASS (${checks} checks)` : `FAILURES: ${failures} of ${checks}`);
process.exitCode = failures === 0 ? 0 : 1;
