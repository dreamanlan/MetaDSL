// pg_deobfuscate.js - renames the obfuscated identifiers of pg.c using the semantic
// mapping tables (pg_map_*.json) and inserts structural comments. Logic is untouched.
const fs = require('fs');
const path = require('path');

const src = fs.readFileSync(path.join(__dirname, 'pg.c'), 'utf8');
const map = {};
for (let i = 1; i <= 5; ++i) {
    Object.assign(map, JSON.parse(fs.readFileSync(path.join(__dirname, `pg_map_${i}.json`), 'utf8')));
}

// Coverage check: every obfuscated identifier must have a mapping.
const ids = new Set([...src.matchAll(/\bl\d+\b/g)].map(m => m[0]));
const missing = [...ids].filter(id => !(id in map)).sort((a, b) => Number(a.slice(1)) - Number(b.slice(1)));
if (missing.length) {
    console.log('UNMAPPED:', missing.join(','));
}
const newNames = new Set(Object.values(map));
if (newNames.size !== Object.keys(map).length) {
    console.log('note: some new names are shared by several old ids (allowed in disjoint scopes)');
}

let out = src.replace(/\bl\d+\b/g, id => map[id] || id);

const header = `/*
The Parser Generator (c) 2001-2022 by DMR, all rights reserved

Readable edition of pg.c (SLK parser generator, LL(k) with generalized conflict
resolution; SLR/LALR/full LR are optional). This file was produced by renaming
the obfuscated l<number> identifiers to semantic names and adding comments.
The algorithm is byte-for-byte the original logic, including the local
modifications listed in modified.txt (cmain entry, -Ps parse stack size,
C#-specific templates, namespace handling, IVisitor.Accept, ...).

Overview of the pipeline (see cmain):
  1. Parse command line options (generate_flags / grammar_flags bit masks).
  2. read_file the grammar, select_scanner (SLK or YACC style), parse_grammar.
  3. analyze_grammar: undefined/unused/equivalent symbols, left recursion,
     left factoring requirements, nullable and multiple-nullable productions.
  4. Optional grammar transformations (-Ld/-Li/-l/-Rr/-Ru/-Rd/-Sn/-St).
  5. compute_first_follow: FIRST/FOLLOW sets and left-corner sets.
  6. build_ll_table (LL) or build_lr_parser (SLR/LALR/LR) or resolve_only_conflicts.
  7. resolve_conflicts: generalized k-lookahead conflict resolution, producing
     the Parse and Conflict tables.
  8. generate_parser: emit Parse/Constants/String/Keywords/Execute files for
     C, C++, C#, Java or JavaScript, using the code templates at the end of
     this file and the per-language LanguageDescriptor records.

Core data structures:
  Symbol             grammar symbol (terminal/nonterminal/action), with FIRST/
                     FOLLOW/left-corner sets and per-symbol analysis flags.
  SymbolSetNode      singly linked set of symbols (firsts/follows/...).
  TableEntry         LL parse table row entry: token -> production.
  Config             production + dot position (+ link/origin), the unit used
                     by the conflict resolver.
  ConflictProduction one production involved in a conflict and its configs.
  Conflict           a parse table conflict, with lookahead tokens and level.
  ConflictEntry/Row/Level   the Conflict table: rows per nonterminal, grouped
                     by lookahead level.
  LRItem/LRState/LRAction/LRGoto  LR automaton items, states and transitions.
  ProductionList     growable list of productions used by the EBNF expander.

Naming conventions for bit masks:
  grammar_flags    scanner/grammar transformation options (low 16 bits).
  generate_flags   output language and content options (0x100 C, 0x200 C++,
                   0x400 Java, 0x800 C#, 0x1000 C-with-classes, 0x2000 JS;
                   0x1 compact tables, 0x4 LL parse, 0x8 LR parse, ...).
  ConflictStatus   RESOLVED/MERGED/EXTENDED/AMBIGUOUS/UNRESOLVABLE/CONDITIONAL/
                   IGNORED in the high 16 bits; low 16 bits = lookahead level.

Section banners mark the major phases below.
*/

`;

// The extend_conflict/set_lookahead_symbol parameter shares its name with the Conflict typedef.
out = out.replace(/void\* Conflict,/g, 'void* conflict_ptr,').replace(/\(Conflict\*\)Conflict/g, '(Conflict*)conflict_ptr');

out = out.replace(/register LRCell\* table = table;/g, 'register LRCell* cell = table;')
    .replace(/while \(\+\+table < cursor\)/g, 'while (++cell < cursor)')
    .replace(/        \* table;/g, '        * cell;')
    .replace(/table = free_slot \+ row->token;/g, 'cell = free_slot + row->token;')
    .replace(/table->row_index/g, 'cell->row_index')
    .replace(/table->entry_value/g, 'cell->entry_value')
    .replace(/table->block/g, 'cell->block')
    .replace(/register LRCell\* table;/g, 'register LRCell* cell;')
    .replace(/    table = table;/g, '    cell = table;')
    .replace(/register Conflict\* conflict = \(Conflict\*\)conflict_ptr;/g, 'register Conflict* conflict_state = (Conflict*)conflict_ptr;')
    .replace(/register ConflictProduction\* production = conflict->configs;/g, 'register ConflictProduction* production = conflict_state->configs;');

// Fail-fast guard (addition, not in the original pg.c): generalized k-lookahead
// conflict resolution can generate an unbounded number of conflicts on grammars
// with many nullable productions (simple.txt -LR grows past thousands of conflicts
// at level 2 without ever finishing). Abort with a clear diagnostic instead of
// hanging forever. Grammars whose resolution completes normally are unaffected.
const budgetAnchor = 'uint extend_conflict(void* conflict_ptr,';
const budgetIx = out.indexOf(budgetAnchor);
if (budgetIx < 0) {
    console.log('extend_conflict budget anchor not found');
}
else {
    const budgetDecl = `
/* Maximum number of new conflicts created during k-lookahead resolution before
   giving up (override at compile time with -DSLK_CONFLICT_BUDGET=n). */
#ifndef SLK_CONFLICT_BUDGET
#define SLK_CONFLICT_BUDGET 10000
#endif
static unsigned long slk_conflicts_created = 0;
`;
    out = out.slice(0, budgetIx) + budgetDecl + out.slice(budgetIx);
    const createAnchor = '        created_conflict = new_conflict_node();';
    const createIx = out.indexOf(createAnchor, budgetIx);
    if (createIx < 0) {
        console.log('new_conflict_node anchor not found');
    }
    else {
        const guard = `        if (++slk_conflicts_created > SLK_CONFLICT_BUDGET) {
            fatal_error(1210, "conflict resolution budget exceeded: the grammar generates too many conflicts for generalized k-lookahead resolution (use default LL(k) or -LA, or reduce -k)");
        }
`;
        out = out.slice(0, createIx) + guard + out.slice(createIx);
    }
}

const banners = [
    ['int cmain(', '================ Command line parsing and the main driver ================'],
    ['void fatal_error(', '================ Error reporting ================'],
    ['uint analyze_grammar(', '================ Grammar analysis (undefined/unused/left recursion/factoring) ================'],
    ['uint left_derives(', '================ Derivation queries ================'],
    ['compute_left_corners(void)', '================ FIRST/FOLLOW and left-corner computation ================'],
    ['void initialize_grammar(', '================ Grammar storage and symbol numbering ================'],
    ['uint compute_first_follow(', '================ Nullable/FIRST/FOLLOW fixed-point computation ================'],
    ['uint build_ll_table(', '================ LL(1) parse table construction ================'],
    ['void generate_parser(', '================ Parser file generation (all target languages) ================'],
    ['next_token(void)', '================ SLK grammar scanner ================'],
    ['static int\nyacc_next_token(', '================ YACC grammar scanner ================'],
    ['uint resolve_only_conflicts(', '================ Conflict resolver only (-Gc) ================'],
    ['uint resolve_conflicts(', '================ Generalized k-lookahead conflict resolution ================'],
    ['expand_ebnf(void)', '================ EBNF expansion and grammar rewriting ================'],
    ['int convert_iso_grammar(', '================ ISO/IEEE grammar format converters ================'],
    ['static char c_token_error_action_decls', '================ C/C++ output code templates ================'],
    ['static char m_get_production_array', '================ Java/C# output code templates ================'],
    ['static char js_get_production_array', '================ JavaScript output code templates ================'],
    ['typedef struct LanguageDescriptor', '================ Per-language output descriptors ================'],
    ['build_lr_parser(int lr_type)', '================ LR automaton construction and LR table output ================'],
];

for (const [anchor, banner] of banners) {
    const ix = out.indexOf(anchor);
    if (ix < 0) {
        console.log('banner anchor not found:', anchor);
        continue;
    }
    out = out.slice(0, ix) + '// ' + banner + '\n' + out.slice(ix);
}

fs.writeFileSync(path.join(__dirname, 'pg_readable.c'), header + out, 'utf8');
console.log('written pg_readable.c, length', header.length + out.length);
