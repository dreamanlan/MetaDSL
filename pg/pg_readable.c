/*
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

/*
The Parser Generator (c) 2001-2022 by DMR, all rights reserved
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef struct Symbol
{
    struct
        Symbol* next;
    int type;
    int number;
    char* name;
    char* define_name;
    struct
        SymbolSetNode* firsts,
        * follows,
        * la_follows,
        * left_corners,
        * follow_nonterminals;
    struct
        TableEntry* table;
    int table_count;
    struct
        Config* configs;
    uint production_count;
    uint use_count;
    uint nullable : 1,
        null_production : 1,
        undefined : 1,
        unused : 1,
        direct_left_recursive : 1,
        indirect_left_recursive : 1,
        needs_direct_factoring : 1,
        needs_indirect_factoring : 1,
        infinite_derivation : 1,
        ignore_conflicts : 1,
        ebnf_token : 1,
        ebnf_nonterminal : 1,
        prefixed_name : 1,
        escaped : 1,
        ebnf_optional : 1,
        start_symbol : 1,
        unit_production : 1,
        equivalent : 1,
        nullable_follows_self : 1,
        conditional : 1;
} Symbol;
extern Symbol* cur_symbol;
extern int trace_level,
verbose_level,
aggressive_check,
compare_config_links,
quiet,
unique_ebnf_names,
conserve_memory,
parse_stack_size;
extern char* dot_string;
extern uint start_state,
state_count;
// ================ Error reporting ================
void fatal_error(int error_code,
    char* error_message);
void note_left_recursion(void);
void note_error(void);
char*
str_dup(char* str);
Symbol* find_symbol(register char* name);
Symbol* new_symbol(int type,
    int number,
    char* name);
void print_symbol_table(void);
uint line_number(void);
char*
cur_token_text(void);
uint ebnf_enabled(void);
char*
action_prefix(char* name);
uint action_prefix_len(char* name);
int (*select_scanner(char* file_name,
    uint grammar_flags))(void);
void parse_grammar(int (*next_token)(void),
    int display);
char*
symbol_type_name(uint type_index);
// ================ Parser file generation (all target languages) ================
void generate_parser(char* parser_name,
    char* namespace_name,
    uint generate_flags,
    uint grammar_flags);
void generate_parser_forward(char* parser_name,
    char* namespace_name,
    int named_actions,
    uint generate_flags,
    FILE* out_file,
    int yacc_grammar);
void generate_managed_parser(char* parser_name,
    char* namespace_name,
    int named_actions,
    uint generate_flags,
    FILE* out_file,
    int yacc_grammar);
void generate_c_parser(char* parser_name,
    char* namespace_name,
    int named_actions,
    uint generate_flags,
    FILE* out_file,
    int yacc_grammar);
void generate_string_file(char* parser_name,
    char* namespace_name,
    uint generate_flags);
// ================ Generalized k-lookahead conflict resolution ================
uint resolve_conflicts(uint show_conflict_numbers,
    uint only_conflict,
    uint only_deep_conflict,
    uint* conflict_status);
// ================ Derivation queries ================
uint left_derives(Symbol* target_symbol,
    Symbol* source_symbol,
    uint display);
void display_left_derivations(char* nonterminal_name);
void remove_unused(char* nonterminal_name);
void substitute_equivalent(char* nonterminal_name,
    uint substitute_nonterminal_flag,
    uint substitute_terminal_flag);
void remove_left_recursion(char* nonterminal_name);
uint check_duplicate_rhs(void);
uint check_duplicate_productions(void);
void remove_duplicate_productions(void);
uint left_factor_indirect(char* nonterminal_name);
uint left_factor_direct(char* nonterminal_name);
uint left_factor_old(char* nonterminal_name);
void // ================ EBNF expansion and grammar rewriting ================
expand_ebnf(void);
void restore_ebnf(void);
// ================ ISO/IEEE grammar format converters ================
int convert_iso_grammar(char* input_name,
    char* output_name);
int convert_ieee_grammar(char* input_name,
    char* output_name);
char*
read_file(char* path_name,
    size_t* data_size);
char*
token_define_name(char* prefix,
    char* suffix,
    Symbol** symbol,
    int make_unique);
int // ================ LR automaton construction and LR table output ================
build_lr_parser(int lr_type);
void resolve_lr_conflict(uint token,
    uint conflict_number);
void write_productions(FILE* out_file,
    uint generate_flags);
void write_lr_tables(char* parser_name,
    char* namespace_name,
    uint generate_flags,
    FILE* out_file);
void print_lr_states(int slr_grammar);
void print_lr_state(int number);
void print_lr_parse_table(void);
void print_all_symbols(void);
typedef struct TableEntry
{
    struct TableEntry* next;
    uint token,
        production;
} TableEntry;
extern Symbol** nonterminals,
** terminals,
** actions,
*** productions;
extern uint nonterminal_count,
terminal_count,
action_count,
production_count,
ignored_conflict_count,
conditional_count,
max_production_length,
start_conflict,
start_action,
start_symbol_number;
// ================ Grammar storage and symbol numbering ================
void initialize_grammar(void);
// ================ Nullable/FIRST/FOLLOW fixed-point computation ================
uint compute_first_follow(void);
// ================ LL(1) parse table construction ================
uint build_ll_table(void);
Symbol**
copy_production(register Symbol** production);
Symbol***
insert_production(Symbol** production_number,
    Symbol*** configs);
void delete_production_at(register Symbol*** production);
void add_production_copy(Symbol** production);
void add_production(register Symbol** production);
uint productions_equal(register Symbol** prod_a,
    register Symbol** prod_b);
int production_number_of(register Symbol* lhs);
void register_symbol(Symbol* symbol);
void terminal_to_nonterminal(register Symbol* symbol);
void set_table_entry(register TableEntry* table,
    register int token,
    int conflict_number);
void replace_conflict_entry(register TableEntry* table,
    int conflict_number,
    int new_production_number);
uint rhs_nullable(register Symbol** dot);
void update_nullable(Symbol* nonterminal);
void print_first_sets(void);
void print_follow_sets(void);
void print_debug_forward(void);
void print_nullable(void);
void print_parse_table(int use_lr);
void print_productions(void);
void print_production_integers(void);
void print_production(char* indent,
    Symbol** production);
void print_production_number(int number);
void print_productions_of(Symbol* nonterminal);
typedef struct Config
{
    struct Config* next;
    struct Symbol** lhs,
        ** dot;
    struct Config* link;
    uint origin;
} Config;
enum ConfigType
{
    CONFIG_BASE = 1,
    CONFIG_CLOSURE = 2,
    CONFIG_EXTENDED = 3
};
Config*
new_config(Symbol** lhs,
    Symbol** dot,
    Config* link,
    uint origin);
uint add_config_front(Config** list,
    register Config* config);
uint add_config(Config** list,
    Symbol** lhs,
    Symbol** dot,
    Config* link,
    Config** out_config,
    uint origin);
uint add_configs(Config** dest_configs,
    register Config* src_configs,
    Config* link);
Config*
find_shared_nonterminal_config(register Config* dest_configs,
    register Config* src_configs);
uint configs_equal(register Config* dest_configs,
    register Config* src_configs);
void free_config(register Config* node);
void free_config_list(register Config** list);
Config*
copy_config_list(register Config* list);
void stash_config_list(Config** list);
void flush_stashed_configs(void);
int configs_have_nonterminal(Config* list);
void print_config(Symbol** lhs,
    Symbol** dot);
void print_configs(Config** list);
extern uint max_lookahead,
base_conflict_count,
conflict_count;
enum ConflictStatus
{
    RESOLVED = 0x00010000,
    MERGED = 0x00020000,
    EXTENDED = 0x00040000,
    AMBIGUOUS = 0x00100000,
    UNRESOLVABLE = 0x01000000,
    CONDITIONAL = 0x02000000,
    IGNORED = 0x04000000,
    AMBIGUOUS_OR_UNRESOLVABLE = (AMBIGUOUS |
    UNRESOLVABLE),
    MERGED_OR_EXTENDED = (MERGED |
        EXTENDED),
    RESOLVED_MASK = (MERGED |
        RESOLVED |
        EXTENDED),
    STATUS_MASK = 0x7FFF0000,
    LEVEL_MASK = 0x0000FFFF
};
typedef struct ConflictProduction
{
    struct
        ConflictProduction* next;
    int number;
    uint conflict;
    Symbol* lookahead;
    Config* configs;
} ConflictProduction;
typedef struct Conflict
{
    struct
        Conflict* next;
    ConflictProduction* configs;
    void* back_link;
    uint lookahead_level;
    uint number;
    uint resolved;
    Symbol** lookahead_tokens;
    uint lr_state;
    Symbol* first_token;
} Conflict;
ConflictProduction*
new_conflict_production(int number,
    uint conflict,
    Config* configs);
ConflictProduction*
copy_conflict_production_forward(register ConflictProduction* conflict_production);
// ================ Conflict resolver only (-Gc) ================
uint resolve_only_conflicts(void);
uint add_conflict(Symbol* lookahead_tokens,
    ConflictProduction* old_production,
    ConflictProduction* production_number,
    uint lr_state);

/* Maximum number of new conflicts created during k-lookahead resolution before
   giving up (override at compile time with -DSLK_CONFLICT_BUDGET=n). */
#ifndef SLK_CONFLICT_BUDGET
#define SLK_CONFLICT_BUDGET 10000
#endif
static unsigned long slk_conflicts_created = 0;
uint extend_conflict(void* conflict_ptr,
    Symbol* lookahead_tokens,
    int old_production,
    ConflictProduction* production_number);
void remove_conflict(uint conflict_number);
void promote_resolved_conflicts(void);
Conflict*
get_conflicts(void);
Conflict*
find_conflict(uint conflict_number);
uint compare_conflict_productions(register ConflictProduction* production);
uint set_lookahead_symbol(void* conflict_ptr,
    Symbol* lookahead_tokens,
    int production_number);
uint report_conflicts(uint show_conflict_numbers,
    uint* conflict_status,
    uint resolved_level);
void print_conflict_pair(Symbol* lookahead_tokens,
    int old_production,
    int production_number);
void print_lookaheads(uint show_conflict_numbers);
void print_conflicts(uint show_conflict_numbers);
typedef struct ConflictEntry
{
    struct ConflictEntry* next;
    int token,
        production;
} ConflictEntry;
typedef struct ConflictRow
{
    struct ConflictRow* next;
    ConflictEntry* entries;
    Symbol* nonterminal;
} ConflictRow;
typedef struct ConflictLevel
{
    struct ConflictLevel* next;
    ConflictRow* rows;
} ConflictLevel;
ConflictRow*
new_conflict_row(ConflictLevel* conflict_level,
    Symbol* nonterminal);
uint merge_conflict_row(ConflictRow* row,
    register struct
    SymbolSetNode* firsts,
    void* conflict,
    struct
    ConflictProduction* production_number);
ConflictLevel*
new_conflict_level(void);
ConflictLevel*
get_conflict_levels(void);
void set_conflict_entry(ConflictRow* row,
    int token,
    int conflict_number);
void remove_conflict_entries(int conflict_number);
void print_conflict_table(void);
void print_conflict_traces(void);
typedef struct SymbolSetNode
{
    struct SymbolSetNode* next;
    struct Symbol* symbol;
} SymbolSetNode;
// ================ Grammar analysis (undefined/unused/left recursion/factoring) ================
uint analyze_grammar(uint ignore_warnings,
    uint reserved_flag);
uint needs_direct_factoring_single(int display,
    Symbol* nonterminal);
uint needs_direct_factoring(int display);
uint needs_indirect_factoring(int display);
uint needs_any_factoring(void);
uint mark_unused(void);
void write_grammar(char* grammar_output_name,
    int use_ebnf);
uint set_add_unique_front(SymbolSetNode** list,
    Symbol* symbol);
uint set_union_front(SymbolSetNode** dest_configs,
    register SymbolSetNode* src_configs);
uint set_add_unique(SymbolSetNode** list,
    Symbol* symbol);
uint set_union(SymbolSetNode** dest_configs,
    register SymbolSetNode* src_configs);
uint set_contains(register SymbolSetNode* list,
    Symbol* symbol);
Symbol* set_intersect(register SymbolSetNode* set_a,
    register SymbolSetNode* set_b);
int sets_equal_unordered(register SymbolSetNode* set_a,
    register SymbolSetNode* set_b);
int sets_equal_ordered(register SymbolSetNode* set_a,
    register SymbolSetNode* set_b);
Symbol* set_intersect_infinite(register SymbolSetNode* set_a,
    register SymbolSetNode* set_b);
void free_symbol_set(SymbolSetNode* list);
uint reused_set_count(void);
void print_firsts_nonterminals(void);
void print_follows_nonterminals(void);
int trace_level = 0,
verbose_level = 0,
aggressive_check = 0,
compare_config_links = 1,
quiet = 0,
unique_ebnf_names = 1,
conserve_memory = 0,
parse_stack_size = 512;
char* dot_string = "$$";
static int in_grammar_parse = 0,
has_left_recursion = 0,
error_count = 0;
static char version_string[] =
"pg  V5.13  (c) 2001-2022 by DMR\n";
static char*
usage_text =
"LL(k) parser generator and generalized conflict resolver using k lookahead\n"
"Usage: pg  input_filename [-options] \n"
"  -a   append parser name to header file token defines (see -n below) \n"
"  -b   enable aggresive heuristic ambiguity checking \n"
"  -c   disable table compacting \n"
"  -cc  generate instance model C code (C with Classes) \n"
"  -cs  generate C#  code \n"
"  -C++ generate C++ code \n"
"  -Cr  -Gc with conflicts specified as __dot_ configs in the grammar \n"
"  -d   display parse derivation of the input grammar for debugging \n"
"  -dot use ^G for dot in configs instead of $$, prints as dot but beeps in console \n"
"  -Da  display all -D values \n"
"  -Dc  display all conflict traces for debugging only \n"
"  -Dd[=<symbol name>] display nonterminals that can left derive <symbol name> \n"
"  -De  display nonterminals that can derive the empty string, epsilon \n"
"  -Df  display first and follow sets \n"
"  -Dl  display lookahead strings for resolved conflicts \n"
"  -Dp  display productions \n"
"  -Dr  display LR states \n"
"  -Ds  display symbol table \n"
"  -Dt  display parse tables \n"
"  -E<n> convert EBNF grammar to SLK format, n=1 is IEEE, n=2 is ISO \n"
"  -e    disable EBNF grammar support \n"
"  -f=<filename>   name of the file for the output grammar \n"
"  -Fa  force _action_ naming so __ can be for user tokens \n"
"  -g   generate the parser even if the grammar is ambiguous \n"
"  -Ga  do not generate anything \n"
"  -Gc  generate conflict resolver only, no parser \n"
"  -Gd  generate parse derivation code in get_predicted_entry for debugging \n"
"  -Gn  do not generate nonterminal strings used for displaying \n"
"  -Gp  do not generate the production strings used for displaying \n"
"  -Gs  do not generate action strings used for displaying \n"
"  -Gt  do not generate terminal strings used for displaying \n"
"  -Gu  do not generate unique names for duplicate EBNF nonterminals \n"
"  -i   ignore non-fatal warnings \n"
"  -j   generate java code \n"
"  -js  generate javascript code \n"
"  -k=<maximum k value to test for in the grammar>  default k=7 \n"
"  -l=<nonterminal name>  indirect left factor nonterminal the old way \n"
"  -Ld[=<nonterminal name>]  direct left factor nonterminal or the grammar \n"
"  -Li[=<nonterminal name>]  indirect left factor nonterminal or the grammar \n"
"  -[LA]LR  LALR or LR grammar, (LRS for SLR grammar) \n"
"  -m   conserve memory by reusing internal structures \n"
"  -n=<name of the parser>  default is Slk, must be length 3 \n"
"  -ns=<namespace or package name>  default is no namespace \n"
"  -O[=<n>]  only analyze conflict number n ( -1 = don't show conflict numbers )\n"
"  -o[=<n>]  only analyze the nth conflict at each level above level 1\n"
"  -Ps=<parse stack size>   size in the generated parse routine, default=512 \n"
"  -q   quiet mode operation \n"
"  -Rd  remove duplicate productions \n"
"  -Rr[=<nonterminal name>]  remove left recursion \n"
"  -Ru[=<nonterminal name>]  remove unused nonterminals \n"
"  -Sn[=<nonterminal name>]  substitute nonterminals for equivalent ones \n"
"  -St[=<nonterminal name>]  substitute terminals for equivalent nonterminals \n"
"  -Tl=<filename>   load token strings from a file \n"
"  -Tw=<filename>   write token strings to a file \n"
"  -t[=<n>]  set grammar transformations trace level to n for debugging only \n"
"            ( no =<n> sets t=1, ( 2, 3, 4 ) ) \n"
"  -v[=<n>]  set verbose output level to n ( no =<n> sets v=1, ( 2, 3 ) ) \n"
"  -Xo  eXpand opt/_opt symbols in an LR grammar to reduce conflicts \n"
"  -y[s]  yacc style scanner is used, s=strip out all actions \n";
static char*
usage_debug_text =
"  -t=-1 -Df to display nonterminal follows for LL debugging \n"
"  -t=-1 to display LR states during build for debugging \n"
"  -t=-2,-3,-4 to display resolve config sets for debugging \n";
static int
load_tokens(char* file_name)
{
    register FILE* file;
    char line_buffer[1024];
    int line_number = 0,
        number,
        errors = 0,
        end_of_file = 0;
    char saved_char;
    Symbol* symbol;
    register char* token_start,
        * cursor;
    file = fopen(file_name, "r");
    if (!file) {
        perror(file_name);
        errors = 1;
        return errors;
    }
    token_start = cursor = line_buffer;
    *token_start = '\0';
    for (;;) {
        switch (*token_start) {
        case '\0':
        case '\n':
        case '\r':
            end_of_file = NULL == fgets(line_buffer, 1024, file);
            ++line_number;
            if (end_of_file) {
                break;
            }
            token_start = cursor = line_buffer;
            break;
        case ' ':
        case '\t':
            token_start = ++cursor;
            break;
        case '/':
            if (*(token_start + 1) == '/') {
                *token_start = '\0';
                break;
            }
        default:
            while (*cursor && !(*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                ++cursor;
            }
            saved_char = *cursor;
            *cursor = '\0';
            symbol = find_symbol(token_start);
            if (symbol) {
                printf("%s: %u: %s: cannot redefine name \n", file_name,
                    line_number, token_start);
                *cursor = saved_char;
                errors = 1;
                break;
            }
            else {
                symbol = new_symbol(2, 0, token_start);
                *cursor = saved_char;
                while (*cursor && (*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                    ++cursor;
                }
                number = atoi(cursor);
                if (number) {
                    symbol->number = number;
                }
                else {
                    errors = 1;
                    break;
                }
                register_symbol(symbol);
                *token_start = '\0';
            }
        }
        if (errors || end_of_file) {
            break;
        }
    }
    if (errors) {
        printf("%s: %u: syntax error \n", file_name, line_number);
    }
    fclose(file);
    return errors;
}
static FILE*
write_tokens(char* file_name)
{
    register Symbol** lookahead_tokens = terminals;
    FILE* file;
    file = fopen(file_name, "w");
    if (file) {
        fprintf(file, "\n// %s - token strings file "
            "generated by the SLK parser generator \n\n",
            file_name);
        while (*++lookahead_tokens) {
            fprintf(file, "%32s  %8u\n", (*lookahead_tokens)->name, (*lookahead_tokens)->number);
        }
    }
    else {
        perror(file_name);
    }
    if (file) {
        fclose(file);
    }
    return file;
}
static char*
expand_opt_file(char* input_file_name)
{
    register char* opt_pos;
    char* after_opt;
    int opt_length = 4;
    int changed = 0;
    int blank_only;
    FILE* input_file, * out_file;
    static int pass_count = 0;
    static char grammar_output_name[128];
    static char line_buffer[1024];
    input_file = fopen(input_file_name, "r");
    if (!input_file) {
        perror(input_file_name);
        return NULL;
    }
    sprintf(grammar_output_name, "%s.%u", input_file_name, ++pass_count);
    out_file = fopen(grammar_output_name, "w");
    if (!out_file) {
        perror(grammar_output_name);
        return NULL;
    }
    while (fgets(line_buffer, 1024, input_file)) {
        opt_pos = strstr(line_buffer, "_opt");
        opt_length = 4;
        if (!opt_pos) {
            opt_pos = strstr(line_buffer, "opt");
            opt_length = 3;
        }
        if (!opt_pos || opt_pos == line_buffer) {
            fputs(line_buffer, out_file);
            continue;
        }
        after_opt = opt_pos + opt_length;
        if (*after_opt) {
            if (!(*after_opt == ' ' || *after_opt == '\n' || *after_opt == '\r' || *after_opt == '\t' || *after_opt == '\v' || *after_opt == '\f')) {
                fputs(line_buffer, out_file);
                continue;
            }
        }
        if ((*(opt_pos - 1) == ' ' || *(opt_pos - 1) == '\n' || *(opt_pos - 1) == '\r' || *(opt_pos - 1) == '\t' || *(opt_pos - 1) == '\v' || *(opt_pos - 1) == '\f')) {
            fputs(line_buffer, out_file);
            continue;
        }
        changed = 1;
        strcpy(opt_pos, after_opt);
        fputs(line_buffer, out_file);
        after_opt = opt_pos;
        for (--opt_pos; opt_pos > line_buffer; --opt_pos) {
            if ((*opt_pos == ' ' || *opt_pos == '\n' || *opt_pos == '\r' || *opt_pos == '\t' || *opt_pos == '\v' || *opt_pos == '\f')) {
                break;
            }
        }
        strcpy(opt_pos, after_opt);
        blank_only = 1;
        for (opt_pos = line_buffer; *opt_pos; ++opt_pos) {
            if (!(*opt_pos == ' ' || *opt_pos == '\n' || *opt_pos == '\r' || *opt_pos == '\t' || *opt_pos == '\v' || *opt_pos == '\f')) {
                blank_only = 0;
            }
        }
        if (blank_only) {
            strcpy(line_buffer, "    _epsilon_\n");
        }
        fputs(line_buffer, out_file);
    }
    fclose(input_file);
    fclose(out_file);
    if (changed && pass_count < 19) {
        return grammar_output_name;
    }
    else {
        return NULL;
    }
}
// ================ Command line parsing and the main driver ================
int cmain(int argc,
    char* argv[])
{
    register char* arg;
    register int grammar_flags = (0x00004000);
    char* grammar_text,
        * input_file_name = NULL,
        * grammar_output_name = NULL;
    size_t data_size;
    uint generate_flags = (0x00000100 | 0x00000001 | 0x00000010 | 0x00000004 | 0x00000020 | 0x00000040 | 0x00000080),
        count,
        substitute_nonterminal_flag = 0,
        substitute_terminal_flag = 0,
        show_conflict_numbers = 1,
        ignore_warnings = 0,
        only_conflict = 0,
        only_deep_conflict = 0,
        analyze_grammar_flag = 1,
        use_lr = 0,
        lr_type = 0x00020000,
        generate_anyway = 0,
        expand_opt_only = 0,
        display_flags = 0;
    int (*scanner)(void) = NULL;
    char* derive_symbol_name = NULL,
        * left_recursion_name = NULL,
        * direct_factor_name = NULL,
        * indirect_factor_name = NULL,
        * old_factor_name = NULL,
        * unused_name = NULL,
        * substitute_name = NULL,
        * namespace_name = NULL,
        convert_format = '\0',
        * write_tokens_name = NULL,
        * load_tokens_name = NULL;
    static char parser_name[16] = "Slk";
    puts(version_string);
    while (--argc > 0) {
        arg = *++argv;
        switch (*arg) {
        case '-':
            if (*++arg) {
                switch (*arg) {
                case 'a':
                    if (generate_flags) {
                        generate_flags |= 0x00000002;
                    }
                    break;
                case 'b':
                    aggressive_check = 1;
                    break;
                case 'c':
                    if (generate_flags) {
                        if (*++arg == 'c') {
                            generate_flags &= ~(0x00000100 | 0x00001000 | 0x00000200 | 0x00000400 | 0x00000800 | 0x00002000);
                            generate_flags |= 0x00001000;
                        }
                        else if (*arg == 's') {
                            generate_flags &= ~(0x00000100 | 0x00001000 | 0x00000200 | 0x00000400 | 0x00000800 | 0x00002000);
                            generate_flags |= 0x00000800;
                        }
                        else {
                            generate_flags &= ~0x00000001;
                        }
                    }
                    break;
                case 'C':
                    if (*++arg == 'r') {
                        analyze_grammar_flag = 0;
                        generate_flags &= ~0x00000004;
                        generate_flags &= ~0x00000001;
                    }
                    else if (*arg == '+' && *++arg == '+') {
                        if (generate_flags) {
                            generate_flags &= ~(0x00000100 | 0x00001000 | 0x00000200 | 0x00000400 | 0x00000800 | 0x00002000);
                            generate_flags |= 0x00000200;
                        }
                    }
                    break;
                case 'd':
                    if (*++arg == 'o' && *++arg == 't') {
                        dot_string = "";
                    }
                    else {
                        grammar_flags |= 0x00000004;
                    }
                    break;
                case 'D':
                    if (*++arg) {
                        switch (*arg) {
                        case 'a':
                            display_flags |= -1;
                            break;
                        case 'c':
                            display_flags |= 0x00000100;
                            break;
                        case 'd':
                            display_flags |= 0x00000080;
                            if (*++arg && *++arg) {
                                derive_symbol_name = arg;
                            }
                            break;
                        case 'e':
                            display_flags |= 0x00000001;
                            break;
                        case 'f':
                            display_flags |= 0x00000020;
                            display_flags |= 0x00000040;
                            break;
                        case 'l':
                            display_flags |= 0x00000200;
                            break;
                        case 'p':
                            display_flags |= 0x00000010;
                            display_flags |= 0x00000002;
                            break;
                        case 'r':
                            display_flags |= 0x00000400;
                            break;
                        case 's':
                            display_flags |= 0x00000004;
                            break;
                        case 't':
                            display_flags |= 0x00000008;
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 'E':
                    convert_format = *++arg;
                    switch (*arg) {
                    case '1':
                    case '2':
                        convert_format = *arg;
                        break;
                    default:
                        grammar_flags |= 0x00000001;
                        printf("invalid option, %s\n", *argv);
                    }
                    break;
                case 'e':
                    grammar_flags &= ~0x00004000;
                    break;
                case 'f':
                    grammar_output_name = "";
                    if (*++arg && *++arg) {
                        grammar_output_name = arg;
                    }
                    break;
                case 'F':
                    if (*++arg) {
                        switch (*arg) {
                        case 'a':
                            grammar_flags |= 0x00008000;
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 'g':
                    generate_anyway = 1;
                    break;
                case 'G':
                    while (*++arg) {
                        switch (*arg) {
                        case 'a':
                            generate_flags = 0;
                            break;
                        case 'c':
                            generate_flags &= ~0x00000004;
                            generate_flags &= ~0x00000001;
                            break;
                        case 'd':
                            if (generate_flags) {
                                generate_flags |= 0x00100000;
                            }
                            break;
                        case 'n':
                            generate_flags &= ~0x00000010;
                            break;
                        case 'p':
                            generate_flags &= ~0x00000080;
                            break;
                        case 's':
                            generate_flags &= ~0x00000040;
                            break;
                        case 't':
                            generate_flags &= ~0x00000020;
                            break;
                        case 'u':
                            unique_ebnf_names = 0;
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 'i':
                    ignore_warnings = 1;
                    break;
                case 'j':
                    if (generate_flags) {
                        generate_flags &= ~(0x00000100 | 0x00001000 | 0x00000200 | 0x00000400 | 0x00000800 | 0x00002000);
                        if (*++arg == 's') {
                            generate_flags |= 0x00002000;
                        }
                        else {
                            generate_flags |= 0x00000400;
                        }
                    }
                    break;
                case 'k':
                    if (*++arg && *++arg) {
                        max_lookahead = atoi(arg);
                    }
                    break;
                case 'l':
                    grammar_flags |= 0x00000400;
                    if (*++arg && *++arg) {
                        old_factor_name = arg;
                    }
                    break;
                case 'L':
                    if (*++arg) {
                        switch (*arg) {
                        case 'd':
                            grammar_flags |= 0x00000200;
                            if (*++arg && *++arg) {
                                direct_factor_name = arg;
                            }
                            break;
                        case 'i':
                            grammar_flags |= 0x00000100;
                            if (*++arg && *++arg) {
                                indirect_factor_name = arg;
                            }
                            break;
                        case 'A':
                            use_lr = 1;
                            analyze_grammar_flag = 0;
                            unique_ebnf_names = 0;
                            if (generate_flags) {
                                generate_flags &= ~0x00000004;
                                generate_flags |= 0x00000008;
                            }
                            if (*++arg && *++arg) {
                                lr_type = 0x00020000;
                            }
                            else {
                                grammar_flags |= 0x00000001;
                                printf("invalid option, %s\n", *argv);
                            }
                            break;
                        case 'R':
                            lr_type = 0x00040000;
                            use_lr = 1;
                            analyze_grammar_flag = 0;
                            unique_ebnf_names = 0;
                            if (generate_flags) {
                                generate_flags &= ~0x00000004;
                                generate_flags |= 0x00000008;
                            }
                            if (*++arg == 'S') {
                                lr_type = 0x00010000;
                            }
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 'm':
                    conserve_memory = 1;
                    break;
                case 'n':
                    if (*++arg) {
                        if (*arg == 's') {
                            if (*++arg && *++arg) {
                                namespace_name = arg;
                            }
                        }
                        else {
                            if (*arg && *++arg) {
                                count = strlen(arg);
                                if (count != 3) {
                                    grammar_flags |= 0x00000001;
                                    puts("-n option length not = 3");
                                    break;
                                }
                                strcpy(parser_name, arg);
                            }
                        }
                    }
                    break;
                case 'O':
                    only_conflict = 1;
                    if (*++arg && *++arg) {
                        only_conflict = atoi(arg);
                        if (only_conflict == -1) {
                            only_conflict = 0;
                            show_conflict_numbers = 0;
                        }
                    }
                    break;
                case 'o':
                    only_deep_conflict = 1;
                    if (*++arg && *++arg) {
                        only_deep_conflict = atoi(arg);
                    }
                    break;
                case 'P':
                    if (*++arg) {
                        switch (*arg) {
                        case 's':
                            if (*++arg && *++arg) {
                                parse_stack_size = atoi(arg);
                            }
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 'q':
                    quiet = 1;
                    break;
                case 'R':
                    if (*++arg) {
                        switch (*arg) {
                        case 'd':
                            grammar_flags |= 0x00000800;
                            break;
                        case 'r':
                            grammar_flags |= 0x00000020;
                            if (*++arg && *++arg) {
                                left_recursion_name = arg;
                            }
                            break;
                        case 'u':
                            grammar_flags |= 0x00000080;
                            if (*++arg && *++arg) {
                                unused_name = arg;
                            }
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 'S':
                    if (*++arg) {
                        switch (*arg) {
                        case 'n':
                            grammar_flags |= 0x00000040;
                            substitute_nonterminal_flag = 1;
                            if (*++arg && *++arg) {
                                substitute_name = arg;
                            }
                            break;
                        case 't':
                            grammar_flags |= 0x00000040;
                            substitute_terminal_flag = 1;
                            if (*++arg && *++arg) {
                                substitute_name = arg;
                            }
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 'T':
                    if (*++arg) {
                        switch (*arg) {
                        case 'l':
                            if (*++arg && *++arg) {
                                grammar_flags |= 0x00002000;
                                load_tokens_name = arg;
                            }
                            else {
                                printf("no load tokens filename given\n");
                            }
                            break;
                        case 'w':
                            if (*++arg && *++arg) {
                                grammar_flags |= 0x00001000;
                                write_tokens_name = arg;
                            }
                            else {
                                printf("no write tokens filename given\n");
                            }
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 't':
                    trace_level = 1;
                    if (*++arg && *++arg) {
                        trace_level = atoi(arg);
                    }
                    break;
                case 'u':
                    break;
                case 'v':
                    verbose_level = 1;
                    if (*++arg && *++arg) {
                        verbose_level = atoi(arg);
                    }
                    break;
                case 'X':
                    if (*++arg) {
                        switch (*arg) {
                        case 'o':
                            expand_opt_only = 1;
                            break;
                        default:
                            grammar_flags |= 0x00000001;
                            printf("invalid option, %s\n", *argv);
                        }
                    }
                    break;
                case 'y':
                    grammar_flags |= 0x00000010;
                    grammar_flags &= ~0x00004000;
                    if (*++arg == 's') {
                        grammar_flags |= 0x00000008;
                    }
                    break;
                default:
                    grammar_flags |= 0x00000001;
                    printf("invalid option, %s\n", *argv);
                }
            }
            break;
        default:
            input_file_name = arg;
        }
    }
    if (!analyze_grammar_flag) {
        grammar_flags &= ~(0x00000020 | 0x00000400 | 0x00000100 | 0x00000200);
        compare_config_links = 0;
    }
    if ((grammar_flags & 0x00000001) || !input_file_name) {
        fputs(usage_text, stdout);
        ;
        ;
        exit(1);
    }
    if (expand_opt_only) {
        char* file_name = input_file_name;
        char* last_file_name = input_file_name;
        char command[128];
        while (file_name = expand_opt_file(file_name)) {
            last_file_name = file_name;
        }
        if (grammar_output_name && *grammar_output_name) {
            sprintf(command, "copy %s %s\n", last_file_name, grammar_output_name);
            system(command);
        }
        return 0;
    }
    if (convert_format) {
        if (!grammar_output_name) {
            puts("output filename was not specified, use -f=filename");
            exit(1);
        }
        switch (convert_format) {
        case '1':
            error_count = convert_ieee_grammar(input_file_name, grammar_output_name);
            break;
        case '2':
            error_count = convert_iso_grammar(input_file_name, grammar_output_name);
            break;
        }
        return error_count;
    }
    grammar_text = read_file(input_file_name, &data_size);
    if (!grammar_text) {
        perror(input_file_name);
        exit(1);
    }
    scanner = select_scanner(grammar_text, grammar_flags);
    if (!scanner) {
        return -1;
    }
    if (grammar_flags & 0x00002000) {
        if (load_tokens(load_tokens_name)) {
            return -2;
        }
    };
    ;
    in_grammar_parse = 1;
    parse_grammar(scanner, (grammar_flags & 0x00000004));
    in_grammar_parse = 0;
    if (!error_count) {
        ;
        ;
        error_count |= analyze_grammar(ignore_warnings, analyze_grammar_flag);
    }
    if (grammar_flags & 0x00000800) {
        remove_duplicate_productions();
    }
    if (grammar_flags & 0x00000020) {
        remove_left_recursion(left_recursion_name);
    }
    if (!error_count) {
        error_count |= compute_first_follow();
    }
    if (!error_count) {
        if (use_lr) {
            error_count |= build_lr_parser(lr_type);
        }
        else if (analyze_grammar_flag) {
            error_count |= build_ll_table();
        }
        else {
            error_count |= resolve_only_conflicts();
        }
    }
    if (grammar_flags & 0x00000400) {
        grammar_flags &= ~(0x00000200 | 0x00000100);
        if (!(grammar_flags & 0x00000020)) {
            if (!has_left_recursion) {
                error_count |= left_factor_old(old_factor_name);
            }
            else {
                printf("cannot left factor a left recursive grammar \n");
            }
        }
        else {
            printf("cannot left factor and remove left recursion "
                "at the same time \n");
        }
    }
    if (grammar_flags & 0x00000200) {
        if (!(grammar_flags & 0x00000020)) {
            if (!has_left_recursion) {
                error_count |= left_factor_direct(direct_factor_name);
            }
            else {
                printf("cannot left factor a left recursive grammar \n");
            }
        }
        else {
            printf("cannot left factor and remove left recursion "
                "at the same time \n");
        }
    }
    if (grammar_flags & 0x00000100) {
        if (!(grammar_flags & 0x00000020)) {
            if (!has_left_recursion) {
                error_count |= left_factor_indirect(indirect_factor_name);
            }
            else {
                printf("cannot left factor a left recursive grammar \n");
            }
        }
        else {
            printf("cannot left factor and remove left recursion "
                "at the same time \n");
        }
    }
    if (grammar_flags & 0x00000040) {
        if (substitute_nonterminal_flag || substitute_terminal_flag) {
            substitute_equivalent(substitute_name,
                substitute_nonterminal_flag,
                substitute_terminal_flag);
        }
    }
    if (grammar_flags & 0x00000080) {
        remove_unused(unused_name);
    }
    if (grammar_flags & (0x00000020 | 0x00000040 | 0x00000080 | 0x00000800 | 0x00000400 | 0x00000100 | 0x00000200)) {
        if (!grammar_output_name) {
            puts("output filename was not specified, use -f=filename");
        }
        error_count = 1;
    }
    if (!error_count) {
        uint resolved_level;
        uint* conflict_status;
        uint result_status;
        if (!quiet) {
            print_conflicts(show_conflict_numbers);
        }
        conflict_status = calloc(base_conflict_count + 4, sizeof(uint));
        if (!conflict_status) {
            fatal_error(1702, "out of memory");
        }
        conflict_status[base_conflict_count + 1] = -1;
        resolved_level = resolve_conflicts(show_conflict_numbers, only_conflict,
            only_deep_conflict, conflict_status);
        result_status = report_conflicts(show_conflict_numbers, conflict_status,
            resolved_level);
        error_count |= result_status;
    }
    if (!error_count || generate_anyway) {
        printf("\n\t total nonterminals   = %d\n", nonterminal_count);
        if (conditional_count) {
            printf("\t       conditionals   = %d\n",
                conditional_count);
        }
        printf("\t total terminals      = %d\n", terminal_count);
        printf("\t total productions    = %d\n", production_count);
        if (use_lr) {
            printf("\t total states         = %d\n", state_count);
            printf("\t parse table size     = %d\n",
                state_count * (nonterminal_count + terminal_count));
        }
        else {
            printf("\t parse table size     = %d\n",
                nonterminal_count * terminal_count);
        }
        if (ignored_conflict_count) {
            printf("\t ignored conflicts    = %d\n", ignored_conflict_count);
        }
        if (base_conflict_count) {
            printf("\t total base conflicts = %d\n", base_conflict_count);
            printf("\t total conflicts      = %d\n", conflict_count);
            printf("\t conflict table size  = %d\n",
                conflict_count * terminal_count);
        }
        putchar('\n');
    }
    if (display_flags & 0x00000200) {
        print_lookaheads(show_conflict_numbers);
    }
    if (display_flags & 0x00000010) {
        print_productions();
    }
    if (display_flags & 0x00000400) {
        print_lr_states(lr_type == 0x00010000);
    }
    if (display_flags & 0x00000008) {
        print_parse_table(use_lr);
        print_conflict_table();
    }
    if (display_flags & 0x00000020) {
        print_firsts_nonterminals();
        print_first_sets();
    }
    if (display_flags & 0x00000040) {
        if (trace_level == -1) {
            print_follows_nonterminals();
        }
        print_follow_sets();
    }
    if (display_flags & 0x00000001) {
        print_nullable();
    }
    if (display_flags & 0x00000002) {
        print_production_integers();
    }
    if (display_flags & 0x00000100) {
        print_conflict_traces();
    }
    if (display_flags & 0x00000080) {
        display_left_derivations(derive_symbol_name);
    }
    if (display_flags & 0x00000004) {
        print_symbol_table();
    }
    if (grammar_flags & 0x00001000) {
        write_tokens(write_tokens_name);
    }
    if (grammar_output_name) {
        generate_flags = 0;
        if (grammar_flags & 0x00004000) {
            restore_ebnf();
        }
        printf("rewriting the grammar\n");
        write_grammar(grammar_output_name, (grammar_flags & 0x00004000));
    }
    if (generate_flags) {
        if (!error_count) {
            printf("generating the parser\n");
            generate_parser(parser_name, namespace_name, generate_flags,
                grammar_flags);
        }
        else if (generate_anyway) {
            printf("warning: error detected, generating the parser anyway\n");
            generate_parser(parser_name, namespace_name, generate_flags,
                grammar_flags);
            error_count = 0;
        }
    }
    return error_count;
}
void fatal_error(int error_code,
    char* error_message)
{
    if (in_grammar_parse) {
        fprintf(stdout, "%u: ", line_number());
    }
    fprintf(stdout, "error %u: %s\n", error_code, error_message);
    exit(1);
}
void note_left_recursion(void)
{
    has_left_recursion = 1;
}
void note_error(void)
{
    ++error_count;
}
static SymbolSetNode* free_set_list = NULL;
static uint reused_count = 0;
static SymbolSetNode*
alloc_recycled_set_node(void)
{
    register SymbolSetNode* set_node = free_set_list;
    if (set_node) {
        free_set_list = set_node->next;
        memset(set_node, 0, sizeof(SymbolSetNode));
        ++reused_count;
    }
    return set_node;
}
static SymbolSetNode*
new_set_node(void)
{
    register SymbolSetNode* set_node;
    static int block_left = 0;
    static SymbolSetNode* block;
    if (--block_left > 0) {
        ++block;
        set_node = block;
    }
    else {
        block_left = 0;
        set_node = alloc_recycled_set_node();
        if (!set_node) {
            block_left = 1024;
            block = (SymbolSetNode*)calloc(block_left, sizeof(SymbolSetNode));
            set_node = block;
            if (!set_node) {
                block_left = 0;
                fatal_error(2101, "out of memory");
            }
        }
    }
    return set_node;
}
static uint
mark_undefined(void)
{
    register Symbol*** block,
        ** nonterminal = nonterminals;
    uint error_found = 0,
        found;
    while (*++nonterminal) {
        block = productions;
        (*nonterminal)->undefined = 0;
        found = 1;
        while (*++block) {
            if (**block == *nonterminal) {
                found = 0;
                break;
            }
        }
        if (found) {
            error_found = 1;
            (*nonterminal)->undefined = 1;
        }
    }
    return error_found;
}
static uint
mark_equivalent(void)
{
    register Symbol*** block,
        ** dot;
    Symbol* lhs,
        * equivalent_symbol,
        ** nonterminal = nonterminals;
    uint found = 0,
        production_count,
        equivalent;
    nonterminals[1]->start_symbol = 1;
    while (*++nonterminal) {
        block = productions;
        (*nonterminal)->equivalent = 0;
        equivalent = 0;
        production_count = 0;
        while (*++block) {
            lhs = **block;
            if (lhs != *nonterminal) {
                continue;
            }
            if (++production_count > 1) {
                break;
            }
            dot = *block;
            if (*++dot) {
                if ((*dot)->type != 3) {
                    if (!*++dot) {
                        if ((*nonterminal)->start_symbol) {
                            equivalent_symbol = *(dot - 1);
                        }
                        equivalent = 1;
                    }
                }
            }
        }
        if (equivalent && production_count == 1) {
            if ((*nonterminal)->start_symbol) {
                equivalent_symbol->start_symbol = 1;
            }
            else {
                found = 1;
                (*nonterminal)->equivalent = 1;
            }
        }
    }
    return found;
}
static void
mark_unit_productions(void)
{
    register Symbol*** block,
        ** dot;
    Symbol* lhs,
        ** nonterminal = nonterminals;
    uint equivalent;
    while (*++nonterminal) {
        block = productions;
        (*nonterminal)->unit_production = 0;
        equivalent = 0;
        while (*++block) {
            lhs = **block;
            if (lhs != *nonterminal) {
                continue;
            }
            dot = *block;
            if (*++dot) {
                if ((*dot)->type == 2) {
                    if (!*++dot) {
                        equivalent = 1;
                    }
                    else if ((*dot)->type == 3) {
                        if (!*++dot) {
                            equivalent = 1;
                        }
                    }
                }
            }
        }
        if (equivalent) {
            (*nonterminal)->unit_production = 1;
        }
    }
}
static struct
{
    Symbol** stack_top,
        * stack_base[127 + 1];
} infinite_recursion_stack = { infinite_recursion_stack.stack_base + 127 };
static uint
not_on_infinite_stack(register Symbol* nonterminal)
{
    register Symbol** cursor = infinite_recursion_stack.stack_top;
    while (*cursor) {
        if (*cursor++ == nonterminal) {
            return 0;
        }
    }
    return 1;
}
static uint
infinite_derivation(Symbol* target_symbol,
    Symbol* source_symbol,
    uint display)
{
    register Symbol** symbol,
        *** block;
    Symbol* lhs;
    uint derives = 0;
    for (block = productions; *++block;) {
        symbol = *block;
        lhs = *symbol;
        if (lhs == source_symbol) {
            while (*++symbol) {
                if ((*symbol)->type == 1) {
                    if (*symbol == target_symbol) {
                        derives = 1;
                        break;
                    }
                    if ((*symbol)->infinite_derivation) {
                        derives = 1;
                        break;
                    }
                    if (not_on_infinite_stack(*symbol)) {
                        if (infinite_recursion_stack.stack_top > infinite_recursion_stack.stack_base)
                            *--infinite_recursion_stack.stack_top = *symbol;
                        else
                            fatal_error(2102, "stack overflow");
                        derives = infinite_derivation(
                            target_symbol,
                            *symbol, display);
                        if (*infinite_recursion_stack.stack_top)
                            infinite_recursion_stack.stack_top++;
                        ;
                    }
                    else {
                        derives = 1;
                    }
                    if (derives) {
                        break;
                    }
                }
            }
        }
        if (derives) {
            if (display && verbose_level < -2) {
                print_production("   ", *block);
            }
            break;
        }
    }
    return derives;
}
static void
mark_infinite_derivations(uint display)
{
    register Symbol** nonterminal;
    uint derives,
        changed;
    for (changed = 1; changed;) {
        changed = 0;
        for (nonterminal = nonterminals; *++nonterminal;) {
            if ((*nonterminal)->infinite_derivation) {
                continue;
            }
            derives = infinite_derivation(*nonterminal, *nonterminal,
                display);
            if (derives && !(*nonterminal)->infinite_derivation) {
                (*nonterminal)->infinite_derivation = 1;
                changed = 1;
                if (display && verbose_level < -1) {
                    printf("  %s:  has infinite derivations \n",
                        (*nonterminal)->name);
                    if (verbose_level < -2) {
                        putchar('\n');
                    }
                }
            }
        }
    }
    if (display && verbose_level < -1) {
        putchar('\n');
    }
}
static uint
check_direct_factoring(int display,
    Symbol* nonterminal)
{
    register Symbol*** prod_iter = productions,
        *** prod_iter2;
    Symbol** rhs_a,
        ** rhs_b,
        * last_lhs = NULL,
        * lhs;
    uint factoring_found,
        needs_direct_factoring = 0;
    while (*++prod_iter) {
        lhs = **prod_iter;
        if (nonterminal && nonterminal != lhs) {
            continue;
        }
        prod_iter2 = prod_iter;
        while (*++prod_iter2) {
            if (**prod_iter2 != lhs) {
                break;
            }
            if ((*prod_iter2)[1] == lhs) {
                continue;
            }
            rhs_a = *prod_iter;
            rhs_b = *prod_iter2;
            ++rhs_a;
            ++rhs_b;
            factoring_found = 0;
            for (; *rhs_a && *rhs_a == *rhs_b; ++rhs_a, ++rhs_b) {
                if ((*rhs_a)->type == 3) {
                    continue;
                }
                if ((*rhs_a)->type == 2) {
                    continue;
                }
                factoring_found = 1;
            }
            if (factoring_found) {
                factoring_found = 0;
                rhs_a = *prod_iter2;
                ++rhs_a;
                for (; rhs_a < rhs_b; ++rhs_a) {
                    if (*rhs_a && (*rhs_a)->infinite_derivation) {
                        lhs->needs_direct_factoring = 1;
                        needs_direct_factoring = 1;
                        if (display) {
                            if (last_lhs != lhs) {
                                last_lhs = lhs;
                                printf("  %s:  needs direct left factoring \n",
                                    lhs->name);
                            }
                            if (verbose_level > 0) {
                                print_production("   ", *prod_iter);
                                print_production("   ", *prod_iter2);
                                putchar('\n');
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    return needs_direct_factoring;
}
static uint
check_indirect_factoring(int display)
{
    register Symbol*** prod_iter = productions,
        *** prod_iter2;
    Symbol** rhs_a,
        ** rhs_b,
        * last_lhs = NULL,
        * symbol,
        * lhs;
    uint factoring_found = 0;
    while (*++prod_iter) {
        lhs = **prod_iter;
        if ((*prod_iter)[1] == lhs) {
            continue;
        }
        prod_iter2 = prod_iter;
        while (*++prod_iter2) {
            if (**prod_iter2 != lhs) {
                break;
            }
            if (lhs->conditional) {
                continue;
            }
            if (lhs->ignore_conflicts) {
                continue;
            }
            if (lhs->needs_direct_factoring) {
                continue;
            }
            if ((*prod_iter2)[1] == lhs) {
                continue;
            }
            rhs_a = *prod_iter;
            rhs_b = *prod_iter2;
            for (++rhs_a, ++rhs_b; *rhs_a && *rhs_b;) {
                if (*rhs_a && (*rhs_a)->type == 3) {
                    ++rhs_a;
                    continue;
                }
                if (*rhs_b && (*rhs_b)->type == 3) {
                    ++rhs_b;
                    continue;
                }
                if (*rhs_a == *rhs_b) {
                    ++rhs_a;
                    ++rhs_b;
                    continue;
                }
                symbol = set_intersect_infinite((*rhs_a)->left_corners,
                    (*rhs_b)->left_corners);
                if (symbol) {
                    factoring_found = 1;
                    lhs->needs_indirect_factoring = 1;
                    if (display) {
                        if (last_lhs != lhs) {
                            last_lhs = lhs;
                            printf("  %s:  needs indirect left factoring \n",
                                lhs->name);
                        }
                        if (verbose_level > 0) {
                            printf("  '%s' "
                                "in '%s' and '%s' \n",
                                symbol->name, (*rhs_a)->name, (*rhs_b)->name);
                        }
                        if (verbose_level > 1) {
                            left_derives(symbol, *rhs_a, 1);
                        }
                        if (verbose_level > 0) {
                            print_production("   ", *prod_iter);
                        }
                        if (verbose_level > 1) {
                            putchar('\n');
                            left_derives(symbol, *rhs_b, 1);
                        }
                        if (verbose_level > 0) {
                            print_production("   ", *prod_iter2);
                            putchar('\n');
                        }
                    }
                    break;
                }
                if ((*rhs_a)->nullable) {
                    ++rhs_a;
                    continue;
                }
                if ((*rhs_b)->nullable) {
                    ++rhs_b;
                    continue;
                }
                break;
            }
        }
    }
    return factoring_found;
}
static uint
report_factoring(void)
{
    uint factoring_found,
        needs_indirect_factoring;
    factoring_found = check_direct_factoring(1, NULL);
    if (factoring_found) {
        putchar('\n');
    }
    needs_indirect_factoring = check_indirect_factoring(1);
    factoring_found |= needs_indirect_factoring;
    if (needs_indirect_factoring) {
        putchar('\n');
    }
    return factoring_found;
}
static uint
report_undefined(void)
{
    register Symbol** nonterminal = nonterminals;
    uint error_found = 0;
    mark_undefined();
    while (*++nonterminal) {
        if ((*nonterminal)->undefined) {
            error_found = 1;
            printf("  %s: undefined \n", (*nonterminal)->name);
        }
    }
    if (error_found) {
        putchar('\n');
    }
    return error_found;
}
static uint
report_equivalent(void)
{
    register Symbol*** block = productions,
        ** dot;
    Symbol* lhs;
    uint found = 0;
    char* symbol_name;
    mark_equivalent();
    while (*++block) {
        dot = *block;
        lhs = *dot;
        if (lhs->equivalent) {
            if (*++dot) {
                symbol_name = (*dot)->name;
            }
            else {
                symbol_name = "";
            }
            found = 1;
            if (verbose_level > 2) {
                printf("  %s: equivalent to %s \n", lhs->name, symbol_name);
            }
        }
    }
    if (found) {
        if (verbose_level > 0) {
            putchar('\n');
        }
    }
    return found;
}
static uint
report_unused(void)
{
    register Symbol** nonterminal = nonterminals + 1;
    uint unused_error_found = 0;
    mark_unused();
    while (*++nonterminal) {
        if ((*nonterminal)->unused) {
            unused_error_found = 1;
            printf("  %s: unused \n", (*nonterminal)->name);
        }
    }
    if (unused_error_found) {
        putchar('\n');
    }
    return unused_error_found;
}
static uint
mark_indirect_left_recursion(void)
{
    register Symbol** nonterminal;
    uint left_recursion_found = 0;
    for (nonterminal = nonterminals; *++nonterminal;) {
        if ((*nonterminal)->direct_left_recursive) {
            continue;
        }
        if ((*nonterminal)->indirect_left_recursive) {
            continue;
        }
        if (left_derives(*nonterminal, *nonterminal, 0)) {
            if (verbose_level > 0) {
                printf("  %s: indirect left recursive: was missed\n",
                    (*nonterminal)->name);
                left_derives(*nonterminal, *nonterminal, 1);
                putchar('\n');
            }
            (*nonterminal)->indirect_left_recursive = 1;
            note_left_recursion();
            left_recursion_found = 1;
        }
    }
    return left_recursion_found;
}
static uint
report_left_recursion(void)
{
    register Symbol** nonterminal;
    uint left_recursion_found = 0;
    mark_indirect_left_recursion();
    for (nonterminal = nonterminals; *++nonterminal;) {
        if ((*nonterminal)->direct_left_recursive) {
            printf("  %s:  direct left recursion\n", (*nonterminal)->name);
            left_recursion_found = 1;
        }
    }
    if (left_recursion_found) {
        putchar('\n');
    }
    for (nonterminal = nonterminals; *++nonterminal;) {
        if ((*nonterminal)->indirect_left_recursive) {
            printf("  %s:  indirect left recursion\n", (*nonterminal)->name);
            left_recursion_found = 1;
        }
    }
    if (left_recursion_found) {
        putchar('\n');
    }
    return left_recursion_found;
}
static uint
rhs_all_nullable(register Symbol** dot)
{
    for (; *dot; ++dot) {
        if ((*dot)->type == 3) {
            continue;
        }
        if (!(*dot)->nullable) {
            break;
        }
    }
    return (*dot == NULL);
}
static uint
check_multiple_nullable(void)
{
    register Symbol*** block = productions,
        ** dot;
    Symbol* lhs;
    Symbol** first_nullable = NULL,
        ** last_nullable = NULL;
    uint nullable_found = 0;
    while (*++block) {
        dot = *block;
        lhs = *dot;
        if (lhs->nullable) {
            if (rhs_all_nullable(dot + 1)) {
                first_nullable = dot;
                while (*++block) {
                    dot = *block;
                    if (*dot != lhs) {
                        --block;
                        break;
                    }
                    if (rhs_all_nullable(dot + 1)) {
                        last_nullable = dot;
                        nullable_found = 1;
                        if (first_nullable) {
                            printf("  %s: multiple nullable productions \n",
                                (*first_nullable)->name);
                            print_production("   ", first_nullable);
                            first_nullable = NULL;
                        }
                        print_production("   ", last_nullable);
                    }
                }
                if (!*block) {
                    break;
                }
            }
        }
    }
    if (nullable_found) {
        putchar('\n');
    }
    return nullable_found;
}
static void
// ================ FIRST/FOLLOW and left-corner computation ================
compute_left_corners(void)
{
    register Symbol** symbol,
        * lhs;
    Symbol*** block;
    int changed;
    for (symbol = nonterminals; *++symbol;) {
        set_add_unique(&(*symbol)->left_corners, *symbol);
    }
    for (changed = 1; changed;) {
        changed = 0;
        block = productions;
        while (*++block) {
            symbol = *block;
            lhs = *symbol;
            while (*++symbol) {
                if ((*symbol)->type == 3) {
                    continue;
                }
                if ((*symbol)->type == 1) {
                    changed |= set_union(&lhs->left_corners,
                        (*symbol)->left_corners);
                }
                if (!(*symbol)->nullable) {
                    break;
                }
            }
        }
    }
}
uint analyze_grammar(uint ignore_warnings,
    uint analyze_grammar_flag)
{
    uint error_found,
        left_recursion_found = 0,
        factoring_found = 0,
        duplicates,
        nullable_found = 0,
        errors = 0,
        unused_error_found;
    error_found = report_undefined();
    unused_error_found = report_unused();
    report_equivalent();
    mark_unit_productions();
    duplicates = check_duplicate_productions();
    if (analyze_grammar_flag) {
        compute_left_corners();
        mark_infinite_derivations(1);
        factoring_found = report_factoring();
        left_recursion_found = report_left_recursion();
        if (!(left_recursion_found || factoring_found)) {
            nullable_found = check_multiple_nullable();
            errors = check_duplicate_rhs();
        }
    }
    if (ignore_warnings) {
        factoring_found = 0;
        unused_error_found = 0;
        errors = 0;
        nullable_found = 0;
    }
    return (errors || duplicates || error_found || unused_error_found ||
        factoring_found || left_recursion_found || nullable_found);
}
uint needs_direct_factoring_single(int display,
    Symbol* nonterminal)
{
    uint factoring_found;
    nonterminal->needs_direct_factoring = 0;
    factoring_found = check_direct_factoring(display,
        nonterminal);
    return factoring_found;
}
uint needs_direct_factoring(int display)
{
    register Symbol** nonterminal;
    uint factoring_found;
    for (nonterminal = nonterminals; *++nonterminal;) {
        (*nonterminal)->needs_direct_factoring = 0;
    }
    factoring_found = check_direct_factoring(display, NULL);
    return factoring_found;
}
uint needs_indirect_factoring(int display)
{
    register Symbol** nonterminal;
    uint factoring_found;
    for (nonterminal = nonterminals; *++nonterminal;) {
        (*nonterminal)->needs_indirect_factoring = 0;
    }
    factoring_found = check_indirect_factoring(display);
    return factoring_found;
}
uint needs_any_factoring(void)
{
    register Symbol** nonterminal;
    uint factoring_found;
    for (nonterminal = nonterminals; *++nonterminal;) {
        (*nonterminal)->needs_direct_factoring = 0;
        (*nonterminal)->needs_indirect_factoring = 0;
    }
    factoring_found = check_direct_factoring(0, NULL);
    factoring_found |= check_indirect_factoring(0);
    return factoring_found;
}
uint mark_unused(void)
{
    register Symbol*** block,
        ** dot,
        ** nonterminal = nonterminals + 1;
    uint unused_error_found = 0,
        unused_found;
    while (*++nonterminal) {
        block = productions;
        (*nonterminal)->unused = 0;
        unused_found = 1;
        while (*++block) {
            dot = *block;
            while (*++dot) {
                if (*dot == *nonterminal) {
                    if (**block != *dot) {
                        unused_found = 0;
                        break;
                    }
                }
            }
            if (unused_found == 0) {
                break;
            }
        }
        if (unused_found) {
            unused_error_found = 1;
            (*nonterminal)->unused = 1;
        }
    }
    return unused_error_found;
}
static char*
strip_suffix_ignorecase(char* suffix,
    char* full_name)
{
    register char* prefix = NULL,
        * cursor;
    uint prefix_length,
        name_length,
        matched = 0;
    static char name_buffer[128];
    prefix_length = strlen(suffix);
    name_length = strlen(full_name);
    if (name_length > prefix_length) {
        if (name_length < sizeof(name_buffer) - 2) {
            strcpy(name_buffer, full_name);
            cursor = full_name;
            while (*cursor) {
                ++cursor;
            }
            cursor -= prefix_length;
            for (; *cursor && *suffix; ++cursor, ++suffix) {
                matched = 1;
                if ((((*cursor >= 'a' && *cursor <= 'z')) ? (*cursor - ('a' - 'A')) : *cursor) != (((*suffix >= 'a' && *suffix <= 'z')) ? (*suffix - ('a' - 'A')) : *suffix)) {
                    matched = 0;
                    break;
                }
            }
            if (matched) {
                cursor = name_buffer + name_length - prefix_length;
                *cursor = '\0';
                if (*--cursor == '_') {
                    *cursor = '\0';
                }
                prefix = name_buffer;
            }
        }
    }
    return prefix;
}
static char*
strip_suffix(char* suffix,
    char* full_name)
{
    register char* base_name = NULL,
        * cursor;
    uint prefix_length,
        name_length,
        matched = 0;
    static char name_buffer[128];
    prefix_length = strlen(suffix);
    name_length = strlen(full_name);
    if (name_length > prefix_length) {
        if (name_length < sizeof(name_buffer) - 2) {
            strcpy(name_buffer, full_name);
            cursor = full_name;
            while (*cursor) {
                ++cursor;
            }
            cursor -= prefix_length;
            for (; *cursor && *suffix; ++cursor, ++suffix) {
                matched = 1;
                if (*cursor != *suffix) {
                    matched = 0;
                    break;
                }
            }
            if (matched) {
                cursor = name_buffer + name_length - prefix_length;
                *cursor = '\0';
                base_name = name_buffer;
            }
        }
    }
    return base_name;
}
static void
write_regexp_productions(FILE* file)
{
    register Symbol** lookahead_tokens;
    Symbol* symbol;
    char* base_name;
    uint wrote_header = 0;
    char name_buffer2[128];
    for (lookahead_tokens = terminals; *++lookahead_tokens;) {
        base_name = strip_suffix("_+", (*lookahead_tokens)->name);
        if (base_name) {
            if (!wrote_header) {
                wrote_header = 1;
                fprintf(file, "\n//\n// Automatically generated regexp"
                    " productions. Some may be wrong.\n//\n\n");
            }
            strncpy(name_buffer2, base_name, sizeof(name_buffer2) - 4);
            strcat(name_buffer2, "_*");
            symbol = find_symbol(name_buffer2);
            if (!symbol) {
                fprintf(file, "%s :\n", name_buffer2);
                fprintf(file, "    %s %s\n", base_name, name_buffer2);
                fprintf(file, "    %s\n\n", "_epsilon_");
            }
            fprintf(file, "%s :\n", (*lookahead_tokens)->name);
            fprintf(file, "    %s %s\n\n", base_name, name_buffer2);
            printf("warning: generating a production for %s\n",
                (*lookahead_tokens)->name);
        }
    }
    for (lookahead_tokens = terminals; *++lookahead_tokens;) {
        base_name = strip_suffix("_*", (*lookahead_tokens)->name);
        if (base_name) {
            if (!wrote_header) {
                wrote_header = 1;
                fprintf(file, "\n//\n// Automatically generated regexp"
                    " productions. Some may be wrong.\n//\n\n");
            }
            fprintf(file, "%s :\n", (*lookahead_tokens)->name);
            fprintf(file, "    %s %s\n", base_name, (*lookahead_tokens)->name);
            fprintf(file, "    %s\n\n", "_epsilon_");
            printf("  generating a production for %s\n", (*lookahead_tokens)->name);
        }
    }
    if (wrote_header) {
        fprintf(file, "\n//\n// End of Automatically generated regexp"
            " productions.\n//\n\n");
    }
}
static void
write_opt_productions(FILE* file)
{
    register Symbol** lookahead_tokens;
    char* base_name;
    uint wrote_header = 0;
    for (lookahead_tokens = terminals; *++lookahead_tokens;) {
        base_name = strip_suffix_ignorecase("opt", (*lookahead_tokens)->name);
        if (base_name) {
            if (!wrote_header) {
                wrote_header = 1;
                fprintf(file, "\n//\n// Automatically generated opt productions."
                    " Some may be wrong.\n//\n\n");
            }
            fprintf(file, "%s :\n", (*lookahead_tokens)->name);
            fprintf(file, "    %s\n", base_name);
            fprintf(file, "    %s\n\n", "_epsilon_");
            printf("  generating a production for %s\n", (*lookahead_tokens)->name);
        }
    }
    if (wrote_header) {
        fprintf(file, "\n//\n// End of Automatically generated opt productions."
            "\n//\n\n");
    }
}
static void
write_or_productions(FILE* file)
{
    register Symbol** lookahead_tokens;
    char* bar_pos;
    char* char_cursor;
    char* dot;
    uint wrote_header = 0;
    char name_buffer[2048 + 4];
    for (lookahead_tokens = terminals; *++lookahead_tokens;) {
        bar_pos = strchr((*lookahead_tokens)->name, '|');
        if (bar_pos) {
            printf("  generating productions for %s\n", (*lookahead_tokens)->name);
            if (!wrote_header) {
                wrote_header = 1;
                fprintf(file, "\n//\n// Automatically generated OR productions."
                    " Some may be wrong.\n//\n\n");
            }
            fprintf(file, "%s :\n", (*lookahead_tokens)->name);
            strncpy(name_buffer, (*lookahead_tokens)->name, sizeof(name_buffer));
            name_buffer[2048] = '\0';
            bar_pos = strchr(name_buffer, '|');
            dot = name_buffer;
            while (bar_pos) {
                *bar_pos = '\0';
                if (*dot == '~') {
                    ++dot;
                }
                if (!*dot) {
                    break;
                }
                for (char_cursor = dot; *char_cursor; ++char_cursor) {
                    if (*char_cursor == '~') {
                        *char_cursor = ' ';
                    }
                }
                fprintf(file, "    %s\n", dot);
                dot = bar_pos + 1;
                bar_pos = strchr(dot, '|');
            }
            if (*dot == '~') {
                ++dot;
            }
            if (!*dot) {
                dot = "_epsilon_";
            }
            for (char_cursor = dot; *char_cursor; ++char_cursor) {
                if (*char_cursor == '~') {
                    *char_cursor = ' ';
                }
            }
            fprintf(file, "    %s\n\n", dot);
        }
    }
    if (wrote_header) {
        fprintf(file, "\n//\n// End of Automatically generated OR productions."
            "\n//\n\n");
    }
}
static void
write_list_productions(FILE* file)
{
    register Symbol** lookahead_tokens;
    char* bar_pos;
    char* list;
    char* dash_pos;
    uint wrote_header = 0;
    char name[2048 + 4];
    for (lookahead_tokens = terminals; *++lookahead_tokens;) {
        bar_pos = strchr((*lookahead_tokens)->name, '|');
        if (bar_pos) {
            continue;
        }
        dash_pos = strrchr((*lookahead_tokens)->name, '-');
        if (!dash_pos) {
            dash_pos = strrchr((*lookahead_tokens)->name, '_');
        }
        if (!dash_pos) {
            continue;
        }
        list = dash_pos + 1;
        if (strcmp(list, "list")) {
            continue;
        }
        printf("  generating productions for %s\n", (*lookahead_tokens)->name);
        if (!wrote_header) {
            wrote_header = 1;
            fprintf(file, "\n//\n// Automatically generated \"list\" productions."
                " Some may be wrong.\n//\n\n");
        }
        fprintf(file, "%s :\n", (*lookahead_tokens)->name);
        strncpy(name, (*lookahead_tokens)->name, sizeof(name));
        name[2048] = '\0';
        dash_pos = strrchr(name, '-');
        if (!dash_pos) {
            dash_pos = strrchr(name, '_');
        }
        if (!dash_pos) {
            continue;
        }
        *dash_pos = '\0';
        fprintf(file, "    %s { , %s }\n\n", name, name);
    }
    if (wrote_header) {
        fprintf(file, "\n//\n// End of Automatically generated \"list\" productions."
            "\n//\n\n");
    }
}
static uint
rhs_empty(register Symbol** dot)
{
    for (++dot; *dot; ++dot) {
        if ((*dot)->type != 3) {
            break;
        }
    }
    return (*dot == NULL);
}
void write_grammar(char* grammar_output_name,
    int use_ebnf)
{
    register Symbol** symbol;
    register Symbol*** block = productions;
    Symbol* lhs = NULL;
    FILE* grammar_file,
        * file = stdout;
    char* name;
    if (grammar_output_name && *grammar_output_name) {
        grammar_file = fopen(grammar_output_name, "w");
        if (grammar_file) {
            file = grammar_file;
        }
        else {
            perror(grammar_output_name);
        }
    }
    while (*++block) {
        symbol = *block;
        if (use_ebnf) {
            if ((*symbol)->ebnf_nonterminal) {
                continue;
            }
        }
        if (*symbol != lhs) {
            if ((*symbol)->conditional) {
                fprintf(file, "\n%s :?\n", (*symbol)->name);
            }
            else if ((*symbol)->ignore_conflicts) {
                fprintf(file, "\n%s :!\n", (*symbol)->name);
            }
            else {
                fprintf(file, "\n%s :\n", (*symbol)->name);
            }
        }
        fprintf(file, "   ");
        if (rhs_empty(symbol)) {
            fprintf(file, " %s", "_epsilon_");
        }
        while (*(symbol + 1) && (*(symbol + 1))->type == 3) {
            ++symbol;
            if (action_prefix_len((*symbol)->name)) {
                fprintf(file, " %s", (*symbol)->name);
            }
            else {
                fprintf(file, " _action_%s", (*symbol)->name);
            }
        }
        while (*++symbol) {
            name = (*symbol)->name;
            if ((*symbol)->type == 3) {
                if (action_prefix_len(name)) {
                    fprintf(file, " %s", name);
                }
                else {
                    fprintf(file, " _action_%s", name);
                }
            }
            else if ((*symbol)->ebnf_token) {
                fprintf(file, " %s", name + 1);
            }
            else if ((*symbol)->escaped) {
                fprintf(file, " \\%s", name);
            }
            else {
                fprintf(file, " %s", name);
            }
        }
        fprintf(file, "\n");
        lhs = **block;
    }
    if (!use_ebnf) {
        write_regexp_productions(file);
        write_opt_productions(file);
    }
    write_or_productions(file);
    if (use_ebnf) {
        write_list_productions(file);
    }
    if (grammar_output_name) {
        if (grammar_file) {
            fclose(grammar_file);
        }
    }
}
uint set_add_unique_front(SymbolSetNode** list,
    Symbol* symbol)
{
    register SymbolSetNode* conflict_production,
        * new_node;
    if (!(symbol && list)) {
        return 0;
    }
    for (conflict_production = *list; conflict_production; conflict_production = conflict_production->next) {
        if (conflict_production->symbol == symbol) {
            return 0;
        }
    }
    new_node = new_set_node();
    new_node->symbol = symbol;
    new_node->next = *list;
    *list = new_node;
    return 1;
}
uint set_union_front(SymbolSetNode** dest_configs,
    register SymbolSetNode* src_configs)
{
    uint changed = 0;
    for (; src_configs; src_configs = src_configs->next) {
        changed |= set_add_unique_front(dest_configs, src_configs->symbol);
    }
    return changed;
}
uint set_add_unique(SymbolSetNode** list,
    Symbol* symbol)
{
    register SymbolSetNode* conflict_production,
        * last_node = NULL;
    SymbolSetNode* new_node;
    if (!*list) {
        new_node = new_set_node();
        new_node->symbol = symbol;
        *list = new_node;
        return 1;
    }
    for (conflict_production = *list; conflict_production; conflict_production = conflict_production->next) {
        last_node = conflict_production;
        if (conflict_production->symbol == symbol) {
            return 0;
        }
    }
    new_node = new_set_node();
    new_node->symbol = symbol;
    last_node->next = new_node;
    return 1;
}
uint set_union(SymbolSetNode** dest_configs,
    register SymbolSetNode* src_configs)
{
    uint changed = 0;
    for (; src_configs; src_configs = src_configs->next) {
        changed |= set_add_unique(dest_configs, src_configs->symbol);
    }
    return changed;
}
uint set_contains(register SymbolSetNode* list,
    Symbol* symbol)
{
    uint contains = 0;
    for (; list; list = list->next) {
        if (list->symbol == symbol) {
            contains = 1;
            break;
        }
    }
    return contains;
}
Symbol* set_intersect(register SymbolSetNode* set_a,
    register SymbolSetNode* set_b)
{
    SymbolSetNode* saved_set_b = set_b;
    Symbol* common_symbol = NULL;
    for (; set_a; set_a = set_a->next) {
        for (; set_b; set_b = set_b->next) {
            if (set_a->symbol == set_b->symbol) {
                common_symbol = set_a->symbol;
                break;
            }
        }
        if (common_symbol) {
            break;
        }
        set_b = saved_set_b;
    }
    return common_symbol;
}
int sets_equal_unordered(register SymbolSetNode* set_a,
    register SymbolSetNode* set_b)
{
    SymbolSetNode* saved_set_a = set_a,
        * saved_set_b = set_b;
    int found = 0,
        equal = 1;
    for (; set_a && set_b; set_a = set_a->next, set_b = set_b->next) {
    }
    if (set_a || set_b) {
        equal = 0;
    }
    else {
        set_a = saved_set_a;
        set_b = saved_set_b;
        for (; set_a; set_a = set_a->next) {
            for (found = 0; set_b; set_b = set_b->next) {
                if (set_a->symbol == set_b->symbol) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                equal = 0;
                break;
            }
            set_b = saved_set_b;
        }
    }
    return equal;
}
int sets_equal_ordered(register SymbolSetNode* set_a,
    register SymbolSetNode* set_b)
{
    for (; set_a && set_b; set_a = set_a->next, set_b = set_b->next) {
        if (set_a->symbol != set_b->symbol) {
            break;
        }
    }
    return (!(set_a || set_b));
}
Symbol* set_intersect_infinite(register SymbolSetNode* set_a,
    register SymbolSetNode* set_b)
{
    SymbolSetNode* saved_set_b = set_b;
    Symbol* common_symbol = NULL;
    for (; set_a; set_a = set_a->next) {
        for (; set_b; set_b = set_b->next) {
            if (set_a->symbol == set_b->symbol) {
                if (set_a->symbol->infinite_derivation) {
                    common_symbol = set_a->symbol;
                    break;
                }
            }
        }
        if (common_symbol) {
            break;
        }
        set_b = saved_set_b;
    }
    return common_symbol;
}
void free_symbol_set(SymbolSetNode* list)
{
    register SymbolSetNode* node,
        * last_node;
    if (!(conserve_memory && list)) {
        return;
    }
    if (!free_set_list) {
        free_set_list = list;
        return;
    }
    for (node = list; node; node = node->next) {
        last_node = node;
    }
    last_node->next = free_set_list;
    free_set_list = list;
}
uint reused_set_count(void)
{
    return reused_count;
}
void print_firsts_nonterminals(void)
{
    register Symbol** block;
    register SymbolSetNode* set_node;
    uint count;
    printf("\n\n\t\t\t FIRSTS SETS OF NONTERMINALS ONLY\n\n");
    for (block = nonterminals; *++block;) {
        printf("%s: ", (*block)->name);
        set_node = (*block)->left_corners;
        count = 0;
        for (; set_node; set_node = set_node->next) {
            printf("  %s", set_node->symbol->name);
            if (++count > 30) {
                printf("\n    ");
                count = 0;
            }
        }
        putchar('\n');
    }
}
void print_follows_nonterminals(void)
{
    register Symbol** block;
    register SymbolSetNode* set_node;
    uint count;
    printf("\n\n\t\t\t FOLLOWS SETS OF NONTERMINALS ONLY\n\n");
    for (block = nonterminals; *++block;) {
        printf("%s: ", (*block)->name);
        set_node = (*block)->follow_nonterminals;
        count = 0;
        for (; set_node; set_node = set_node->next) {
            printf("  %s", set_node->symbol->name);
            if (++count > 30) {
                printf("\n    ");
                count = 0;
            }
        }
        putchar('\n');
    }
}
static Config* free_config_nodes,
* stashed_config_nodes;
static Config*
alloc_recycled_config(void)
{
    register Config* node = free_config_nodes;
    if (node) {
        free_config_nodes = node->next;
        memset(node, 0, sizeof(Config));
    }
    return node;
}
static Config*
new_config_node(void)
{
    register Config* config;
    static int block_left = 0;
    static Config* block;
    if (--block_left > 0) {
        ++block;
        config = block;
    }
    else {
        block_left = 0;
        config = alloc_recycled_config();
        if (!config) {
            block_left = 1024;
            block = (Config*)calloc(block_left, sizeof(Config));
            config = block;
            if (!config) {
                fatal_error(1301, "out of memory");
            }
        }
    }
    return config;
}
Config*
new_config(Symbol** lhs,
    Symbol** dot,
    Config* link,
    uint origin)
{
    register Config* new_node;
    new_node = new_config_node();
    new_node->lhs = lhs;
    new_node->dot = dot;
    new_node->link = link;
    new_node->origin = origin;
    return new_node;
}
uint add_config_front(Config** list,
    register Config* config)
{
    register Config* conflict_production;
    Config* new_node = NULL,
        * last_node = NULL;
    if (!*list) {
        new_node = new_config_node();
        new_node->lhs = config->lhs;
        new_node->dot = config->dot;
        new_node->link = config->link;
        new_node->origin = config->origin;
        *list = new_node;
        return 1;
    }
    for (conflict_production = *list; conflict_production; conflict_production = conflict_production->next) {
        last_node = conflict_production;
        if (conflict_production->dot == config->dot) {
            if (compare_config_links) {
                if (conflict_production->link == config->link) {
                    return 0;
                }
            }
            else {
                return 0;
            }
        }
    }
    new_node = new_config_node();
    new_node->lhs = config->lhs;
    new_node->dot = config->dot;
    new_node->link = config->link;
    new_node->origin = config->origin;
    last_node->next = new_node;
    return 1;
}
uint add_config(Config** list,
    Symbol** lhs,
    Symbol** dot,
    Config* link,
    Config** out_config,
    uint origin)
{
    register Config* last_node = NULL,
        * new_node = NULL;
    Config* conflict_production;
    int changed = 1;
    if (*list) {
        for (conflict_production = *list; conflict_production; conflict_production = conflict_production->next) {
            last_node = conflict_production;
            if (conflict_production->dot == dot) {
                if (compare_config_links) {
                    if (conflict_production->link == link) {
                        changed = 0;
                    }
                }
                else {
                    changed = 0;
                }
                if (!changed) {
                    if (out_config) {
                        *out_config = conflict_production;
                    }
                    break;
                }
            }
        }
    }
    if (changed) {
        new_node = new_config_node();
        new_node->lhs = lhs;
        new_node->dot = dot;
        new_node->link = link;
        new_node->origin = origin;
        if (out_config) {
            *out_config = new_node;
        }
        if (*list) {
            last_node->next = new_node;
        }
        else {
            *list = new_node;
        }
    }
    if (verbose_level > 8) {
        if (changed) {
        }
        else {
            if (conflict_production->link != link) {
                ;
                ;
                print_config(lhs, dot);
                if (conflict_production->link) {
                    ;
                    ;
                    print_config(conflict_production->link->lhs, conflict_production->link->dot);
                }
                if (link) {
                    ;
                    ;
                    print_config(link->lhs, link->dot);
                }
            }
        }
    }
    return changed;
}
uint add_configs(Config** dest_configs,
    register Config* src_configs,
    Config* link)
{
    uint changed = 0;
    for (; src_configs; src_configs = src_configs->next) {
        changed |= add_config(dest_configs, src_configs->lhs, src_configs->dot,
            link, NULL, src_configs->origin);
    }
    return changed;
}
Config*
find_shared_nonterminal_config(register Config* dest_configs,
    register Config* src_configs)
{
    Config* saved_configs = src_configs,
        * found_config = NULL;
    Symbol* dot;
    for (; dest_configs; dest_configs = dest_configs->next) {
        for (; src_configs; src_configs = src_configs->next) {
            if (dest_configs->dot == src_configs->dot) {
                dot = *dest_configs->dot;
                if (dot) {
                    if (dot->type == 1) {
                        if (!dot->nullable) {
                            found_config = dest_configs;
                            break;
                        }
                    }
                }
            }
        }
        if (found_config) {
            break;
        }
        src_configs = saved_configs;
    }
    return found_config;
}
uint configs_equal(register Config* dest_configs,
    register Config* src_configs)
{
    for (; dest_configs && src_configs; dest_configs = dest_configs->next, src_configs = src_configs->next) {
        if (dest_configs->dot != src_configs->dot) {
            break;
        }
    }
    return (!(dest_configs || src_configs));
}
void free_config(register Config* node)
{
    if (!conserve_memory) {
        return;
    }
    node->next = free_config_nodes;
    free_config_nodes = node;
}
void free_config_list(Config** list)
{
    register Config* node = free_config_nodes,
        * last_node;
    if (!conserve_memory) {
        return;
    }
    if (!*list) {
        return;
    }
    if (!node) {
        free_config_nodes = *list;
        *list = NULL;
        return;
    }
    for (; node; node = node->next) {
        last_node = node;
    }
    last_node->next = *list;
    *list = NULL;
}
Config*
copy_config_list(register Config* list)
{
    register Config* node,
        * copy_node;
    Config* copy_head = NULL;
    if (list) {
        copy_node = new_config_node();
        *copy_node = *list;
        node = copy_node;
        copy_head = copy_node;
        list = list->next;
    }
    for (; list; list = list->next, node = node->next) {
        copy_node = new_config_node();
        *copy_node = *list;
        node->next = copy_node;
        copy_node->next = NULL;
    }
    return copy_head;
}
void stash_config_list(Config** list)
{
    register Config* node = stashed_config_nodes,
        * last_node;
    if (!conserve_memory) {
        return;
    }
    if (!*list) {
        return;
    }
    if (!node) {
        stashed_config_nodes = *list;
        *list = NULL;
        return;
    }
    for (; node; node = node->next) {
        last_node = node;
    }
    last_node->next = *list;
    *list = NULL;
}
void flush_stashed_configs(void)
{
    if (!conserve_memory) {
        return;
    }
    free_config_list(&stashed_config_nodes);
}
int configs_have_nonterminal(Config* list)
{
    register Symbol** symbol;
    int found = 0;
    for (; list; list = list->next) {
        for (symbol = list->lhs; *++symbol;) {
            if ((*symbol)->type == 1) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    return found;
}
void print_config(Symbol** lhs,
    Symbol** dot)
{
    register Symbol** symbol = lhs;
    ;
    ;
    while (*++symbol) {
        if (symbol != dot) {
            ;
            ;
        }
        else {
            ;
            ;
        }
    }
    if (!*dot) {
        ;
        ;
    };
    ;
}
void print_configs(Config** list)
{
    register Config* node;
    register Config* link;
    if (!*list) {
        return;
    }
    for (node = *list; node; node = node->next) {
        print_config(node->lhs, node->dot);
        if (trace_level < -3) {
            link = node->link;
            for (; link; link = link->link) {
                ;
                ;
                print_config(link->lhs, link->dot);
            };
            ;
        }
    };
    ;
}
uint nonterminal_count = 0,
terminal_count = 0,
action_count = 0,
production_count = 0;
static uint nonterminal_capacity = 0,
terminal_capacity = 0,
action_capacity = 0,
production_capacity = 0;
uint conditional_count = 0,
ignored_conflict_count = 0,
max_production_length = 0,
start_conflict = 0,
start_action = 0,
start_symbol_number = 0;
Symbol
** nonterminals = NULL,
** terminals = NULL,
** actions = NULL,
*** productions = NULL;
static struct recursion_stack
{
    Symbol** stack_top,
        * stack_base[255 + 1];
} stack = { stack.stack_base + 255 };
static TableEntry*
new_table_entry(void)
{
    static int block_left = 0;
    static TableEntry* table;
    if (--block_left > 0) {
        return (++table);
    }
    else {
        block_left = 1024;
        table = (TableEntry*)calloc(block_left, sizeof(TableEntry));
        if (!table) {
            block_left = 0;
            fatal_error(1502, "out of memory");
        }
    }
    return table;
}
static uint
not_on_nullable_stack(register Symbol* nonterminal)
{
    register Symbol** block = stack.stack_top;
    while (*block) {
        if (*block++ == nonterminal) {
            return 0;
        }
    }
    return 1;
}
static void
print_recursion_stack(void)
{
    register Symbol** block = stack.stack_top;
    while (*block) {
        printf("    %s\n", (*block)->name);
        ++block;
    }
}
static uint
nullable_derives(Symbol* nonterminal)
{
    register Symbol** symbol;
    register Symbol*** block = productions;
    Symbol* lhs;
    int is_nullable;
    int nullable = 0;
    while (*++block) {
        symbol = *block;
        lhs = *symbol;
        if (lhs == nonterminal) {
            is_nullable = 1;
            while (*++symbol) {
                if ((*symbol)->type == 2) {
                    is_nullable = 0;
                    break;
                }
                else if ((*symbol)->type == 1) {
                    if (*symbol == lhs) {
                        continue;
                    }
                    if (not_on_nullable_stack(*symbol)) {
                        if (stack.stack_top > stack.stack_base)
                            *--stack.stack_top = *symbol;
                        else
                            fatal_error(1501, "stack overflow");
                        is_nullable = nullable_derives(*symbol);
                        if (*stack.stack_top)
                            stack.stack_top++;
                        ;
                        if (!is_nullable) {
                            break;
                        }
                    }
                    else {
                        if (verbose_level > 2) {
                            if (!nonterminal->indirect_left_recursive) {
                                printf("  %s: indirect left recursive \n",
                                    nonterminal->name);
                                print_recursion_stack();
                            }
                        }
                        note_left_recursion();
                        nonterminal->indirect_left_recursive = 1;
                    }
                }
            }
            if (is_nullable) {
                nullable = 1;
            }
        }
    }
    return (nullable);
}
static void
compute_nullable(void)
{
    register Symbol** symbol,
        * lhs;
    Symbol*** block = productions;
    int nullable,
        changed;
    while (*++block) {
        symbol = *block;
        lhs = *symbol;
        if (!lhs->nullable) {
            lhs->nullable = 1;
            lhs->null_production = 1;
            while (*++symbol) {
                if ((*symbol)->type != 3) {
                    lhs->nullable = 0;
                    lhs->null_production = 0;
                    break;
                }
            }
        }
    }
    do {
        changed = 0;
        symbol = nonterminals;
        while (*++symbol) {
            if ((*symbol)->nullable) {
                continue;
            }
            nullable = nullable_derives(*symbol);
            if (nullable) {
                (*symbol)->nullable = 1;
                changed = 1;
            }
        }
    }
    while (changed);
}
static void
count_productions(void)
{
    register Symbol* lhs,
        *** block = &productions[1];
    uint count;
    for (lhs = **block, count = 0; *block; ++block, ++count) {
        if (lhs != **block) {
            lhs->production_count = count;
            count = 0;
            lhs = **block;
        }
    }
}
static void
seed_configs(void)
{
    register Symbol** dot,
        *** block = productions;
    Symbol* lhs;
    while (*++block) {
        dot = *block;
        lhs = *dot;
        for (++dot; *dot && ((*dot)->type == 3); ++dot)
            ;
        add_config(&lhs->configs, *block, dot, NULL, NULL, 0);
    }
}
static uint
compute_firsts(void)
{
    register Symbol** symbol,
        * lhs;
    Symbol*** block;
    int changed;
    uint errors = 0;
    symbol = terminals;
    while (*++symbol) {
        set_add_unique_front(&(*symbol)->firsts, *symbol);
    }
    for (changed = 1; changed;) {
        changed = 0;
        block = productions;
        while (*++block) {
            symbol = *block;
            lhs = *symbol;
            while (*++symbol) {
                if ((*symbol)->type == 3) {
                    continue;
                }
                changed |= set_union_front(&lhs->firsts, (*symbol)->firsts);
                if (!(*symbol)->nullable) {
                    break;
                }
            }
            if (!*symbol) {
                if (!lhs->nullable) {
                    printf("error: %s: is_nullable not set \n", lhs->name);
                    lhs->nullable = 1;
                    ++errors;
                }
            }
        }
    }
    return errors;
}
static uint
compute_follows(void)
{
    register Symbol** symbol,
        ** rhs_cursor;
    Symbol*** block,
        * stack_base = *productions[1],
        * eof_symbol;
    int changed, follow_changed;
    uint errors = 0;
    eof_symbol = find_symbol("END_OF_SLK_INPUT");
    set_add_unique_front(&stack_base->follows, eof_symbol);
    for (changed = 1; changed;) {
        changed = 0;
        block = productions;
        while (*++block) {
            symbol = *block;
            while (*++symbol) {
                if ((*symbol)->type != 1) {
                    continue;
                }
                rhs_cursor = symbol;
                for (;;) {
                    if (!*++rhs_cursor) {
                        break;
                    }
                    if ((*rhs_cursor)->type == 3) {
                        continue;
                    }
                    changed |= set_union_front(&(*symbol)->follows,
                        (*rhs_cursor)->firsts);
                    if ((*rhs_cursor)->type == 1) {
                        changed |= set_add_unique(&(*symbol)->follow_nonterminals,
                            *rhs_cursor);
                    }
                    if (!(*rhs_cursor)->nullable) {
                        break;
                    }
                }
                if (!*rhs_cursor && (*symbol) != (**block)) {
                    changed |= set_union_front(&(*symbol)->follows,
                        (**block)->follows);
                    follow_changed = set_union_front(&(*symbol)->follow_nonterminals,
                        (**block)->follow_nonterminals);
                    changed |= follow_changed;
                    if (trace_level == -1 && follow_changed && (*symbol)->nullable) {
                        ;
                        ;
                    }
                }
            }
        }
    }
    return errors;
}
static void
print_derivation_trace(Symbol* nonterminal,
    int depth,
    char* visited)
{
    register Symbol** dot,
        *** block = productions;
    Symbol** found,
        * lhs;
    int index;
    static char indent_spaces[] = "                                                      ";
    for (index = 1; *++block; ++index) {
        dot = *block;
        lhs = *dot;
        found = NULL;
        for (++dot; *dot; ++dot) {
            if (*dot == nonterminal) {
                if (lhs == nonterminal) {
                    continue;
                }
                if (visited[index]) {
                    continue;
                }
                found = dot;
                for (++dot; *dot; ++dot) {
                    if ((*dot)->type == 3) {
                        continue;
                    }
                    if (!(*dot)->nullable) {
                        break;
                    }
                }
            }
            if (found && !*dot) {
                indent_spaces[depth + 1] = '\0';
                print_production(indent_spaces, *block);
                indent_spaces[depth + 1] = ' ';
                visited[index] = 1;
                print_derivation_trace(lhs, depth + 1, visited);
            }
        }
    }
}
static uint
check_nullable_follow_self(void)
{
    register Symbol** nonterminal = nonterminals + 1;
    uint contains,
        found = 0;
    while (*++nonterminal) {
        if ((*nonterminal)->nullable) {
            contains = set_contains((*nonterminal)->follow_nonterminals,
                *nonterminal);
            if (contains) {
                found = 1;
                (*nonterminal)->nullable_follows_self = 1;
                printf(" %s: ambiguous: nullable can follow itself \n",
                    (*nonterminal)->name);
                if (trace_level == -1) {
                    char* visited = calloc(production_count + 4, 1);
                    print_derivation_trace(*nonterminal, 0, visited);
                }
            }
        }
    }
    return found;
}
static void
insert_table_entry(TableEntry** table,
    int token,
    int production)
{
    register TableEntry* new_node,
        * block = *table;
    new_node = new_table_entry();
    new_node->token = token;
    new_node->production = production;
    if (!block) {
        *table = new_node;
        return;
    }
    if (block->token > token) {
        new_node->next = block;
        *table = new_node;
        return;
    }
    for (; block; block = block->next) {
        if (!block->next) {
            block->next = new_node;
            break;
        }
        else if (block->next->token > token) {
            new_node->next = block->next;
            block->next = new_node;
            break;
        }
    }
}
static int
find_table_entry(register TableEntry* table,
    register int token)
{
    for (; table; table = table->next) {
        if (table->token == token) {
            return (table->production);
        }
    }
    return 0;
}
static ConflictProduction*
new_conflict_production_for(int number)
{
    Symbol** lhs,
        ** dot;
    Config* config;
    ConflictProduction* new_node;
    lhs = productions[number];
    dot = lhs + 1;
    for (; *dot && ((*dot)->type == 3); ++dot)
        ;
    config = new_config(lhs, dot, NULL, CONFIG_BASE);
    new_node = new_conflict_production(number, number, config);
    return (new_node);
}
static uint
build_ll_conflicts(void)
{
    register SymbolSetNode* firsts_node,
        * follows_node;
    Symbol* lhs,
        ** dot,
        *** block = productions;
    int token,
        production_number = 0,
        old_production;
    ConflictProduction* conflict_production,
        * new_node;
    uint errors = 0;
    while (*++block) {
        dot = *block;
        lhs = *dot;
        ++production_number;
        if (rhs_nullable(++dot)) {
            for (follows_node = lhs->follows; follows_node; follows_node = follows_node->next) {
                token = follows_node->symbol->number;
                old_production = find_table_entry(lhs->table, token);
                if (old_production) {
                    if (old_production != production_number) {
                        conflict_production = new_conflict_production_for(old_production);
                        new_node = new_conflict_production_for(production_number);
                        add_conflict(follows_node->symbol, conflict_production, new_node, 0);
                    }
                }
                else {
                    ++lhs->table_count;
                    insert_table_entry(&lhs->table, token, production_number);
                }
            }
        }
        for (; *dot; ++dot) {
            if ((*dot)->type == 3) {
                continue;
            }
            for (firsts_node = (*dot)->firsts; firsts_node; firsts_node = firsts_node->next) {
                token = firsts_node->symbol->number;
                old_production = find_table_entry(lhs->table, token);
                if (old_production) {
                    if (old_production != production_number) {
                        conflict_production = new_conflict_production_for(old_production);
                        new_node = new_conflict_production_for(production_number);
                        add_conflict(firsts_node->symbol, conflict_production, new_node, 0);
                    }
                }
                else {
                    ++lhs->table_count;
                    insert_table_entry(&lhs->table, token, production_number);
                }
            }
            if (!(*dot)->nullable) {
                break;
            }
        }
    }
    return errors;
}
static void
assign_symbol_numbers(void)
{
    register Symbol** block,
        ** slot_cursor,
        * symbol;
    Symbol** dest_slot = &nonterminals[nonterminal_count + 1],
        ** cursor = &nonterminals[nonterminal_count + 1 -
        conditional_count];
    int conditional_total = conditional_count,
        type_index;
    if (nonterminal_count && nonterminals[1]->number) {
        return;
    }
    if (conditional_total) {
        for (block = nonterminals; ++block < cursor;) {
            if ((*block)->conditional) {
                *dest_slot = *block;
                for (slot_cursor = block; *slot_cursor; ++slot_cursor) {
                    *slot_cursor = *(slot_cursor + 1);
                }
                --block;
            }
        }
    }
    for (type_index = 1, block = terminals; *++block;) {
        (*block)->number = type_index++;
    }
    start_symbol_number = type_index;
    for (block = nonterminals; *++block;) {
        (*block)->number = type_index++;
    }
    start_action = type_index;
    block = actions;
    if (*++block) {
        symbol = *block;
        if (symbol->number) {
            for (; *block; ++block) {
                symbol = *block;
                if (!symbol->number) {
                    fatal_error(1512, "Cannot mix numbered and unnumbered actions");
                }
                symbol->number += start_action - 1;
            }
        }
        else {
            for (; *block; ++block) {
                symbol = *block;
                if (symbol->number) {
                    fatal_error(1513, "Cannot mix numbered and unnumbered actions");
                }
                symbol->number = type_index++;
            }
        }
    }
    start_conflict = production_count + 1;
}
void initialize_grammar(void)
{
    if (!production_count) {
        note_error();
        return;
    }
    if (ebnf_enabled()) {
        expand_ebnf();
    }
    assign_symbol_numbers();
    compute_nullable();
    count_productions();
    seed_configs();
}
uint compute_first_follow(void)
{
    uint errors = 0;
    ;
    ;
    errors |= compute_firsts();
    ;
    ;
    errors |= compute_follows();
    check_nullable_follow_self();
    return errors;
}
uint build_ll_table(void)
{
    uint errors = 0;
    ;
    ;
    errors |= build_ll_conflicts();
    return errors;
}
Symbol**
copy_production(register Symbol** production)
{
    register Symbol** new_node;
    uint count;
    static size_t data_size = 1024 * sizeof(Symbol**);
    static Symbol** arena = NULL,
        ** cursor = NULL;
    new_node = production;
    while (*new_node++) {
    }
    count = new_node - production;
    if (count > max_production_length) {
        max_production_length = count;
    }
    if (arena + count > cursor) {
        arena = (Symbol**)malloc(data_size);
        if (!arena) {
            fatal_error(1504, "out of memory");
        }
        cursor = arena + (data_size / sizeof(Symbol**)) - 1;
    }
    new_node = arena;
    while (*new_node++ = *production++) {
    }
    arena += count;
    return (arena - count);
}
static Symbol**
find_duplicate_production(Symbol** production)
{
    register Symbol*** block = productions;
    while (*++block) {
        if (**block == *production) {
            if (productions_equal(*block, production)) {
                break;
            }
        }
    }
    return *block;
}
Symbol***
insert_production(Symbol** production_number,
    Symbol*** configs)
{
    register Symbol*** block = NULL;
    char* memory;
    if (find_duplicate_production(production_number)) {
        if (trace_level > 3) {
            print_production("already exists: \n", production_number);
        }
        return block;
    }
    if (++production_count > production_capacity) {
        production_capacity += (64 * 1024);
        productions = (Symbol***)realloc(productions,
            (production_capacity + 4) * sizeof(void*));
        if (!productions) {
            fatal_error(1511, "out of memory");
        }
        memory = (char*)&productions[production_capacity + 4 - (64 * 1024)];
        memset(memory, 0, (64 * 1024) * sizeof(void*));
    }
    block = &productions[production_count];
    for (; block != configs; --block) {
        *block = *(block - 1);
    }
    *block = production_number;
    return block;
}
void delete_production_at(register Symbol*** production)
{
    for (; *production; ++production) {
        *production = *(production + 1);
    }
    --production_count;
}
void add_production_copy(register Symbol** production)
{
    register Symbol*** block;
    Symbol*** insert_pos = NULL;
    char* memory;
    if (++production_count > production_capacity) {
        production_capacity += (64 * 1024);
        productions = (Symbol***)realloc(productions,
            (production_capacity + 4) * sizeof(void*));
        if (!productions) {
            fatal_error(1505, "out of memory");
        }
        memory = (char*)&productions[production_capacity + 4 - (64 * 1024)];
        memset(memory, 0, (64 * 1024) * sizeof(void*));
    }
    for (block = productions; *++block;) {
        if (**block == *production) {
            for (; *block; ++block) {
                if (**block == *production) {
                    if (productions_equal(*block, production)) {
                        if (verbose_level > 2) {
                            printf("  Tried to add duplicate production:\n");
                            print_production("    ", production);
                        }
                        return;
                    }
                }
                else {
                    insert_pos = block;
                    break;
                }
            }
            break;
        }
    }
    if (!*block) {
        *block = copy_production(production);
    }
    else {
        block = &productions[production_count];
        for (; block != insert_pos; --block) {
            *block = *(block - 1);
        }
        *block = copy_production(production);
    }
}
void add_production(register Symbol** production)
{
    register Symbol*** block;
    Symbol*** insert_pos = NULL;
    char* memory;
    if (++production_count > production_capacity) {
        production_capacity += (64 * 1024);
        productions = (Symbol***)realloc(productions,
            (production_capacity + 4) * sizeof(void*));
        if (!productions) {
            fatal_error(1505, "out of memory");
        }
        memory = (char*)&productions[production_capacity + 4 - (64 * 1024)];
        memset(memory, 0, (64 * 1024) * sizeof(void*));
    }
    for (block = productions; *++block;) {
        if (**block == *production) {
            for (; *block; ++block) {
                if (**block == *production) {
                    if (productions_equal(*block, production)) {
                        if (verbose_level > 2) {
                            printf("  Tried to add duplicate production:\n");
                            print_production("    ", production);
                        }
                        return;
                    }
                }
                else {
                    insert_pos = block;
                    break;
                }
            }
            break;
        }
    }
    if (!*block) {
        *block = production;
    }
    else {
        block = &productions[production_count];
        for (; block != insert_pos; --block) {
            *block = *(block - 1);
        }
        *block = production;
    }
}
uint productions_equal(register Symbol** prod_a,
    register Symbol** prod_b)
{
    for (; *prod_a == *prod_b; ++prod_a, ++prod_b) {
        if (!*prod_a) {
            break;
        }
    }
    return (*prod_a == *prod_b);
}
int production_number_of(register Symbol* lhs)
{
    register Symbol*** block = productions;
    int production_number = 1;
    for (; *++block; ++production_number) {
        if (lhs == **block) {
            break;
        }
    }
    return production_number;
}
void register_symbol(Symbol* symbol)
{
    int action_value;
    char* memory;
    if (!nonterminals) {
        nonterminals = (Symbol**)calloc((64 * 1024), sizeof(void*));
        terminals = (Symbol**)calloc((64 * 1024), sizeof(void*));
        actions = (Symbol**)calloc((64 * 1024), sizeof(void*));
        productions = (Symbol***)calloc((64 * 1024), sizeof(void*));
        nonterminal_capacity = (64 * 1024) - 4;
        terminal_capacity = (64 * 1024) - 4;
        action_capacity = (64 * 1024) - 4;
        production_capacity = (64 * 1024) - 4;
        if (!(nonterminals && terminals && actions && productions)) {
            fatal_error(1511, "out of memory");
        }
    }
    switch (symbol->type) {
    case 1:
        nonterminals[++nonterminal_count] = symbol;
        if (nonterminal_count > nonterminal_capacity) {
            nonterminal_capacity += (64 * 1024);
            nonterminals = (Symbol**)realloc(nonterminals,
                (nonterminal_capacity + 4) * sizeof(void*));
            if (!nonterminals) {
                fatal_error(1506, "out of memory");
            }
            memory = (char*)&nonterminals[nonterminal_capacity + 4 - (64 * 1024)];
            memset(memory, 0, (64 * 1024) * sizeof(void*));
        }
        break;
    case 2:
        terminals[++terminal_count] = symbol;
        if (terminal_count > terminal_capacity) {
            terminal_capacity += (64 * 1024);
            terminals = (Symbol**)realloc(terminals,
                (terminal_capacity + 4) * sizeof(void*));
            if (!terminals) {
                fatal_error(1507, "out of memory");
            }
            memory = (char*)&terminals[terminal_capacity + 4 - (64 * 1024)];
            memset(memory, 0, (64 * 1024) * sizeof(void*));
        }
        break;
    case 3:
        ++action_count;
        action_value = symbol->number;
        if (action_value) {
            break;
        }
        actions[action_count] = symbol;
        if (action_count > action_capacity) {
            action_capacity += (64 * 1024);
            actions = (Symbol**)realloc(actions,
                (action_capacity + 4) * sizeof(void*));
            if (!actions) {
                fatal_error(1508, "out of memory");
            }
            memory = (char*)&actions[action_capacity + 4 - (64 * 1024)];
            memset(memory, 0, (64 * 1024) * sizeof(void*));
        }
        break;
    }
}
void terminal_to_nonterminal(register Symbol* symbol)
{
    register Symbol** block;
    char* memory;
    for (block = terminals; *++block;) {
        if (*block == symbol) {
            for (; *block; ++block) {
                *block = *(block + 1);
            }
            --terminal_count;
            break;
        }
    }
    symbol->type = 1;
    nonterminals[++nonterminal_count] = symbol;
    if (nonterminal_count > nonterminal_capacity) {
        nonterminal_capacity += (64 * 1024);
        nonterminals = (Symbol**)realloc(nonterminals,
            (nonterminal_capacity + 4) * sizeof(void*));
        if (!nonterminals) {
            fatal_error(1509, "out of memory");
        }
        memory = (char*)&nonterminals[nonterminal_capacity + 4 - (64 * 1024)];
        memset(memory, 0, (64 * 1024) * sizeof(void*));
    }
}
void set_table_entry(register TableEntry* table,
    register int token,
    int conflict_number)
{
    for (; table; table = table->next) {
        if (table->token == token) {
            table->production = (conflict_number + (start_conflict - 1));
            break;
        }
    }
    if (!table) {
        ;
        ;
        fatal_error(1510, "");
    }
}
void replace_conflict_entry(register TableEntry* table,
    int conflict_number,
    int new_production_number)
{
    int value = (conflict_number + (start_conflict - 1));
    for (; table; table = table->next) {
        if (table->production == value) {
            remove_conflict_entries(conflict_number);
            table->production = new_production_number;
        }
    }
}
uint rhs_nullable(register Symbol** dot)
{
    for (; *dot; ++dot) {
        if ((*dot)->type != 3 && !(*dot)->nullable) {
            return 0;
        }
    }
    return 1;
}
void update_nullable(Symbol* nonterminal)
{
    register Symbol** symbol,
        * lhs;
    Symbol*** block = productions;
    while (*++block) {
        symbol = *block;
        lhs = *symbol;
        if (lhs == nonterminal) {
            if (!lhs->nullable) {
                lhs->nullable = 1;
                lhs->null_production = 1;
                while (*++symbol) {
                    if ((*symbol)->type != 3) {
                        lhs->nullable = 0;
                        lhs->null_production = 0;
                        break;
                    }
                }
            }
        }
    }
    if (!nonterminal->nullable) {
        nonterminal->nullable = nullable_derives(*symbol);
    }
}
static char*
unique_name(char* conflict_production)
{
    static uint number = 0;
    static char new_node[128];
    uint count;
    count = strlen(conflict_production);
    if (count >= sizeof(new_node) - 12) {
        if (trace_level > 0) {
            print_productions();
        }
        printf("old string too long:\n  %s\n", conflict_production);
        fatal_error(1902, "");
    }
    sprintf(new_node, "%s_%02u", conflict_production, ++number);
    return new_node;
}
void print_usage_productions(void)
{
    register Symbol*** block = productions,
        ** symbol;
    Symbol** lhs;
    int index = 0;
    while (*++block) {
        lhs = *block;
        symbol = *block;
        printf("%2d: %s -->", ++index, (*symbol)->name);
        while (*++symbol) {
            if ((*symbol)->type == 1 && *symbol != *lhs) {
                if (!(*symbol)->unit_production) {
                    ++(*symbol)->use_count;
                }
            }
            if ((*symbol)->type == 1 && *symbol != *lhs) {
                if ((*symbol)->use_count > 1) {
                    printf(" %s (%d)", (*symbol)->name, (*symbol)->use_count);
                }
                else {
                    printf(" %s ", (*symbol)->name);
                }
            }
            else {
                printf(" %s ", (*symbol)->name);
            }
        }
        putchar('\n');
    }
}
void print_usage_productions2(void)
{
    register Symbol*** block = productions,
        ** symbol;
    int index = 0;
    print_usage_productions();
    while (*++block) {
        symbol = *block;
        printf("%2d: %s -->", ++index, (*symbol)->name);
        while (*++symbol) {
            printf(" %s", (*symbol)->name);
        }
        putchar('\n');
    }
}
void print_first_sets(void)
{
    register Symbol** block;
    register SymbolSetNode* set_node;
    printf("\n\n\t\t\t NONTERMINAL FIRSTS SETS \n\n");
    for (block = nonterminals; *++block;) {
        printf("%s: ", (*block)->name);
        if ((*block)->nullable) {
            printf("  _epsilon_");
        }
        for (set_node = (*block)->firsts; set_node; set_node = set_node->next) {
            printf("  %s", set_node->symbol->name);
        }
        putchar('\n');
    }
}
void print_follow_sets(void)
{
    register Symbol** block;
    register SymbolSetNode* set_node;
    printf("\n\n\t\t\t NONTERMINAL FOLLOWS SETS \n\n");
    for (block = nonterminals; *++block;) {
        printf("%s: ", (*block)->name);
        for (set_node = (*block)->follows; set_node; set_node = set_node->next) {
            printf("  %s", set_node->symbol->name);
        }
        putchar('\n');
    }
}
void print_nullable(void)
{
    register Symbol** nonterminal = nonterminals;
    fputs("\n\n\t\t NONTERMINALS GOING TO EMPTY STRING \n\n", stdout);
    while (*++nonterminal)
        if ((*nonterminal)->nullable)
            printf("\t%s\n", (*nonterminal)->name);
}
void print_parse_table(int use_lr)
{
    register Symbol** nonterminal = nonterminals;
    register TableEntry* table;
    fputs("\n\n\t\t\t PARSE TABLE \n\n", stdout);
    if (use_lr) {
        print_lr_parse_table();
        return;
    }
    while (*++nonterminal) {
        fputs((*nonterminal)->name, stdout);
        putchar(':');
        for (table = (*nonterminal)->table; table; table = table->next) {
            printf("   %s %d", terminals[table->token]->name,
                table->production);
        }
        putchar('\n');
    }
}
void print_productions(void)
{
    register Symbol*** block = productions,
        ** symbol;
    int index = 0;
    printf("\n\n\t\t\t PRODUCTION STRINGS \n\n");
    while (*++block) {
        symbol = *block;
        printf("%2d: %s -->", ++index, (*symbol)->name);
        while (*++symbol) {
            printf(" %s", (*symbol)->name);
        }
        putchar('\n');
    }
}
void print_production_integers(void)
{
    register Symbol*** production = productions;
    register Symbol** block;
    int index = 0;
    fputs("\n\n\t\t\t PRODUCTION INTEGERS \n\n", stdout);
    while (*++production) {
        block = *production;
        printf("%2d: %d -->", ++index, (*block)->number);
        while (*++block)
            printf("%6d", (*block)->number);
        putchar('\n');
    }
}
void print_production(char* indent,
    Symbol** production)
{
    register Symbol** symbol = production;
    if (indent) {
        printf("%s ", indent);
    }
    printf("%s -->", (*symbol)->name);
    while (*++symbol) {
        printf("  %s", (*symbol)->name);
    }
    putchar('\n');
}
void print_production_number(int number)
{
    register Symbol** symbol;
    if (!number) {
        return;
    }
    symbol = productions[number];
    printf("%d:  %s -->", number, (*symbol)->name);
    while (*++symbol) {
        printf(" %s", (*symbol)->name);
    }
    putchar('\n');
}
void print_productions_of(Symbol* nonterminal)
{
    register Symbol*** block = productions;
    while (*++block) {
        if (**block == nonterminal) {
            print_production(NULL, *block);
        }
    }
}
static Symbol* symbol_buckets[10007];
static Symbol*
new_symbol_node(void)
{
    static int block_left = 0;
    static Symbol* name;
    if (--block_left > 0) {
        return (++name);
    }
    else {
        block_left = 256;
        name = (Symbol*)calloc(block_left, sizeof(Symbol));
        if (!name) {
            block_left = 0;
            fatal_error(1601, "out of memory");
        }
    }
    return name;
}
static uint
hash_symbol(char* str)
{
    register char* arg = str - 1;
    register uint hash_value = 0;
    register uint high_bits;
    while (*++arg) {
        hash_value = (hash_value << 4) + *arg;
        if (high_bits = hash_value & 0xf0000000) {
            hash_value ^= (high_bits >> 24);
            hash_value ^= high_bits;
        }
    }
    return (hash_value % 10007);
}
char*
str_dup(char* str)
{
    uint count;
    static size_t data_size = 1024 * 16;
    static char* arena = NULL,
        * cursor = NULL;
    count = strlen(str) + 1;
    if (arena + count > cursor) {
        arena = malloc(data_size);
        if (!arena) {
            fatal_error(1602, "out of memory");
        }
        cursor = arena + data_size - 1;
    }
    strcpy(arena, str);
    arena += count;
    return (arena - count);
}
Symbol* find_symbol(register char* name)
{
    register Symbol* block;
    block = symbol_buckets[hash_symbol(name)];
    if (block) {
        while ((block = block->next)) {
            if (!(strcmp(name, block->name))) {
                return block;
            }
        }
    }
    return NULL;
}
Symbol* new_symbol(int type,
    int number,
    char* name)
{
    register Symbol* new_node,
        * bucket;
    int hash_index;
    hash_index = hash_symbol(name);
    bucket = symbol_buckets[hash_index];
    if (!bucket) {
        bucket = new_symbol_node();
        symbol_buckets[hash_index] = bucket;
    }
    new_node = new_symbol_node();
    new_node->type = type;
    new_node->number = number;
    new_node->name = str_dup(name);
    new_node->next = bucket->next;
    bucket->next = new_node;
    return new_node;
}
void print_symbol_table(void)
{
    register Symbol** bucket = symbol_buckets,
        * symbol;
    int hash_index;
    fputs("\n HASHVAL  TYPE  TOKEN  NAME ", stdout);
    fputs("\n -------  ----  -----  ---------------------\n", stdout);
    for (hash_index = 0; hash_index < 10007; ++hash_index) {
        symbol = *bucket++;
        if (symbol) {
            while ((symbol = symbol->next)) {
                printf("%6d    %4d  %5d  %s \n",
                    hash_index, symbol->type, symbol->number, symbol->name);
            }
        }
    }
}
char* array_close = "}";
static uint
max2(uint value_a,
    uint value_b)
{
    uint max2 = value_a;
    if (value_b > max2) {
        max2 = value_b;
    }
    return (max2);
}
static uint
max3(uint value_a,
    uint value_b,
    uint value_c)
{
    uint max3 = value_a;
    if (value_b > max3) {
        max3 = value_b;
    }
    if (value_c > max3) {
        max3 = value_c;
    }
    return (max3);
}
static int
actions_are_named(int yacc_grammar)
{
    register Symbol** symbol;
    int named_actions = 1;
    uchar* name_cursor,
        * name_end;
    for (symbol = actions; *++symbol;) {
        name_cursor = (*symbol)->name;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        if (((*name_end >= '0' && *name_end <= '9'))) {
            named_actions = 0;
        }
    }
    return named_actions;
}
static void
write_parse_table_plain(FILE* out_file,
    int* row_offsets,
    uint generate_flags)
{
    register int* block;
    register TableEntry* table;
    int offset,
        table_count = terminal_count,
        token;
    Symbol** nonterminal;
    int count;
    if (generate_flags & 0x00002000) {
        fputs("var Parse = [0,0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static slk_size_t Parse[] = {0,0\n\n", out_file);
    }
    else {
        fputs("private static short[] Parse = {0,0\n\n", out_file);
    }
    nonterminal = nonterminals;
    offset = 1;
    block = row_offsets;
    while (*++nonterminal) {
        token = 0;
        *++block = offset;
        for (table = (*nonterminal)->table; table; table = table->next) {
            while (++token < table->token) {
                fputs(",0", out_file);
            }
            fprintf(out_file, ",%u", table->production);
        }
        while (++token <= terminal_count) {
            fputs(",0", out_file);
        }
        offset += table_count;
        fputs("\n", out_file);
    }
    *++block = 0;
    fprintf(out_file, "%s;\n\n", array_close);
    if (generate_flags & 0x00002000) {
        fputs("var Parse_row = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static int Parse_row[] = {0\n\n", out_file);
    }
    else {
        fputs("private static int[] Parse_row = {0\n\n", out_file);
    }
    block = row_offsets;
    for (count = 1; *++block; ++count) {
        fprintf(out_file, ",%u", *block);
        if (count >= 16) {
            count = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
}
static void
write_conflict_table_plain(FILE* out_file,
    int* row_offsets,
    uint generate_flags)
{
    register int* row_offsets2;
    register ConflictEntry* block;
    int offset,
        table_count = terminal_count,
        production,
        token;
    ConflictRow* row;
    uint total_levels = 0,
        row_count;
    uint terminal_only;
    ConflictLevel* conflict_level;
    int count;
    conflict_level = get_conflict_levels();
    if (generate_flags & 0x00002000) {
        fprintf(out_file, "var Conflict = [0,0\n\n");
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fprintf(out_file, "static slk_size_t Conflict[] = {0,0\n\n");
    }
    else {
        fprintf(out_file, "private static short[] Conflict = {0,0\n\n");
    }
    offset = 1;
    row_offsets2 = row_offsets;
    for (; conflict_level; conflict_level = conflict_level->next) {
        terminal_only = 1;
        row_count = 0;
        for (row = conflict_level->rows; row; row = row->next) {
            ++row_count;
        }
        total_levels += row_count;
        for (row = conflict_level->rows; row; row = row->next) {
            token = 0;
            *++row_offsets2 = offset;
            for (block = row->entries; block; block = block->next) {
                while (++token < block->token) {
                    fputs(",0", out_file);
                }
                production = block->production;
                if ((production >= start_conflict)) {
                    production += total_levels;
                    terminal_only = 0;
                }
                fprintf(out_file, ",%u", production);
            }
            while (++token <= terminal_count) {
                fputs(",0", out_file);
            }
            offset += table_count;
            fputs("\n", out_file);
        }
        fputs("\n", out_file);
        if (terminal_only) {
            break;
        }
    }
    *++row_offsets2 = 0;
    fprintf(out_file, "%s;\n\n", array_close);
    if (generate_flags & 0x00002000) {
        fprintf(out_file, "var Conflict_row = [0\n\n");
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fprintf(out_file, "static int Conflict_row[] = {0\n\n");
    }
    else {
        fprintf(out_file, "private static int[] Conflict_row = {0\n\n");
    }
    row_offsets2 = row_offsets;
    for (count = 1; *++row_offsets2; ++count) {
        fprintf(out_file, ",%u", *row_offsets2);
        if (count >= 16) {
            count = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
}
static int
next_row_to_compact(void)
{
    register Symbol** nonterminal;
    static int entries_left = 0;
    static uint first_call = 1;
    static int row = 0;
    if (first_call) {
        first_call = 0;
        nonterminal = nonterminals;
        while (*++nonterminal) {
            if ((*nonterminal)->table_count > entries_left)
                entries_left = (*nonterminal)->table_count;
        }
    }
    do {
        while (++row <= nonterminal_count)
            if (nonterminals[row]->table_count == entries_left)
                return (row);
        row = 0;
    }
    while (--entries_left > 0);
    return (0);
}
static int*
compact_parse_table(uint original_size,
    int* table,
    uint table_size,
    int* row_offsets)
{
    register int* free_slot;
    register TableEntry* block;
    int* table_limit = table +
        table_size - terminal_count,
        * last_used = NULL,
        * saved_slot,
        * offset,
        row;
    TableEntry* row_entries;
    uint fits;
    printf("compacting parse table from %u ", original_size);
    while (row = next_row_to_compact()) {
        row_entries = nonterminals[row]->table;
        free_slot = table;
        for (;;) {
            while (*++free_slot) {
                if (free_slot > table_limit) {
                    fatal_error(1102, "\n compact failed");
                }
            }
            block = row_entries;
            if (!block) {
                printf("\n no table entries for %s\n", nonterminals[row]->name);
                fatal_error(1103, "");
            }
            if (free_slot - block->token <= table) {
                continue;
            }
            saved_slot = free_slot;
            free_slot -= block->token;
            fits = 1;
            for (block = row_entries; block; block = block->next) {
                if (*(free_slot + block->token)) {
                    fits = 0;
                    break;
                }
            }
            if (fits) {
                row_offsets[row] = free_slot - table;
                for (block = row_entries; block; block = block->next) {
                    offset = free_slot + block->token;
                    *offset = block->production;
                    if (free_slot + terminal_count > last_used) {
                        last_used = free_slot + terminal_count;
                    }
                }
                break;
            }
            free_slot = saved_slot;
        }
    }
    row_offsets[nonterminal_count + 1] = 0;
    printf("to %lu\n", (ulong)(++last_used - table - 1));
    return last_used;
}
static void
write_parse_table(FILE* out_file,
    int* cursor,
    int* table,
    int* row_offsets,
    uint generate_flags)
{
    register int* block;
    uint count = 1,
        entries = 1;
    block = table;
    if (generate_flags & 0x00002000) {
        fprintf(out_file, "var Parse = [\n\n%u", *block);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fprintf(out_file, "static slk_size_t Parse[] = {\n\n%u", *block);
    }
    else {
        fprintf(out_file, "private static short[] Parse = {\n\n%u", *block);
    }
    while (++block < cursor) {
        ++entries;
        if (++count > 19) {
            count = 0;
            fputs("\n", out_file);
        }
        fprintf(out_file, ",%u", *block);
    }
    fprintf(out_file, "\n%s;\n\n", array_close);
    if (generate_flags & 0x00002000) {
        fputs("var Parse_row = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        if (entries < (1024 * 64 - 32)) {
            fputs("static slk_size_t Parse_row[] = {0\n\n", out_file);
        }
        else {
            fputs("static int Parse_row[] = {0\n\n", out_file);
        }
    }
    else {
        fputs("private static int[] Parse_row = {0\n\n", out_file);
    }
    block = row_offsets;
    for (count = 1; *++block; ++count) {
        fprintf(out_file, ",%u", *block);
        if (count >= 16) {
            count = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
}
static uint
conflict_entries_equal(register ConflictEntry* entries_a,
    register ConflictEntry* entries_b)
{
    uint matched = 1;
    for (; entries_a && entries_b; entries_a = entries_a->next, entries_b = entries_b->next) {
        if (entries_a->token != entries_b->token ||
            entries_a->production != entries_b->production) {
            matched = 0;
            break;
        }
    }
    if (entries_a || entries_b) {
        matched = 0;
    }
    return matched;
}
static int
verify_parse_table(int* table_data,
    int* row_offsets)
{
    register TableEntry* block;
    register Symbol** nonterminal;
    int offset,
        token,
        errors = 0,
        row,
        entry_value,
        production;
    TableEntry* row_entries;
    for (row = 1, nonterminal = nonterminals; *++nonterminal; ++row) {
        row_entries = (*nonterminal)->table;
        for (block = row_entries; block; block = block->next) {
            if (!block) {
                printf("\n no table entries for %s\n", (*nonterminal)->name);
                fatal_error(1143, "");
            }
            production = block->production;
            token = block->token;
            offset = row_offsets[row];
            offset += token;
            entry_value = table_data[offset];
            if (production != entry_value) {
                errors = 1;
                printf("\n%3d: ", row);
                printf("%s: ", (*nonterminal)->name);
                printf("%s: %u != %u at offset %u\n",
                    terminals[token]->name,
                    production, entry_value, offset);
                print_production_number(production);
                print_production_number(entry_value);
            }
        }
    }
    return errors;
}
static int
verify_conflict_table(int* table_data,
    int* row_offsets)
{
    register ConflictEntry* block;
    register ConflictRow* row;
    int conflict_number,
        entry_value,
        errors = 0,
        production;
    uint total_levels = 0,
        token,
        offset,
        row_count;
    uint terminal_only;
    ConflictLevel* conflict_level;
    conflict_level = get_conflict_levels();
    conflict_number = 1;
    for (; conflict_level; conflict_level = conflict_level->next) {
        terminal_only = 1;
        row_count = 0;
        for (row = conflict_level->rows; row; row = row->next) {
            ++row_count;
        }
        total_levels += row_count;
        for (row = conflict_level->rows; row; row = row->next) {
            for (block = row->entries; block; block = block->next) {
                production = block->production;
                if ((production >= start_conflict)) {
                    production += total_levels;
                    terminal_only = 0;
                }
                token = block->token;
                offset = row_offsets[conflict_number];
                offset += token;
                entry_value = table_data[offset];
                if (production != entry_value) {
                    errors = 1;
                    printf("\n%3d: ", conflict_number);
                    printf("%s: ", row->nonterminal->name);
                    printf("%s: %u != %u at offset %u\n",
                        terminals[token]->name,
                        production, entry_value, offset);
                    print_production_number(production);
                    print_production_number(entry_value);
                }
            }
            ++conflict_number;
        }
        if (terminal_only) {
            break;
        }
    }
    return errors;
}
static int*
compact_conflict_table(uint original_size2,
    int* table_data,
    uint table_size2,
    int* row_offsets)
{
    register ConflictEntry* block;
    register ConflictRow* row;
    ConflictRow* previous_row;
    int production;
    uint total_levels = 0,
        conflict_number = 0,
        row_count;
    int* free_slot,
        * table_limit = table_data +
        table_size2 - terminal_count,
        * last_used = table_data,
        * offset,
        * saved_slot;
    uint fits,
        terminal_only;
    ConflictLevel* conflict_level;
    printf("compacting conflict table from %u ", original_size2);
    conflict_level = get_conflict_levels();
    for (; conflict_level; conflict_level = conflict_level->next) {
        terminal_only = 1;
        row_count = 0;
        for (row = conflict_level->rows; row; row = row->next) {
            ++row_count;
        }
        total_levels += row_count;
        previous_row = NULL;
        for (row = conflict_level->rows; row; row = row->next) {
            ++conflict_number;
            free_slot = NULL;
            if (previous_row) {
                if (conflict_entries_equal(previous_row->entries, row->entries)) {
                    *(row_offsets + 1) = *row_offsets;
                    ++row_offsets;
                    previous_row = row;
                    continue;
                }
                if (previous_row->nonterminal == row->nonterminal) {
                    free_slot = table_data + *row_offsets + terminal_count;
                }
            }
            if (!free_slot) {
                free_slot = table_data;
            }
            for (;;) {
                while (*++free_slot) {
                    if (free_slot > table_limit) {
                        fatal_error(1104, "\n compact failed");
                    }
                }
                block = row->entries;
                if (!block) {
                    if (verbose_level > 2) {
                        printf("\n  no table entries for conflict %u   ",
                            conflict_number);
                    }
                    *++row_offsets = free_slot - table_data;
                    break;
                }
                if (free_slot - block->token <= table_data) {
                    continue;
                }
                saved_slot = free_slot;
                free_slot -= block->token;
                fits = 1;
                for (block = row->entries; block; block = block->next) {
                    if (*(free_slot + block->token)) {
                        fits = 0;
                        break;
                    }
                }
                if (fits) {
                    *++row_offsets = free_slot - table_data;
                    for (block = row->entries; block; block = block->next) {
                        offset = free_slot + block->token;
                        production = block->production;
                        if ((production >= start_conflict)) {
                            production += total_levels;
                            terminal_only = 0;
                        }
                        if (*offset) {
                            printf("error 1140: nonzero entry = %u\n", *offset);
                        }
                        *offset = production;
                        if (offset > last_used) {
                            last_used = offset;
                        }
                    }
                    break;
                }
                free_slot = saved_slot;
            }
            previous_row = row;
        }
        if (terminal_only) {
            break;
        }
    }
    *++row_offsets = 0;
    printf("to %lu\n", (ulong)(++last_used - table_data - 1));
    return last_used;
}
static void
write_conflict_table(FILE* out_file,
    int* cursor,
    int* table,
    int* row_offsets,
    uint generate_flags)
{
    register int* block;
    uint count = 1,
        entries = 1;
    block = table;
    if (generate_flags & 0x00002000) {
        fprintf(out_file, "var Conflict = [\n\n%u", *block);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fprintf(out_file, "static slk_size_t Conflict[] = {\n\n%u", *block);
    }
    else {
        fprintf(out_file, "private static short[] Conflict = {\n\n%u", *block);
    }
    while (++block < cursor) {
        ++entries;
        if (++count > 19) {
            count = 0;
            fputs("\n", out_file);
        }
        fprintf(out_file, ",%u", *block);
    }
    fprintf(out_file, "\n%s;\n\n", array_close);
    if (generate_flags & 0x00002000) {
        fputs("var Conflict_row = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        if (entries < (1024 * 64 - 32)) {
            fputs("static slk_size_t Conflict_row[] = {0\n\n", out_file);
        }
        else {
            fputs("static int Conflict_row[] = {0\n\n", out_file);
        }
    }
    else {
        fputs("private static int[] Conflict_row = {0\n\n", out_file);
    }
    block = row_offsets;
    for (count = 1; *++block; ++count) {
        fprintf(out_file, ",%u", *block);
        if (count >= 16) {
            count = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
}
static void
output_parse_table(uint generate_flags,
    FILE* out_file)
{
    int* table_data,
        * row_offsets,
        * cursor;
    uint original_size,
        table_size2 = 0;
    row_offsets = calloc(nonterminal_count + 2, sizeof(int*));
    if (!row_offsets) {
        fatal_error(1115, "out of memory");
    }
    if (generate_flags & 0x00000001) {
        original_size = nonterminal_count * terminal_count;
        table_size2 = max2(1024 * 10, original_size / 3);
        table_data = calloc(table_size2, sizeof(int));
        if (!table_data) {
            fatal_error(1116, "out of memory");
        }
        cursor = compact_parse_table(original_size, table_data,
            table_size2, row_offsets);
        write_parse_table(out_file, cursor, table_data, row_offsets,
            generate_flags);
        if (verify_parse_table(table_data, row_offsets)) {
            printf("error 1133: table compacting failed\n");
        }
    }
    else {
        write_parse_table_plain(out_file, row_offsets, generate_flags);
    }
}
static void
output_conflict_table(uint generate_flags,
    FILE* out_file)
{
    int* table_data,
        * row_offsets,
        * cursor;
    uint original_size2,
        table_size2 = 0;
    row_offsets = calloc(conflict_count + 2, sizeof(int*));
    if (!row_offsets) {
        fatal_error(1117, "out of memory");
    }
    if (generate_flags & 0x00000001) {
        original_size2 = conflict_count * terminal_count;
        table_size2 = max2(1024 * 10, original_size2);
        table_data = calloc(table_size2, sizeof(int));
        if (!table_data) {
            fatal_error(1116, "out of memory");
        }
        cursor = compact_conflict_table(original_size2, table_data,
            table_size2, row_offsets);
        write_conflict_table(out_file, cursor, table_data, row_offsets,
            generate_flags);
        if (verify_conflict_table(table_data, row_offsets)) {
            printf("error 1134: table compacting failed\n");
        }
    }
    else {
        write_conflict_table_plain(out_file, row_offsets, generate_flags);
    }
}
void generate_parser(char* parser_name,
    char* namespace_name,
    uint generate_flags,
    uint grammar_flags)
{
    int named_actions,
        language_flag = 0x00000100;
    FILE* out_file;
    char file_name[32];
    if (generate_flags & (0x00000200)) {
        language_flag = 0x00000200;
    }
    else if (generate_flags & (0x00001000)) {
        language_flag = 0x00001000;
    }
    else if (generate_flags & (0x00000800)) {
        language_flag = 0x00000800;
    }
    else if (generate_flags & (0x00000400)) {
        language_flag = 0x00000400;
    }
    else if (generate_flags & (0x00002000)) {
        language_flag = 0x00002000;
        array_close = "]";
    }
    parser_name[3] = '\0';
    named_actions = actions_are_named(grammar_flags & 0x00000010);
    strcpy(file_name, parser_name);
    switch (language_flag) {
    case 0x00000200:
        strcat(file_name, "Parse.cpp");
        break;
    case 0x00000100:
    case 0x00001000:
        strcat(file_name, "Parse.c");
        break;
    case 0x00000800:
        strcat(file_name, "Parser.cs");
        break;
    case 0x00000400:
        strcat(file_name, "Parser.java");
        break;
    case 0x00002000:
        strcat(file_name, "Parser.js");
        break;
    }
    out_file = fopen(file_name, "w");
    if (!out_file) {
        perror(file_name);
        return;
    }
    fprintf(out_file, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    if (generate_flags & 0x00000800) {
        fprintf(out_file, "using Dsl.Common;\n\n");
    }
    switch (language_flag) {
    case 0x00000200:
    case 0x00000100:
    case 0x00001000:
        fprintf(out_file, "#include \"%sParse.h\"\n\n", parser_name);
        break;
    }
    if (namespace_name) {
        switch (language_flag) {
        case 0x00000200:
        case 0x00000800:
            fprintf(out_file, "namespace %s {\n\n", namespace_name);
            break;
        case 0x00000400:
            fprintf(out_file, "package %s;\n\n", namespace_name);
            break;
        }
    }
    switch (language_flag) {
    case 0x00000800:
        fprintf(out_file, "class %sParser {\n\n", parser_name);
        break;
    case 0x00000400:
        fprintf(out_file, "public class %sParser {\n\n", parser_name);
        break;
    }
    write_productions(out_file, generate_flags);
    if (generate_flags & 0x00000004) {
        output_parse_table(generate_flags, out_file);
    }
    else if (generate_flags & 0x00000008) {
        write_lr_tables(parser_name, namespace_name, generate_flags, out_file);
    }
    output_conflict_table(generate_flags, out_file);
    switch (language_flag) {
    case 0x00000200:
    case 0x00000100:
    case 0x00001000:
        generate_c_parser(parser_name, namespace_name, named_actions,
            generate_flags, out_file, (grammar_flags & 0x00000010));
        break;
    case 0x00000800:
    case 0x00000400:
    case 0x00002000:
        generate_managed_parser(parser_name, namespace_name, named_actions,
            generate_flags, out_file, (grammar_flags & 0x00000010));
        break;
    }
    if (namespace_name) {
        switch (language_flag) {
        case 0x00000200:
        case 0x00000800:
            fprintf(out_file, "\n\n}\n");
            break;
        }
    }
    fclose(out_file);
    generate_string_file(parser_name, namespace_name, generate_flags);
}
static char get_symbol_name_decl[] =
"const char *xxxGetSymbolName ( unsigned int   symbol )";
static char get_symbol_name_body[] =
"{ if ( symbol >= START_ACTION  &&  symbol < END_ACTION ) {\n"
"      return ( GET_ACTION_NAME (symbol) );\n"
"  } else if ( symbol >= START_SYMBOL ) {\n"
"      return ( GET_NONTERMINAL_NAME (symbol) );\n"
"  } else if ( symbol > 0 ) {\n"
"      return ( GET_TERMINAL_NAME (symbol) );\n"
"  } else {\n"
"      return ( \"not a symbol\" );\n"
"  }\n"
"}\n";
static char get_production_name_decl[] =
"const char *xxxGetProductionName ( unsigned int  production_number )";
static char get_production_name_body[] =
"{\n"
"  return ( GET_PRODUCTION_NAME (production_number) );\n"
"}\n";
static char* c_string_decl = "static const char *",
* cpp_string_decl = "static const char *",
* cs_string_decl = "private static string[]",
* java_string_decl = "private static String[]",
* js_var_decl = "var",
* string_decl = "not assigned";
static char* array_suffix = "",
* array_begin = "={",
* array_end = "}";
static void
write_nonterminal_names(FILE* out_file)
{
    register Symbol** nonterminal = nonterminals;
    fprintf(out_file, "%s Nonterminal_name%s %s\"0\"\n\n", string_decl, array_suffix, array_begin);
    while (*++nonterminal)
        fprintf(out_file, ",\"%s\"\n", (*nonterminal)->name);
    fprintf(out_file, "%s;\n\n", array_end);
}
static void
write_terminal_names(FILE* out_file)
{
    register Symbol** lookahead_tokens = terminals;
    fprintf(out_file, "%s Terminal_name%s %s\"0\"\n\n", string_decl, array_suffix, array_begin);
    while (*++lookahead_tokens)
        fprintf(out_file, ",\"%s\"\n", (*lookahead_tokens)->name);
    fprintf(out_file, "%s;\n\n", array_end);
}
static void
write_action_names(FILE* out_file)
{
    register Symbol** action_value = actions;
    fprintf(out_file, "%s Action_name%s %s\"0\"\n\n", string_decl, array_suffix, array_begin);
    while (*++action_value)
        fprintf(out_file, ",\"%s\"\n", (*action_value)->name);
    fprintf(out_file, "%s;\n\n", array_end);
}
static void
write_production_names(FILE* out_file)
{
    register Symbol*** block = productions,
        ** symbol;
    fprintf(out_file, "%s Production_name%s %s\"0\"\n\n", string_decl, array_suffix, array_begin);
    while (*++block) {
        symbol = *block;
        fprintf(out_file, ",\"%s -->", (*symbol)->name);
        while (*++symbol) {
            fprintf(out_file, " %s", (*symbol)->name);
        }
        fputs("\"\n", out_file);
    }
    fprintf(out_file, "%s;\n\n", array_end);
}
static void
write_string_header(char* parser_name,
    char* namespace_name,
    uint generate_flags)
{
    FILE* out_stream;
    uchar file_name[16];
    sprintf(file_name, "%sString.h", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1101, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "#ifndef _%sSTRING_H\n#define _%sSTRING_H\n\n",
        parser_name, parser_name);
    if (generate_flags & 0x00000100) {
        fprintf(out_stream, "#ifdef __cplusplus\n"
            "extern \"C\" {\n"
            "#endif\n\n");
    }
    else if (generate_flags & 0x00000200) {
        if (namespace_name) {
            fprintf(out_stream, "namespace %s {\n\n", namespace_name);
        }
    }
    fprintf(out_stream, "%s;\n", get_symbol_name_decl);
    fprintf(out_stream, "%s;\n\n", get_production_name_decl);
    if (generate_flags & 0x00000100) {
        fprintf(out_stream, "#ifdef __cplusplus\n"
            "}\n"
            "#endif\n");
    }
    else if (generate_flags & 0x00000200) {
        if (namespace_name) {
            fprintf(out_stream, "\n\n}\n");
        }
    }
    fprintf(out_stream, "\n#endif\n");
    fclose(out_stream);
}
static void
write_c_string_file(char* parser_name,
    char* namespace_name,
    FILE* out_file,
    uint generate_flags)
{
    char* template_cursor;
    for (template_cursor = get_symbol_name_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = get_symbol_name_body; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = get_production_name_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    write_string_header(parser_name, namespace_name, generate_flags);
    if (generate_flags & 0x00000010) {
        write_nonterminal_names(out_file);
    }
    if (generate_flags & 0x00000020) {
        write_terminal_names(out_file);
    }
    if (generate_flags & 0x00000040) {
        if (actions[1]) {
            write_action_names(out_file);
        }
        else {
            generate_flags &= ~0x00000040;
        }
    }
    if (generate_flags & 0x00000080) {
        write_production_names(out_file);
    }
    fprintf(out_file, "#define START_SYMBOL %d\n", start_symbol_number);
    fprintf(out_file, "#define START_ACTION %d\n", start_action);
    fprintf(out_file, "#define END_ACTION %d\n", start_action + action_count);
    if (generate_flags & 0x00000010) {
        fprintf(out_file, "#define GET_NONTERMINAL_NAME(symbol) "
            "(Nonterminal_name [symbol - %d])\n",
            start_symbol_number - 1);
    }
    else {
        fprintf(out_file, "#define GET_NONTERMINAL_NAME(symbol) \"no table\"\n");
    }
    if (generate_flags & 0x00000020) {
        fprintf(out_file, "#define GET_TERMINAL_NAME(symbol) "
            "(Terminal_name [symbol])\n");
    }
    else {
        fprintf(out_file, "#define GET_TERMINAL_NAME(symbol) \"no table\"\n");
    }
    if (generate_flags & 0x00000040) {
        fprintf(out_file, "#define GET_ACTION_NAME(symbol) "
            "(Action_name [symbol-(START_ACTION-1)])\n");
    }
    else {
        fprintf(out_file, "#define GET_ACTION_NAME(symbol) \"_action_\"\n");
    }
    if (generate_flags & 0x00000080) {
        fprintf(out_file, "#define GET_PRODUCTION_NAME(number) "
            "(Production_name [number])\n\n");
    }
    else {
        fprintf(out_file, "#define GET_PRODUCTION_NAME(number) \"no table\"\n\n");
    }
    fprintf(out_file, "%s\n", get_symbol_name_decl);
    fprintf(out_file, "%s\n", get_symbol_name_body);
    fprintf(out_file, "%s\n", get_production_name_decl);
    fprintf(out_file, "%s\n", get_production_name_body);
}
static void
write_managed_string_file(char* parser_name,
    char* namespace_name,
    FILE* out_file,
    uint generate_flags)
{
    if (generate_flags & 0x00000010) {
        write_nonterminal_names(out_file);
    }
    if (generate_flags & 0x00000020) {
        write_terminal_names(out_file);
    }
    if (generate_flags & 0x00000040) {
        if (actions[1]) {
            write_action_names(out_file);
        }
        else {
            generate_flags &= ~0x00000040;
        }
    }
    if (generate_flags & 0x00000080) {
        write_production_names(out_file);
    }
    if (generate_flags & 0x00000400) {
        fprintf(out_file, "private static final short   START_SYMBOL = %d;\n",
            start_symbol_number);
        fprintf(out_file, "private static final short   START_ACTION = %d;\n",
            start_action);
        fprintf(out_file, "private static final short   END_ACTION = %d;\n\n",
            start_action + action_count);
        fprintf(out_file, "public static String  GetSymbolName ( short symbol )\n");
    }
    else if (generate_flags & 0x00000800) {
        fprintf(out_file, "private const short   START_SYMBOL = %d;\n",
            start_symbol_number);
        fprintf(out_file, "private const short   START_ACTION = %d;\n",
            start_action);
        fprintf(out_file, "private const short   END_ACTION = %d;\n\n",
            start_action + action_count);
        fprintf(out_file, "public static string  GetSymbolName ( short symbol )\n");
    }
    fputs("{\n  if ( symbol >= START_ACTION && symbol < END_ACTION ) {\n", out_file);
    if (generate_flags & 0x00000040) {
        fprintf(out_file, "      return ( %s );\n",
            "Action_name [symbol - (START_ACTION-1)]");
    }
    else {
        fprintf(out_file, "      return ( %s );\n", "\"_action_\"");
    }
    fputs("  } else if ( symbol >= START_SYMBOL ) {\n", out_file);
    if (generate_flags & 0x00000010) {
        fprintf(out_file, "      return ( %s );\n",
            "Nonterminal_name [symbol - (START_SYMBOL-1)]");
    }
    else {
        fprintf(out_file, "      return ( %s );\n", "\"no table\"");
    }
    fputs("  } else if ( symbol > 0 ) {\n", out_file);
    if (generate_flags & 0x00000020) {
        fprintf(out_file, "      return ( Terminal_name [ symbol ] );\n");
    }
    else {
        fprintf(out_file, "      return ( %s );\n", "\"no table\"");
    }
    fputs("  }\n", out_file);
    fputs("  return ( \"not a symbol\" );\n", out_file);
    fputs("}\n\n", out_file);
    if (generate_flags & 0x00000400) {
        fputs("public static String  GetProductionName ( short production_number )\n", out_file);
    }
    else if (generate_flags & 0x00000800) {
        fputs("public static string  GetProductionName ( short production_number )\n", out_file);
    }
    if (generate_flags & 0x00000080) {
        fprintf(out_file, "{\n  return ( %s );\n}\n",
            "Production_name [production_number]");
    }
    else {
        fprintf(out_file, "{\n  return ( %s );\n}\n\n", "\"no table\"");
    }
    fprintf(out_file, "\n\n};\n");
}
static void
write_js_string_file(char* parser_name,
    char* namespace_name,
    FILE* out_file,
    uint generate_flags)
{
    if (generate_flags & 0x00000010) {
        write_nonterminal_names(out_file);
    }
    if (generate_flags & 0x00000020) {
        write_terminal_names(out_file);
    }
    if (generate_flags & 0x00000040) {
        if (actions[1]) {
            write_action_names(out_file);
        }
        else {
            generate_flags &= ~0x00000040;
        }
    }
    if (generate_flags & 0x00000080) {
        write_production_names(out_file);
    }
    fprintf(out_file, "function  GetSymbolName ( symbol )\n");
    fputs("{\n  if ( symbol >= START_ACTION && symbol < END_ACTION ) {\n", out_file);
    if (generate_flags & 0x00000040) {
        fprintf(out_file, "      return ( %s );\n",
            "Action_name [symbol - (START_ACTION-1)]");
    }
    else {
        fprintf(out_file, "      return ( %s );\n", "\"_action_\"");
    }
    fputs("  } else if ( symbol >= START_SYMBOL ) {\n", out_file);
    if (generate_flags & 0x00000010) {
        fprintf(out_file, "      return ( %s );\n",
            "Nonterminal_name [symbol - (START_SYMBOL-1)]");
    }
    else {
        fprintf(out_file, "      return ( %s );\n", "\"no table\"");
    }
    fputs("  } else if ( symbol > 0 ) {\n", out_file);
    if (generate_flags & 0x00000020) {
        fprintf(out_file, "      return ( Terminal_name [ symbol ] );\n");
    }
    else {
        fprintf(out_file, "      return ( %s );\n", "\"no table\"");
    }
    fputs("  }\n", out_file);
    fputs("  return ( \"not a symbol\" );\n", out_file);
    fputs("}\n\n", out_file);
    fputs("function  GetProductionName ( production_number )\n", out_file);
    if (generate_flags & 0x00000080) {
        fprintf(out_file, "{\n  return ( %s );\n}\n",
            "Production_name [production_number]");
    }
    else {
        fprintf(out_file, "{\n  return ( %s );\n}\n\n", "\"no table\"");
    }
}
void generate_string_file(char* parser_name,
    char* namespace_name,
    uint generate_flags)
{
    int language_flag = 0x00000100;
    FILE* out_file;
    char file_name[32];
    if (generate_flags & (0x00000100 | 0x00001000)) {
        language_flag = 0x00000100;
        string_decl = c_string_decl;
        array_suffix = "[]";
    }
    else if (generate_flags & (0x00000200)) {
        language_flag = 0x00000200;
        string_decl = cpp_string_decl;
        array_suffix = "[]";
    }
    else if (generate_flags & (0x00000800)) {
        language_flag = 0x00000800;
        string_decl = cs_string_decl;
    }
    else if (generate_flags & (0x00000400)) {
        language_flag = 0x00000400;
        string_decl = java_string_decl;
    }
    else if (generate_flags & (0x00002000)) {
        language_flag = 0x00002000;
        string_decl = js_var_decl;
        array_begin = "=[";
        array_end = "]";
    }
    parser_name[3] = '\0';
    strcpy(file_name, parser_name);
    switch (language_flag) {
    case 0x00000200:
        strcat(file_name, "String.cpp");
        break;
    case 0x00000100:
        strcat(file_name, "String.c");
        break;
    case 0x00000800:
        strcat(file_name, "String.cs");
        break;
    case 0x00000400:
        strcat(file_name, "String.java");
        break;
    case 0x00002000:
        strcat(file_name, "String.js");
        break;
    }
    out_file = fopen(file_name, "w");
    if (!out_file) {
        perror(file_name);
        return;
    }
    fprintf(out_file, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    switch (language_flag) {
    case 0x00000200:
    case 0x00000100:
        fprintf(out_file, "#include \"%sString.h\"\n\n", parser_name);
        break;
    }
    if (namespace_name) {
        switch (language_flag) {
        case 0x00000200:
        case 0x00000800:
            fprintf(out_file, "namespace %s {\n\n", namespace_name);
            break;
        case 0x00000400:
            fprintf(out_file, "package %s;\n\n", namespace_name);
            break;
        }
    }
    switch (language_flag) {
    case 0x00000800:
        fprintf(out_file, "class %sString {\n\n", parser_name);
        break;
    case 0x00000400:
        fprintf(out_file, "public class %sString {\n\n", parser_name);
        break;
    }
    switch (language_flag) {
    case 0x00000200:
    case 0x00000100:
        write_c_string_file(parser_name, namespace_name, out_file,
            generate_flags);
        break;
    case 0x00000800:
    case 0x00000400:
        write_managed_string_file(parser_name, namespace_name, out_file,
            generate_flags);
        break;
    case 0x00002000:
        write_js_string_file(parser_name, namespace_name, out_file, generate_flags);
        break;
    }
    if (namespace_name) {
        switch (language_flag) {
        case 0x00000200:
        case 0x00000800:
            fprintf(out_file, "\n\n}\n");
            break;
        }
    }
    fclose(out_file);
}
static char*
ascii_names[] = {
    "NUL",
    "SOH",
    "STX",
    "ETX",
    "EOT",
    "ENQ",
    "ACK",
    "BEL",
    "BS",
    "HT",
    "LF",
    "VT",
    "FF",
    "CR",
    "SO",
    "SI",
    "DLE",
    "DC1",
    "DC2",
    "DC3",
    "DC4",
    "NAK",
    "SYN",
    "ETB",
    "CAN",
    "EM",
    "SUB",
    "ESC",
    "FS",
    "GS",
    "RS",
    "US",
    "SPACE",
    "NOT_",
    "QUOTE_",
    "POUND_",
    "DOLLAR_",
    "PERCENT_",
    "AND_",
    "SQUOTE_",
    "LPAREN_",
    "RPAREN_",
    "STAR_",
    "PLUS_",
    "COMMA_",
    "_",
    "DOT_",
    "SLASH_",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "COLON_",
    "SEMI_",
    "LESS_",
    "EQUAL_",
    "GREATER_",
    "QMARK_",
    "AT",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "LBRACK_",
    "BSLASH_",
    "RBRACK_",
    "CARET_",
    "_",
    "TICK_",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "LBRACE_",
    "OR_",
    "RBRACE_",
    "TILDE_",
    "HOUSE",
    0 };
static uchar
last_char(register uchar* str)
{
    if (!*str) {
        return (*str);
    }
    while (*str) {
        ++str;
    }
    return (*--str);
}
char*
token_define_name(char* prefix,
    char* suffix,
    Symbol** symbol,
    int make_unique)
{
    register uchar* name_cursor = (*symbol)->name;
    register Symbol* existing_symbol;
    int minus_seen = 0;
    static uchar define_name[1024 * 2];
    strcpy(define_name, prefix);
    if (((*name_cursor >= '0' && *name_cursor <= '9'))) {
        if (!*define_name) {
            *define_name = '_';
        }
    }
    else {
        while (*name_cursor == '-') {
            strcat(define_name, "MINUS_");
            ++name_cursor;
            minus_seen = 1;
        }
    }
    if ((*symbol)->prefixed_name) {
        name_cursor += 2;
    }
    for (; *name_cursor; ++name_cursor) {
        if (*name_cursor == '_' && minus_seen) {
            continue;
        }
        strcat(define_name, ascii_names[*name_cursor]);
        minus_seen = (last_char(define_name) == '_');
    }
    if (last_char(define_name) != '_') {
        strcat(define_name, "_");
    }
    strcat(define_name, suffix);
    if (make_unique) {
        existing_symbol = find_symbol(define_name);
        if (!existing_symbol) {
            new_symbol(11, 0, define_name);
        }
        else if (existing_symbol->type == 11) {
            while (existing_symbol) {
                strcat(define_name, "2_");
                existing_symbol = find_symbol(define_name);
                if (!existing_symbol) {
                    new_symbol(11, 0, define_name);
                    break;
                }
                else if (existing_symbol->type != 11) {
                    break;
                }
            }
        }
    }
    return define_name;
}
static char* grammar_production_texts[] =
{
    "\n",
    "productions -->  production productions\n",
    "productions -->  {5} \n",
    "production  -->  NONTERMINAL {1} : symbols {4} alternates ;\n",
    "production  -->  TERMINAL {1} : symbols {4} alternates ;\n",
    "alternates  -->  | {2} symbols {4} alternates\n",
    "alternates  -->\n",
    "symbols     -->  NONTERMINAL {3} symbols\n",
    "symbols     -->     TERMINAL {3} symbols\n",
    "symbols     -->     ACTION   {3} symbols\n",
    "symbols     -->\n" };
static int grammar_parse_table[][8] =
{
    {0},
    {0, 1, 1, 0, 0, 0, 0, 2},
    {0, 3, 4},
    {0, 0, 0, 0, 0, 5, 6},
    {0, 7, 8, 9, 0, 10, 10} };
static int grammar_production_data[] =
{
    0,
    0, (1024 + 1), (1024 + 1) + 1,
    0, -5,
    0, 6, (1024 + 1) + 2, -4, (1024 + 1) + 3, 4, -1, 1,
    0, 6, (1024 + 1) + 2, -4, (1024 + 1) + 3, 4, -1, 2,
    0, (1024 + 1) + 2, -4, (1024 + 1) + 3, -2, 5,
    0,
    0, (1024 + 1) + 3, -3, 1,
    0, (1024 + 1) + 3, -3, 2,
    0, (1024 + 1) + 3, -3, 3,
    0,
    0 };
static int* grammar_production_ptrs[] =
{
    0, grammar_production_data + 1, grammar_production_data + 4, grammar_production_data + 6, grammar_production_data + 14, grammar_production_data + 22, grammar_production_data + 28, grammar_production_data + 29, grammar_production_data + 33, grammar_production_data + 37, grammar_production_data + 41, 0 };
static char* token_type_names[] =
{
    "TYPE_NOT_ASSIGNED",
    "NONTERMINAL",
    "TERMINAL",
    "ACTION",
    "LHS_SEPARATOR",
    "NEW_ALTERNATE",
    "END_PRODUCTION",
    "END_PARSE_INPUT" };
static int recovery_token_sets[][4] =
{
    {0},
    {0, 7},
    {0, 1, 2, 7},
    {0, 6},
    {0, 5, 6} };
static void
errors(int missing,
    int symbol,
    int grammar_text)
{
    fprintf(stdout, "%u: %s: ", line_number(), cur_token_text());
    if (missing) {
        fprintf(stdout, "missing %s\n", token_type_names[symbol]);
    }
    else if (!symbol) {
        fputs("input remaining\n", stdout);
    }
    else if (grammar_text == 4) {
        fputs("missing production terminator \n", stdout);
    }
    else {
        fputs("syntax error\n", stdout);
        fprintf(stdout, "  input  = %s\n", token_type_names[grammar_text]);
        fprintf(stdout, "  symbol = %d\n", symbol);
    }
    note_error();
}
static void
grammar_action(int number,
    Symbol* action_symbol)
{
    static Symbol* lhs,
        ** block;
    static uint production_length;
    static Symbol* production_buffer[(1024 * 4) + 4];
    switch (number) {
    case 1:
        lhs = action_symbol;
        if (lhs->type == 2) {
            terminal_to_nonterminal(lhs);
        }
    case 2:
        production_length = 0;
        block = production_buffer;
        *block = lhs;
        break;
    case 3:
        if (++production_length > (1024 * 4)) {
            *block = NULL;
            print_production(NULL, production_buffer);
            fatal_error(1801, "production too long");
        }
        *++block = action_symbol;
        break;
    case 4:
        *++block = NULL;
        block = production_buffer;
        while (*++block) {
            if ((*block)->type != 3) {
                if (*block == lhs) {
                    note_left_recursion();
                    lhs->direct_left_recursive = 1;
                }
                else {
                    break;
                }
            }
        }
        add_production_copy(production_buffer);
        break;
    case 5:
        initialize_grammar();
        break;
    }
}
static uint
contains(register int grammar_text,
    int* follows_node)
{
    while (*++follows_node)
        if (grammar_text == *follows_node)
            return (1);
    return (0);
}
void parse_grammar(int (*next_token)(void),
    int display)
{
    register int* stack_top,
        * production_cursor;
    int symbol,
        grammar_text,
        block,
        * follows_node;
    Symbol* last_node;
    int parse_stack[127 + 1];
    stack_top = parse_stack + 127;
    *stack_top = 0;
    if (--stack_top > parse_stack)
        *stack_top = (1024 + 1);
    else
        fatal_error(1802, "parse stack overflow");
    grammar_text = next_token();
    if (display) {
        fputs("\n\n\t\tPARSE DERIVATION\n\n", stdout);
    }
    for (symbol = (*stack_top++); symbol; symbol = (*stack_top++)) {
        if (symbol >= (1024 + 1)) {
            block = grammar_parse_table[symbol - ((1024 + 1) - 1)][grammar_text];
            if (block) {
                if (display) {
                    fputs(grammar_production_texts[block], stdout);
                }
                production_cursor = grammar_production_ptrs[block];
                while (*++production_cursor) {
                    if (--stack_top > parse_stack)
                        *stack_top = *production_cursor;
                    else
                        fatal_error(1802, "parse stack overflow");
                }
            }
            else {
                errors(0, symbol, grammar_text);
                follows_node = recovery_token_sets[symbol - ((1024 + 1) - 1)];
                if (!contains(grammar_text, follows_node))
                    while ((grammar_text = next_token()) != 7)
                        if (contains(grammar_text, follows_node))
                            break;
            }
        }
        else if (symbol > 0) {
            if (symbol == grammar_text) {
                last_node = cur_symbol;
                grammar_text = next_token();
            }
            else {
                errors(1, symbol, grammar_text);
            }
        }
        else {
            grammar_action(-symbol, last_node);
        }
    }
    if (grammar_text != 7)
        errors(0, symbol, grammar_text);
}
char*
symbol_type_name(uint type_index)
{
    return token_type_names[type_index];
}
Symbol* cur_symbol;
enum
{
    SCAN_START,
    SCAN_PRODUCTION_END,
    SCAN_RHS_COMPLETE,
    SCAN_LHS,
    SCAN_RHS,
    SCAN_EPSILON
};
static uint ebnf_flag = 0,
strip_actions = 0,
double_underscore_actions = 1,
scanner_state = SCAN_START;
static int scanner_line_number = 1;
static char* token_start,
* input_cursor,
token_text_buffer[32];
static int
is_action_name(char* name)
{
    int is_action = 0;
    if (double_underscore_actions) {
        is_action = !strncmp(name, "__", 2);
    }
    if (!is_action) {
        is_action = !strncmp(name, "_action_", 8);
    }
    return is_action;
}
static void
scanner_error(char* str,
    char error_char)
{
    printf("%d:  %s %c\n", scanner_line_number, str, error_char);
    note_error();
}
static int
// ================ SLK grammar scanner ================
next_token(void)
{
    register char* token_start = input_cursor,
        * cursor = input_cursor;
    int escaped = 0,
        number = 0,
        type = 0;
    char saved_char,
        * line_start = input_cursor,
        * newline_pos = cursor,
        * arg = "not_assigned";
    for (;;) {
        token_start = cursor;
        while ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
            if (*cursor == '\n') {
                newline_pos = cursor;
                ++scanner_line_number;
                ++cursor;
                while ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                    if (*cursor == '\n') {
                        ++scanner_line_number;
                        switch (scanner_state) {
                        case SCAN_START:
                        case SCAN_LHS:
                        case SCAN_RHS:
                            break;
                        case SCAN_EPSILON:;
                            scanner_state = SCAN_RHS_COMPLETE;
                            cursor = newline_pos;
                            input_cursor = cursor;
                            return (type = 5);
                        case SCAN_PRODUCTION_END:
                        case SCAN_RHS_COMPLETE:;
                            scanner_state = SCAN_START;
                            input_cursor = ++cursor;
                            return (type = 6);
                        }
                    }
                    ++cursor;
                }
                switch (scanner_state) {
                case SCAN_START:
                case SCAN_LHS:
                case SCAN_PRODUCTION_END:
                case SCAN_RHS:
                    break;
                case SCAN_RHS_COMPLETE:
                case SCAN_EPSILON:
                    scanner_state = SCAN_PRODUCTION_END;
                    break;
                }
            }
            if ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                ++cursor;
            }
            token_start = cursor;
            line_start = cursor;
        }
        if (*cursor == '/') {
            if (*(cursor + 1) == '/') {
                while (*++cursor) {
                    if (*cursor == '\n') {
                        break;
                    }
                }
                continue;
            }
            else if (*(cursor + 1) == '*') {
                cursor += 1;
                while (*++cursor) {
                    if (*cursor == '*' && *(cursor + 1) == '/') {
                        cursor += 2;
                        break;
                    }
                    else if (*cursor == '\n') {
                        ++scanner_line_number;
                    }
                }
                continue;
            }
        }
        while (*cursor && !(*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
            ++cursor;
        }
        switch (*token_start) {
        case '\0':
            if (scanner_state != SCAN_START) {
                type = 6;
                scanner_state = SCAN_START;
            }
            else {
                token_start = "END_OF_SLK_INPUT";
                cur_symbol = find_symbol("END_OF_SLK_INPUT");
                if (!cur_symbol) {
                    cur_symbol = new_symbol(2, 0,
                        "END_OF_SLK_INPUT");
                    register_symbol(cur_symbol);
                }
                type = 7;
                scanner_state = SCAN_START;
            }
            break;
        case '\\':
            cursor = ++token_start;
            switch (*cursor) {
            case '\r':
                if (*++cursor == '\n') {
                    ++cursor;
                    ++scanner_line_number;
                }
                continue;
            case '\n':
                if (*++cursor == '\r') {
                    ++cursor;
                }
                ++scanner_line_number;
                continue;
            case 'a':
                number = '\a';
                token_start = "\\a";
                break;
            case 'b':
                number = '\b';
                token_start = "\\b";
                break;
            case 'f':
                number = '\f';
                token_start = "\\f";
                break;
            case 't':
                number = '\t';
                token_start = "\\t";
                break;
            case 'v':
                number = '\v';
                token_start = "\\v";
                break;
            case 'n':
                number = '\n';
                token_start = "\\n";
                break;
            case 'r':
                number = '\r';
                token_start = "\\r";
                break;
            case '\\':
                number = '\\';
                token_start = "\\\\";
                break;
            case '\?':
                number = '\?';
                token_start = "\\\?";
                break;
            case '\'':
                number = '\'';
                token_start = "\\\'";
                break;
            case '\"':
                number = '\"';
                token_start = "\\\"";
                break;
            case 'x':
                *--token_start = '0';
                number = (int)strtol(token_start, NULL, 0);
                *token_start = '\\';
                cursor += 2;
                break;
            case '/':
                if (*(cursor + 1) == '/') {
                    ++cursor;
                    number = 258;
                    token_start = "//";
                    escaped = 1;
                }
                else if (*(cursor + 1) == '*') {
                    ++cursor;
                    number = 259;
                    token_start = "/*";
                    escaped = 1;
                }
                else {
                    number = '/';
                }
                break;
            case '*':
                if (*(cursor + 1) == '/') {
                    ++cursor;
                    number = 260;
                    token_start = "*/";
                    escaped = 1;
                }
                else {
                    number = '*';
                }
                break;
            case '[':
                number = '[';
                token_start = "[";
                escaped = 1;
                break;
            case ']':
                number = ']';
                token_start = "]";
                escaped = 1;
                break;
            case '{':
                number = '{';
                token_start = "{";
                escaped = 1;
                break;
            case '}':
                if (*(cursor + 1) == '+') {
                    ++cursor;
                    number = 257;
                    token_start = "}+";
                    escaped = 1;
                }
                else {
                    number = '}';
                    token_start = "}";
                    escaped = 1;
                }
                break;
            default:
                number = *cursor;
            }
            type = 2;
            ++cursor;
            break;
        case ':':
        case '-':
        case '=':
            if (scanner_state == SCAN_LHS) {
                type = 4;
                scanner_state = SCAN_RHS;
                switch (*(token_start + 1)) {
                case '?':
                    if (!cur_symbol->conditional) {
                        cur_symbol->conditional = 1;
                        ++conditional_count;
                    }
                    break;
                case '!':
                    if (!cur_symbol->ignore_conflicts) {
                        cur_symbol->ignore_conflicts = 1;
                        ++ignored_conflict_count;
                    }
                    break;
                }
                break;
            }
        default:
            if (cursor <= token_start + 2) {
                switch (*token_start) {
                case '[':
                    if (cursor == token_start + 1) {
                        number = '[';
                        if (ebnf_flag) {
                            number = -1;
                            token_start = "\\[";
                        }
                    }
                    break;
                case ']':
                    if (cursor == token_start + 1) {
                        number = ']';
                        if (ebnf_flag) {
                            number = -2;
                            token_start = "\\]";
                        }
                    }
                    break;
                case '{':
                    if (cursor == token_start + 1) {
                        number = '{';
                        if (ebnf_flag) {
                            number = -3;
                            token_start = "\\{";
                        }
                    }
                    break;
                case '}':
                    if (*(token_start + 1) == '+') {
                        number = 257;
                        if (ebnf_flag) {
                            number = -5;
                            token_start = "\\}+";
                        }
                    }
                    else {
                        if (cursor == token_start + 1) {
                            number = '}';
                            if (ebnf_flag) {
                                number = -4;
                                token_start = "\\}";
                            }
                        }
                    }
                    break;
                default:
                    number = 0;
                }
                if (number) {
                    type = 2;
                    saved_char = *cursor;
                    *cursor = '\0';
                    if (!(cur_symbol = find_symbol(token_start))) {
                        cur_symbol = new_symbol(2, number, token_start);
                        if (!ebnf_flag) {
                            register_symbol(cur_symbol);
                        }
                    }
                    *cursor = saved_char;
                    if (ebnf_flag) {
                        cur_symbol->ebnf_token = 1;
                    }
                    else {
                        cur_symbol->escaped = 1;
                    }
                    break;
                }
            }
            if (!strncmp(token_start, "_epsilon_", 9)) {
                ;
                if (scanner_state != SCAN_RHS_COMPLETE) {
                    scanner_state = SCAN_EPSILON;
                }
                else {
                    scanner_state = SCAN_RHS_COMPLETE;
                }
                continue;
            }
            if (is_action_name(token_start)) {
                type = 3;
                number = atoi(token_start + action_prefix_len(token_start));
                break;
            }
            if (scanner_state == SCAN_START) {
                scanner_state = SCAN_LHS;
                type = 1;
                arg = (cursor - 1);
                switch (*arg) {
                case '?':
                case '!':
                    --arg;
                    break;
                }
                if (*arg == ':') {
                    cursor = arg;
                }
            }
            else {
                type = 2;
            }
            if (cursor == token_start + 1) {
                if (type == 2) {
                    number = *token_start;
                }
            }
            else if (cursor == token_start + 2) {
                if (!strncmp(token_start, "*/", 2)) {
                    scanner_error("extra '*/'", ' ');
                    token_start = cursor;
                    line_start = cursor;
                    continue;
                }
            }
        }
        input_cursor = cursor;
        token_start = token_start;
        switch (type) {
        case 3:
        case 2:
        case 1:
            saved_char = *cursor;
            *cursor = '\0';
            cur_symbol = find_symbol(token_start);
            if (!cur_symbol) {
                cur_symbol = new_symbol(type, number, token_start);
                register_symbol(cur_symbol);
            }
            *cursor = saved_char;
            if (escaped) {
                cur_symbol->escaped = 1;
                if (number > 255) {
                    cur_symbol->number = 0;
                }
            }
        case 7:
        case 0:
            switch (scanner_state) {
            case SCAN_START:;
                scanner_state = SCAN_LHS;
                break;
            case SCAN_PRODUCTION_END:
            case SCAN_EPSILON:;
                type = 5;
                scanner_state = SCAN_RHS_COMPLETE;
                input_cursor = line_start;
                break;
            case SCAN_RHS:;
                scanner_state = SCAN_RHS_COMPLETE;
                break;
            default:;
            }
            break;
        default:;
        }
        return type;
    }
}
// ================ YACC grammar scanner ================
static int
yacc_next_token(void)
{
    register char* token_start,
        * cursor;
    int action_value,
        number = 0,
        type = 0;
    char saved_char;
    char name_end[64];
    cursor = input_cursor;
    for (;;) {
        token_start = cursor;
        token_start = token_start;
        while ((*token_start == ' ' || *token_start == '\n' || *token_start == '\r' || *token_start == '\t' || *token_start == '\v' || *token_start == '\f')) {
            if (*token_start == '\n') {
                ++scanner_line_number;
            }
            cursor = ++token_start;
        }
        if (*cursor == '/') {
            if (*(cursor + 1) == '/') {
                while (*++cursor) {
                    if (*cursor == '\n') {
                        break;
                    }
                }
                continue;
            }
            else if (*(cursor + 1) == '*') {
                cursor += 2;
                while (*++cursor) {
                    if (*cursor == '*' && *(cursor + 1) == '/') {
                        cursor += 2;
                        break;
                    }
                    else if (*cursor == '\n') {
                        ++scanner_line_number;
                    }
                }
                continue;
            }
        }
        if ((((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9'))) || *cursor == '_') {
            do
                ++cursor;
            while ((((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9'))) || *cursor == '_');
            type = 2;
            input_cursor = cursor;
            while ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                ++cursor;
            }
            if (*cursor == ':') {
                type = 1;
            }
            cursor = input_cursor;
            saved_char = *cursor;
            *cursor = '\0';
            if (!(cur_symbol = find_symbol(token_start))) {
                cur_symbol = new_symbol(type, 0, token_start);
                register_symbol(cur_symbol);
            }
            *cursor = saved_char;
            input_cursor = cursor;
            return cur_symbol->type;
        }
        switch (*cursor) {
        case '\0':
        eof_label:
            cur_symbol = find_symbol("END_OF_SLK_INPUT");
            if (!cur_symbol) {
                cur_symbol = new_symbol(2, 0,
                    "END_OF_SLK_INPUT");
                register_symbol(cur_symbol);
            }
            input_cursor = cursor;
            return 7;
        case '\n':
            ++scanner_line_number;
            ++cursor;
            break;
        case '{':
            cursor = ++token_start;
            while ((*token_start == ' ' || *token_start == '\n' || *token_start == '\r' || *token_start == '\t' || *token_start == '\v' || *token_start == '\f')) {
                cursor = ++token_start;
            }
            if (strip_actions) {
                int brace_depth = 1;
                while (brace_depth > 0) {
                    if (*cursor == '}') {
                        --brace_depth;
                        ++cursor;
                    }
                    else if (*cursor == '{') {
                        ++brace_depth;
                        ++cursor;
                    }
                    else if (*cursor == '\n') {
                        scanner_line_number++;
                        ++cursor;
                    }
                    else if (!*cursor) {
                        goto eof_label;
                    }
                    else {
                        ++cursor;
                    }
                }
                if (brace_depth > 0) {
                    scanner_error("missing", '}');
                }
                cur_symbol = find_symbol(token_start);
            }
            else if (((*cursor >= '0' && *cursor <= '9'))) {
                action_value = atoi(cursor);
                if (!action_value) {
                    scanner_error("invalid action specification", ' ');
                }
                while (*++cursor) {
                    if (*cursor == '}') {
                        break;
                    }
                }
                if (*cursor == '}') {
                    ++cursor;
                }
                else {
                    scanner_error("missing", '}');
                }
                sprintf(name_end, "_action_%u", action_value);
                cur_symbol = find_symbol(name_end);
                if (!cur_symbol) {
                    cur_symbol = new_symbol(3, action_value, name_end);
                    register_symbol(cur_symbol);
                }
            }
            else {
                while (*++cursor) {
                    if (*cursor == '}' || (*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                        break;
                    }
                }
                saved_char = *cursor;
                *cursor = '\0';
                cur_symbol = find_symbol(token_start);
                if (!cur_symbol && *token_start != '$') {
                    cur_symbol = new_symbol(3, 0, token_start);
                    register_symbol(cur_symbol);
                }
                *cursor = saved_char;
                for (; *cursor; ++cursor) {
                    if (*cursor == '}') {
                        break;
                    }
                }
                if (*cursor == '}') {
                    ++cursor;
                }
                else {
                    scanner_error("missing", '}');
                }
            }
            input_cursor = cursor;
            return 3;
        case '\'':
            ++token_start;
            if (*++cursor == '\\') {
                switch (*++cursor) {
                case 'b':
                    number = '\b';
                    break;
                case 'f':
                    number = '\f';
                    break;
                case 't':
                    number = '\t';
                    break;
                case 'n':
                    number = '\n';
                    break;
                case 'r':
                    number = '\r';
                    break;
                default:
                    number = *cursor;
                }
            }
            else {
                number = *cursor;
            }
            saved_char = *++cursor;
            *cursor = '\0';
            cur_symbol = find_symbol(token_start);
            if (!cur_symbol) {
                cur_symbol = new_symbol(2, number, token_start);
                register_symbol(cur_symbol);
            }
            *cursor = saved_char;
            if (saved_char == '\'') {
                ++cursor;
            }
            else {
                scanner_error("missing", '\'');
            }
            input_cursor = cursor;
            return (cur_symbol->type);
        case '|':
            input_cursor = ++cursor;
            return 5;
        case ':':
            switch (*++cursor) {
            case '?':
                if (!cur_symbol->conditional) {
                    cur_symbol->conditional = 1;
                    ++conditional_count;
                }
                break;
            case '!':
                if (!cur_symbol->ignore_conflicts) {
                    cur_symbol->ignore_conflicts = 1;
                    ++ignored_conflict_count;
                }
                break;
            }
            input_cursor = ++cursor;
            return (4);
        case ';':
            input_cursor = ++cursor;
            return 6;
        default:
            scanner_error("invalid character", *cursor);
            token_start = ++cursor;
        }
    }
}
uint line_number(void)
{
    return scanner_line_number;
}
char*
cur_token_text(void)
{
    uint count;
    count = input_cursor - token_start;
    count = count < 32 ? count : 32 - 1;
    token_text_buffer[count] = '\0';
    strncpy(token_text_buffer, token_start, count);
    return token_text_buffer;
}
uint ebnf_enabled(void)
{
    return ebnf_flag;
}
char*
action_prefix(char* name)
{
    if (!strncmp(name, "_action_", 8)) {
        return "_action_";
    }
    if (!strncmp(name, "__", 2)) {
        return "__";
    }
    return "";
}
uint action_prefix_len(char* name)
{
    if (!strncmp(name, "_action_", 8)) {
        return 8;
    }
    if (!strncmp(name, "__", 2)) {
        return 2;
    }
    return 0;
}
int (*select_scanner(char* grammar_text,
    uint grammar_flags))(void)
{
    int (*scanner)(void) = NULL;
    ebnf_flag = (grammar_flags & 0x00004000);
    strip_actions = (grammar_flags & 0x00000008);
    double_underscore_actions = !(grammar_flags & 0x00008000);
    scanner_state = SCAN_START;
    input_cursor = grammar_text;
    scanner_line_number = 1;
    if (grammar_flags & 0x00000010) {
        if (ebnf_flag) {
            puts("EBNF is not supported with the YACC-style scanner.");
        }
        else {
            scanner = yacc_next_token;
        }
    }
    else {
        scanner = next_token;
    }
    return scanner;
}
uint max_lookahead = 7,
base_conflict_count,
conflict_count;
static Conflict* conflicts,
* extended_conflicts,
* resolved_conflicts,
* free_conflicts;
static ConflictProduction* free_conflict_productions;
static ConflictProduction*
alloc_recycled_cp(void)
{
    register ConflictProduction* node = free_conflict_productions;
    if (node) {
        free_conflict_productions = node->next;
        memset(node, 0, sizeof(ConflictProduction));
    }
    return node;
}
static void
free_conflict_production(register ConflictProduction* node)
{
    free_config_list(&node->configs);
    node->next = free_conflict_productions;
    free_conflict_productions = node;
}
static Conflict*
alloc_recycled_conflict(void)
{
    register Conflict* node = free_conflicts;
    if (node) {
        free_conflicts = node->next;
        memset(node, 0, sizeof(Conflict) + (max_lookahead * sizeof(void*)));
    }
    return node;
}
static void
free_conflict(register Conflict* node)
{
    ConflictProduction* production = node->configs,
        * recycled_node;
    while (production) {
        recycled_node = production;
        production = production->next;
        free_conflict_production(recycled_node);
    }
    node->next = free_conflicts;
    free_conflicts = node;
}
static void
append_resolved_conflict(Conflict* conflict)
{
    register Conflict* cursor;
    if (resolved_conflicts) {
        cursor = resolved_conflicts;
        for (; cursor->next; cursor = cursor->next) {
        }
        cursor->next = conflict;
    }
    else {
        resolved_conflicts = conflict;
    }
    conflict->next = NULL;
}
static Conflict*
new_conflict_node(void)
{
    register Conflict* conflict;
    uint conflict_size = sizeof(Conflict) +
        (max_lookahead * sizeof(void*));
    static int block_left = 0;
    static Conflict* block;
    if (--block_left > 0) {
        block = (Conflict*)((char*)block + conflict_size);
        conflict = block;
    }
    else {
        block_left = 0;
        conflict = alloc_recycled_conflict();
        if (!conflict) {
            block_left = 1024;
            block = (Conflict*)calloc(block_left, conflict_size);
            conflict = block;
            if (!conflict) {
                fatal_error(1201, "out of memory");
            }
        }
    }
    conflict->lookahead_tokens = &conflict->first_token;
    conflict->lookahead_level = 1;
    return conflict;
}
static ConflictProduction*
new_conflict_production_node(void)
{
    ConflictProduction* production;
    static int block_left = 0;
    static ConflictProduction* block;
    if (--block_left > 0) {
        ++block;
        production = block;
    }
    else {
        block_left = 0;
        production = alloc_recycled_cp();
        if (!production) {
            block_left = 1024;
            block = (ConflictProduction*)calloc(block_left,
                sizeof(ConflictProduction));
            production = block;
            if (!production) {
                fatal_error(1202, "out of memory");
            }
        }
    }
    return production;
}
static void
copy_symbols(register Symbol** dst_symbols,
    register Symbol** src_symbols)
{
    while ((*dst_symbols++ = *src_symbols++)) {
    }
}
static uint
symbols_equal(register Symbol** dst_symbols,
    register Symbol** src_symbols)
{
    for (; *dst_symbols == *src_symbols; ++dst_symbols, ++src_symbols) {
        if (!*dst_symbols) {
            break;
        }
    }
    return (*dst_symbols == *src_symbols);
}
static uint
append_conflict_production(ConflictProduction** list,
    register ConflictProduction* new_node)
{
    register ConflictProduction* conflict_production;
    ConflictProduction* last_node = NULL;
    if (new_node->next) {
        fatal_error(1222, "append_production: new->next is not null");
    }
    if (!*list) {
        *list = new_node;
        return 1;
    }
    for (conflict_production = *list; conflict_production; conflict_production = conflict_production->next) {
        last_node = conflict_production;
        if (conflict_production->conflict == new_node->conflict) {
            if (conflict_production->number == new_node->number) {
                return 0;
            }
        }
    }
    last_node->next = new_node;
    return 1;
}
static Config*
copy_configs_for(register ConflictProduction* production,
    int number)
{
    Config* configs = NULL;
    for (; production; production = production->next) {
        if (production->conflict == number) {
            configs = copy_config_list(production->configs);
            break;
        }
    }
    return configs;
}
static uint
compare_conflict_configs(ConflictProduction* configs,
    int old_production,
    int production_number)
{
    register ConflictProduction* prod_a = configs,
        * prod_b = configs;
    uint found = 0;
    for (; prod_a; prod_a = prod_a->next) {
        if (prod_a->conflict == old_production) {
            break;
        }
    }
    for (; prod_b; prod_b = prod_b->next) {
        if (prod_b->conflict == production_number) {
            break;
        }
    }
    if (!(prod_a && prod_b)) {
        fatal_error(1203, "production not found");
    }
    found = configs_equal(prod_a->configs,
        prod_b->configs);
    if (found) {
        found = configs_have_nonterminal(prod_a->configs);
        if (found) {
            found = AMBIGUOUS;
        }
    }
    return found;
}
static Symbol*
common_lookahead(ConflictProduction* conflict_prod_a,
    ConflictProduction* conflict_prod_b)
{
    register Symbol** rhs_a,
        ** rhs_b;
    Symbol* lhs_a,
        * lhs_b,
        * lookahead_tokens = NULL;
    if (!(conflict_prod_a && conflict_prod_b)) {
        return lookahead_tokens;
    }
    lhs_a = *conflict_prod_a->configs->lhs;
    lhs_b = *conflict_prod_b->configs->lhs;
    rhs_a = conflict_prod_a->configs->dot;
    rhs_b = conflict_prod_b->configs->dot;
    if (*rhs_a && *rhs_b) {
        lookahead_tokens = set_intersect((*rhs_a)->firsts, (*rhs_b)->firsts);
        if (lookahead_tokens) {
            return lookahead_tokens;
        }
    }
    if (rhs_nullable(rhs_a)) {
        if (rhs_nullable(rhs_b)) {
            lookahead_tokens = set_intersect(lhs_a->follows, lhs_b->follows);
            if (lookahead_tokens) {
                return lookahead_tokens;
            }
        }
        if (*rhs_b) {
            lookahead_tokens = set_intersect(lhs_a->follows, (*rhs_b)->firsts);
            if (lookahead_tokens) {
                return lookahead_tokens;
            }
        }
    }
    if (rhs_nullable(rhs_b)) {
        if (*rhs_a) {
            lookahead_tokens = set_intersect((*rhs_a)->firsts, lhs_b->follows);
            if (lookahead_tokens) {
                return lookahead_tokens;
            }
        }
    };
    ;
    print_config(conflict_prod_a->configs->lhs,
        conflict_prod_a->configs->dot);
    print_config(conflict_prod_b->configs->lhs,
        conflict_prod_b->configs->dot);
    return lookahead_tokens;
}
static uint
verify_conflict_grammar(void)
{
    register Conflict* conflict = conflicts;
    register ConflictProduction* conflict_prod_a = NULL,
        * conflict_prod_next = NULL;
    Symbol* lookahead_tokens = NULL;
    uint conflict_number = 0,
        errors = 0;
    for (; conflict; conflict = conflict->next) {
        if (conflict->number != ++conflict_number) {
            errors = 1;
            ;
            ;
            return errors;
        }
    }
    base_conflict_count = conflict_number;
    if (verbose_level > 2) {
        ;
        ;
    }
    for (conflict = conflicts; conflict; conflict = conflict->next) {
        conflict_prod_a = conflict->configs;
        if (!conflict_prod_a) {
            errors = 1;
            ;
            ;
            continue;
        }
        conflict_prod_next = conflict_prod_a->next;
        if (!conflict_prod_next) {
            errors = 1;
            ;
            ;
            continue;
        }
        lookahead_tokens = common_lookahead(conflict_prod_a, conflict_prod_next);
        if (!lookahead_tokens) {
            ;
            ;
            errors = 1;
            continue;
        }
        *conflict->lookahead_tokens = lookahead_tokens;
        while ((conflict_prod_next = conflict_prod_next->next)) {
            lookahead_tokens = common_lookahead(conflict_prod_a, conflict_prod_next);
            if (!lookahead_tokens) {
                ;
                ;
                errors = 1;
            }
            else if (*conflict->lookahead_tokens != lookahead_tokens) {
                errors = 1;
                ;
                ;
                ;
                ;
                print_config(conflict_prod_a->configs->lhs,
                    conflict_prod_a->configs->dot);
                ;
                ;
                print_config(conflict_prod_next->configs->lhs,
                    conflict_prod_next->configs->dot);
            }
        }
    }
    if (verbose_level > 2 && errors) {
        ;
        ;
    }
    return errors;
}
static void
add_gc_conflict(uint conflict_number,
    ConflictProduction* production_number)
{
    register Conflict* conflict = conflicts,
        * last_conflict = NULL;
    Conflict* created_conflict = NULL;
    for (; conflict; conflict = conflict->next) {
        if (conflict->number == conflict_number) {
            break;
        }
    }
    if (!conflict) {
        conflict = new_conflict_node();
        conflict->number = conflict_number;
        created_conflict = conflict;
    }
    append_conflict_production(&conflict->configs, production_number);
    if (created_conflict) {
        if (!conflicts) {
            conflicts = conflict;
        }
        else {
            conflict = conflicts;
            last_conflict = conflict;
            if (conflict->number > conflict_number) {
                conflicts = created_conflict;
                created_conflict->next = conflict;
            }
            else {
                for (; conflict; conflict = conflict->next) {
                    if (conflict->number > conflict_number) {
                        last_conflict->next = created_conflict;
                        created_conflict->next = conflict;
                        break;
                    }
                    last_conflict = conflict;
                }
                if (!conflict) {
                    last_conflict->next = created_conflict;
                }
            }
        }
        conflict = created_conflict;
    }
    if (verbose_level > 2) {
        print_conflicts(1);
    }
}
static uint
collect_gc_conflicts(void)
{
    register Symbol** dot,
        *** block = productions;
    Symbol** lhs,
        ** dot_pos;
    Config* config;
    int production_number = 0;
    int conflict_number;
    ConflictProduction* conflict_prod_a = NULL;
    uint errors = 0;
    while (*++block) {
        lhs = *block;
        dot = lhs;
        ++production_number;
        while (*++dot) {
            if (!strncmp((*dot)->name, "__dot_", 6)) {
                conflict_number = atoi((*dot)->name + 6);
                if (conflict_number <= 0) {
                    errors = 1;
                    ;
                    ;
                    break;
                }
                if (verbose_level > 2) {
                    print_production("  ", lhs);
                }
                for (dot_pos = dot; (*dot = *(dot + 1)); ++dot) {
                }
                config = new_config(lhs, dot_pos,
                    NULL, CONFIG_BASE);
                conflict_prod_a = new_conflict_production(production_number, production_number,
                    config);
                add_gc_conflict(conflict_number, conflict_prod_a);
                break;
            }
        }
    }
    errors |= verify_conflict_grammar();
    if (verbose_level > 2) {
        print_conflicts(1);
        if (errors) {
            ;
            ;
        }
    }
    return errors;
}
uint resolve_only_conflicts(void)
{
    register Symbol** dot,
        *** block = productions;
    Symbol** lhs,
        ** dot_pos,
        * lookahead_tokens;
    Config* config;
    int production_number = 0;
    ConflictProduction* conflict_prod_a = NULL,
        * conflict_prod_b = NULL;
    uint errors = 0;
    ;
    ;
    while (*++block) {
        lhs = *block;
        dot = lhs;
        ++production_number;
        while (*++dot) {
            if (!strcmp((*dot)->name, "__dot_")) {
                for (dot_pos = dot; (*dot = *(dot + 1)); ++dot) {
                }
                config = new_config(lhs, dot_pos,
                    NULL, CONFIG_BASE);
                if (conflict_prod_a) {
                    conflict_prod_b = new_conflict_production(production_number,
                        production_number, config);
                }
                else {
                    conflict_prod_a = new_conflict_production(production_number,
                        production_number, config);
                }
                if (verbose_level > 2) {
                    print_production("  ", lhs);
                }
                break;
            }
        }
        if (conflict_prod_b) {
            break;
        }
    }
    if (conflict_prod_b) {
        lookahead_tokens = common_lookahead(conflict_prod_a, conflict_prod_b);
        if (lookahead_tokens) {
            if (verbose_level > 2) {
                ;
                ;
            }
            add_conflict(lookahead_tokens, conflict_prod_a, conflict_prod_b, 0);
        }
    }
    else {
        errors = collect_gc_conflicts();
    }
    if (verbose_level > 2 && errors) {
        ;
        ;
    }
    return errors;
}
ConflictProduction*
new_conflict_production(int number,
    uint conflict,
    Config* config)
{
    register ConflictProduction* new_node;
    new_node = new_conflict_production_node();
    new_node->number = number;
    new_node->conflict = conflict;
    new_node->configs = config;
    return (new_node);
}
ConflictProduction*
copy_conflict_production(register ConflictProduction* conflict_production)
{
    register ConflictProduction* new_node;
    new_node = new_conflict_production_node();
    new_node->number = conflict_production->number;
    new_node->conflict = conflict_production->conflict;
    new_node->configs = copy_config_list(conflict_production->configs);
    return (new_node);
}
uint add_conflict(Symbol* lookahead_tokens,
    ConflictProduction* old_production,
    ConflictProduction* production_number,
    uint lr_state)
{
    register Conflict* conflict = conflicts,
        * last_conflict = NULL;
    ConflictProduction* production;
    uint changed = 0,
        conflict_number = 1;
    if (verbose_level > 2) {
        print_conflict_pair(lookahead_tokens, old_production->number, production_number->number);
    }
    for (; conflict; conflict = conflict->next) {
        ++conflict_number;
        last_conflict = conflict;
        production = conflict->configs;
        if (production->conflict == old_production->conflict &&
            *conflict->lookahead_tokens == lookahead_tokens) {
            if (conflict->lr_state == lr_state) {
                changed = append_conflict_production(&conflict->configs,
                    production_number);
                break;
            }
        }
    }
    if (!conflict) {
        conflict = new_conflict_node();
        conflict->number = conflict_number;
        base_conflict_count = conflict_number;
        *conflict->lookahead_tokens = lookahead_tokens;
        conflict->lr_state = lr_state;
        append_conflict_production(&conflict->configs, old_production);
        append_conflict_production(&conflict->configs, production_number);
        if (last_conflict) {
            last_conflict->next = conflict;
        }
        else {
            conflicts = conflict;
        }
        changed = 1;
    }
    return (changed);
}
uint extend_conflict(void* conflict_ptr,
    Symbol* lookahead_tokens,
    int old_production,
    ConflictProduction* production_number)
{
    register Conflict* conflict_cursor,
        * created_conflict;
    Conflict* conflict = (Conflict*)conflict_ptr,
        * last_conflict = NULL;
    ConflictProduction* production;
    uint status = 0;
    if (conflict->lookahead_level >= max_lookahead) {
        ;
        ;
        fatal_error(1204, "");
    }
    if (aggressive_check) {
        status = compare_conflict_configs(conflict->configs, old_production,
            production_number->conflict);
    }
    if (status) {
        return status;
    }
    conflict->lookahead_tokens[conflict->lookahead_level] = lookahead_tokens;
    conflict_cursor = extended_conflicts;
    for (; conflict_cursor; conflict_cursor = conflict_cursor->next) {
        last_conflict = conflict_cursor;
        production = conflict_cursor->configs;
        if (production->conflict == old_production &&
            symbols_equal(conflict_cursor->lookahead_tokens, conflict->lookahead_tokens) &&
            conflict->lr_state == conflict_cursor->lr_state) {
            append_conflict_production(&conflict_cursor->configs, copy_conflict_production(production_number));
            status = MERGED;
            break;
        }
    }
    if (!status) {
        if (++slk_conflicts_created > SLK_CONFLICT_BUDGET) {
            fatal_error(1210, "conflict resolution budget exceeded: the grammar generates too many conflicts for generalized k-lookahead resolution (use default LL(k) or -LA, or reduce -k)");
        }
        created_conflict = new_conflict_node();
        copy_symbols(created_conflict->lookahead_tokens, conflict->lookahead_tokens);
        production = conflict->configs;
        for (; production; production = production->next) {
            if (production->conflict == old_production) {
                break;
            }
        }
        if (!production) {
            ;
            ;
            fatal_error(1206, "");
        }
        append_conflict_production(&created_conflict->configs, copy_conflict_production(production));
        append_conflict_production(&created_conflict->configs, copy_conflict_production(production_number));
        created_conflict->back_link = conflict->back_link;
        created_conflict->number = conflict->number;
        created_conflict->lookahead_level = conflict->lookahead_level + 1;
        created_conflict->lr_state = conflict->lr_state;
        if (last_conflict) {
            last_conflict->next = created_conflict;
        }
        else {
            extended_conflicts = created_conflict;
        }
        status = EXTENDED;
    }
    conflict->lookahead_tokens[conflict->lookahead_level] = NULL;
    return status;
}
void remove_conflict(uint conflict_number)
{
    register Conflict* conflict_cursor,
        * next;
    for (conflict_cursor = next = conflicts; next;) {
        if (next->number == conflict_number) {
            if (next == conflicts) {
                conflict_cursor = next = conflicts = conflicts->next;
            }
            else {
                next = conflict_cursor->next = next->next;
            }
        }
        else {
            conflict_cursor = next;
            next = conflict_cursor->next;
        }
    }
}
void promote_resolved_conflicts(void)
{
    register Conflict* conflict_cursor,
        * recycled_node;
    for (conflict_cursor = conflicts; conflict_cursor;) {
        if (conflict_cursor->resolved) {
            recycled_node = conflict_cursor;
            conflict_cursor = conflict_cursor->next;
            append_resolved_conflict(recycled_node);
        }
        else {
            conflict_cursor = conflict_cursor->next;
        }
    }
    if (conserve_memory) {
        for (conflict_cursor = conflicts; conflict_cursor;) {
            recycled_node = conflict_cursor;
            conflict_cursor = conflict_cursor->next;
            free_conflict(recycled_node);
        }
    }
    conflicts = extended_conflicts;
    extended_conflicts = NULL;
}
Conflict*
get_conflicts(void)
{
    return conflicts;
}
Conflict*
find_conflict(uint conflict_number)
{
    register Conflict* conflict = conflicts;
    for (; conflict; conflict = conflict->next) {
        if (conflict->number == conflict_number) {
            break;
        }
    }
    return conflict;
}
Conflict*
get_resolved_conflicts(void)
{
    return resolved_conflicts;
}
uint compare_conflict_productions(register ConflictProduction* production)
{
    register ConflictProduction* prod_b;
    uint equal = 0;
    for (; production; production = production->next) {
        prod_b = production->next;
        for (; prod_b; prod_b = prod_b->next) {
            equal = configs_equal(production->configs,
                prod_b->configs);
            if (equal) {
                break;
            }
        }
        if (equal) {
            break;
        }
    }
    return equal;
}
uint set_lookahead_symbol(void* conflict_ptr,
    Symbol* lookahead_tokens,
    int conflict)
{
    register Conflict* conflict_state = (Conflict*)conflict_ptr;
    register ConflictProduction* production = conflict_state->configs;
    uint found = 0;
    for (; production; production = production->next) {
        if (production->conflict == conflict) {
            found = 1;
            production->lookahead = lookahead_tokens;
            break;
        }
    }
    if (!found) {
        ;
        ;
        fatal_error(1208, "");
    }
    return found;
}
uint report_conflicts(uint show_conflict_numbers,
    uint* conflict_status,
    uint resolved_level)
{
    register Conflict* conflict;
    register uint* status;
    uint unresolvable_count = 0,
        ambiguous_count = 0,
        remaining_count = 0,
        conflict_number = 0,
        level,
        result_status = 0;
    char number_buffer[32];
    *number_buffer = '\0';
    if (verbose_level != 1) {
        printf("--------------------------------------------------\n\n");
    }
    for (status = &conflict_status[1]; *status != -1; ++status) {
        if (show_conflict_numbers) {
            sprintf(number_buffer, " %u", ++conflict_number);
        }
        level = (*status & LEVEL_MASK);
        if (*status & CONDITIONAL) {
            if (verbose_level != 1) {
                printf("Conflict%s on conditional nonterminal \n",
                    number_buffer);
            }
        }
        else if (*status & IGNORED) {
            if (verbose_level != 1) {
                printf("Conflict%s is being ignored by request,"
                    " using the first production\n",
                    number_buffer);
            }
        }
        else if (*status & AMBIGUOUS) {
            ++ambiguous_count;
            printf("Conflict%s is ambiguous at level %u.\n",
                number_buffer, level);
        }
        else if (*status & UNRESOLVABLE) {
            ++unresolvable_count;
            printf("Conflict%s is unresolvable at level %u.\n",
                number_buffer, level);
        }
        else if (*status & MERGED_OR_EXTENDED) {
            printf("Conflict%s is extended to level %u.\n",
                number_buffer, level + 1);
        }
        else if (*status & RESOLVED) {
            if (verbose_level != 1) {
                printf("Conflict%s is resolved at level %u.\n",
                    number_buffer, level);
            }
        }
        else if ((*status & STATUS_MASK)) {
            printf("invalid conflict status = 0x%x \n", *status);
            fatal_error(1705, "");
        }
        else {
            if ((*status & LEVEL_MASK)) {
                *status |= UNRESOLVABLE;
                ++unresolvable_count;
                printf("Conflict%s is unresolvable at level %u.\n",
                    number_buffer, level);
            }
        }
    }
    conflict = get_conflicts();
    conflict_number = 0;
    for (remaining_count = 0; conflict; conflict = conflict->next) {
        ++remaining_count;
        if (conflict_number == 0 && !quiet) {
            printf("\nconflicts remaining:\n\n");
        }
        if (conflict_number != conflict->number) {
            conflict_number = conflict->number;
            if (!quiet) {
                printf("Conflict %d is unresolved\n", conflict_number);
            }
        }
    }
    printf("--------------------------------------------------\n\n");
    if (remaining_count) {
        printf("%d conflict(s) remain at lookahead level k=%d\n",
            remaining_count, max_lookahead);
        result_status = 1;
    }
    if (ambiguous_count) {
        printf("Ambiguity is suggested by %d ambiguous conflict(s)\n",
            ambiguous_count);
        result_status = 1;
    }
    if (unresolvable_count) {
        printf("Ambiguity is suggested by %d unresolvable conflict(s)\n",
            unresolvable_count);
        result_status = 1;
    }
    if (conditional_count) {
        printf("Backtracking will be used on %d conditional nonterminal(s)\n",
            conditional_count);
    }
    if (ignored_conflict_count) {
        printf("Conflicts were ignored by request on %d nonterminal(s)\n",
            ignored_conflict_count);
    }
    if (!result_status) {
        printf("Conflicts were resolved at lookahead level k=%d\n", resolved_level);
    }
    return result_status;
}
void print_conflict_pair(Symbol* lookahead_tokens,
    int old_production,
    int production_number)
{
    register Symbol** symbol;
    ;
    ;
    symbol = productions[old_production];
    ;
    ;
    while (*++symbol) {
        ;
        ;
    };
    ;
    symbol = productions[production_number];
    ;
    ;
    while (*++symbol) {
        ;
        ;
    };
    ;
}
void print_conflicts(uint show_conflict_numbers)
{
    register Conflict* conflict = conflicts;
    register ConflictProduction* production;
    Symbol** lookahead_tokens;
    char* token_name = "not set";
    char number_buffer[32];
    char state_buffer[32];
    *number_buffer = '\0';
    *state_buffer = '\0';
    for (; conflict; conflict = conflict->next) {
        lookahead_tokens = conflict->lookahead_tokens;
        if (*lookahead_tokens) {
            token_name = (*lookahead_tokens)->name;
        }
        if (show_conflict_numbers) {
            sprintf(number_buffer, " %u", conflict->number);
        }
        if (conflict->lr_state) {
            sprintf(state_buffer, " in state %u",
                conflict->lr_state);
        }
        printf("\nConflict%s:  parse table conflict under \"%s\"%s:\n",
            number_buffer, token_name, state_buffer);
        production = conflict->configs;
        for (; production; production = production->next) {
            print_production_number(production->number);
        }
    }
}
void print_lookaheads(uint show_conflict_numbers)
{
    register Conflict* conflict = resolved_conflicts;
    register ConflictProduction* production;
    Symbol** lookahead_tokens;
    char* dollar_name = "$";
    char number_buffer[32];
    *number_buffer = '\0';
    if (find_symbol("$")) {
        dollar_name = "$$$";
    }
    printf("\n\n\t\t LOOKAHEAD STRINGS FOR RESOLVED CONFLICTS\n\n");
    for (; conflict; conflict = conflict->next) {
        lookahead_tokens = conflict->lookahead_tokens;
        if (show_conflict_numbers) {
            sprintf(number_buffer, " %u", conflict->number);
        }
        printf("Conflict%s was resolved at lookahead level %u:\n",
            number_buffer, conflict->lookahead_level + 1);
        production = conflict->configs;
        for (; production; production = production->next) {
            print_production_number(production->number);
            printf("      Lookahead string:  ");
            lookahead_tokens = conflict->lookahead_tokens;
            while (*lookahead_tokens) {
                printf("%s ", (*lookahead_tokens)->name);
                ++lookahead_tokens;
            }
            if (production->lookahead) {
                printf("%s \n\n", production->lookahead->name);
            }
            else {
                printf("%s \n\n", dollar_name);
            }
        }
    }
}
static ConflictLevel* conflict_levels;
static ConflictEntry*
new_conflict_entry_node(void)
{
    static int block_left = 0;
    static ConflictEntry* block;
    if (--block_left > 0) {
        return (++block);
    }
    else {
        block_left = 1024;
        block = (ConflictEntry*)calloc(block_left, sizeof(ConflictEntry));
        if (!block) {
            block_left = 0;
            fatal_error(1401, "out of memory");
        }
    }
    return block;
}
static ConflictRow*
new_conflict_row_node(void)
{
    static int block_left = 0;
    static ConflictRow* row;
    if (--block_left > 0) {
        return (++row);
    }
    else {
        block_left = 1024;
        row = (ConflictRow*)calloc(block_left, sizeof(ConflictRow));
        if (!row) {
            block_left = 0;
            fatal_error(1402, "out of memory");
        }
    }
    return row;
}
static ConflictLevel*
new_conflict_level_node(void)
{
    static int block_left = 0;
    static ConflictLevel* conflict_level;
    if (--block_left > 0) {
        return (++conflict_level);
    }
    else {
        block_left = 16;
        conflict_level = (ConflictLevel*)calloc(block_left, sizeof(ConflictLevel));
        if (!conflict_level) {
            block_left = 0;
            fatal_error(1403, "out of memory");
        }
    }
    return conflict_level;
}
static ConflictEntry*
find_conflict_entry(register ConflictEntry* block,
    register int token)
{
    for (; block; block = block->next) {
        if (block->token == token) {
            break;
        }
    }
    return block;
}
static void
print_conflict_entries(register ConflictEntry* block)
{
    for (; block; block = block->next) {
        ;
        ;
    };
    ;
}
static void
insert_conflict_entry(ConflictEntry** block,
    int token,
    int production)
{
    register ConflictEntry* new_node,
        * conflict_production = *block;
    new_node = new_conflict_entry_node();
    new_node->token = token;
    new_node->production = production;
    if (!conflict_production) {
        *block = new_node;
        return;
    }
    if (conflict_production->token > token) {
        new_node->next = conflict_production;
        *block = new_node;
        return;
    }
    for (; conflict_production; conflict_production = conflict_production->next) {
        if (!conflict_production->next) {
            conflict_production->next = new_node;
            break;
        }
        else if (conflict_production->next->token > token) {
            new_node->next = conflict_production->next;
            conflict_production->next = new_node;
            break;
        }
    }
}
ConflictRow*
new_conflict_row(ConflictLevel* conflict_level,
    Symbol* nonterminal)
{
    register ConflictRow* row,
        ** rows;
    rows = &conflict_level->rows;
    if (!*rows) {
        *rows = new_conflict_row_node();
        (*rows)->nonterminal = nonterminal;
        return *rows;
    }
    for (row = *rows; row->next; row = row->next) {
    }
    row->next = new_conflict_row_node();
    row = row->next;
    row->nonterminal = nonterminal;
    return row;
}
uint merge_conflict_row(ConflictRow* row,
    register SymbolSetNode* firsts,
    void* conflict,
    ConflictProduction* production_number)
{
    register Symbol* lookahead_tokens;
    int token,
        old_production;
    ConflictEntry** block = &row->entries,
        * entry;
    uint status = 0;
    for (; firsts; firsts = firsts->next) {
        lookahead_tokens = firsts->symbol;
        token = lookahead_tokens->number;
        entry = find_conflict_entry(*block, token);
        if (entry) {
            old_production = entry->production;
            if (old_production != production_number->conflict) {
                if (verbose_level > 2) {
                    ;
                    ;
                    print_conflict_pair(lookahead_tokens, old_production,
                        production_number->number);
                }
                status |= extend_conflict(conflict, lookahead_tokens, old_production,
                    production_number);
            }
        }
        else {
            insert_conflict_entry(block, token, production_number->conflict);
            status |= RESOLVED;
            set_lookahead_symbol(conflict, lookahead_tokens, production_number->conflict);
        }
    }
    return status;
}
ConflictLevel*
new_conflict_level(void)
{
    register ConflictLevel* conflict_level,
        * conflict_cursor;
    conflict_level = new_conflict_level_node();
    conflict_cursor = conflict_levels;
    if (conflict_cursor) {
        while (conflict_cursor->next) {
            conflict_cursor = conflict_cursor->next;
        }
        conflict_cursor->next = conflict_level;
    }
    else {
        conflict_levels = conflict_level;
    }
    return conflict_level;
}
ConflictLevel*
get_conflict_levels(void)
{
    return (conflict_levels);
}
void set_conflict_entry(ConflictRow* row,
    int token,
    int conflict_number)
{
    register ConflictEntry* block,
        * entry;
    block = row->entries;
    entry = find_conflict_entry(block, token);
    if (entry) {
        entry->production = (conflict_number + (start_conflict - 1));
    }
    else {
        ;
        ;
        print_conflict_entries(block);
        fatal_error(1404, "");
    }
}
static void
clear_conflict_entries(ConflictLevel* conflict_level,
    int level_number,
    int conflict_number)
{
    register ConflictEntry* block;
    register ConflictRow* row;
    int production;
    uint row_index = 0;
    for (row = conflict_level->rows; row; row = row->next) {
        if (++row_index != conflict_number) {
            continue;
        }
        for (block = row->entries; block; block = block->next) {
            production = block->production;
            if ((production >= start_conflict)) {
                if (conflict_level->next) {
                    clear_conflict_entries(conflict_level->next,
                        level_number + 1,
                        (production - (start_conflict - 1)));
                }
            }
        }
        if (verbose_level > 1) {
            ;
            ;
            if (verbose_level > 1) {
                for (block = row->entries; block; block = block->next) {
                    ;
                    ;
                }
            }
        }
        row->entries = NULL;
        break;
    }
}
void remove_conflict_entries(int conflict_number)
{
    ConflictLevel* conflict_level;
    conflict_level = get_conflict_levels();
    clear_conflict_entries(conflict_level, 1, conflict_number);
}
void print_conflict_table(void)
{
    register ConflictEntry* block;
    register ConflictRow* row;
    int conflict_number,
        production;
    uint total_levels = 0,
        row_count;
    uint terminal_only;
    ConflictLevel* conflict_level;
    ;
    ;
    conflict_level = get_conflict_levels();
    conflict_number = start_conflict;
    for (; conflict_level; conflict_level = conflict_level->next) {
        terminal_only = 1;
        row_count = 0;
        for (row = conflict_level->rows; row; row = row->next) {
            ++row_count;
        }
        total_levels += row_count;
        for (row = conflict_level->rows; row; row = row->next) {
            ;
            ;
            for (block = row->entries; block; block = block->next) {
                production = block->production;
                if ((production >= start_conflict)) {
                    production += total_levels;
                    terminal_only = 0;
                };
                ;
            };
            ;
            ++conflict_number;
        };
        ;
        if (terminal_only) {
            break;
        }
    }
}
static void
trace_conflict(ConflictLevel* conflict_level,
    int conflict_number,
    int depth)
{
    register ConflictEntry* block;
    register ConflictRow* row;
    int production;
    uint row_index = 0;
    for (row = conflict_level->rows; row; row = row->next) {
        if (++row_index != conflict_number) {
            continue;
        }
        for (block = row->entries; block; block = block->next) {
            production = block->production;
            if ((production >= start_conflict)) {
                ;
                ;
                ;
                ;
                if (conflict_level->next) {
                    trace_conflict(conflict_level->next,
                        (production - (start_conflict - 1)),
                        depth + 1);
                }
            }
        }
        break;
    }
}
void print_conflict_traces(void)
{
    register Symbol** nonterminal = nonterminals;
    register TableEntry* table;
    ConflictLevel* conflict_level;
    int conflict_number,
        found;
    conflict_level = get_conflict_levels();
    ;
    ;
    while (*++nonterminal) {
        found = 0;
        for (table = (*nonterminal)->table; table; table = table->next) {
            if ((table->production >= start_conflict)) {
                found = 1;
                conflict_number = (table->production - (start_conflict - 1));
                ;
                ;
                trace_conflict(conflict_level, conflict_number, 1);
            }
        }
        if (found) {
            ;
            ;
        }
    }
}
static uint
rhs_all_nullable2(register Symbol** dot)
{
    for (; *dot; ++dot) {
        if ((*dot)->type == 3)
            continue;
        if (!(*dot)->nullable) {
            break;
        }
    }
    return (*dot == NULL);
}
static void
report_conflict_status(uint status,
    uint conflict_id,
    uint prod_iter,
    uint show_conflict_numbers)
{
    uint level = (status & LEVEL_MASK);
    char number_buffer[32];
    *number_buffer = '\0';
    if (show_conflict_numbers) {
        sprintf(number_buffer, " %u", conflict_id);
    }
    if (status & CONDITIONAL) {
        ;
        ;
    }
    else if (status & IGNORED) {
        ;
        ;
    }
    else if (status & AMBIGUOUS) {
        ;
        ;
    }
    else if (status & UNRESOLVABLE) {
        ;
        ;
    }
    else if (status & MERGED_OR_EXTENDED) {
        ;
        ;
    }
    else if (status & RESOLVED) {
        ;
        ;
    }
    else if ((status & STATUS_MASK)) {
        ;
        ;
        fatal_error(1704, "");
    }
    else {
        ;
        ;
    };
    ;
}
static uint
add_closure_configs(Symbol* target_nonterminal,
    Config** configs)
{
    register Symbol** dot,
        *** block = productions;
    uint changed = 0;
    while (*++block) {
        dot = *block;
        while (*++dot) {
            if ((*dot)->type == 3)
                continue;
            if (*dot == target_nonterminal) {
                for (++dot; *dot && ((*dot)->type == 3); ++dot)
                    ;
                changed |= add_config(configs, *block, dot,
                    NULL, NULL, CONFIG_CLOSURE);
                while (*dot) {
                    if ((*dot)->nullable) {
                        for (++dot; *dot && ((*dot)->type == 3); ++dot)
                            ;
                        if (*dot) {
                            changed |= add_config(configs, *block,
                                dot, NULL, NULL, CONFIG_CLOSURE);
                        }
                    }
                    else {
                        break;
                    }
                }
                if (!*dot) {
                    break;
                }
            }
        }
    }
    return changed;
}
static void
close_configs(Config** configs)
{
    register Config* config;
    uint changed = 1;
    while (changed) {
        changed = 0;
        for (config = *configs; config; config = config->next) {
            if (rhs_all_nullable2(config->dot)) {
                changed |= add_closure_configs(*config->lhs, configs);
            }
        }
    }
}
static void
advance_configs(Config** configs)
{
    register Config* config;
    register Symbol** dot;
    uint changed = 1;
    Config* out_config;
    while (changed) {
        changed = 0;
        for (config = *configs; config; config = config->next) {
            dot = config->dot;
            if (!*dot) {
                changed |= add_config(configs, config->lhs, dot,
                    config->link, NULL,
                    config->origin);
                continue;
            }
            out_config = config;
            while (*dot && (*dot)->type == 1) {
                changed |= add_configs(configs,
                    (*dot)->configs, out_config);
                if ((*dot)->nullable) {
                    for (++dot; *dot && ((*dot)->type == 3); ++dot)
                        ;
                    changed |= add_config(configs, config->lhs, dot,
                        out_config->link,
                        &out_config,
                        out_config->origin);
                }
                else {
                    break;
                }
            }
        }
    }
}
static uint
advance_on_nullable(Symbol* target_nonterminal,
    uint* succeeded,
    Config** new_configs,
    Config** configs)
{
    register Config* config;
    register Symbol** dot;
    Symbol** prev_symbol;
    uint advanced_changed = 0,
        changed;
    for (config = *configs; config; config = config->next) {
        dot = config->dot;
        if (*dot == target_nonterminal) {
            for (++dot; *dot && ((*dot)->type == 3); ++dot)
                ;
            changed = add_config(new_configs, config->lhs, dot,
                config->link, NULL,
                config->origin);
            advanced_changed |= changed;
            while (changed) {
                changed = 0;
                if (rhs_all_nullable2(dot)) {
                    changed = advance_on_nullable(*config->lhs, succeeded,
                        new_configs, configs);
                    advanced_changed |= changed;
                }
                else {
                    *succeeded = 0;
                }
                if (*dot) {
                    if ((*dot)->nullable) {
                        for (++dot; *dot && ((*dot)->type == 3); ++dot)
                            ;
                        if (*dot) {
                            changed |= add_config(new_configs,
                                config->lhs, dot,
                                config->link, NULL,
                                config->origin);
                        }
                    }
                }
            }
        }
        else {
            prev_symbol = dot - 1;
            for (; *prev_symbol && ((*prev_symbol)->type == 3); --prev_symbol)
                ;
            if (prev_symbol > config->lhs && *prev_symbol == target_nonterminal) {
                changed = add_config(new_configs, config->lhs, dot,
                    config->link, NULL,
                    config->origin);
                advanced_changed |= changed;
                while (changed) {
                    changed = 0;
                    if (rhs_all_nullable2(dot)) {
                        changed = advance_on_nullable(*config->lhs, succeeded,
                            new_configs,
                            configs);
                        advanced_changed |= changed;
                    }
                    else {
                        *succeeded = 0;
                    }
                    if (*dot) {
                        if ((*dot)->nullable) {
                            for (++dot; *dot && ((*dot)->type == 3); ++dot)
                                ;
                            if (*dot) {
                                changed |= add_config(new_configs,
                                    config->lhs, dot,
                                    config->link, NULL,
                                    config->origin);
                            }
                        }
                    }
                }
            }
        }
    }
    return advanced_changed;
}
static uint
advance_configs_for_token(Config** configs,
    Symbol** lhs,
    Symbol* lookahead_tokens)
{
    register Config* config;
    Symbol** dot,
        * eof_label,
        ** dot_pos;
    uint changed = 1,
        found = 0,
        succeeded = 1;
    Config* new_list = NULL;
    Config* link,
        * temp_configs;
    for (config = *configs; config; config = config->next) {
        dot = config->dot;
        if (*dot == lookahead_tokens) {
            found = 1;
            for (++dot; *dot && ((*dot)->type == 3); ++dot)
                ;
            config->dot = dot;
            add_config(&new_list, config->lhs, dot,
                config->link, NULL,
                config->origin);
            dot_pos = dot;
            if (rhs_all_nullable2(dot)) {
                if (trace_level < -3) {
                    print_config(config->lhs, dot);
                }
                link = config->link;
                if (!link) {
                    if (trace_level < -3) {
                        ;
                        ;
                    }
                    if (config->lhs != lhs) {
                        succeeded = 0;
                    }
                }
                while (link) {
                    if (trace_level < -3) {
                        ;
                        ;
                        print_config(link->lhs, link->dot);
                    }
                    dot = link->dot;
                    for (++dot; *dot && ((*dot)->type == 3); ++dot)
                        ;
                    if (*dot) {
                        changed |= add_config(&new_list,
                            link->lhs, dot,
                            link->link,
                            NULL,
                            link->origin);
                        while ((*dot)->nullable) {
                            for (++dot; *dot && ((*dot)->type == 3); ++dot)
                                ;
                            if (*dot) {
                                changed |= add_config(&new_list,
                                    link->lhs, dot,
                                    link->link,
                                    NULL,
                                    link->origin);
                            }
                            else {
                                break;
                            }
                        }
                    }
                    if (!rhs_all_nullable2(dot)) {
                        succeeded = 0;
                        break;
                    }
                    link = link->link;
                }
            }
            else {
                succeeded = 0;
            }
            dot = dot_pos;
            if (rhs_all_nullable2(dot)) {
                advance_on_nullable(*config->lhs, &succeeded,
                    &new_list, configs);
            }
            while (*dot) {
                if ((*dot)->nullable) {
                    for (++dot; *dot && ((*dot)->type == 3); ++dot)
                        ;
                    if (*dot) {
                        changed |= add_config(&new_list, config->lhs, dot,
                            config->link, NULL,
                            config->origin);
                    }
                }
                else {
                    break;
                }
            }
        }
    }
    stash_config_list(configs);
    *configs = new_list;
    new_list = NULL;
    if (found) {
        for (config = *configs; config; config = config->next) {
            dot = config->dot;
            if (rhs_all_nullable2(dot)) {
                if (config->origin) {
                    temp_configs = NULL;
                    add_config(&temp_configs, config->lhs, dot,
                        config->link, NULL,
                        config->origin);
                    close_configs(&temp_configs);
                    add_configs(configs, temp_configs, NULL);
                    free_config_list(&temp_configs);
                }
            }
        }
    }
    else {
        succeeded = 0;
        eof_label = find_symbol("END_OF_SLK_INPUT");
        if (lookahead_tokens != eof_label) {
            ;
            ;
            fatal_error(1706, "");
        }
    }
    return succeeded;
}
static uint
check_conflict_ambiguity(Conflict* conflict)
{
    register ConflictProduction* production,
        * prod_iter2;
    uint found = 0;
    production = conflict->configs;
    for (; production; production = production->next) {
        prod_iter2 = production->next;
        for (; prod_iter2; prod_iter2 = prod_iter2->next) {
            found = configs_equal(production->configs,
                prod_iter2->configs);
            if (found) {
                found = configs_have_nonterminal(
                    production->configs);
                if (found) {
                    found = AMBIGUOUS;
                    return found;
                }
            }
        }
    }
    return found;
}
static uint
resolve_conflict_production(Conflict* conflict,
    ConflictRow* row,
    ConflictProduction* production)
{
    register Config* config,
        * last_node;
    register Symbol** dot;
    Symbol** lhs,
        * eof_label,
        * lhs_symbol;
    uint status = 0,
        succeeded,
        has_entries = 0,
        lookahead_level = conflict->lookahead_level;
    Symbol** lookahead_tokens = conflict->lookahead_tokens;
    Config* temp_configs;
    uint production_number = production->number;
    Config** configs = &production->configs;
    lhs = productions[production_number];
    if (lookahead_level == 1) {
        dot = lhs;
        lhs_symbol = *lhs;
        for (++dot; *dot && ((*dot)->type == 3); ++dot)
            ;
        if (lhs_symbol->conditional) {
            if (verbose_level) {
                ;
                ;
            }
            return CONDITIONAL;
        }
        if (lhs_symbol->ignore_conflicts) {
            if (verbose_level) {
                ;
                ;
            }
            return IGNORED;
        }
        if (lhs_symbol->nullable_follows_self) {
            if (verbose_level) {
                ;
                ;
            }
            return AMBIGUOUS;
        }
        close_configs(configs);
    }
    advance_configs(configs);
    if (trace_level < -2) {
        ;
        ;
        ;
        ;
        print_configs(configs);
    }
    succeeded = advance_configs_for_token(configs, lhs,
        lookahead_tokens[lookahead_level - 1]);
    while (succeeded) {
        dot = lhs;
        for (++dot; *dot && ((*dot)->type == 3); ++dot)
            ;
        if (rhs_all_nullable2(dot)) {
            break;
        }
        for (; *dot; ++dot) {
        }
        temp_configs = NULL;
        add_config(&temp_configs, lhs, dot, NULL, NULL,
            CONFIG_BASE);
        close_configs(&temp_configs);
        add_configs(configs, temp_configs, NULL);
        free_config_list(&temp_configs);
        break;
    }
    for (config = *configs; config; config = config->next) {
        dot = config->dot;
        if (*dot) {
            has_entries = 1;
            break;
        }
    }
    if (!has_entries) {
        for (config = *configs; config; config = config->next) {
            dot = config->dot;
            if (!*dot) {
                if ((*config->lhs)->start_symbol) {
                    eof_label = find_symbol("END_OF_SLK_INPUT");
                    if (lookahead_tokens[lookahead_level - 1] != eof_label) {
                        has_entries = 1;
                    }
                }
            }
        }
    }
    if (trace_level < -1) {
        ;
        ;
        ;
        ;
        print_configs(configs);
    }
    if (verbose_level) {
        ;
        ;
    }
    if (has_entries) {
        for (config = *configs; config;) {
            dot = config->dot;
            if (*dot) {
                if (verbose_level) {
                    print_config(config->lhs, dot);
                }
                status |= merge_conflict_row(row, (*dot)->firsts,
                    conflict, production);
            }
            else if ((*config->lhs)->start_symbol) {
                if (verbose_level) {
                    print_config(config->lhs, dot);
                }
            }
            else {
                if (config == *configs) {
                    *configs = config->next;
                    free_config(config);
                    config = *configs;
                }
                else {
                    last_node = *configs;
                    for (; last_node->next; last_node = last_node->next) {
                        if (last_node->next == config) {
                            last_node->next = config->next;
                            free_config(config);
                            config = last_node->next;
                            break;
                        }
                    }
                }
                continue;
            }
            config = config->next;
        }
    }
    else {
        status = UNRESOLVABLE;
    }
    if (verbose_level) {
        ;
        ;
    }
    return status;
}
static uint
resolve_conflict(Conflict* conflict,
    uint level,
    int conflict_number,
    ConflictLevel* conflict_level)
{
    register ConflictProduction* production;
    Symbol* lhs;
    int token,
        old_production;
    uint status = 0;
    ConflictRow* row,
        * back_link;
    production = conflict->configs;
    old_production = production->number;
    lhs = *productions[old_production];
    row = new_conflict_row(conflict_level, lhs);
    back_link = (ConflictRow*)conflict->back_link;
    conflict->back_link = row;
    for (; production; production = production->next) {
        status |= resolve_conflict_production(conflict, row, production);
    }
    if (!status) {
        return status;
    }
    if (aggressive_check) {
        status |= check_conflict_ambiguity(conflict);
    }
    token = (conflict->lookahead_tokens[level - 1])->number;
    if (level == 1) {
        if ((status & RESOLVED_MASK)) {
            if (lhs->table) {
                set_table_entry(lhs->table, token, conflict_number);
            }
            else {
                resolve_lr_conflict(token, conflict_number);
            }
        }
    }
    else {
        if ((status & RESOLVED_MASK)) {
            set_conflict_entry(back_link, token, conflict_number);
        }
    }
    return status;
}
static void
apply_resolved_conflicts(uint* conflict_status,
    uint* chosen_productions)
{
    register uint* status = &conflict_status[1],
        * old_production = &chosen_productions[1];
    register Symbol* lhs;
    int conflict_number = 1;
    for (; *status != -1; ++status, ++old_production, ++conflict_number) {
        if (*status & AMBIGUOUS_OR_UNRESOLVABLE) {
            if (!*old_production) {
                ;
                ;
                fatal_error(1701, "no production number");
            }
            lhs = *productions[*old_production];
            if (verbose_level > 2) {
                ;
                ;
            }
            replace_conflict_entry(lhs->table, conflict_number,
                *old_production);
            remove_conflict(conflict_number);
        }
    }
}
uint resolve_conflicts(uint show_conflict_numbers,
    uint only_conflict,
    uint only_deep_conflict,
    uint* conflict_status)
{
    register Conflict* conflict;
    Symbol** lookahead_tokens;
    int conflict_number;
    uint level,
        resolved_level = 1,
        total_count = base_conflict_count,
        status,
        * chosen_productions;
    ConflictLevel* conflict_level;
    chosen_productions = calloc(base_conflict_count + 4, sizeof(uint));
    if (!chosen_productions) {
        fatal_error(1703, "out of memory");
    }
    for (level = 1; level < max_lookahead; ++level) {
        conflict = get_conflicts();
        if (!conflict) {
            break;
        }
        if (verbose_level) {
            ;
            ;
        }
        conflict_number = 0;
        conflict_level = new_conflict_level();
        for (; conflict; conflict = conflict->next) {
            ++conflict_number;
            if (!(verbose_level || (conflict_number % 2000))) {
                ;
                ;
                fflush(stdout);
            }
            if (only_conflict) {
                if (level == 1) {
                    if (conflict_number != only_conflict) {
                        continue;
                    }
                }
            }
            if (only_deep_conflict) {
                if (level > 1) {
                    if (conflict_number != only_deep_conflict) {
                        if (conflict->next) {
                            continue;
                        }
                    }
                }
            }
            status = conflict_status[conflict->number];
            if (status & AMBIGUOUS_OR_UNRESOLVABLE) {
                if (!only_conflict) {
                    continue;
                }
            }
            if (verbose_level) {
                ;
                ;
                lookahead_tokens = conflict->lookahead_tokens;
                while (*lookahead_tokens) {
                    ;
                    ;
                    ++lookahead_tokens;
                };
                ;
            }
            status = resolve_conflict(conflict, level,
                conflict_number, conflict_level);
            if ((status & STATUS_MASK) == RESOLVED) {
                resolved_level = level + 1;
                conflict->resolved = 1;
            }
            status |= level;
            if ((conflict_status[conflict->number] & LEVEL_MASK) == level) {
                conflict_status[conflict->number] |= status;
            }
            else {
                conflict_status[conflict->number] = status;
            }
            chosen_productions[conflict->number] = conflict->configs->number;
            if (verbose_level) {
                report_conflict_status(status, conflict->number,
                    conflict->configs->number, show_conflict_numbers);
            }
        }
        conflict_count += conflict_number;
        total_count = conflict_count;
        promote_resolved_conflicts();
    }
    apply_resolved_conflicts(conflict_status, chosen_productions);
    flush_stashed_configs();
    return resolved_level;
}
static struct
{
    Symbol** stack_top,
        * stack_base[63 + 1];
} recursion_stack = { recursion_stack.stack_base + 63 };
static Symbol* production_buffer[(1024 * 4) + 4];
static uint
not_on_recursion_stack(register Symbol* nonterminal)
{
    register Symbol** cursor = recursion_stack.stack_top;
    while (*cursor) {
        if (*cursor++ == nonterminal) {
            return 0;
        }
    }
    return 1;
}
static char*
unique_more_name(char* conflict_production)
{
    Symbol* symbol;
    uint count;
    uint number;
    static char name_buffer[512];
    char* cursor;
    count = strlen(conflict_production);
    if (count >= sizeof(name_buffer) - 12) {
        if (trace_level > 0) {
            print_productions();
        }
        printf("old string too long:\n  %s\n", conflict_production);
        fatal_error(1903, "");
    }
    sprintf(name_buffer, "more_%s", conflict_production);
    for (cursor = name_buffer; *cursor; ++cursor) {
    }
    for (number = 2; number < 1000; ++number) {
        symbol = find_symbol(name_buffer);
        if (symbol) {
            sprintf(cursor, "_%u", number);
        }
        else {
            break;
        }
    }
    return name_buffer;
}
static char*
unique_tail_name(char* conflict_production)
{
    Symbol* symbol;
    uint count;
    uint number;
    static char name_buffer[512];
    char* cursor;
    count = strlen(conflict_production);
    if (count >= sizeof(name_buffer) - 12) {
        if (trace_level > 0) {
            print_productions();
        }
        printf("old string too long:\n  %s\n", conflict_production);
        fatal_error(1904, "");
    }
    sprintf(name_buffer, "%s_tail", conflict_production);
    for (cursor = name_buffer; *cursor; ++cursor) {
    }
    for (number = 2; number < 1000; ++number) {
        symbol = find_symbol(name_buffer);
        if (symbol) {
            sprintf(cursor, "_%u", number);
        }
        else {
            break;
        }
    }
    return name_buffer;
}
static Symbol*
new_nonterminal(char* name)
{
    register Symbol* new_node;
    new_node = new_symbol(1, 0, name);
    register_symbol(new_node);
    return new_node;
}
static Symbol*
find_nonterminal(char* name)
{
    register Symbol* symbol = NULL;
    if (!name) {
        return symbol;
    }
    symbol = find_symbol(name);
    if (symbol) {
        if (symbol->type != 1) {
            printf("%s: not a nonterminal: type = %s \n", symbol->name,
                symbol_type_name(symbol->type));
            symbol = NULL;
        }
    }
    else {
        if (trace_level > 2) {
            printf("%s: not a symbol \n", name);
        }
    }
    return symbol;
}
static Symbol**
copy_symbols_ret(register Symbol** prod_a,
    register Symbol** prod_b)
{
    while ((*prod_a++ = *prod_b++)) {
    }
    return --prod_a;
}
static void
move_productions_before(Symbol* target_symbol,
    Symbol* source_symbol)
{
    register Symbol*** block,
        *** prod_iter;
    Symbol** production;
    for (;;) {
        if (trace_level > 3) {
            print_productions();
        }
        block = productions;
        prod_iter = NULL;
        while (*++block) {
            if (**block == source_symbol) {
                prod_iter = block;
                if (trace_level > 2) {
                    print_production("  first_production  = ",
                        *prod_iter);
                }
                break;
            }
        }
        if (!prod_iter) {
            break;
        }
        for (; *block; ++block) {
            if (**block == target_symbol) {
                production = *block;
                if (trace_level > 2) {
                    print_production("    move_production = ",
                        production);
                }
                delete_production_at(block);
                insert_production(production, prod_iter);
                break;
            }
        }
        if (!*block) {
            break;
        }
    }
}
static uint
direct_left_factor(Symbol* nonterminal)
{
    register Symbol*** prod_a,
        *** prod_b;
    char* name_buffer;
    uint number = 0,
        depth,
        mismatch = 0,
        prefix_length,
        shared_prefix = 0,
        changed = 0;
    Symbol*** prod_iter,
        *** last_production,
        ** dot,
        * lhs,
        * created_nonterminal,
        ** new_node,
        ** production[128];
    if (trace_level > 0) {
        printf("direct left factoring %s \n", nonterminal->name);
    }
    for (prod_b = productions; *++prod_b;) {
        if (**prod_b == nonterminal) {
            production[number] = *prod_b;
            if (number == 0) {
                prod_iter = prod_b;
            }
            if (++number >= 128) {
                if (trace_level > 2) {
                    print_productions();
                }
                printf("direct_left_factor: more than 127 productions "
                    "of nonterminal '%s'\n",
                    nonterminal->name);
                return changed;
            }
        }
    }
    if (number <= 1) {
        return changed;
    }
    last_production = &production[number - 1];
    prod_a = production;
    for (; prod_a < last_production; ++prod_a) {
        prod_b = prod_a;
        while (++prod_b <= last_production) {
            if (prod_b[0][1] == prod_a[0][1]) {
                shared_prefix = 1;
                break;
            }
        }
        if (shared_prefix) {
            break;
        }
    }
    if (!shared_prefix) {
        return changed;
    }
    changed = 1;
    lhs = **prod_a;
    prod_b = prod_a;
    while (++prod_b <= last_production) {
        if (prod_b[0][1] != prod_a[0][1]) {
            *prod_b = NULL;
        }
    }
    for (prefix_length = 1;; ++prefix_length) {
        prod_b = prod_a;
        while (++prod_b <= last_production) {
            if (!*prod_b) {
                continue;
            }
            if (prod_b[0][prefix_length] != prod_a[0][prefix_length]) {
                --prefix_length;
                mismatch = 1;
                break;
            }
        }
        if (mismatch) {
            break;
        }
    }
    new_node = production_buffer;
    dot = *prod_a;
    for (depth = 0; depth <= prefix_length; ++depth) {
        *new_node++ = *dot++;
    }
    name_buffer = unique_tail_name(lhs->name);
    created_nonterminal = new_nonterminal(name_buffer);
    *new_node++ = created_nonterminal;
    *new_node = NULL;
    new_node = copy_production(production_buffer);
    insert_production(new_node, prod_iter);
    prod_b = prod_a;
    for (; prod_b <= last_production; ++prod_b) {
        if (!*prod_b) {
            continue;
        }
        prod_b[0][0] = created_nonterminal;
        copy_symbols_ret(&prod_b[0][1],
            &prod_b[0][prefix_length + 1]);
    }
    move_productions_before(lhs, created_nonterminal);
    created_nonterminal->needs_direct_factoring = 1;
    update_nullable(created_nonterminal);
    return changed;
}
static uint
inline_production(Symbol** rhs_a,
    Symbol*** old_production)
{
    register Symbol*** block;
    Symbol** dot,
        * lhs = *rhs_a,
        ** new_node;
    uint inserted_count = 0;
    if (trace_level > 0) {
        printf("looking for %s productions \n", lhs->name);
    }
    for (block = productions; *++block;) {
        if (**block == lhs) {
            break;
        }
    }
    if (trace_level > 0) {
        print_production("first production: ", *block);
    }
    for (new_node = NULL; *block && **block == lhs; ++block) {
        new_node = production_buffer;
        dot = *old_production;
        for (; dot != rhs_a; ++dot) {
            *new_node++ = *dot;
        }
        new_node = copy_symbols_ret(new_node, &block[0][1]);
        copy_symbols_ret(new_node, ++dot);
        new_node = copy_production(production_buffer);
        if (insert_production(new_node, old_production)) {
            ++old_production;
            ++inserted_count;
            if (trace_level > 0) {
                print_production("inserted: ", new_node);
            }
        }
    }
    if (new_node) {
        if (trace_level > 0) {
            print_production("deleting: ", *old_production);
        }
        delete_production_at(old_production);
    }
    if (trace_level > 0) {
        putchar('\n');
    }
    return inserted_count;
}
static uint
indirect_left_factor(Symbol* nonterminal,
    uint aggressive)
{
    register Symbol** rhs_a,
        ** rhs_b;
    Symbol*** prod_a,
        *** prod_c,
        *** prod_d,
        ** epsilon_production = NULL,
        * lhs,
        * symbol;
    uint inserted_count,
        found = 0;
    if (trace_level > 0) {
        printf("indirect left factoring %s \n", nonterminal->name);
    }
    for (prod_a = productions; *++prod_a;) {
        if (**prod_a == nonterminal) {
            break;
        }
    }
    for (; *prod_a; ++prod_a) {
        if (**prod_a != nonterminal) {
            break;
        }
        for (prod_c = prod_a; *++prod_c;) {
            if (**prod_c != nonterminal) {
                break;
            }
            rhs_a = *prod_a;
            rhs_b = *prod_c;
            for (++rhs_a, ++rhs_b; *rhs_a && *rhs_b;) {
                if ((*rhs_a)->null_production && !epsilon_production) {
                    epsilon_production = rhs_a;
                    prod_d = prod_a;
                }
                if ((*rhs_b)->null_production && !epsilon_production) {
                    epsilon_production = rhs_b;
                    prod_d = prod_c;
                }
                if (*rhs_a == *rhs_b) {
                    ++rhs_a;
                    ++rhs_b;
                    continue;
                }
                if (aggressive) {
                    symbol = set_intersect_infinite((*rhs_a)->left_corners,
                        (*rhs_b)->left_corners);
                }
                else {
                    symbol = set_intersect((*rhs_a)->left_corners,
                        (*rhs_b)->left_corners);
                    if (!symbol) {
                        symbol = set_intersect((*rhs_a)->firsts,
                            (*rhs_b)->firsts);
                    }
                }
                if (symbol) {
                    found = 1;
                    break;
                }
                break;
            }
            if (found) {
                break;
            }
        }
        if (found) {
            break;
        }
    }
    if (!found) {
        if (needs_direct_factoring_single(0, nonterminal)) {
            return found;
        }
        if (epsilon_production) {
            inserted_count = inline_production(epsilon_production,
                prod_d);
            if (inserted_count) {
                found = 1;
            }
        }
        return found;
    }
    if (trace_level > 0) {
        printf("%s: common indirect symbol needs factoring in \n",
            symbol->name);
        print_config(*prod_a, rhs_a);
        print_config(*prod_c, rhs_b);
    }
    lhs = **prod_c;
    if (lhs == *rhs_b) {
        printf("configuration is left recursive, cannot factor: \n");
        print_config(*prod_c, rhs_b);
        found = 0;
        return found;
    }
    lhs = **prod_a;
    if (lhs == *rhs_a) {
        printf("configuration is left recursive, cannot factor: \n");
        print_config(*prod_a, rhs_a);
        found = 0;
        return found;
    }
    if (!left_derives(*rhs_a, *rhs_b, 0)) {
        inserted_count = inline_production(rhs_a, prod_a);
        if (inserted_count) {
            lhs->needs_direct_factoring = 1;
            --inserted_count;
            prod_c += inserted_count;
        }
    }
    if (!left_derives(*rhs_b, *rhs_a, 0)) {
        inserted_count = inline_production(rhs_b, prod_c);
        if (inserted_count) {
            lhs->needs_direct_factoring = 1;
        }
    }
    if (trace_level > 0) {
        print_productions_of(nonterminal);
        putchar('\n');
    }
    return found;
}
static uint
direct_left_factor_all(void)
{
    register Symbol** nonterminal;
    uint depth, outer_depth,
        errors = 0,
        changed;
    for (outer_depth = 0; outer_depth < 9; ++outer_depth) {
        if (!needs_direct_factoring(verbose_level)) {
            break;
        }
        for (nonterminal = nonterminals; *++nonterminal;) {
            if ((*nonterminal)->needs_direct_factoring) {
                for (depth = 0; depth < 29; ++depth) {
                    changed = direct_left_factor(*nonterminal);
                    if (!changed) {
                        break;
                    }
                }
                if (depth >= 29) {
                    printf("depth exceeded during direct left factoring"
                        " of %s\n",
                        (*nonterminal)->name);
                    errors = 1;
                }
            }
        }
    }
    if (outer_depth >= 9) {
        printf("outer depth exceeded during direct left factoring\n");
        errors = 1;
    }
    return errors;
}
static uint
indirect_left_factor_all(void)
{
    register Symbol** nonterminal;
    uint depth, outer_depth, pass,
        errors = 0,
        changed;
    for (pass = 0; pass < 3; ++pass) {
        for (outer_depth = 0; outer_depth < 9; ++outer_depth) {
            if (!needs_indirect_factoring(verbose_level)) {
                break;
            }
            for (nonterminal = nonterminals; *++nonterminal;) {
                if ((*nonterminal)->needs_indirect_factoring) {
                    for (depth = 0; depth < 29; ++depth) {
                        changed = indirect_left_factor(*nonterminal, 1);
                        if (!changed) {
                            break;
                        }
                    }
                    if (depth >= 29) {
                        printf("depth exceeded during indirect left factoring"
                            " of %s\n",
                            (*nonterminal)->name);
                        errors = 1;
                    }
                }
            }
        }
        if (outer_depth >= 9) {
            printf("outer depth exceeded during indirect left factoring\n");
            errors = 1;
        }
        if (!errors) {
            direct_left_factor_all();
        }
    }
    return errors;
}
static uint
has_direct_left_recursion(Symbol* symbol)
{
    register Symbol*** block = productions,
        ** dot;
    uint left_recursion_found = 0;
    while (*++block) {
        if (**block == symbol) {
            dot = *block;
            while (*++dot) {
                if ((*dot)->type == 2) {
                    break;
                }
                if ((*dot)->type == 1) {
                    if (*dot == symbol) {
                        left_recursion_found = 1;
                    }
                    break;
                }
            }
        }
        if (left_recursion_found) {
            break;
        }
    }
    return left_recursion_found;
}
static void
remove_direct_left_recursion(Symbol* recursive_nonterminal)
{
    register Symbol*** block,
        ** dot,
        ** new_node;
    Symbol** lhs,
        * created_more_nonterminal;
    uint type,
        has_other_productions = 0,
        production_length;
    Symbol* production_number[4];
    if (trace_level > 0) {
        printf("removing   direct left recursion from %s \n",
            recursive_nonterminal->name);
    }
    created_more_nonterminal = new_nonterminal(
        unique_more_name(recursive_nonterminal->name));
    created_more_nonterminal->nullable = 1;
    created_more_nonterminal->null_production = 1;
    for (block = productions; *++block;) {
        if (**block == recursive_nonterminal) {
            lhs = *block;
            dot = *block;
            while (*++dot) {
                type = (*dot)->type;
                if (type != 3) {
                    break;
                }
            }
            if (*dot == recursive_nonterminal) {
                *lhs = created_more_nonterminal;
                for (; *dot; ++dot) {
                    *dot = *(dot + 1);
                    if (!*dot) {
                        break;
                    }
                }
                *dot = created_more_nonterminal;
                dot = *block;
                while (*++dot) {
                    if ((*dot)->type != 3) {
                        break;
                    }
                }
                if (*dot == created_more_nonterminal) {
                    if (trace_level > 0) {
                        print_productions();
                    }
                    printf("  %s: infinite left recursion",
                        recursive_nonterminal->name);
                    fatal_error(1907, "");
                }
                if (trace_level > 2) {
                    print_productions();
                }
            }
            else {
                has_other_productions = 1;
                new_node = production_buffer;
                dot = *block;
                *new_node = *lhs;
                production_length = 2;
                while (*++new_node = *++dot) {
                    if (++production_length > (1024 * 4)) {
                        *new_node = NULL;
                        if (trace_level > 0) {
                            print_productions();
                        }
                        print_production(NULL, production_buffer);
                        fatal_error(1908, "production too long");
                    }
                }
                *new_node = created_more_nonterminal;
                *++new_node = NULL;
                *block = copy_production(production_buffer);
                if (trace_level > 2) {
                    print_productions();
                }
            }
        }
    }
    for (block = productions; *++block;) {
        if (**block == created_more_nonterminal) {
            if (!has_other_productions) {
                copy_symbols_ret(production_buffer, *block);
                *production_buffer = recursive_nonterminal;
                insert_production(copy_production(production_buffer), block);
            }
            while (*++block) {
                if (**block != created_more_nonterminal) {
                    break;
                }
            }
            break;
        }
    }
    production_number[0] = created_more_nonterminal;
    production_number[1] = NULL;
    insert_production(copy_production(production_number), block);
    move_productions_before(recursive_nonterminal, created_more_nonterminal);
    if (trace_level > 2) {
        print_productions();
    }
}
static void
expand_nonterminal_in(Symbol*** production,
    Symbol* expanded_nonterminal)
{
    register Symbol*** prod_b = productions,
        ** new_node,
        ** dot;
    uint production_length;
    if (trace_level > 1) {
        printf("  expand %s in: \n",
            expanded_nonterminal->name);
        print_production("   ", *production);
    }
    while (*++prod_b) {
        if (**prod_b == expanded_nonterminal) {
            dot = *prod_b;
            new_node = production_buffer;
            *new_node = **production;
            production_length = 2;
            while (*++new_node = *++dot) {
                if (++production_length > 256) {
                    *new_node = NULL;
                    print_production(NULL, production_buffer);
                    fatal_error(1909, "production too long\n"
                        "  probably need to remove recursion from "
                        "the rhs nonterminal first");
                }
            }
            --new_node;
            dot = *production;
            while (*++dot != expanded_nonterminal) {
                *++new_node = *dot;
                if (++production_length > 256) {
                    *new_node = NULL;
                    print_production(NULL, production_buffer);
                    fatal_error(1910, "production too long\n"
                        "  probably need to remove recursion from "
                        "the rhs nonterminal first");
                }
            }
            while (*++new_node = *++dot) {
                if (++production_length > 256) {
                    *new_node = NULL;
                    print_production(NULL, production_buffer);
                    fatal_error(1911, "production too long\n"
                        "  probably need to remove recursion from "
                        "the rhs nonterminal first");
                }
            }
            *++new_node = NULL;
            if (trace_level > 1) {
                print_production("  new production:\n   ", production_buffer);
            }
            new_node = copy_production(production_buffer);
            insert_production(new_node, production + 1);
            if (prod_b > production) {
                ++prod_b;
            }
        }
    }
}
static uint
remove_indirect_left_recursion(Symbol* nonterminal)
{
    register Symbol** dot,
        *** prod_b = productions;
    uint type,
        changed = 0;
    if (trace_level > 0) {
        printf("removing indirect left recursion from %s \n",
            nonterminal->name);
    }
    while (*++prod_b) {
        if (**prod_b == nonterminal) {
            dot = *prod_b;
            while (*++dot) {
                type = (*dot)->type;
                if (type == 3) {
                    continue;
                }
                if (type == 1) {
                    if (nonterminal != *dot) {
                        if (left_derives(nonterminal, *dot, 0)) {
                            expand_nonterminal_in(prod_b, *dot);
                            delete_production_at(prod_b);
                            --prod_b;
                            changed = 1;
                            if (trace_level > 2) {
                                print_productions();
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    if (has_direct_left_recursion(nonterminal)) {
        remove_direct_left_recursion(nonterminal);
        changed = 1;
    }
    return changed;
}
static void
remove_all_left_recursion(void)
{
    register Symbol** nonterminal;
    uint changed = 0,
        depth;
    for (depth = 0; depth < 30; ++depth) {
        changed = 0;
        for (nonterminal = nonterminals; *++nonterminal;) {
            if (has_direct_left_recursion(*nonterminal)) {
                remove_direct_left_recursion(*nonterminal);
                changed = 1;
            }
            if (left_derives(*nonterminal, *nonterminal, 0)) {
                changed |= remove_indirect_left_recursion(*nonterminal);
            }
        }
        if (!changed) {
            break;
        }
    }
    if (changed) {
        printf("remove left recursion is incomplete \n");
    }
}
static uint
remove_nonterminal(Symbol* removed_nonterminal)
{
    register Symbol** nonterminal = nonterminals + 1,
        *** block;
    uint changed = 0,
        found = 0;
    for (nonterminal = nonterminals; *++nonterminal;) {
        if (*nonterminal == removed_nonterminal) {
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("  %s: not found \n", removed_nonterminal->name);
        return changed;
    }
    for (; *nonterminal; ++nonterminal) {
        *nonterminal = *(nonterminal + 1);
    }
    changed = 1;
    --nonterminal_count;
    for (block = productions; *++block;) {
        if (**block == removed_nonterminal) {
            delete_production_at(block);
            --block;
        }
    }
    return changed;
}
static uint
remove_unused_nonterminals(void)
{
    register Symbol** nonterminal = nonterminals + 1;
    uint changed = 0;
    for (nonterminal = nonterminals; *++nonterminal;) {
        if ((*nonterminal)->unused) {
            changed |= remove_nonterminal(*nonterminal);
            --nonterminal;
        }
    }
    return changed;
}
static uint
substitute_nonterminal(Symbol* removed_nonterminal,
    uint substitute_nonterminal_flag,
    uint substitute_terminal_flag)
{
    register Symbol** nonterminal,
        ** dot,
        *** block;
    Symbol* replacement = NULL;
    uint changed = 0,
        epsilon_only = 1,
        found = 0;
    for (nonterminal = nonterminals; *++nonterminal;) {
        if (*nonterminal == removed_nonterminal) {
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("  %s: not found \n", removed_nonterminal->name);
        return changed;
    }
    for (block = productions; *++block;) {
        if (**block == removed_nonterminal) {
            dot = *block;
            if (*++dot) {
                if (substitute_terminal_flag && (*dot)->type == 2) {
                    replacement = *dot;
                }
                else if (substitute_nonterminal_flag && (*dot)->type == 1) {
                    replacement = *dot;
                }
                epsilon_only = 0;
            }
            break;
        }
    }
    if (!replacement) {
        if (epsilon_only) {
            printf("  %s: no replacement found \n", removed_nonterminal->name);
        }
        return changed;
    }
    delete_production_at(block);
    for (block = productions; *++block;) {
        dot = *block;
        while (*++dot) {
            if (*dot == removed_nonterminal) {
                *dot = replacement;
            }
        }
    }
    for (; *nonterminal; ++nonterminal) {
        *nonterminal = *(nonterminal + 1);
    }
    changed = 1;
    --nonterminal_count;
    return changed;
}
static uint
substitute_equivalents(uint substitute_nonterminal_flag,
    uint substitute_terminal_flag)
{
    register Symbol** nonterminal;
    uint changed = 0,
        result;
    for (nonterminal = nonterminals; *++nonterminal;) {
        if ((*nonterminal)->equivalent) {
            result = substitute_nonterminal(*nonterminal,
                substitute_nonterminal_flag,
                substitute_terminal_flag);
            if (result) {
                --nonterminal;
                changed = 1;
            }
        }
    }
    remove_duplicate_productions();
    return changed;
}
uint left_derives(Symbol* target_symbol,
    Symbol* source_symbol,
    uint display)
{
    register Symbol** symbol,
        *** block;
    Symbol* lhs;
    uint derives = 0;
    for (block = productions; *++block;) {
        symbol = *block;
        lhs = *symbol;
        if (lhs == source_symbol) {
            while (*++symbol) {
                if ((*symbol)->type == 1) {
                    if (*symbol == target_symbol) {
                        derives = 1;
                        break;
                    }
                    if (not_on_recursion_stack(*symbol)) {
                        if (recursion_stack.stack_top > recursion_stack.stack_base)
                            *--recursion_stack.stack_top = *symbol;
                        else
                            fatal_error(1901, "stack overflow");
                        derives = left_derives(target_symbol,
                            *symbol, display);
                        if (*recursion_stack.stack_top)
                            recursion_stack.stack_top++;
                        ;
                    }
                    if (derives) {
                        break;
                    }
                    if (!(*symbol)->nullable) {
                        break;
                    }
                }
                else if ((*symbol)->type == 2) {
                    if (*symbol == target_symbol) {
                        derives = 1;
                    }
                    break;
                }
                else if ((*symbol)->type == 3) {
                    continue;
                }
            }
        }
        if (derives) {
            if (display) {
                print_production("   ", *block);
            }
            break;
        }
    }
    return derives;
}
void display_left_derivations(char* name_cursor)
{
    register Symbol** target_symbol,
        ** source_symbol;
    uint count,
        line_length;
    Symbol* symbol;
    if (name_cursor) {
        symbol = find_symbol(name_cursor);
        if (symbol) {
            if (symbol->type == 1 || symbol->type == 2) {
                printf("%s is derived by: \n", symbol->name);
                line_length = 0;
                source_symbol = nonterminals;
                while (*++source_symbol) {
                    if (*source_symbol == symbol) {
                        continue;
                    }
                    if (left_derives(symbol, *source_symbol, 0)) {
                        count = strlen((*source_symbol)->name) + 2;
                        if (line_length + count > 79) {
                            line_length = 0;
                            putchar('\n');
                        }
                        printf("  %s", (*source_symbol)->name);
                        line_length += count;
                    }
                }
                putchar('\n');
                if (line_length) {
                    putchar('\n');
                }
            }
            else {
                printf("%s: invalid type = %s \n", symbol->name,
                    symbol_type_name(symbol->type));
            }
        }
        else {
            printf("%s: not a symbol name \n", name_cursor);
        }
    }
    else {
        printf("\n      Nonterminals Deriving Other Nonterminals \n\n");
        for (target_symbol = nonterminals; *++target_symbol;) {
            printf("%s is derived by: \n", (*target_symbol)->name);
            line_length = 0;
            source_symbol = nonterminals;
            while (*++source_symbol) {
                if (*source_symbol == *target_symbol) {
                    continue;
                }
                if (left_derives(*target_symbol, *source_symbol, 0)) {
                    count = strlen((*source_symbol)->name) + 2;
                    if (line_length + count > 79) {
                        line_length = 0;
                        putchar('\n');
                    }
                    printf("  %s", (*source_symbol)->name);
                    line_length += count;
                }
            }
            putchar('\n');
            if (line_length) {
                putchar('\n');
            }
        }
    }
}
void remove_unused(char* nonterminal_name)
{
    Symbol* nonterminal;
    uint depth,
        changed;
    mark_unused();
    if (nonterminal_name) {
        nonterminal = find_nonterminal(nonterminal_name);
        if (nonterminal) {
            if (nonterminal->unused) {
                printf("removing unused nonterminal %s \n",
                    nonterminal->name);
                remove_nonterminal(nonterminal);
            }
            else {
                printf("not unused: %s \n", nonterminal->name);
            }
        }
    }
    else {
        printf("removing unused nonterminals \n");
        for (depth = 0; depth < 9; ++depth) {
            changed = remove_unused_nonterminals();
            if (!changed) {
                break;
            }
            mark_unused();
        }
    }
}
void substitute_equivalent(char* nonterminal_name,
    uint substitute_nonterminal_flag,
    uint substitute_terminal_flag)
{
    Symbol* nonterminal;
    if (nonterminal_name) {
        nonterminal = find_nonterminal(nonterminal_name);
        if (nonterminal) {
            if (nonterminal->equivalent) {
                printf("removing equivalent nonterminal %s \n",
                    nonterminal->name);
                substitute_nonterminal(nonterminal,
                    substitute_nonterminal_flag,
                    substitute_terminal_flag);
            }
            else {
                printf("not equivalent: %s \n", nonterminal->name);
            }
        }
        else {
            printf("not a nonterminal: %s \n", nonterminal_name);
        }
    }
    else {
        printf("removing equivalent nonterminals \n");
        substitute_equivalents(substitute_nonterminal_flag,
            substitute_terminal_flag);
    }
}
void remove_left_recursion(char* nonterminal_name)
{
    Symbol* nonterminal;
    if (nonterminal_name) {
        nonterminal = find_nonterminal(nonterminal_name);
        if (nonterminal) {
            printf("removing left recursion from %s \n", nonterminal->name);
            remove_indirect_left_recursion(nonterminal);
        }
    }
    else {
        printf("removing left recursion \n");
        remove_all_left_recursion();
    }
}
uint check_duplicate_rhs(void)
{
    register Symbol*** block,
        *** prod_iter2;
    Symbol*** prod_iter;
    uint duplicates = 0;
    Symbol* lhs_a,
        * lhs_b,
        ** rhs_a,
        ** rhs_b;
    for (block = productions; *++block;) {
        prod_iter = block;
        prod_iter2 = block;
        rhs_a = *prod_iter;
        ++rhs_a;
        if (!*rhs_a) {
            continue;
        }
        while (*++prod_iter2) {
            rhs_b = *prod_iter2;
            ++rhs_b;
            if (productions_equal(rhs_a, rhs_b)) {
                lhs_a = **prod_iter;
                lhs_b = **prod_iter2;
                if (left_derives(lhs_a, lhs_b, 0)) {
                    duplicates = 1;
                    printf("duplicate rhs where %s derives %s:\n",
                        lhs_b->name, lhs_a->name);
                    print_production("   ", *prod_iter2);
                    print_production("   ", *prod_iter);
                    if (trace_level > 0) {
                        printf("\n  reverse derivation trace:\n");
                        left_derives(lhs_a, lhs_b, 1);
                    }
                    putchar('\n');
                }
                if (left_derives(lhs_b, lhs_a, 0)) {
                    duplicates = 1;
                    printf("duplicate rhs where %s derives %s:\n",
                        lhs_a->name, lhs_b->name);
                    print_production("   ", *prod_iter);
                    print_production("   ", *prod_iter2);
                    if (trace_level > 0) {
                        printf("\n  reverse derivation trace:\n");
                        left_derives(lhs_b, lhs_a, 1);
                    }
                    putchar('\n');
                }
            }
        }
    }
    if (duplicates) {
        putchar('\n');
    }
    return duplicates;
}
uint check_duplicate_productions(void)
{
    register Symbol*** block,
        *** prod_iter,
        *** prod_iter2;
    uint duplicates = 0;
    for (block = productions; *++block;) {
        prod_iter = block;
        prod_iter2 = block;
        while (*++prod_iter2) {
            if (**prod_iter2 != **prod_iter) {
                break;
            }
            if (productions_equal(*prod_iter2, *prod_iter)) {
                print_production("duplicate production:\n ", *prod_iter2);
                if (trace_level > 2) {
                    print_production("  first_production  = ",
                        *prod_iter);
                    print_production("   next_production  = ",
                        *prod_iter2);
                }
                duplicates = 1;
            }
        }
    }
    if (duplicates) {
        putchar('\n');
    }
    return duplicates;
}
void remove_duplicate_productions(void)
{
    register Symbol*** block,
        *** prod_iter,
        *** prod_iter2;
    if (trace_level > 3) {
        print_productions();
    }
    for (block = productions; *++block;) {
        prod_iter = block;
        prod_iter2 = block;
        while (*++prod_iter2) {
            if (productions_equal(*prod_iter2, *prod_iter)) {
                if (trace_level > 0) {
                    print_production("removing duplicate production:\n  ",
                        *prod_iter2);
                }
                if (trace_level > 2) {
                    print_production("  first_production  = ",
                        *prod_iter);
                    print_production("   next_production  = ",
                        *prod_iter2);
                }
                delete_production_at(prod_iter2);
                --prod_iter2;
            }
        }
    }
    if (trace_level > 3) {
        print_productions();
    }
}
uint left_factor_indirect(char* nonterminal_name)
{
    Symbol* nonterminal;
    uint depth,
        errors = 0,
        changed;
    if (nonterminal_name) {
        nonterminal = find_nonterminal(nonterminal_name);
        if (nonterminal) {
            if (!trace_level) {
                printf("left factoring %s \n", nonterminal->name);
            }
            for (depth = 0; depth < 29; ++depth) {
                changed = indirect_left_factor(nonterminal, 1);
                if (!changed) {
                    break;
                }
            }
            if (depth >= 29) {
                errors = 1;
            }
            else {
                for (depth = 0; depth < 29; ++depth) {
                    changed = direct_left_factor(nonterminal);
                    if (!changed) {
                        break;
                    }
                }
                if (depth >= 29) {
                    errors = 1;
                }
            }
        }
        else {
            printf("%s: not found \n", nonterminal_name);
        }
    }
    else {
        printf("left factoring grammar \n");
        errors = indirect_left_factor_all();
    }
    if (errors) {
        printf("left factoring was not completed\n");
    }
    return errors;
}
uint left_factor_direct(char* nonterminal_name)
{
    Symbol* nonterminal;
    uint depth,
        errors = 0,
        changed;
    if (nonterminal_name) {
        nonterminal = find_nonterminal(nonterminal_name);
        if (nonterminal) {
            if (!trace_level) {
                printf("direct left factoring %s \n", nonterminal->name);
            }
            for (depth = 0; depth < 29; ++depth) {
                changed = direct_left_factor(nonterminal);
                if (!changed) {
                    break;
                }
            }
            if (depth >= 29) {
                errors = 1;
            }
        }
        else {
            printf("%s: not found \n", nonterminal_name);
        }
    }
    else {
        printf("direct left factoring grammar \n");
        errors = direct_left_factor_all();
    }
    if (errors) {
        printf("direct left factoring was not completed\n");
    }
    return errors;
}
uint left_factor_old(char* nonterminal_name)
{
    Symbol* nonterminal;
    uint depth,
        errors = 0,
        changed;
    if (nonterminal_name) {
        nonterminal = find_nonterminal(nonterminal_name);
        if (nonterminal) {
            if (!trace_level) {
                printf("left factoring %s \n", nonterminal->name);
            }
            for (depth = 0; depth < 29; ++depth) {
                changed = indirect_left_factor(nonterminal, 0);
                if (!changed) {
                    break;
                }
            }
            if (depth >= 29) {
                errors = 1;
            }
            else {
                for (depth = 0; depth < 29; ++depth) {
                    changed = direct_left_factor(nonterminal);
                    if (!changed) {
                        break;
                    }
                }
                if (depth >= 29) {
                    errors = 1;
                }
            }
        }
        else {
            printf("%s: not found \n", nonterminal_name);
        }
    }
    else {
        printf("nonterminal was not specified\n");
    }
    if (errors) {
        printf("left factoring was not completed\n");
    }
    return errors;
}
typedef struct Symbol** Production;
typedef struct ProductionList
{
    Production* list;
    int conflict_cursor;
    int count;
    int capacity;
    int increment;
    Production(*list_next)(struct ProductionList*);
    void (*list_append)(struct ProductionList*, Production production);
    void (*list_print)(struct ProductionList*);
    void (*list_reset)(struct ProductionList*);
    void (*list_free)(struct ProductionList*);
} ProductionList;
void list_init(ProductionList* list);
static Symbol* production_buffer[(1024 * 4) + 4];
static ProductionList ebnf_production_list;
static char*
make_ebnf_name(Symbol** group_begin,
    Symbol** cursor,
    char* suffix,
    int unique_names)
{
    int count,
        name_length = 0;
    Symbol* symbol;
    uint number;
    static char name_buffer[(2 * 1024)];
    register char* name = name_buffer;
    for (++group_begin; group_begin < cursor; ++group_begin) {
        if ((*group_begin)->type == 3) {
            continue;
        }
        count = sprintf(name, "%s_", (*group_begin)->name);
        if (count > 0) {
            name += count;
            name_length += count;
        }
        else {
            fatal_error(2201, "sprintf failed");
        }
        if (name_length >= sizeof(name_buffer) - 12) {
            printf("EBNF name too long:\n  %s\n", name_buffer);
            fatal_error(2202, "");
        }
    }
    for (name = name_buffer; *name; ++name) {
        if (*name == '\\') {
            if (*(name + 1) == '\\') {
                strcpy(name, name + 2);
            }
            else {
                strcpy(name, name + 1);
            }
        }
    }
    for (name = name_buffer; *name; ++name) {
        if (*name == '\\') {
            *name = '_';
        }
        if (*name == '_') {
            if (*(name + 1) == '_') {
                strcpy(name, name + 1);
            }
        }
    }
    sprintf(name, "%s", suffix);
    if (unique_names) {
        for (number = 2; number < 1000; ++number) {
            symbol = find_symbol(name_buffer);
            if (symbol) {
                sprintf(name, "%u_%s", number, suffix);
            }
            else {
                break;
            }
        }
    }
    return name_buffer;
}
static Symbol*
expand_ebnf_group(Symbol** group_begin,
    Symbol** cursor,
    Symbol* trailing_action)
{
    register Symbol** production = production_buffer;
    char* name,
        * suffix = "???";
    int ebnf_optional = 0;
    int unique_names = unique_ebnf_names;
    Symbol* created_group_nonterminal,
        * production_parts[8];
    switch ((*cursor)->number) {
    case -2:
        suffix = "opt";
        ebnf_optional = 1;
        break;
    case -4:
    case -5:
        suffix = "*";
        break;
    default:
        fatal_error(2203, "invalid end token");
    }
    name = make_ebnf_name(group_begin, cursor, suffix, unique_names);
    created_group_nonterminal = find_symbol(name);
    if (created_group_nonterminal) {
        if (unique_names) {
            printf("EBNF name already exists:\n  %s\n", name);
            fatal_error(2204, "");
        }
    }
    else {
        created_group_nonterminal = new_symbol(1, 0, name);
        register_symbol(created_group_nonterminal);
        created_group_nonterminal->ebnf_nonterminal = 1;
        if (ebnf_optional) {
            created_group_nonterminal->ebnf_optional = 1;
        }
    }
    switch ((*cursor)->number) {
    case -2:
        *production++ = created_group_nonterminal;
        while (++group_begin < cursor) {
            *production++ = *group_begin;
        }
        *production = NULL;
        ebnf_production_list.list_append(&ebnf_production_list, copy_production(production_buffer));
        production = production_parts;
        *production++ = created_group_nonterminal;
        if (trailing_action) {
            *production++ = trailing_action;
        }
        *production = NULL;
        ebnf_production_list.list_append(&ebnf_production_list, copy_production(production_parts));
        break;
    case -4:
    case -5:
        *production++ = created_group_nonterminal;
        while (++group_begin < cursor) {
            *production++ = *group_begin;
        }
        *production++ = created_group_nonterminal;
        *production = NULL;
        ebnf_production_list.list_append(&ebnf_production_list, copy_production(production_buffer));
        production = production_parts;
        *production++ = created_group_nonterminal;
        if (trailing_action) {
            *production++ = trailing_action;
        }
        *production = NULL;
        ebnf_production_list.list_append(&ebnf_production_list, copy_production(production_parts));
        break;
    }
    return created_group_nonterminal;
}
static int ebnf_error = 0;
static Symbol**
expand_ebnf_symbols(register Symbol** dot)
{
    register Symbol** group_begin = NULL,
        ** cursor = NULL;
    Symbol* created_symbol,
        * trailing_action;
    uint end_token;
    for (; *dot; ++dot) {
        if ((*dot)->ebnf_token) {
            switch ((*dot)->number) {
            case -1:
            case -3:
                group_begin = dot;
                cursor = expand_ebnf_symbols(dot + 1);
                if (!(cursor && *cursor)) {
                    puts("missing end ebnf marker");
                    ebnf_error = 1;
                    break;
                }
                end_token = (*cursor)->number;
                if ((*dot)->number == -1) {
                    if (end_token != -2) {
                        puts("missing ]");
                        ebnf_error = 1;
                        break;
                    }
                }
                else {
                    if (end_token != -4 && end_token != -5) {
                        puts("missing }");
                        ebnf_error = 1;
                        break;
                    }
                }
                trailing_action = *(cursor + 1);
                if (trailing_action && trailing_action->type != 3) {
                    trailing_action = NULL;
                }
                created_symbol = expand_ebnf_group(group_begin, cursor, trailing_action);
                if (end_token != -5) {
                    *group_begin = created_symbol;
                    if (trailing_action) {
                        ++cursor;
                    }
                    while (*++group_begin = *++cursor) {
                    }
                }
                else {
                    *cursor = created_symbol;
                    while (*group_begin = *(group_begin + 1)) {
                        ++group_begin;
                    }
                    dot = --cursor;
                    if (trailing_action) {
                        group_begin = cursor + 1;
                        while (*group_begin = *(group_begin + 1)) {
                            ++group_begin;
                        }
                    }
                }
                break;
            case -2:
            case -4:
            case -5:
                return dot;
            default:
                printf("ebnf token = %d  %s\n", (*dot)->number, (*dot)->name);
                fatal_error(2205, "invalid ebnf symbol");
            }
        }
    }
    return cursor;
}
void expand_ebnf(void)
{
    register Symbol*** block = productions;
    Symbol** dot,
        ** production;
    list_init(&ebnf_production_list);
    while (*++block) {
        dot = *block;
        ebnf_error = 0;
        expand_ebnf_symbols(++dot);
        if (ebnf_error) {
            print_production(" ", *block);
            note_error();
        }
    }
    while (production = ebnf_production_list.list_next(&ebnf_production_list)) {
        add_production(production);
    }
    ebnf_production_list.list_free(&ebnf_production_list);
}
static void
copy_symbols2(register Symbol** dst_symbols,
    register Symbol** src_symbols)
{
    while ((*dst_symbols++ = *src_symbols++)) {
    }
}
static Symbol***
find_production_of(register Symbol* lhs)
{
    register Symbol*** block = productions;
    while (*++block) {
        if (lhs == **block) {
            break;
        }
    }
    return block;
}
static Symbol**
restore_ebnf_nonterminal(register Symbol** dot)
{
    register Symbol** cursor = production_buffer;
    Symbol* lhs,
        ** rhs_b,
        *** block,
        * open_marker,
        * close_marker;
    *cursor = *dot;
    ++cursor;
    ++dot;
    for (; *dot; ++dot) {
        if ((*dot)->ebnf_nonterminal) {
            block = find_production_of(*dot);
            rhs_b = *block;
            lhs = *rhs_b;
            if (lhs->ebnf_optional) {
                open_marker = find_symbol("\\[");
                close_marker = find_symbol("\\]");
            }
            else {
                open_marker = find_symbol("\\{");
                close_marker = find_symbol("\\}");
                if (!close_marker) {
                    close_marker = new_symbol(2, -4, "\\}");
                    close_marker->ebnf_token = 1;
                }
            }
            *cursor = open_marker;
            ++cursor;
            for (++rhs_b; *rhs_b; ++rhs_b, ++cursor) {
                *cursor = *rhs_b;
            }
            --rhs_b;
            if (lhs == *rhs_b) {
                --cursor;
            }
            *cursor = close_marker;
            ++cursor;
            rhs_b = *++block;
            if (*++rhs_b) {
                *cursor = *rhs_b;
                ++cursor;
            }
        }
        else {
            *cursor = *dot;
            ++cursor;
        }
    }
    *cursor = NULL;
    return production_buffer;
}
static Symbol**
convert_star_to_plus(register Symbol** dot)
{
    register Symbol** cursor = production_buffer;
    Symbol** production = NULL,
        ** dot_pos,
        ** saved_out,
        ** close_pos,
        * open_marker,
        * plus_marker,
        * close_marker;
    close_marker = find_symbol("\\}");
    if (!close_marker) {
        return production;
    }
    open_marker = find_symbol("\\{");
    plus_marker = find_symbol("\\}+");
    if (!plus_marker) {
        plus_marker = new_symbol(2, -5, "\\}+");
        plus_marker->ebnf_token = 1;
    }
    *cursor = *dot;
    ++cursor;
    ++dot;
    for (; *dot; ++dot) {
        if (*dot == close_marker) {
            dot_pos = dot;
            saved_out = cursor;
            close_pos = dot;
            while (*--cursor != open_marker) {
            }
            for (--dot, --cursor; *dot != open_marker; --dot, --cursor) {
                if (cursor < production_buffer) {
                    break;
                }
                if (*dot != *cursor) {
                    break;
                }
            }
            if (*dot == open_marker) {
                *close_pos = plus_marker;
                copy_symbols2(cursor + 1, dot);
                production = production_buffer;
                break;
            }
            else {
                dot = dot_pos;
                cursor = saved_out;
                *cursor = *dot;
                ++cursor;
            }
        }
        else {
            *cursor = *dot;
            ++cursor;
        }
    }
    return production;
}
void restore_ebnf(void)
{
    register Symbol*** block;
    register Symbol** dot;
    Symbol** production;
    int changed = 1;
    for (changed = 1; changed;) {
        changed = 0;
        for (block = productions; *++block;) {
            dot = *block;
            if ((*dot)->ebnf_nonterminal) {
                continue;
            }
            while (*++dot) {
                if ((*dot)->ebnf_nonterminal) {
                    production = restore_ebnf_nonterminal(*block);
                    *block = copy_production(production);
                    changed = 1;
                    break;
                }
            }
        }
    }
    for (changed = 1; changed;) {
        changed = 0;
        for (block = productions; *++block;) {
            dot = *block;
            if ((*dot)->ebnf_nonterminal) {
                continue;
            }
            while (*++dot) {
                if ((*dot)->ebnf_token) {
                    production = convert_star_to_plus(*block);
                    if (production) {
                        *block = copy_production(production);
                        changed = 1;
                    }
                    break;
                }
            }
        }
    }
}
struct
{
    char** stack_top,
        * stack_base[511 + 1];
} brace_stack = { brace_stack.stack_base + 511 };
static char*
emit_text(char* prefix,
    register char* stack_base,
    char* cursor,
    register char* out_cursor)
{
    for (; *prefix; ++prefix) {
        *out_cursor++ = *prefix;
    }
    if (stack_base) {
        for (; stack_base <= cursor; ++stack_base) {
            *out_cursor++ = *stack_base;
        }
    }
    return out_cursor;
}
static int
skip_ws_match(register char* cursor,
    register char* str)
{
    while ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
        ++cursor;
    }
    while (*str && *cursor == *str) {
        ++cursor;
        ++str;
    }
    return (!*str);
}
int convert_iso_grammar(char* input_name,
    char* output_name)
{
    register char* cursor;
    char* stack_base;
    char* token_start = NULL;
    char* token_end;
    char* brace_mark;
    char* segment_start;
    char* prefix = " ";
    char last_bar = '\0';
    int line_number = 1;
    int bracket_depth = 0;
    FILE* file;
    char* grammar_text;
    char* out_buffer;
    char* out_cursor;
    uint repeat_flag;
    uint status = 0;
    size_t data_size;
    grammar_text = read_file(input_name, &data_size);
    cursor = grammar_text;
    if (!grammar_text) {
        perror(input_name);
        exit(1);
    }
    file = fopen(output_name, "wb");
    if (!file) {
        perror(output_name);
        exit(1);
    }
    out_buffer = (char*)malloc(data_size * 4);
    out_cursor = out_buffer;
    if (!out_cursor) {
        printf("malloc failed for size %lu\n", (ulong)(data_size * 4));
        exit(1);
    }
    for (;;) {
        stack_base = cursor;
        switch (*cursor++) {
        case 0:
            *out_cursor++ = '\n';
            goto convert_end;
        case 9:
        case 13:
            goto convert_whitespace;
        case 10:
            ++line_number;
            stack_base = cursor + 1;
            goto convert_whitespace;
        case 32:
        convert_whitespace:
            *(cursor - 1) = ' ';
            while ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                if (*cursor == '\n') {
                    ++line_number;
                    stack_base = cursor + 1;
                }
                *cursor = ' ';
                ++cursor;
            }
            break;
        case '/':
            if (*cursor == '/') {
                while (*cursor && *cursor != '\n') {
                    ++cursor;
                }
                goto convert_whitespace;
            }
            goto convert_default;
        case '$':
            goto convert_identifier;
        case '[':
        case '{':
            ++bracket_depth;
            goto convert_default;
        case ']':
        case '}':
            if (bracket_depth > 0) {
                --bracket_depth;
                if (!bracket_depth) {
                    prefix = " ";
                }
            }
            else {
                printf("%d: extra '%c' bracket\n", line_number,
                    *(cursor - 1));
            }
            goto convert_default;
        case '|':
            if (bracket_depth > 0) {
                if (prefix != "~") {
                    for (; segment_start < out_cursor; ++segment_start) {
                        if (*segment_start == ' ') {
                            *segment_start = '~';
                        }
                    }
                }
                *out_cursor++ = '|';
                prefix = "~";
            }
            else {
                out_cursor = emit_text("\n   ", NULL, NULL, out_cursor);
                last_bar = '|';
            }
            break;
        case '<':
            if (!(((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9')))) {
                goto convert_default;
            }
            token_start = stack_base;
            while (*cursor) {
                if (*cursor == ' ') {
                    *cursor = '_';
                }
                else if (*cursor == '\r' || *cursor == '\n') {
                    *cursor = '>';
                    break;
                }
                else if (*cursor == '>') {
                    break;
                }
                ++cursor;
            }
            token_end = cursor;
            ++cursor;
            repeat_flag = 0;
            if (*cursor == '.' && *(cursor + 1) == '.' && *(cursor + 2) == '.') {
                cursor += 3;
                repeat_flag = 1;
            }
            if (skip_ws_match(cursor, "::=") || skip_ws_match(cursor, ":=")) {
                if (last_bar == '|') {
                    out_cursor = emit_text("_epsilon_", NULL, NULL, out_cursor);
                }
                out_cursor = emit_text("\n\n", token_start, token_end, out_cursor);
                if (repeat_flag) {
                    printf("%d: repeating nonterminal on lhs\n",
                        line_number);
                }
            }
            else if (repeat_flag) {
                out_cursor = emit_text(prefix, "{", "{", out_cursor);
                out_cursor = emit_text(prefix, token_start, token_end, out_cursor);
                out_cursor = emit_text(prefix, NULL, NULL, out_cursor);
                out_cursor = emit_text("}+", NULL, NULL, out_cursor);
            }
            else {
                out_cursor = emit_text(prefix, token_start, token_end, out_cursor);
            }
            last_bar = '\0';
            break;
        default:
        convert_default:
            if ((((*stack_base >= 'a' && *stack_base <= 'z')) || ((*stack_base >= 'A' && *stack_base <= 'Z')) || ((*stack_base >= '0' && *stack_base <= '9')))) {
                goto convert_identifier;
            }
            last_bar = '\0';
            switch (*stack_base) {
            case ':':
                if (*cursor == ':') {
                    if (*(cursor + 1) == '=') {
                        ++cursor;
                        out_cursor = emit_text(prefix, stack_base, cursor, out_cursor);
                        ++cursor;
                        break;
                    }
                }
                else if (*cursor == '=') {
                    out_cursor = emit_text(prefix, stack_base, cursor, out_cursor);
                    ++cursor;
                    break;
                }
                goto convert_operator;
            case ',':
            case ';':
            case '(':
            case ')':
            case ']':
                out_cursor = emit_text(prefix, stack_base, stack_base, out_cursor);
                break;
            case '[':
                out_cursor = emit_text(prefix, stack_base, stack_base, out_cursor);
                segment_start = out_cursor + 1;
                break;
            case '{':
                out_cursor = emit_text(prefix, stack_base, stack_base, out_cursor);
                (brace_stack.stack_top > brace_stack.stack_base ? *--brace_stack.stack_top = out_cursor - 1 : 0);
                segment_start = out_cursor + 1;
                break;
            case '}':
                repeat_flag = 0;
                if (*cursor == '.' && *(cursor + 1) == '.' &&
                    *(cursor + 2) == '.') {
                    cursor += 3;
                    repeat_flag = 1;
                }
                if (repeat_flag) {
                    out_cursor = emit_text(prefix, NULL, NULL, out_cursor);
                    out_cursor = emit_text("}+", NULL, NULL, out_cursor);
                }
                else {
                    brace_mark = (*brace_stack.stack_top ? *brace_stack.stack_top++ : 0);
                    if (brace_mark) {
                        *brace_mark = ' ';
                    }
                    else {
                        printf("%d: extra end '}...'\n", line_number);
                    }
                }
                break;
            default:
            convert_operator:
                while (!((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f') || (((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9'))))) {
                    if (*cursor == '|' ||
                        *cursor == ',' ||
                        *cursor == ';' ||
                        *cursor == '(' ||
                        *cursor == ')' ||
                        *cursor == '[' ||
                        *cursor == ']' ||
                        *cursor == '{' ||
                        *cursor == '}') {
                        break;
                    }
                    ++cursor;
                }
                if ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                    *cursor = ' ';
                }
                if ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f') || (((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9'))) ||
                    *cursor == '|' ||
                    *cursor == ',' ||
                    *cursor == ';' ||
                    *cursor == '(' ||
                    *cursor == ')' ||
                    *cursor == '[' ||
                    *cursor == ']' ||
                    *cursor == '{' ||
                    *cursor == '}') {
                    out_cursor = emit_text(prefix, stack_base, cursor - 1, out_cursor);
                }
                else {
                    out_cursor = emit_text(prefix, stack_base, cursor, out_cursor);
                }
            }
            break;
        convert_identifier:
            token_start = stack_base;
            while (*cursor) {
                if (!((((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9'))) || *cursor == '_')) {
                    break;
                }
                ++cursor;
            }
            token_end = cursor - 1;
            out_cursor = emit_text(prefix, token_start, token_end, out_cursor);
            last_bar = '\0';
            break;
        }
    }
convert_end:
    if (bracket_depth != 0) {
        printf("unbalanced brackets\n");
    }
    fwrite(out_buffer, 1, out_cursor - out_buffer, file);
    fclose(file);
    return status;
}
int convert_ieee_grammar(char* input_name,
    char* output_name)
{
    register char* cursor;
    char* stack_base;
    char* token_start = NULL;
    char* token_end;
    char* segment_start;
    char* prefix = " ";
    char last_bar = '\0';
    int line_number = 1;
    int bracket_depth = 0;
    FILE* file;
    char* grammar_text;
    char* out_buffer;
    char* out_cursor;
    uint status = 0;
    size_t data_size;
    grammar_text = read_file(input_name, &data_size);
    cursor = grammar_text;
    if (!grammar_text) {
        perror(input_name);
        exit(1);
    }
    file = fopen(output_name, "wb");
    if (!file) {
        perror(output_name);
        exit(1);
    }
    out_buffer = (char*)malloc(data_size * 4);
    out_cursor = out_buffer;
    if (!out_cursor) {
        printf("malloc failed for size %lu\n", (ulong)(data_size * 4));
        exit(1);
    }
    for (;;) {
        stack_base = cursor;
        switch (*cursor++) {
        case 0:
            *out_cursor++ = '\n';
            goto convert_end;
        case 9:
        case 13:
            goto convert_whitespace;
        case 10:
            ++line_number;
            stack_base = cursor + 1;
            goto convert_whitespace;
        case 32:
        convert_whitespace:
            *(cursor - 1) = ' ';
            while ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                if (*cursor == '\n') {
                    ++line_number;
                    stack_base = cursor + 1;
                }
                *cursor = ' ';
                ++cursor;
            }
            break;
        case '/':
            if (*cursor == '/') {
                while (*cursor && *cursor != '\n') {
                    ++cursor;
                }
                goto convert_whitespace;
            }
            goto convert_default;
        case '$':
            goto convert_identifier;
        case '[':
        case '{':
            ++bracket_depth;
            goto convert_default;
        case ']':
        case '}':
            if (bracket_depth > 0) {
                --bracket_depth;
                if (!bracket_depth) {
                    prefix = " ";
                }
            }
            else {
                printf("%d: extra '%c' bracket\n", line_number,
                    *(cursor - 1));
            }
            goto convert_default;
        case '|':
            if (bracket_depth > 0) {
                if (prefix != "~") {
                    for (; segment_start < out_cursor; ++segment_start) {
                        if (*segment_start == ' ') {
                            *segment_start = '~';
                        }
                    }
                }
                *out_cursor++ = '|';
                prefix = "~";
            }
            else {
                out_cursor = emit_text("\n   ", NULL, NULL, out_cursor);
                last_bar = '|';
            }
            break;
        default:
        convert_default:
            if ((((*stack_base >= 'a' && *stack_base <= 'z')) || ((*stack_base >= 'A' && *stack_base <= 'Z')) || ((*stack_base >= '0' && *stack_base <= '9')))) {
                goto convert_identifier;
            }
            last_bar = '\0';
            switch (*stack_base) {
            case ':':
                if (*cursor == ':') {
                    if (*(cursor + 1) == '=') {
                        ++cursor;
                        out_cursor = emit_text(prefix, stack_base, cursor, out_cursor);
                        ++cursor;
                        break;
                    }
                }
                else if (*cursor == '=') {
                    out_cursor = emit_text(prefix, stack_base, cursor, out_cursor);
                    ++cursor;
                    break;
                }
                goto convert_operator;
            case ',':
            case ';':
            case '(':
            case ')':
            case ']':
            case '}':
                out_cursor = emit_text(prefix, stack_base, stack_base, out_cursor);
                break;
            case '[':
            case '{':
                out_cursor = emit_text(prefix, stack_base, stack_base, out_cursor);
                segment_start = out_cursor + 1;
                break;
            default:
            convert_operator:
                while (!((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f') || (((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9'))))) {
                    if (*cursor == '|' ||
                        *cursor == ',' ||
                        *cursor == ';' ||
                        *cursor == '(' ||
                        *cursor == ')' ||
                        *cursor == '[' ||
                        *cursor == ']' ||
                        *cursor == '{' ||
                        *cursor == '}') {
                        break;
                    }
                    ++cursor;
                }
                if ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f')) {
                    *cursor = ' ';
                }
                if ((*cursor == ' ' || *cursor == '\n' || *cursor == '\r' || *cursor == '\t' || *cursor == '\v' || *cursor == '\f') || (((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9'))) ||
                    *cursor == '|' ||
                    *cursor == ',' ||
                    *cursor == ';' ||
                    *cursor == '(' ||
                    *cursor == ')' ||
                    *cursor == '[' ||
                    *cursor == ']' ||
                    *cursor == '{' ||
                    *cursor == '}') {
                    out_cursor = emit_text(prefix, stack_base, cursor - 1, out_cursor);
                }
                else {
                    out_cursor = emit_text(prefix, stack_base, cursor, out_cursor);
                }
            }
            break;
        convert_identifier:
            token_start = stack_base;
            while (*cursor) {
                if (!((((*cursor >= 'a' && *cursor <= 'z')) || ((*cursor >= 'A' && *cursor <= 'Z')) || ((*cursor >= '0' && *cursor <= '9'))) || *cursor == '_')) {
                    break;
                }
                ++cursor;
            }
            token_end = cursor - 1;
            if (skip_ws_match(cursor, "::=") || skip_ws_match(cursor, ":=")) {
                if (last_bar == '|') {
                    out_cursor = emit_text("_epsilon_", NULL, NULL, out_cursor);
                }
                out_cursor = emit_text("\n\n", token_start, token_end, out_cursor);
            }
            else {
                out_cursor = emit_text(prefix, token_start, token_end, out_cursor);
            }
            last_bar = '\0';
            break;
        }
    }
convert_end:
    if (bracket_depth != 0) {
        printf("unbalanced brackets\n");
    }
    fwrite(out_buffer, 1, out_cursor - out_buffer, file);
    fclose(file);
    return status;
}
char*
read_file(char* path_name,
    size_t* data_size)
{
    size_t file_size;
    FILE* file;
    char* file_buffer = NULL;
    file = fopen(path_name, "rb");
    if (file) {
        fseek(file, 0L, 2);
        file_size = ftell(file);
        rewind(file);
        file_buffer = (char*)malloc(file_size + 4);
        if (file_buffer) {
            *data_size = fread(file_buffer, 1, file_size, file);
            if (*data_size == file_size) {
                file_buffer[file_size] = '\0';
                file_buffer[file_size + 1] = '\0';
            }
            else {
                free(file_buffer);
                file_buffer = NULL;
            }
        }
        else {
            printf("malloc failed for size %lu\n", (ulong)(*data_size * 4));
        }
        fclose(file);
    }
    return file_buffer;
}
// ================ C/C++ output code templates ================
static char c_token_error_action_decls[] =
"typedef struct {\n"
"    slk_size_t  (*get)  ( void );\n"
"    slk_size_t  (*peek) ( int level );\n"
"} xxxToken;\n"
"\n"
"typedef struct {\n"
"    slk_size_t  (*mismatch) ( slk_size_t symbol, slk_size_t token );\n"
"    slk_size_t  (*no_entry) ( slk_size_t symbol, slk_size_t token, int level );\n"
"    void        (*input_left) ( void );\n"
"    void        (*message) ( char  *message );\n"
"} xxxError;\n"
"\n"
"typedef struct {\n"
"    void  (*execute) ( slk_size_t action );\n"
"    void  (*predict) ( slk_size_t entry );\n"
"    void  (*reduce)  ( slk_size_t entry );\n"
"    void  (*state)   ( slk_size_t state );\n"
"} xxxAction;\n";
static char c_action_includes[] =
"#include \"xxxToken.h\"\n"
"#include \"xxxError.h\"\n"
"#include \"xxxAction.h\"\n";
static char c_push_pop_macros[] =
"#define SLK_PUSH(symbol,stack,top) if ( top > stack ) { *--top = symbol; } else { message( error, \"stack overflow\\n\", tokens ); }\n"
"#define SLK_POP(top)   (*top ? *top++ : 0)\n";
static char c_symbol_type_decl[] =
"#define NOT_A_SYMBOL       0\n"
"#define NONTERMINAL_SYMBOL 1\n"
"#define TERMINAL_SYMBOL    2\n"
"#define ACTION_SYMBOL      3\n\n"
"int xxxGetSymbolType ( slk_size_t symbol )";
static char c_symbol_type_body[] =
"{\n"
"   int   symbol_type = NOT_A_SYMBOL;\n"
"\n"
"   if ( symbol >= START_ACTION  &&  symbol < END_ACTION ) {\n"
"       symbol_type = ACTION_SYMBOL;\n"
"   } else if ( symbol >= START_SYMBOL ) {\n"
"       symbol_type = NONTERMINAL_SYMBOL;\n"
"   } else if ( symbol > 0 ) {\n"
"       symbol_type = TERMINAL_SYMBOL;\n"
"   }\n"
"   return  symbol_type;\n"
"}\n";
static char c_production_array_decl[] =
"slk_size_t *xxxGetProductionArray ( slk_size_t   production_number )";
static char c_production_array_body[] =
"{\n"
"    return   &Production [ Production_row [production_number] ];\n"
"}\n";
static char c_get_production_decl[] =
"slk_size_t xxxGetProduction ( slk_size_t   conflict_number,\n"
"                              xxxToken yyytokens ) ";
static char c_get_production_body[] =
"{\n"
"    slk_size_t  entry = 0;\n"
"    int         index, level;\n"
"\n"
"    if ( conflict_number <= TOTAL_CONFLICTS ) {\n"
"        entry = conflict_number + (START_CONFLICT -1);\n"
"        level = 1;\n"
"        while ( entry >= START_CONFLICT ) {\n"
"            index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"            index += peek ( tokens, level );\n"
"            entry = Conflict [ index ];\n"
"            ++level;\n"
"        }\n"
"    }\n"
"\n"
"    return  entry;\n"
"}\n";
static char c_is_nonterminal_decl[] =
"int xxxIsNonterminal ( slk_size_t symbol )";
static char c_is_nonterminal_body[] =
"{\n"
"   return ( symbol >= START_SYMBOL  &&  symbol < START_ACTION );\n"
"}\n";
static char c_is_terminal_decl[] =
"int xxxIsTerminal ( slk_size_t symbol )";
static char c_is_terminal_body[] =
"{\n"
"   return ( symbol > 0  &&  symbol < START_SYMBOL );\n"
"}\n";
static char c_is_action_decl[] =
"int xxxIsAction ( slk_size_t symbol )";
static char c_is_action_body[] =
"{\n"
"   return ( symbol >= START_ACTION  &&  symbol < END_ACTION );\n"
"}\n";
static char c_predicted_entry_part1[] =
"static slk_size_t\n"
"get_predicted_entry ( xxxToken yyytokens, \n"
"                      slk_size_t production_number,\n"
"                      slk_size_t token,\n"
"                      int        scan_level,\n"
"                      int        depth )\n"
"{\n"
" register\n"
" slk_size_t  *top, *production;\n"
" slk_size_t   entry, symbol, predicted_entry, lhs;\n"
" slk_size_t   save_token = token;\n"
" int          save_scan_level = scan_level;\n"
" int          production_length, index, level;\n"
" slk_size_t   stack [ PARSE_STACK_SIZE ];\n"
"\n"
" top = stack + (PARSE_STACK_SIZE-1);\n"
" *top = 0;\n"
" predicted_entry = production_number;\n"
" production = &Production [ Production_row [predicted_entry] ];\n"
" lhs = *(production + 1);\n"
"\n"
" for (;;) {\n"
"   top = stack + (PARSE_STACK_SIZE-1);\n"
"   token = save_token;\n"
"   scan_level = save_scan_level;\n"
"   production = &Production [ Production_row [predicted_entry] ];\n"
"   symbol = *(production+1);\n"
"   if ( symbol != lhs ) {\n"
"       predicted_entry = 0;\n"
"       break;\n"
"   }\n"
"   production_length = *production - 1;\n"
"   production += production_length + 1;\n"
"   for (;  production_length-- > 0;  --production ) {\n"
"       SLK_PUSH ( *production, stack, top );\n"
"   }\n"
"   for ( symbol = SLK_POP ( top );  symbol;  symbol = SLK_POP ( top ) ) {\n"
"\n"
"       if ( symbol >= START_SYMBOL  &&  symbol < START_ACTION ) {\n"
"           entry = 0;\n"
"           production_number = GET_CONDITIONAL_PRODUCTION ( symbol );\n"
"           if ( production_number ) {\n"
"               entry = get_predicted_entry ( tokens, \n"
"                                             production_number, token, \n"
"                                             scan_level, depth + 1 );\n"
"           }\n"
"           if ( ! entry ) {\n"
"               index = Parse_row [symbol - (START_SYMBOL-1)];\n"
"               index += token;\n"
"               entry = Parse [ index ];\n"
"           }\n"
"           level = scan_level;\n"
"           while ( entry >= START_CONFLICT ) {\n"
"               index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"               index += peek (tokens, level);\n"
"               entry = Conflict [ index ];\n"
"               ++level;\n"
"           }\n"
"           if ( entry ) {\n"
"               production = &Production [ Production_row [entry] ];\n"
"               production_length = *production - 1;\n"
"               if ( *++production == symbol ) {\n";
static char c_predicted_entry_part2[] =
"                   production += production_length;\n"
"                   for (;  production_length-- > 0;  --production ) {\n"
"                       SLK_PUSH ( *production, stack, top );\n"
"                   }\n"
"               } else {\n"
"                   ++predicted_entry;\n"
"                   break;\n"
"               }\n"
"           } else {\n"
"               ++predicted_entry;\n"
"               break;\n"
"           }\n"
"       } else if ( symbol > 0 ) {\n"
"           if ( symbol == token ) {\n"
"               token = peek ( tokens, scan_level++ );\n"
"           } else {\n"
"               ++predicted_entry;\n"
"               break;\n"
"           }\n"
"       }\n"
"   }\n"
"   if ( ! symbol ) {\n"
"       break;\n"
"   }\n"
" }\n"
"\n"
" return  predicted_entry;\n"
"}\n";
static char c_ll_parse_decl[] =
"void xxxParse ( xxxActionyyyaction, \n"
"                xxxToken yyytokens, \n"
"                xxxError yyyerror, \n"
"                slk_size_t  start_symbol ) ";
static char c_ll_parse_body[] =
"{\n"
" slk_size_t  *top, *production;\n"
" slk_size_t   production_number, entry, symbol, token, new_token;\n"
" int          production_length, index, level;\n"
" slk_size_t   stack [ PARSE_STACK_SIZE ];\n"
"\n"
" top = stack + (PARSE_STACK_SIZE-1);\n"
" *top = 0;\n"
" if ( ! start_symbol ) {\n"
"     start_symbol = START_SYMBOL;\n"
" }\n"
" SLK_PUSH ( start_symbol, stack, top );\n"
" token = get(tokens);\n"
" new_token = token;\n"
"\n"
" for ( symbol = SLK_POP ( top );  symbol;  ) {\n"
"\n"
"     if ( symbol >= START_ACTION ) {\n"
"         execute ( action, (symbol-(START_ACTION-1)) );\n"
"\n"
"     } else if ( symbol >= START_SYMBOL ) {\n"
"         entry = 0;\n"
"         level = 1;\n"
"         production_number = GET_CONDITIONAL_PRODUCTION ( symbol );\n"
"         if ( production_number ) {\n"
"             entry = get_predicted_entry ( tokens,\n"
"                                           production_number, token,\n"
"                                           level, 1 );\n"
"         }\n"
"         if ( ! entry ) {\n"
"             index = Parse_row [symbol - (START_SYMBOL-1)];\n"
"             index += token;\n"
"             entry = Parse [ index ];\n"
"         }\n"
"         while ( entry >= START_CONFLICT ) {\n"
"             index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"             index += peek (tokens, level);\n"
"             entry = Conflict [ index ];\n"
"             ++level;\n"
"         }\n"
"         if ( entry ) {\n"
"             production = &Production [ Production_row [entry] ];\n"
"             production_length = *production - 1;\n"
"             if ( *++production == symbol ) {\n"
"                 predict ( action, entry, symbol, token, level - 1, tokens.getLastToken(), tokens.getLastLineNumber(), tokens.getCurToken(), tokens.getLineNumber() );\n"
"                 production += production_length;\n"
"                 for (;  production_length-- > 0;  --production ) {\n"
"                     SLK_PUSH ( *production, stack, top );\n"
"                 }\n"
"             } else {\n"
"                 new_token = no_entry ( error, entry, symbol, token, level - 1, tokens );\n"
"             }\n"
"         } else {\n"
"             new_token = no_entry ( error, entry, symbol, token, level - 1, tokens );\n"
"         }\n"
"     } else if ( symbol > 0 ) {\n"
"         if ( symbol == token ) {\n"
"             token = get(tokens);\n"
"             new_token = token;\n"
"         } else {\n"
"             new_token = mismatch ( error, symbol, token, tokens );\n"
"         }\n"
"     } else {\n"
"         message(error, \"\\n parser error: symbol value 0\\n\", tokens);\n"
"     }\n"
"     if ( token != new_token ) {\n"
"         if ( new_token ) {\n"
"             token = new_token;\n"
"         }\n"
"         if ( token != END_OF_SLK_INPUT_ ) {\n"
"             continue;\n"
"         }\n"
"     }\n"
"     symbol = SLK_POP ( top );\n"
" }\n"
" if ( token != END_OF_SLK_INPUT_ ) {\n"
"     input_left ( error, tokens );\n"
" }\n"
"}\n";
static char c_lr_parse_decl[] =
"void xxxParse ( xxxAction yyyaction, \n"
"                xxxToken yyytokens, \n"
"                xxxError yyyerror, \n"
"                slk_size_t  start_symbol ) ";
static char c_lr_parse_body[] =
"{\n"
" slk_size_t  *top, *production;\n"
" slk_size_t   state, production_number, entry, symbol, token, new_token;\n"
" int          action_number, production_length, index, level;\n"
" slk_size_t   stack [ PARSE_STACK_SIZE ];\n"
"\n"
" top = stack + (PARSE_STACK_SIZE-1);\n"
" *top = 0;\n"
" if ( ! start_symbol ) {\n"
"     start_symbol = START_SYMBOL;\n"
" }\n"
" SLK_PUSH ( 1, stack, top );\n"
" token = get(tokens);\n"
" new_token = token;\n"
"\n"
" for ( state = *top;  state;  ) {\n"
"     index = Parse_row [ state ];\n"
"     index += token;\n"
"     entry = Parse [ index ];\n"
"     if ( state != Parse_state [ index ] )  entry = 0;\n"
"     level = 1;\n"
"     state ( action, state );\n"
"\n"
"     if ( entry >= START_CONFLICT ) {\n"
"         while ( entry >= START_CONFLICT && entry < END_CONFLICT ) {\n"
"             index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"             index += peek (tokens, level);\n"
"             entry = Conflict [ index ];\n"
"             ++level;\n"
"         }\n"
"     }\n"
"     if ( entry >= START_STATE ) {\n"
"         state = entry - (START_STATE-1);\n"
"         SLK_PUSH ( state, stack, top );\n"
"         token = get(tokens);\n"
"         new_token = token;\n"
"\n"
"     } else if ( entry > 0 ) {\n"
"         reduce ( action, entry );\n"
"         production_number = entry;\n"
"         action_number = Action_number [production_number];\n"
"         if ( action_number ) {\n"
"             action_number -= (START_ACTION-1);\n"
"             if ( action_number < END_ACTION ) {\n"
"                 execute ( action, action_number );\n"
"             } else {\n"
"                 message ( error, \"\\n error: action out of range\\n\" );\n"
"             }\n"
"         }\n"
"         production = &Production [ Production_row [production_number] ];\n"
"         production_length = *production - 1;\n"
"         symbol = *++production;\n"
"         for (;  production_length > 0;  --production_length ) {\n"
"             SLK_POP ( top );\n"
"         }\n"
"         state = *top;\n"
"         index = Parse_row [ state ];\n"
"         index += symbol;\n"
"         entry = Parse [ index ];\n"
"         if ( state != Parse_state [ index ] )  entry = 0;\n"
"         if ( entry >= START_CONFLICT ) {\n"
"             message ( error, \"\\n reduce error: conflict not state\\n\" );\n"
"         } else if ( entry >= START_STATE ) {\n"
"             state = entry - (START_STATE-1);\n"
"             SLK_PUSH ( state, stack, top );\n"
"         } else if ( entry > 0 ) {\n"
"             message ( error, \"\\n reduce error: not a state\\n\" );\n"
"         } else if ( token != END_OF_SLK_INPUT_ ) {\n"
"             new_token = no_entry ( error, state, token, level-1 );\n"
"         }\n"
"     } else {\n"
"         new_token = no_entry ( error, state, token, level-1 );\n"
"         if ( new_token == END_OF_SLK_INPUT_ ) {\n"
"             break;\n"
"         }\n"
"     }\n"
"     if ( token != new_token ) {\n"
"         if ( new_token ) {\n"
"             token = new_token;\n"
"         }\n"
"     }\n"
"     state = *top;\n"
"     if ( state <= 1 ) {\n"
"         break;\n"
"     }\n"
" }\n"
" if ( token != END_OF_SLK_INPUT_ ) {\n"
"     input_left ( error );\n"
" }\n"
"}\n";
static void
write_c_action_table(char* parser_name,
    uint generate_flags,
    uint yacc_grammar)
{
    register Symbol** symbol;
    FILE* out_stream;
    uchar* name_cursor,
        * name_end,
        action_type_name[16],
        file_name[16];
    if (generate_flags & 0x00001000) {
        sprintf(action_type_name, "%sAction *", parser_name);
    }
    else {
        sprintf(action_type_name, "void");
    }
    sprintf(file_name, "%sTable.h", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1107, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "#ifndef _%sTABLE_H\n#define _%sTABLE_H\n\n",
        parser_name, parser_name);
    if (generate_flags & 0x00001000) {
        fprintf(out_stream, "#include \"%sAction.h\"\n\n", parser_name);
    }
    fprintf(out_stream, "#ifdef __cplusplus\n"
        "extern \"C\" {\n"
        "#endif\n\n");
    for (symbol = actions; *++symbol;) {
        name_cursor = (*symbol)->name;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        fprintf(out_stream, "void    %s ( %s );\n", name_end, action_type_name);
        if (((*name_end >= '0' && *name_end <= '9'))) {
            fatal_error(1110, "Cannot mix numbered actions with named actions");
        }
    }
    fprintf(out_stream, "\nextern void (*%sActions []) ( %s );\n\n",
        parser_name, action_type_name);
    fprintf(out_stream, "#ifdef __cplusplus\n"
        "}\n"
        "#endif\n");
    fprintf(out_stream, "\n#endif\n");
    fclose(out_stream);
    sprintf(file_name, "%sTable.c", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1109, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "#include \"%sTable.h\"\n\n", parser_name);
    fprintf(out_stream, "void ( *%sActions [] ) ( %s ) = { 0\n",
        parser_name, action_type_name);
    for (symbol = actions; *++symbol;) {
        name_cursor = (*symbol)->name;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        fprintf(out_stream, "   ,%s\n", name_end);
    }
    fprintf(out_stream, "};\n");
    fclose(out_stream);
    sprintf(file_name, "%sExecute.txt", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1109, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "static void ( *%sActions [] ) ( %s ) = { 0\n",
        parser_name, action_type_name);
    for (symbol = actions; *++symbol;) {
        name_cursor = (*symbol)->name;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        fprintf(out_stream, "   ,%s\n", name_end);
    }
    fprintf(out_stream, "};\n\n");
    if (generate_flags & 0x00001000) {
        fprintf(out_stream, "static void\n"
            "(execute) ( %sa, slk_size_t  n ) "
            "  { ( %sActions [ n ] ) ( a ); }\n",
            action_type_name,
            parser_name);
    }
    else {
        fprintf(out_stream, "static void\n"
            "execute ( slk_size_t  number ) "
            "  { ( %sActions [ number ] ) (); }\n",
            parser_name);
    }
    fclose(out_stream);
}
static void
write_cpp_action_table(char* parser_name,
    uint generate_flags,
    char* namespace_name,
    uint yacc_grammar)
{
    register Symbol** symbol;
    int action_number,
        action_count = 0;
    FILE* out_stream;
    uchar* name_cursor,
        * name_end,
        file_name[16];
    sprintf(file_name, "%sTable.h", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1112, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "#ifndef _%sTABLE_H\n#define _%sTABLE_H\n\n",
        parser_name, parser_name);
    if (namespace_name) {
        fprintf(out_stream, "namespace %s {\n\n", namespace_name);
    }
    fprintf(out_stream, "public:\n\n");
    for (symbol = actions; *++symbol; ++action_count) {
        name_cursor = (*symbol)->name;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        fprintf(out_stream, "void    %s ( void );\n", name_end);
        if (((*name_end >= '0' && *name_end <= '9'))) {
            fatal_error(1113, "Cannot mix numbered actions with named actions");
        }
    }
    fprintf(out_stream, "\nvoid    ( %sAction::*Action [ %u ] ) ( void );\n\n",
        parser_name, action_count + 1);
    fprintf(out_stream, "void    initialize_table ( void );\n");
    fprintf(out_stream, "void\n"
        "execute ( int  number ) "
        "  { ( this->*Action [ number ] ) (); }\n");
    if (namespace_name) {
        fprintf(out_stream, "\n\n}\n");
    }
    fprintf(out_stream, "\n#endif\n");
    fclose(out_stream);
    sprintf(file_name, "%sTable.cpp", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1114, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "#include \"%sAction.h\"\n\n", parser_name);
    if (namespace_name) {
        fprintf(out_stream, "namespace %s {\n\n", namespace_name);
    }
    fprintf(out_stream, "void\n"
        "%sAction ::\n"
        "initialize_table ( void )\n"
        "{\n"
        "    Action [ 0 ] = 0;\n",
        parser_name);
    for (symbol = actions; *++symbol;) {
        name_cursor = (*symbol)->name;
        action_number = (*symbol)->number;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        fprintf(out_stream, "    Action [ %u ] = &%sAction::%s;\n",
            (action_number - (start_action - 1)),
            parser_name, name_end);
    }
    fprintf(out_stream, "}\n");
    if (namespace_name) {
        fprintf(out_stream, "\n\n}\n");
    }
    fclose(out_stream);
    sprintf(file_name, "%sExecute.txt", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1112, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n"
        "private:\n",
        file_name);
    for (symbol = actions; *++symbol; ++action_count) {
        name_cursor = (*symbol)->name;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        fprintf(out_stream, "void    %s ( void );\n", name_end);
        if (((*name_end >= '0' && *name_end <= '9'))) {
            fatal_error(1113, "Cannot mix numbered actions with named actions");
        }
    }
    fprintf(out_stream, "\npublic:\nvoid execute ( slk_size_t  number )\n"
        "{\n"
        "  switch ( number ) {\n");
    for (symbol = actions; *++symbol; ++action_count) {
        name_cursor = (*symbol)->name;
        action_number = (*symbol)->number;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        fprintf(out_stream, "    case %d:  %s();  break;\n",
            (action_number - (start_action - 1)), name_end);
        if (((*name_end >= '0' && *name_end <= '9'))) {
            fatal_error(1119, "Cannot mix numbered actions with named actions");
        }
    }
    fprintf(out_stream, "  }\n}\n");
    fclose(out_stream);
}
static void
write_c_headers(char* parser_name,
    char* namespace_name,
    uint generate_flags)
{
    register Symbol** symbol;
    int number,
        first_entry;
    FILE* out_stream,
        * header_file;
    uchar file_name[32],
        * define_name;
    char* prefix = "",
        * suffix = "";
    char* size_type = "short";
    if (nonterminal_count + terminal_count + action_count > (64 * 1024 - 4)) {
        size_type = "int";
    }
    else if (production_count + conflict_count > (64 * 1024 - 4)) {
        size_type = "int";
    }
    if (generate_flags & 0x00000002) {
        suffix = parser_name;
    }
    sprintf(file_name, "%sParse.h", parser_name);
    header_file = fopen(file_name, "w");
    if (!header_file) {
        perror(file_name);
        fatal_error(1101, "");
    }
    sprintf(file_name, "%sConstants.h", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1101, "");
    }
    fprintf(header_file, "\n// %sParse.h - generated by the SLK parser generator \n\n",
        parser_name);
    fprintf(header_file, "#ifndef _%sPARSE_H\n#define _%sPARSE_H\n\n",
        parser_name, parser_name);
    fprintf(out_stream, "\n// %sConstants.h - generated by the SLK parser generator \n\n",
        parser_name);
    fprintf(out_stream, "#ifndef _%sCONSTANTS_H\n#define _%sCONSTANTS_H\n\n",
        parser_name, parser_name);
    if (generate_flags & 0x00000100) {
        fprintf(header_file, "#ifdef __cplusplus\n"
            "extern \"C\" {\n"
            "#endif\n\n");
        fprintf(out_stream, "#ifdef __cplusplus\n"
            "extern \"C\" {\n"
            "#endif\n\n");
    }
    else if (generate_flags & 0x00000200) {
        if (namespace_name) {
            fprintf(header_file, "namespace %s {\n\n", namespace_name);
            fprintf(out_stream, "namespace %s {\n\n", namespace_name);
        }
    }
    fprintf(out_stream, "enum _%s_token_defines { \n", parser_name);
    first_entry = 0;
    for (symbol = terminals; *++symbol;) {
        number = (*symbol)->number;
        define_name = token_define_name(prefix, suffix, symbol, 1);
        (*symbol)->define_name = str_dup(define_name);
        if (first_entry) {
            fprintf(out_stream, ", %s = %u \n", define_name, number);
        }
        else {
            fprintf(out_stream, "  %s = %u \n", define_name, number);
            first_entry = 1;
        }
    }
    fprintf(out_stream, "}; \n\n");
    first_entry = 0;
    prefix = "NT_";
    fprintf(out_stream, "enum _%s_Nonterminal_defines { \n", parser_name);
    for (symbol = nonterminals; *++symbol;) {
        number = (*symbol)->number;
        define_name = token_define_name(prefix, suffix, symbol, 0);
        if (first_entry) {
            fprintf(out_stream, ", %s = %u \n", define_name, number);
        }
        else {
            fprintf(out_stream, "  %s = %u \n", define_name, number);
            first_entry = 1;
        }
    }
    fprintf(out_stream, "}; \n\n");
    fprintf(header_file, "typedef unsigned %s   slk_size_t;\n\n", size_type);
    fprintf(out_stream, "typedef unsigned %s   slk_size_t;\n\n", size_type);
    fprintf(header_file, "%s;\n", c_symbol_type_decl);
    fprintf(header_file, "%s;\n", c_production_array_decl);
    fprintf(header_file, "slk_size_t *%sGetState ( slk_size_t  state_number );\n",
        parser_name);
    fprintf(header_file, "%s;\n", c_is_nonterminal_decl);
    fprintf(header_file, "%s;\n", c_is_terminal_decl);
    fprintf(header_file, "%s;\n\n", c_is_action_decl);
    fprintf(out_stream, "%s;\n", c_symbol_type_decl);
    fprintf(out_stream, "%s;\n", c_production_array_decl);
    fprintf(out_stream, "slk_size_t *%sGetState ( slk_size_t  state_number );\n",
        parser_name);
    fprintf(out_stream, "%s;\n", c_is_nonterminal_decl);
    fprintf(out_stream, "%s;\n", c_is_terminal_decl);
    fprintf(out_stream, "%s;\n\n", c_is_action_decl);
    if (generate_flags & 0x00000100) {
        fprintf(header_file, "%s \n", c_token_error_action_decls);
    }
    else {
        fprintf(header_file, "%s \n", c_action_includes);
    }
    fprintf(header_file, "%s;\n", c_get_production_decl);
    if (generate_flags & (0x00000004 | 0x00000008)) {
        fprintf(header_file, "%s;\n\n", c_ll_parse_decl);
    }
    if (generate_flags & 0x00000100) {
        fprintf(header_file, "#ifdef __cplusplus\n"
            "}\n"
            "#endif\n");
        fprintf(out_stream, "#ifdef __cplusplus\n"
            "}\n"
            "#endif\n");
    }
    else if (generate_flags & 0x00000200) {
        if (namespace_name) {
            fprintf(header_file, "\n\n}\n");
            fprintf(out_stream, "\n\n}\n");
        }
    }
    fprintf(header_file, "\n#endif\n");
    fprintf(out_stream, "\n#endif\n");
    fclose(header_file);
    fclose(out_stream);
}
static void
write_keywords_header(char* parser_name,
    char* namespace_name,
    uint generate_flags)
{
    register Symbol** symbol;
    int number,
        eof_token_number,
        first_entry;
    Symbol* eof_label;
    FILE* out_stream;
    uchar file_name[32],
        * define_name,
        * name;
    sprintf(file_name, "%sKeywords.txt", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1191, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "// Assumes all alpha terminals are keywords, "
        "usually needs manual editing to remove non-keywords.\n\n");
    fprintf(out_stream, "#ifndef _%sKEYWORDS_H\n#define _%sKEYWORDS_H\n\n",
        parser_name, parser_name);
    if (generate_flags & 0x00000100) {
        fprintf(out_stream, "#ifdef __cplusplus\n"
            "extern \"C\" {\n"
            "#endif\n\n");
    }
    else if (generate_flags & 0x00000200) {
        if (namespace_name) {
            fprintf(out_stream, "namespace %s {\n\n", namespace_name);
        }
    }
    fprintf(out_stream, "#include \"%sConstants.h\" \n\n", parser_name);
    fprintf(out_stream, "typedef struct _%s_keyword { \n"
        "    slk_size_t  token;\n    const char  *name;\n}"
        "  %s_keyword_t};\n\n",
        parser_name, parser_name);
    fprintf(out_stream, "static %s_keyword_t %s_keyword [] = { \n",
        parser_name, parser_name);
    first_entry = 0;
    eof_label = find_symbol("END_OF_SLK_INPUT");
    eof_token_number = eof_label->number;
    for (symbol = terminals; *++symbol;) {
        number = (*symbol)->number;
        if (number == eof_token_number) {
            continue;
        }
        name = (*symbol)->name;
        if (name && (((*name >= 'a' && *name <= 'z')) || ((*name >= 'A' && *name <= 'Z'))) || (((*(name + 1) >= 'a' && *(name + 1) <= 'z')) || ((*(name + 1) >= 'A' && *(name + 1) <= 'Z')))) {
            define_name = (*symbol)->define_name;
            if (first_entry) {
                fprintf(out_stream, ",{ %s, \"%s\" } \n", define_name, name);
            }
            else {
                fprintf(out_stream, " { %s, \"%s\" } \n", define_name, name);
                first_entry = 1;
            }
        }
    }
    fprintf(out_stream, ",{ 0, NULL } \n");
    fprintf(out_stream, "}; \n\n");
    if (generate_flags & 0x00000100) {
        fprintf(out_stream, "#ifdef __cplusplus\n"
            "}\n"
            "#endif\n");
    }
    else if (generate_flags & 0x00000200) {
        if (namespace_name) {
            fprintf(out_stream, "\n\n}\n");
        }
    }
    fprintf(out_stream, "\n#endif\n");
    fclose(out_stream);
}
static void
write_terminals_header(char* parser_name,
    char* namespace_name,
    uint generate_flags)
{
    register Symbol** symbol;
    int first_entry;
    FILE* out_stream;
    uchar file_name[32],
        * define_name,
        * name;
    sprintf(file_name, "%sTerminals.h", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1191, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "// Declaration of terminals values as int, "
        "can be used to seed the symbol table with terminals\n\n");
    fprintf(out_stream, "#ifndef _%sTERMINALS_H\n#define _%sTERMINALS_H\n\n",
        parser_name, parser_name);
    if (generate_flags & 0x00000100) {
        fprintf(out_stream, "#ifdef __cplusplus\n"
            "extern \"C\" {\n"
            "#endif\n\n");
    }
    else if (generate_flags & 0x00000200) {
        if (namespace_name) {
            fprintf(out_stream, "namespace %s {\n\n", namespace_name);
        }
    }
    fprintf(out_stream, "#include \"%sConstants.h\" \n\n", parser_name);
    fprintf(out_stream, "typedef struct _%s_terminal { \n"
        "    slk_size_t  token;\n    const char  *name;\n}"
        " %s_terminal_t;\n\n",
        parser_name, parser_name);
    fprintf(out_stream, "static %s_terminal_t %s_terminal [] = { \n",
        parser_name, parser_name);
    first_entry = 0;
    for (symbol = terminals; *++symbol;) {
        name = (*symbol)->name;
        if (name) {
            define_name = (*symbol)->define_name;
            if (first_entry) {
                fprintf(out_stream, ",{ %s, \"%s\" } \n", define_name, name);
            }
            else {
                fprintf(out_stream, " { %s, \"%s\" } \n", define_name, name);
                first_entry = 1;
            }
        }
    }
    fprintf(out_stream, ",{ 0, NULL } \n");
    fprintf(out_stream, "}; \n\n");
    if (generate_flags & 0x00000100) {
        fprintf(out_stream, "#ifdef __cplusplus\n"
            "}\n"
            "#endif\n");
    }
    else if (generate_flags & 0x00000200) {
        if (namespace_name) {
            fprintf(out_stream, "\n\n}\n");
        }
    }
    fprintf(out_stream, "\n#endif\n");
    fclose(out_stream);
}
static void
write_conditional_c(register FILE* out_file)
{
    register Symbol** nonterminal;
    int production_number,
        count = 0,
        conditional_threshold;
    if (conditional_count == 0) {
        fputs("#define GET_CONDITIONAL_PRODUCTION( symbol )  0 \n", out_file);
        fputs("#define get_predicted_entry( a,b,c,d,e )  0 \n\n", out_file);
    }
    else if (conditional_count == 1) {
        fputs("#define GET_CONDITIONAL_PRODUCTION( symbol ) \\ \n (", out_file);
        for (nonterminal = nonterminals; *++nonterminal;) {
            if ((*nonterminal)->conditional) {
                production_number = production_number_of(*nonterminal);
                fprintf(out_file, " symbol == %u ? %u :", (*nonterminal)->number,
                    production_number);
            }
        }
        fputs(" 0 ) \n\n", out_file);
    }
    else {
        conditional_threshold = start_symbol_number + nonterminal_count - 1 -
            conditional_count;
        fputs("static slk_size_t Conditional_production[] = {0\n", out_file);
        for (nonterminal = nonterminals; *++nonterminal;) {
            if ((*nonterminal)->conditional) {
                production_number = production_number_of(*nonterminal);
                fprintf(out_file, ",%u", production_number);
                if (++count > 20) {
                    count = 0;
                    fputs("\n", out_file);
                }
            }
        }
        fputs("};\n\n", out_file);
        fputs("#define GET_CONDITIONAL_PRODUCTION( symbol ) \\ \n (", out_file);
        fprintf(out_file, " symbol > %u ? Conditional_production [ symbol - %u ]"
            " : 0 ) \n\n",
            conditional_threshold, conditional_threshold);
    }
}
static void
patch_c_templates(char* parser_name,
    uint generate_flags)
{
    char* template_cursor, * template_cursor2;
    char* reference_prefix = "   ";
    if (generate_flags & 0x00000200) {
        reference_prefix = "  &";
    }
    else if (generate_flags & 0x00001000) {
        reference_prefix = "  *";
    }
    if (!(generate_flags & 0x00000001)) {
        for (template_cursor = c_lr_parse_body; template_cursor;) {
            template_cursor = strstr(template_cursor, "if ( state != Parse_state");
            if (template_cursor) {
                strncpy(template_cursor, "//   ", 5);
            }
        }
    }
    for (template_cursor = c_token_error_action_decls; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_action_includes; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_push_pop_macros; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_symbol_type_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_production_array_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_is_nonterminal_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_is_terminal_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_is_action_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_predicted_entry_part1; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_ll_parse_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_ll_parse_body; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_lr_parse_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_lr_parse_body; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_get_production_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = c_get_production_body; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor2 = c_predicted_entry_part1; template_cursor2;) {
        template_cursor2 = strstr(template_cursor2, "yyy");
        if (template_cursor2) {
            strncpy(template_cursor2, reference_prefix, 3);
        }
    }
    for (template_cursor2 = c_ll_parse_decl; template_cursor2;) {
        template_cursor2 = strstr(template_cursor2, "yyy");
        if (template_cursor2) {
            strncpy(template_cursor2, reference_prefix, 3);
        }
    }
    for (template_cursor2 = c_get_production_decl; template_cursor2;) {
        template_cursor2 = strstr(template_cursor2, "yyy");
        if (template_cursor2) {
            strncpy(template_cursor2, reference_prefix, 3);
        }
    }
    for (template_cursor2 = c_lr_parse_decl; template_cursor2;) {
        template_cursor2 = strstr(template_cursor2, "yyy");
        if (template_cursor2) {
            strncpy(template_cursor2, reference_prefix, 3);
        }
    }
}
void generate_c_parser(char* parser_name,
    char* namespace_name,
    int named_actions,
    uint generate_flags,
    FILE* out_file,
    int yacc_grammar)
{
    Symbol* eof_label;
    patch_c_templates(parser_name, generate_flags);
    write_c_headers(parser_name, namespace_name, generate_flags);
    write_keywords_header(parser_name, namespace_name, generate_flags);
    write_terminals_header(parser_name, namespace_name, generate_flags);
    if (named_actions) {
        if (generate_flags & 0x00000200) {
            write_cpp_action_table(parser_name, generate_flags,
                namespace_name, yacc_grammar);
        }
        else {
            write_c_action_table(parser_name, generate_flags,
                yacc_grammar);
        }
    }
    write_conditional_c(out_file);
    eof_label = find_symbol("END_OF_SLK_INPUT");
    fprintf(out_file, "#define START_SYMBOL %u\n", start_symbol_number);
    fprintf(out_file, "#define %s_ %u\n", "END_OF_SLK_INPUT", eof_label->number);
    fprintf(out_file, "#define START_STATE %u\n", start_state);
    fprintf(out_file, "#define START_CONFLICT %u\n", start_conflict);
    fprintf(out_file, "#define END_CONFLICT %u\n", start_conflict + conflict_count);
    fprintf(out_file, "#define START_ACTION %u\n", start_action);
    fprintf(out_file, "#define END_ACTION %u\n", start_action + action_count);
    fprintf(out_file, "#define TOTAL_CONFLICTS %u\n", conflict_count);
    fprintf(out_file, "#define PARSE_STACK_SIZE %u\n", parse_stack_size);
    fprintf(out_file, "%s\n", c_push_pop_macros);
    if (!(generate_flags & 0x00001000)) {
        fprintf(out_file,
            "#define peek(self,a)                   self.peek(a)\n"
            "#define get(self)                      self.get()\n"
            "#define mismatch(self,a,b,c)           self.mismatch(a,b,c)\n"
            "#define no_entry(self,a,b,c,d,e)       self.no_entry(a,b,c,d,e)\n"
            "#define input_left(self,a)             self.input_left(a)\n"
            "#define message(self,a,b)              self.message(a,b)\n"
            "#define predict(self,a,b,c,d,e,f,g,h)  self.predict(a,b,c,d,e,f,g,h)\n"
            "#define reduce(self,a)                 self.reduce(a)\n"
            "#define state(self,a)                  self.state(a)\n"
            "#define execute(self,a)                self.execute(a)\n\n");
    }
    fprintf(out_file, "%s\n", c_symbol_type_decl);
    fprintf(out_file, "%s\n", c_symbol_type_body);
    fprintf(out_file, "%s\n", c_production_array_decl);
    fprintf(out_file, "%s\n", c_production_array_body);
    fprintf(out_file, "%s\n", c_is_nonterminal_decl);
    fprintf(out_file, "%s\n", c_is_nonterminal_body);
    fprintf(out_file, "%s\n", c_is_terminal_decl);
    fprintf(out_file, "%s\n", c_is_terminal_body);
    fprintf(out_file, "%s\n", c_is_action_decl);
    fprintf(out_file, "%s\n", c_is_action_body);
    if (conflict_count > 0) {
        fprintf(out_file, "%s\n", c_get_production_decl);
        fprintf(out_file, "%s\n", c_get_production_body);
    }
    if (generate_flags & 0x00000004) {
        if (conditional_count > 0) {
            if (generate_flags & 0x00100000) {
                fprintf(out_file, "#include <stdio.h>\n#include \"SlkString.h\"\n\n");
            }
            fprintf(out_file, "%s", c_predicted_entry_part1);
            if (generate_flags & 0x00100000) {
                fprintf(out_file, "\t\t   printf ( \"--%%s\\n\", "
                    "SlkGetProductionName ( entry ) );\n");
            }
            fprintf(out_file, "%s\n", c_predicted_entry_part2);
        }
        fprintf(out_file, "%s\n", c_ll_parse_decl);
        fprintf(out_file, "%s\n", c_ll_parse_body);
    }
    else if (generate_flags & 0x00000008) {
        fprintf(out_file, "%s\n", c_lr_parse_decl);
        fprintf(out_file, "%s\n", c_lr_parse_body);
    }
}
// ================ Java/C# output code templates ================
static char m_get_production_array[] =
"public static short[]\n"
"GetProductionArray ( short  production_number )\n"
"{\n"
"   short   index = (short)  Production_row [ production_number ],\n"
"           array_length = (short)  Production [ index ],\n"
"           new_index = 0;\n"
"   short[] productionArray = new short[yyy         \n"
"\n"
"   while ( array_length-- >= 0 ) {\n"
"       productionArray [ new_index++ ] = Production [ index++ ];\n"
"   }\n"
"   return  productionArray;\n"
"}\n";
static char m_get_symbol_type[] =
"public static int GetSymbolType ( short   symbol )\n"
"{\n"
"   int   symbol_type = NOT_A_SYMBOL;\n"
"\n"
"   if ( symbol >= START_ACTION  &&  symbol < END_ACTION ) {\n"
"       symbol_type = ACTION_SYMBOL;\n"
"   } else if ( symbol >= START_SYMBOL ) {\n"
"       symbol_type = NONTERMINAL_SYMBOL;\n"
"   } else if ( symbol > 0 ) {\n"
"       symbol_type = TERMINAL_SYMBOL;\n"
"   }\n"
"   return  symbol_type;\n"
"}\n";
static char m_is_nonterminal[] =
"public static boolean IsNonterminal ( short   symbol )\n"
"{\n"
"   return ( symbol >= START_SYMBOL  &&  symbol < START_ACTION );\n"
"}\n";
static char m_is_terminal[] =
"public static boolean IsTerminal ( short   symbol )\n"
"{\n"
"   return ( symbol > 0  &&  symbol < START_SYMBOL );\n"
"}\n";
static char m_is_action[] =
"public static boolean IsAction ( short   symbol )\n"
"{\n"
"   return ( symbol >= START_ACTION  &&  symbol < END_ACTION );\n"
"}\n";
static char m_get_terminal_index[] =
"public static short GetTerminalIndex ( short   token )"
"{\n"
" return ( token );\n"
"}\n";
static char m_get_production[] =
"public static short\n"
"get_production ( short     conflict_number,\n"
"                 xxxToken  tokens )\n"
"{\n"
"    short   entry = 0;\n"
"    int     index, level;\n"
"\n"
"    if ( conflict_number <= TOTAL_CONFLICTS ) {\n"
"        entry = (short) ( conflict_number + (START_CONFLICT - 1) );\n"
"        level = 1;\n"
"        while ( entry >= START_CONFLICT ) {\n"
"            index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"            index += tokens.peek ( level );\n"
"            entry = Conflict [ index ];\n"
"            ++level;\n"
"        }\n"
"    }\n"
"\n"
"    return  entry;\n"
"}\n";
static char m_predicted_entry_decl[] =
"private static short\n"
"get_predicted_entry ( xxxToken   tokens,\n"
"                      short      production_number,\n"
"                      short      token,\n"
"                      int        scan_level,\n"
"                      int        depth )\n";
static char m_predicted_entry_body[] =
"{\n"
" short     entry, symbol, predicted_entry, lhs;\n"
" short     save_token = token;\n"
" int       save_scan_level = scan_level;\n"
" int       production_length, top, index, level;\n"
" short[]   stack = new short[128];\n"
"\n"
" top = 127;\n"
" stack [ top ] = 0;\n"
" predicted_entry = production_number;\n"
" index = Production_row [ predicted_entry ];\n"
" lhs = Production [ ++index ];\n"
"\n"
" for (;;) {\n"
"   top = 127;\n"
"   token = save_token;\n"
"   scan_level = save_scan_level;\n"
"   index = Production_row [ predicted_entry ];\n"
"   symbol = Production [ ++index ];\n"
"   if ( symbol != lhs ) {\n"
"       predicted_entry = (short) 0;\n"
"       break;\n"
"   }\n"
"   production_length = Production [ index ] - 1;\n"
"   lhs = Production [ ++index ];\n"
"   index += production_length;\n"
"   for (;  production_length-- > 0;  --index ) {\n"
"       if ( top > 0 ) { stack [--top] = Production [index];\n"
"       } else { return 0; }\n"
"   }\n"
"   symbol = (stack[top] != 0  ? stack[top++] : (short) 0);\n"
"\n"
"   for ( ;  symbol != 0 ;  symbol = (stack[top] != 0  ? stack[top++] : (short) 0) ) {\n"
"\n"
"       if ( symbol >= START_SYMBOL  &&  symbol < START_ACTION ) {\n"
"           entry = 0;\n"
"           production_number = get_conditional_production ( symbol );\n"
"           if ( production_number != 0 ) {\n"
"               entry = get_predicted_entry ( tokens,\n"
"                                             production_number, token,\n"
"                                             scan_level, depth + 1 );\n"
"           }\n"
"           if ( entry == 0 ) {\n"
"               index = Parse_row [ symbol - (START_SYMBOL-1) ];\n"
"               index += token;\n"
"               entry = Parse [ index ];\n"
"           }\n"
"           level = scan_level;\n"
"           while ( entry >= START_CONFLICT ) {\n"
"               index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"               index += tokens.peek (level);\n"
"               entry = Conflict [ index ];\n"
"               ++level;\n"
"           }\n"
"           if ( entry != 0 ) {\n"
"               index = Production_row [ entry ];\n"
"               production_length = Production [ index ] - 1;\n"
"               lhs = Production [ ++index ];\n"
"               if ( lhs == symbol ) {\n"
"                 index += production_length;\n"
"                 for (;  production_length-- > 0;  --index ) {\n"
"                     if ( top > 0 ) { stack [--top] = Production [index];\n"
"                     } else { return 0; }\n"
"                 }\n"
"               } else {\n"
"                   ++predicted_entry;\n"
"                   break;\n"
"               }\n"
"           } else {\n"
"               ++predicted_entry;\n"
"               break;\n"
"           }\n"
"       } else if ( symbol > 0 ) {\n"
"           if ( symbol == token ) {\n"
"               token = tokens.peek ( scan_level++ );\n"
"           } else {\n"
"               ++predicted_entry;\n"
"               break;\n"
"           }\n"
"       }\n"
"   }\n"
"   if ( symbol == 0 ) {\n"
"       break;\n"
"   }\n"
" }\n"
" return  predicted_entry;\n"
"}\n";
static char m_ll_parse[] =
"public static void\n"
"parse ( xxxAction   action,\n"
"        xxxToken    tokens,\n"
"        xxxError    error,\n"
"        short       start_symbol )\n"
"{\n"
" short     lhs;\n"
" short     production_number, entry, symbol, token, new_token;\n"
" int       production_length, top, index, level;\n"
" short[]   stack = new short[512];\n"
"\n"
" top = 511;\n"
" stack [ top ] = 0;\n"
" if ( start_symbol == 0 ) {\n"
"     start_symbol = START_SYMBOL;\n"
" }\n"
" if ( top > 0 ) { stack [--top] = start_symbol;\n"
" } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
" token = tokens.get();\n"
" new_token = token;\n"
"\n"
" for ( symbol = (stack[top] != 0  ? stack[top++] : (short) 0);  symbol != 0; ) {\n"
"\n"
"     if ( symbol >= START_ACTION ) {\n"
"         action.execute ( symbol - (START_ACTION-1) );\n"
"\n"
"     } else if ( symbol >= START_SYMBOL ) {\n"
"         entry = 0;\n"
"         level = 1;\n"
"         production_number = get_conditional_production ( symbol );\n"
"         if ( production_number != 0 ) {\n"
"             entry = get_predicted_entry ( tokens,\n"
"                                           production_number, token,\n"
"                                           level, 1 );\n"
"         }\n"
"         if ( entry == 0 ) {\n"
"             index = Parse_row [ symbol - (START_SYMBOL-1) ];\n"
"             index += token;\n"
"             entry = Parse [ index ];\n"
"         }\n"
"         while ( entry >= START_CONFLICT ) {\n"
"             index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"             index += tokens.peek (level);\n"
"             entry = Conflict [ index ];\n"
"             ++level;\n"
"         }\n"
"         if ( entry != 0 ) {\n"
"             index = Production_row [ entry ];\n"
"             production_length = Production [ index ] - 1;\n"
"             lhs = Production [ ++index ];\n"
"             if ( lhs == symbol ) {\n"
"                 action.predict ( entry );\n"
"                 index += production_length;\n"
"                 for (;  production_length-- > 0;  --index ) {\n"
"                     if ( top > 0 ) { stack [--top] = Production [index];\n"
"                     } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
"                 }\n"
"             } else {\n"
"                 new_token = error.no_entry ( symbol, token, level-1 );\n"
"             }\n"
"         } else {                                       // no table entry\n"
"             new_token = error.no_entry ( symbol, token, level-1 );\n"
"         }\n"
"     } else if ( symbol > 0 ) {\n"
"         if ( symbol == token ) {\n"
"             token = tokens.get();\n"
"             new_token = token;\n"
"         } else {\n"
"             new_token = error.mismatch ( symbol, token );\n"
"         }\n"
"     } else {\n"
"         error.message ( \"\\n parser error: symbol value 0\\n\" );\n"
"     }\n"
"     if ( token != new_token ) {\n"
"         if ( new_token != 0 ) {\n"
"             token = new_token;\n"
"         }\n"
"         if ( token != END_OF_SLK_INPUT_ ) {\n"
"             continue;\n"
"         }\n"
"     }\n"
"     symbol = (stack[top] != 0  ? stack[top++] : (short) 0);\n"
" }\n"
" if ( token != END_OF_SLK_INPUT_ ) {\n"
"     error.input_left ();\n"
" }\n"
"}\n";
static char m_lr_parse[] =
"public static void\n"
"parse ( xxxAction   action,\n"
"        xxxToken    tokens,\n"
"        xxxError    error,\n"
"        short       start_symbol )\n"
"{\n"
" short     lhs;\n"
" short     state, production_number, entry, symbol, token, new_token;\n"
" int       action_number, production_length, top, index, level;\n"
" short[]   stack = new short[512];\n"
"\n"
" top = 511;\n"
" stack [ top ] = 0;\n"
" if ( start_symbol == 0 ) {\n"
"     start_symbol = START_SYMBOL;\n"
" }\n"
" if ( top > 0 ) { stack [--top] = 1;\n"
" } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
" token = tokens.get();\n"
" new_token = token;\n"
"\n"
" for ( state = stack[top];  state != 0;  ) {\n"
"     index = Parse_row [ state ];\n"
"     index += token;\n"
"     entry = Parse [ index ];\n"
"     if ( state != Parse_state [ index ] )  entry = 0;\n"
"     level = 1;\n"
"     action.state ( state );\n"
"\n"
"     if ( entry >= START_CONFLICT ) {\n"
"         while ( entry >= START_CONFLICT && entry < END_CONFLICT ) {\n"
"             index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"             index += tokens.peek (level);\n"
"             entry = Conflict [ index ];\n"
"             ++level;\n"
"         }\n"
"     }\n"
"     if ( entry >= START_STATE ) {\n"
"         state = (short) (entry - (START_STATE - 1));\n"
"         if ( top > 0 ) { stack [--top] = state;\n"
"         } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
"         token = tokens.get();\n"
"         new_token = token;\n"
"\n"
"     } else if ( entry > 0 ) {\n"
"         action.reduce ( entry );\n"
"         production_number = entry;\n"
"         action_number = Action_number [production_number];\n"
"         if ( action_number != 0 ) {\n"
"             action_number -= (START_ACTION-1);\n"
"             if ( action_number < END_ACTION ) {\n"
"                 action.execute ( action_number );\n"
"             } else {\n"
"                 error.message ( \"\\n error: action out of range\\n\" );\n"
"             }\n"
"         }\n"
"         index = Production_row [ entry ];\n"
"         production_length = Production [ index ] - 1;\n"
"         lhs = Production [ ++index ];\n"
"         for (;  production_length > 0;  --production_length ) {\n"
"              if ( stack[top] != 0 )  ++top;\n"
"         }\n"
"         state = stack[top];\n"
"         index = Parse_row [ state ];\n"
"         index += lhs;\n"
"         entry = Parse [ index ];\n"
"         if ( state != Parse_state [ index ] )  entry = 0;\n"
"         if ( entry >= START_CONFLICT ) {\n"
"             error.message ( \"\\n reduce error: conflict not state\\n\" );\n"
"         } else if ( entry >= START_STATE ) {\n"
"             state = (short) (entry - (START_STATE - 1));\n"
"             if ( top > 0 ) { stack [--top] = state;\n"
"             } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
"         } else if ( entry > 0 ) {\n"
"             error.message ( \"\\n reduce error: not a state\\n\" );\n"
"         } else if ( token != END_OF_SLK_INPUT_ ) {\n"
"             new_token = error.no_entry ( state, token, level-1 );\n"
"         }\n"
"     } else {\n"
"         new_token = error.no_entry ( state, token, level-1 );\n"
"         if ( new_token == END_OF_SLK_INPUT_ ) {\n"
"             break;\n"
"         }\n"
"     }\n"
"     if ( token != new_token ) {\n"
"         if ( new_token != 0 ) {\n"
"             token = new_token;\n"
"         }\n"
"     }\n"
"     state = stack[top];\n"
"     if ( state <= 1 ) {\n"
"         break;\n"
"     }\n"
" }\n"
" if ( token != END_OF_SLK_INPUT_ ) {\n"
"     error.input_left ();\n"
" }\n"
"}\n";
static char l850_cs[] =
"public static short\n"
"get_production ( short     conflict_number,\n"
"                 ref xxxToken  tokens )\n"
"{\n"
"    short   entry = 0;\n"
"    int     index, level;\n"
"\n"
"    if ( conflict_number <= TOTAL_CONFLICTS ) {\n"
"        entry = (short) ( conflict_number + (START_CONFLICT - 1) );\n"
"        level = 1;\n"
"        while ( entry >= START_CONFLICT ) {\n"
"            index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"            index += tokens.peek ( level );\n"
"            entry = Conflict [ index ];\n"
"            ++level;\n"
"        }\n"
"    }\n"
"\n"
"    return  entry;\n"
"}\n";
static char l851_cs[] =
"private static short\n"
"get_predicted_entry ( ref xxxToken   tokens,\n"
"                      short      production_number,\n"
"                      short      token,\n"
"                      int        scan_level,\n"
"                      int        depth )\n";
static char l852_cs[] =
"{\n"
" short     entry, symbol, predicted_entry, lhs;\n"
" short     save_token = token;\n"
" int       save_scan_level = scan_level;\n"
" int       production_length, top, index, level;\n"
" short[]   stack = new short[128];\n"
"\n"
" top = 127;\n"
" stack [ top ] = 0;\n"
" predicted_entry = production_number;\n"
" index = Production_row [ predicted_entry ];\n"
" lhs = Production [ ++index ];\n"
"\n"
" for (;;) {\n"
"   top = 127;\n"
"   token = save_token;\n"
"   scan_level = save_scan_level;\n"
"   index = Production_row [ predicted_entry ];\n"
"   symbol = Production [ ++index ];\n"
"   if ( symbol != lhs ) {\n"
"       predicted_entry = (short) 0;\n"
"       break;\n"
"   }\n"
"   production_length = Production [ index ] - 1;\n"
"   lhs = Production [ ++index ];\n"
"   index += production_length;\n"
"   for (;  production_length-- > 0;  --index ) {\n"
"       if ( top > 0 ) { stack [--top] = Production [index];\n"
"       } else { return 0; }\n"
"   }\n"
"   symbol = (stack[top] != 0  ? stack[top++] : (short) 0);\n"
"\n"
"   for ( ;  symbol != 0 ;  symbol = (stack[top] != 0  ? stack[top++] : (short) 0) ) {\n"
"\n"
"       if ( symbol >= START_SYMBOL  &&  symbol < START_ACTION ) {\n"
"           entry = 0;\n"
"           production_number = get_conditional_production ( symbol );\n"
"           if ( production_number != 0 ) {\n"
"               entry = get_predicted_entry ( ref tokens,\n"
"                                             production_number, token,\n"
"                                             scan_level, depth + 1 );\n"
"           }\n"
"           if ( entry == 0 ) {\n"
"               index = Parse_row [ symbol - (START_SYMBOL-1) ];\n"
"               index += token;\n"
"               entry = Parse [ index ];\n"
"           }\n"
"           level = scan_level;\n"
"           while ( entry >= START_CONFLICT ) {\n"
"               index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"               index += tokens.peek (level);\n"
"               entry = Conflict [ index ];\n"
"               ++level;\n"
"           }\n"
"           if ( entry != 0 ) {\n"
"               index = Production_row [ entry ];\n"
"               production_length = Production [ index ] - 1;\n"
"               lhs = Production [ ++index ];\n"
"               if ( lhs == symbol ) {\n"
"                 index += production_length;\n"
"                 for (;  production_length-- > 0;  --index ) {\n"
"                     if ( top > 0 ) { stack [--top] = Production [index];\n"
"                     } else { return 0; }\n"
"                 }\n"
"               } else {\n"
"                   ++predicted_entry;\n"
"                   break;\n"
"               }\n"
"           } else {\n"
"               ++predicted_entry;\n"
"               break;\n"
"           }\n"
"       } else if ( symbol > 0 ) {\n"
"           if ( symbol == token ) {\n"
"               token = tokens.peek ( scan_level++ );\n"
"           } else {\n"
"               ++predicted_entry;\n"
"               break;\n"
"           }\n"
"       }\n"
"   }\n"
"   if ( symbol == 0 ) {\n"
"       break;\n"
"   }\n"
" }\n"
" return  predicted_entry;\n"
"}\n";
static char l853_cs[] =
"internal static\n"
"void Accept(IVisitor visitor)\n"
"{\n"
"    visitor.Visit(Production, Production_row, Parse, Parse_row, START_SYMBOL, START_ACTION);\n"
"}\n"
"\n"
"internal unsafe static void\n"
"parse (ref DslAction   action,\n"
"        ref xxxToken    tokens,\n"
"        ref xxxError    error,\n"
"        short       start_symbol )\n"
"{\n"
" short     lhs;\n"
" short     production_number, entry, symbol, token, new_token;\n"
" int       production_length, top, index, level;\n"
" short* stack = stackalloc short[PARSE_STACK_SIZE];\n"
"\n"
" top = PARSE_STACK_SIZE - 1;\n"
" stack [ top ] = 0;\n"
" if ( start_symbol == 0 ) {\n"
"     start_symbol = START_SYMBOL;\n"
" }\n"
" if ( top > 0 ) { stack [--top] = start_symbol;\n"
" } else { error.message (\"xxxParse: stack overflow\\n\", ref tokens); return; }\n"
" token = tokens.get();\n"
" new_token = token;\n"
"\n"
" for ( symbol = (stack[top] != 0  ? stack[top++] : (short) 0);  symbol != 0; ) {\n"
"\n"
"     if ( symbol >= START_ACTION ) {\n"
"         action.execute ( symbol - (START_ACTION-1) );\n"
"\n"
"     } else if ( symbol >= START_SYMBOL ) {\n"
"         entry = 0;\n"
"         level = 1;\n"
"         production_number = get_conditional_production ( symbol );\n"
"         if ( production_number != 0 ) {\n"
"             entry = get_predicted_entry ( ref tokens,\n"
"                                           production_number, token,\n"
"                                           level, 1 );\n"
"         }\n"
"         if ( entry == 0 ) {\n"
"             index = Parse_row [ symbol - (START_SYMBOL-1) ];\n"
"             index += token;\n"
"             entry = Parse [ index ];\n"
"         }\n"
"         while ( entry >= START_CONFLICT ) {\n"
"             index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"             index += tokens.peek (level);\n"
"             entry = Conflict [ index ];\n"
"             ++level;\n"
"         }\n"
"         if ( entry != 0 ) {\n"
"             index = Production_row [ entry ];\n"
"             production_length = Production [ index ] - 1;\n"
"             lhs = Production [ ++index ];\n"
"             if ( lhs == symbol ) {\n"
"                 action.predict ( entry, symbol, token, level - 1, tokens.getLastToken(), tokens.getLastLineNumber(), tokens.getCurToken(), tokens.getLineNumber() );\n"
"                 index += production_length;\n"
"                 for (;  production_length-- > 0;  --index ) {\n"
"                     if ( top > 0 ) { stack [--top] = Production [index];\n"
"                     } else { error.message (\"xxxParse: stack overflow\\n\", ref tokens); return; }\n"
"                 }\n"
"             } else {\n"
"                 new_token = error.no_entry ( entry, symbol, token, level - 1, ref tokens );\n"
"             }\n"
"         } else {                                       // no table entry\n"
"             new_token = error.no_entry ( entry, symbol, token, level - 1, ref tokens );\n"
"         }\n"
"     } else if ( symbol > 0 ) {\n"
"         if ( symbol == token ) {\n"
"             token = tokens.get();\n"
"             new_token = token;\n"
"         } else {\n"
"             new_token = error.mismatch ( symbol, token, ref tokens );\n"
"         }\n"
"     } else {\n"
"         error.message ( \"\\n parser error: symbol value 0\\n\", ref tokens );\n"
"     }\n"
"     if ( token != new_token ) {\n"
"         if ( new_token != 0 ) {\n"
"             token = new_token;\n"
"         }\n"
"         if ( token != END_OF_SLK_INPUT_ ) {\n"
"             continue;\n"
"         }\n"
"     }\n"
"     symbol = (stack[top] != 0  ? stack[top++] : (short) 0);\n"
" }\n"
" if ( token != END_OF_SLK_INPUT_ ) {\n"
"     error.input_left (ref tokens);\n"
" }\n"
"}\n";
static char l854_cs[] =
"internal static\n"
"void Accept(IVisitor visitor)\n"
"{\n"
"    visitor.Visit(Production, Production_row, Parse, Parse_row, START_SYMBOL, START_ACTION);\n"
"}\n"
"\n"
"internal unsafe static void\n"
"parse ( ref DslAction   action,\n"
"        ref xxxToken    tokens,\n"
"        ref xxxError    error,\n"
"        short       start_symbol )\n"
"{\n"
" short     lhs;\n"
" short     state, production_number, entry, symbol, token, new_token;\n"
" int       action_number, production_length, top, index, level;\n"
" short* stack = stackalloc short[PARSE_STACK_SIZE];\n"
"\n"
" top = PARSE_STACK_SIZE - 1;\n"
" stack [ top ] = 0;\n"
" if ( start_symbol == 0 ) {\n"
"     start_symbol = START_SYMBOL;\n"
" }\n"
" if ( top > 0 ) { stack [--top] = 1;\n"
" } else { error.message (\"xxxParse: stack overflow\\n\", ref tokens); return; }\n"
" token = tokens.get();\n"
" new_token = token;\n"
"\n"
" for ( state = stack[top];  state != 0;  ) {\n"
"     index = Parse_row [ state ];\n"
"     index += token;\n"
"     entry = Parse [ index ];\n"
"     if ( state != Parse_state [ index ] )  entry = 0;\n"
"     level = 1;\n"
"     action.state ( state );\n"
"\n"
"     if ( entry >= START_CONFLICT ) {\n"
"         while ( entry >= START_CONFLICT && entry < END_CONFLICT ) {\n"
"             index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"             index += tokens.peek (level);\n"
"             entry = Conflict [ index ];\n"
"             ++level;\n"
"         }\n"
"     }\n"
"     if ( entry >= START_STATE ) {\n"
"         state = (short) (entry - (START_STATE - 1));\n"
"         if ( top > 0 ) { stack [--top] = state;\n"
"         } else { error.message (\"xxxParse: stack overflow\\n\", ref tokens); return; }\n"
"         token = tokens.get();\n"
"         new_token = token;\n"
"\n"
"     } else if ( entry > 0 ) {\n"
"         action.reduce ( entry, symbol, token, level - 1, tokens.getLastToken(), tokens.getLastLineNumber(), tokens.getCurToken(), tokens.getLineNumber() );\n"
"         production_number = entry;\n"
"         action_number = Action_number [production_number];\n"
"         if ( action_number != 0 ) {\n"
"             action_number -= (START_ACTION-1);\n"
"             if ( action_number < END_ACTION ) {\n"
"                 action.execute ( action_number );\n"
"             } else {\n"
"                 error.message ( \"\\n error: action out of range\\n\", ref tokens );\n"
"             }\n"
"         }\n"
"         index = Production_row [ entry ];\n"
"         production_length = Production [ index ] - 1;\n"
"         lhs = Production [ ++index ];\n"
"         for (;  production_length > 0;  --production_length ) {\n"
"              if ( stack[top] != 0 )  ++top;\n"
"         }\n"
"         state = stack[top];\n"
"         index = Parse_row [ state ];\n"
"         index += lhs;\n"
"         entry = Parse [ index ];\n"
"         if ( state != Parse_state [ index ] )  entry = 0;\n"
"         if ( entry >= START_CONFLICT ) {\n"
"             error.message ( \"\\n reduce error: conflict not state\\n\", ref tokens );\n"
"         } else if ( entry >= START_STATE ) {\n"
"             state = (short) (entry - (START_STATE - 1));\n"
"             if ( top > 0 ) { stack [--top] = state;\n"
"             } else { error.message (\"xxxParse: stack overflow\\n\", ref tokens); return; }\n"
"         } else if ( entry > 0 ) {\n"
"             error.message ( \"\\n reduce error: not a state\\n\", ref tokens );\n"
"         } else if ( token != END_OF_SLK_INPUT_ ) {\n"
"             new_token = error.no_entry ( entry, state, token, level-1, ref tokens );\n"
"         }\n"
"     } else {\n"
"         new_token = error.no_entry ( entry, state, token, level-1, ref tokens );\n"
"         if ( new_token == END_OF_SLK_INPUT_ ) {\n"
"             break;\n"
"         }\n"
"     }\n"
"     if ( token != new_token ) {\n"
"         if ( new_token != 0 ) {\n"
"             token = new_token;\n"
"         }\n"
"     }\n"
"     state = stack[top];\n"
"     if ( state <= 1 ) {\n"
"         break;\n"
"     }\n"
" }\n"
" if ( token != END_OF_SLK_INPUT_ ) {\n"
"     error.input_left (ref tokens);\n"
" }\n"
"}\n";
// ================ JavaScript output code templates ================
static char js_get_production_array[] =
"function\n"
"GetProductionArray ( production_number )\n"
"{\n"
"   var     index =    Production_row [ production_number ],\n"
"           array_length =    Production [ index ],\n"
"           new_index = 0;\n"
"   var     productionArray = new Array(yyy         \n"
"\n"
"   while ( array_length-- >= 0 ) {\n"
"       productionArray [ new_index++ ] = Production [ index++ ];\n"
"   }\n"
"   return  productionArray;\n"
"}\n";
static char js_get_symbol_type[] =
"function GetSymbolType ( symbol )\n"
"{\n"
"   var   symbol_type = NOT_A_SYMBOL;\n"
"\n"
"   if ( symbol >= START_ACTION  &&  symbol < END_ACTION ) {\n"
"       symbol_type = ACTION_SYMBOL;\n"
"   } else if ( symbol >= START_SYMBOL ) {\n"
"       symbol_type = NONTERMINAL_SYMBOL;\n"
"   } else if ( symbol > 0 ) {\n"
"       symbol_type = TERMINAL_SYMBOL;\n"
"   }\n"
"   return  symbol_type;\n"
"}\n";
static char js_is_nonterminal[] =
"function IsNonterminal ( symbol )\n"
"{\n"
"   return ( symbol >= START_SYMBOL  &&  symbol < START_ACTION );\n"
"}\n";
static char js_is_terminal[] =
"function IsTerminal ( symbol )\n"
"{\n"
"   return ( symbol > 0  &&  symbol < START_SYMBOL );\n"
"}\n";
static char js_is_action[] =
"function IsAction ( symbol )\n"
"{\n"
"   return ( symbol >= START_ACTION  &&  symbol < END_ACTION );\n"
"}\n";
static char js_get_terminal_index[] =
"function GetTerminalIndex ( token )"
"{\n"
" return ( token );\n"
"}\n";
static char js_get_production[] =
"function\n"
"get_production ( conflict_number, tokens )\n"
"{\n"
"    var     entry = 0;\n"
"    var     index, level;\n"
"\n"
"    if ( conflict_number <= TOTAL_CONFLICTS ) {\n"
"        entry =   ( conflict_number + (START_CONFLICT - 1) );\n"
"        level = 1;\n"
"        while ( entry >= START_CONFLICT ) {\n"
"            index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"            index += tokens.peek ( level );\n"
"            entry = Conflict [ index ];\n"
"            ++level;\n"
"        }\n"
"    }\n"
"\n"
"    return  entry;\n"
"}\n";
static char js_predicted_entry_decl[] =
"function\n"
"get_predicted_entry ( tokens, production_number, token, scan_level, depth )\n";
static char js_predicted_entry_body[] =
"{\n"
" var       entry, symbol, predicted_entry, lhs;\n"
" var       save_token = token;\n"
" var       save_scan_level = scan_level;\n"
" var       production_length, top, index, level;\n"
" var       stack = new Array(128);\n"
"\n"
" top = 127;\n"
" stack [ top ] = 0;\n"
" predicted_entry = production_number;\n"
" index = Production_row [ predicted_entry ];\n"
" lhs = Production [ ++index ];\n"
"\n"
" for (;;) {\n"
"   top = 127;\n"
"   token = save_token;\n"
"   scan_level = save_scan_level;\n"
"   index = Production_row [ predicted_entry ];\n"
"   symbol = Production [ ++index ];\n"
"   if ( symbol != lhs ) {\n"
"       predicted_entry =   0;\n"
"       break;\n"
"   }\n"
"   production_length = Production [ index ] - 1;\n"
"   lhs = Production [ ++index ];\n"
"   index += production_length;\n"
"   for (;  production_length-- > 0;  --index ) {\n"
"       if ( top > 0 ) { stack [--top] = Production [index];\n"
"       } else { return 0; }\n"
"   }\n"
"   symbol = (stack[top] != 0  ? stack[top++] :   0);\n"
"\n"
"   for ( ;  symbol != 0 ;  symbol = (stack[top] != 0  ? stack[top++] :   0) ) {\n"
"\n"
"       if ( symbol >= START_SYMBOL  &&  symbol < START_ACTION ) {\n"
"           entry = 0;\n"
"           production_number = get_conditional_production ( symbol );\n"
"           if ( production_number != 0 ) {\n"
"               entry = get_predicted_entry ( tokens,\n"
"                                             production_number, token,\n"
"                                             scan_level, depth + 1 );\n"
"           }\n"
"           if ( entry == 0 ) {\n"
"               index = Parse_row [ symbol - (START_SYMBOL-1) ];\n"
"               index += token;\n"
"               entry = Parse [ index ];\n"
"           }\n"
"           level = scan_level;\n"
"           while ( entry >= START_CONFLICT ) {\n"
"               index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"               index += tokens.peek (level);\n"
"               entry = Conflict [ index ];\n"
"               ++level;\n"
"           }\n"
"           if ( entry != 0 ) {\n"
"               index = Production_row [ entry ];\n"
"               production_length = Production [ index ] - 1;\n"
"               lhs = Production [ ++index ];\n"
"               if ( lhs == symbol ) {\n"
"                 index += production_length;\n"
"                 for (;  production_length-- > 0;  --index ) {\n"
"                     if ( top > 0 ) { stack [--top] = Production [index];\n"
"                     } else { return 0; }\n"
"                 }\n"
"               } else {\n"
"                   ++predicted_entry;\n"
"                   break;\n"
"               }\n"
"           } else {\n"
"               ++predicted_entry;\n"
"               break;\n"
"           }\n"
"       } else if ( symbol > 0 ) {\n"
"           if ( symbol == token ) {\n"
"               token = tokens.peek ( scan_level++ );\n"
"           } else {\n"
"               ++predicted_entry;\n"
"               break;\n"
"           }\n"
"       }\n"
"   }\n"
"   if ( symbol == 0 ) {\n"
"       break;\n"
"   }\n"
" }\n"
" return  predicted_entry;\n"
"}\n";
static char js_ll_parse[] =
"function\n"
"parse ( action, tokens, error, start_symbol )\n"
"{\n"
" var     lhs;\n"
" var     production_number, entry, symbol, token, new_token;\n"
" var       production_length, top, index, level;\n"
" var   stack = new Array(512);\n"
"\n"
" top = 511;\n"
" stack [ top ] = 0;\n"
" if ( start_symbol == 0 ) {\n"
"     start_symbol = START_SYMBOL;\n"
" }\n"
" if ( top > 0 ) { stack [--top] = start_symbol;\n"
" } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
" token = tokens.get();\n"
" new_token = token;\n"
"\n"
" for ( symbol = (stack[top] != 0  ? stack[top++] : 0);  symbol != 0; ) {\n"
"\n"
"     if ( symbol >= START_ACTION ) {\n"
"         action.execute ( symbol - (START_ACTION-1) );\n"
"\n"
"     } else if ( symbol >= START_SYMBOL ) {\n"
"         entry = 0;\n"
"         level = 1;\n"
"         production_number = get_conditional_production ( symbol );\n"
"         if ( production_number != 0 ) {\n"
"             entry = get_predicted_entry ( tokens,\n"
"                                           production_number, token,\n"
"                                           level, 1 );\n"
"         }\n"
"         if ( entry == 0 ) {\n"
"             index = Parse_row [ symbol - (START_SYMBOL-1) ];\n"
"             index += token;\n"
"             entry = Parse [ index ];\n"
"         }\n"
"         while ( entry >= START_CONFLICT ) {\n"
"             index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"             index += tokens.peek (level);\n"
"             entry = Conflict [ index ];\n"
"             ++level;\n"
"         }\n"
"         if ( entry != 0 ) {\n"
"             index = Production_row [ entry ];\n"
"             production_length = Production [ index ] - 1;\n"
"             lhs = Production [ ++index ];\n"
"             if ( lhs == symbol ) {\n"
"                 action.predict ( entry );\n"
"                 index += production_length;\n"
"                 for (;  production_length-- > 0;  --index ) {\n"
"                     if ( top > 0 ) { stack [--top] = Production [index];\n"
"                     } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
"                 }\n"
"             } else {\n"
"                 new_token = error.no_entry ( symbol, token, level-1 );\n"
"             }\n"
"         } else {                                       // no table entry\n"
"             new_token = error.no_entry ( symbol, token, level-1 );\n"
"         }\n"
"     } else if ( symbol > 0 ) {\n"
"         if ( symbol == token ) {\n"
"             token = tokens.get();\n"
"             new_token = token;\n"
"         } else {\n"
"             new_token = error.mismatch ( symbol, token );\n"
"         }\n"
"     } else {\n"
"         error.message ( \"\\n parser error: symbol value 0\\n\" );\n"
"     }\n"
"     if ( token != new_token ) {\n"
"         if ( new_token != 0 ) {\n"
"             token = new_token;\n"
"         }\n"
"         if ( token != END_OF_SLK_INPUT_ ) {\n"
"             continue;\n"
"         }\n"
"     }\n"
"     symbol = (stack[top] != 0  ? stack[top++] : 0);\n"
" }\n"
" if ( token != END_OF_SLK_INPUT_ ) {\n"
"     error.input_left ();\n"
" }\n"
"}\n";
static char js_lr_parse[] =
"function\n"
"parse (   action,\n"
"           tokens,\n"
"           error,\n"
"              start_symbol )\n"
"{\n"
" var     lhs;\n"
" var     state, production_number, entry, symbol, token, new_token;\n"
" var       action_number, production_length, top, index, level;\n"
" var   stack = new Array(512);\n"
"\n"
" top = 511;\n"
" stack [ top ] = 0;\n"
" if ( start_symbol == 0 ) {\n"
"     start_symbol = START_SYMBOL;\n"
" }\n"
" if ( top > 0 ) { stack [--top] = 1;\n"
" } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
" token = tokens.get();\n"
" new_token = token;\n"
"\n"
" for ( state = stack[top];  state != 0;  ) {\n"
"     index = Parse_row [ state ];\n"
"     index += token;\n"
"     entry = Parse [ index ];\n"
"     if ( state != Parse_state [ index ] )  entry = 0;\n"
"     level = 1;\n"
"     action.state ( state );\n"
"\n"
"     if ( entry >= START_CONFLICT ) {\n"
"         while ( entry >= START_CONFLICT && entry < END_CONFLICT ) {\n"
"             index = Conflict_row [entry - (START_CONFLICT -1)];\n"
"             index += tokens.peek (level);\n"
"             entry = Conflict [ index ];\n"
"             ++level;\n"
"         }\n"
"     }\n"
"     if ( entry >= START_STATE ) {\n"
"         state =   (entry - (START_STATE - 1));\n"
"         if ( top > 0 ) { stack [--top] = state;\n"
"         } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
"         token = tokens.get();\n"
"         new_token = token;\n"
"\n"
"     } else if ( entry > 0 ) {\n"
"         action.reduce ( entry );\n"
"         production_number = entry;\n"
"         action_number = Action_number [production_number];\n"
"         if ( action_number != 0 ) {\n"
"             action_number -= (START_ACTION-1);\n"
"             if ( action_number < END_ACTION ) {\n"
"                 action.execute ( action_number );\n"
"             } else {\n"
"                 error.message ( \"\\n error: action out of range\\n\" );\n"
"             }\n"
"         }\n"
"         index = Production_row [ entry ];\n"
"         production_length = Production [ index ] - 1;\n"
"         lhs = Production [ ++index ];\n"
"         for (;  production_length > 0;  --production_length ) {\n"
"              if ( stack[top] != 0 )  ++top;\n"
"         }\n"
"         state = stack[top];\n"
"         index = Parse_row [ state ];\n"
"         index += lhs;\n"
"         entry = Parse [ index ];\n"
"         if ( state != Parse_state [ index ] )  entry = 0;\n"
"         if ( entry >= START_CONFLICT ) {\n"
"             error.message ( \"\\n reduce error: conflict not state\\n\" );\n"
"         } else if ( entry >= START_STATE ) {\n"
"             state =   (entry - (START_STATE - 1));\n"
"             if ( top > 0 ) { stack [--top] = state;\n"
"             } else { error.message (\"xxxParse: stack overflow\\n\"); return; }\n"
"         } else if ( entry > 0 ) {\n"
"             error.message ( \"\\n reduce error: not a state\\n\" );\n"
"         } else if ( token != END_OF_SLK_INPUT_ ) {\n"
"             new_token = error.no_entry ( state, token, level-1 );\n"
"         }\n"
"     } else {\n"
"         new_token = error.no_entry ( state, token, level-1 );\n"
"         if ( new_token == END_OF_SLK_INPUT_ ) {\n"
"             break;\n"
"         }\n"
"     }\n"
"     if ( token != new_token ) {\n"
"         if ( new_token != 0 ) {\n"
"             token = new_token;\n"
"         }\n"
"     }\n"
"     state = stack[top];\n"
"     if ( state <= 1 ) {\n"
"         break;\n"
"     }\n"
" }\n"
" if ( token != END_OF_SLK_INPUT_ ) {\n"
"     error.input_left ();\n"
" }\n"
"}\n";
// ================ Per-language output descriptors ================
typedef struct LanguageDescriptor
{
    char* extension;
    char* array_begin;
    char* array_end;
    char* array_assign;
    char* package_keyword;
    char* class_keyword;
    char* cast;
    char* short_type;
    char* private_short_const;
    char* public_short_const;
    char* public_int_const;
    char* private_static_short;
    char* private_static_short_array;
    char* public_static_short_array;
    char* public_static_string_array;
    char* get_production_array_code;
    char* get_symbol_type_code;
    char* is_nonterminal_code;
    char* is_terminal_code;
    char* is_action_code;
    char* get_terminal_index_code;
    char* get_production_code;
    char* predicted_entry_decl_code;
    char* predicted_entry_body_code;
    char* ll_parse_code;
    char* lr_parse_code;
} LanguageDescriptor;
static LanguageDescriptor java_descriptor = {
    "java",
    "{",
    "}",
    "",
    "package",
    "public class",
    "(short)",
    "short",
    "private static final short",
    "public static final short",
    "public static final int",
    "private static short",
    "private static short[]",
    "public static short[]",
    "public static String[]",
    m_get_production_array,
    m_get_symbol_type,
    m_is_nonterminal,
    m_is_terminal,
    m_is_action,
    m_get_terminal_index,
    m_get_production,
    m_predicted_entry_decl,
    m_predicted_entry_body,
    m_ll_parse,
    m_lr_parse };
static LanguageDescriptor js_descriptor = {
    "js",
    "[",
    "]",
    "=",
    "",
    "var",
    "",
    "",
    "var",
    "var",
    "var",
    "function",
    "var",
    "var",
    "var",
    js_get_production_array,
    js_get_symbol_type,
    js_is_nonterminal,
    js_is_terminal,
    js_is_action,
    js_get_terminal_index,
    js_get_production,
    js_predicted_entry_decl,
    js_predicted_entry_body,
    js_ll_parse,
    js_lr_parse };
static LanguageDescriptor cs_descriptor = {
    "cs",
    "{",
    "}",
    "",
    "namespace",
    "class",
    "(short)",
    "short",
    "private const short",
    "public const short",
    "public const int",
    "private static short",
    "private static short[]",
    "public static short[]",
    "public static string[]",
    m_get_production_array,
    m_get_symbol_type,
    m_is_nonterminal,
    m_is_terminal,
    m_is_action,
    m_get_terminal_index,
    l850_cs,
    l851_cs,
    l852_cs,
    l853_cs,
    l854_cs };
static LanguageDescriptor active_descriptor;
static void
write_action_execute(char* parser_name,
    uint generate_flags,
    uint yacc_grammar)
{
    register Symbol** symbol;
    int action_number,
        action_count = 0;
    FILE* out_stream;
    uchar* name_cursor,
        * name_end,
        * type_name = "public void ",
        * execute_assign = "",
        * execute_number_type = "int",
        file_name[32];
    sprintf(file_name, "%sExecute.txt", parser_name);
    if (generate_flags & 0x00002000) {
        type_name = "this.";
        execute_assign = "= function";
        execute_number_type = "";
    }
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1118, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "// This file can be edited into the SlkAction class. \n\n");
    fprintf(out_stream, "%sexecute %s ( %s  number )\n"
        "{\n"
        "  switch ( number ) {\n",
        type_name, execute_assign, execute_number_type);
    for (symbol = actions; *++symbol; ++action_count) {
        name_cursor = (*symbol)->name;
        action_number = (*symbol)->number;
        name_end = name_cursor;
        if (!yacc_grammar) {
            name_end += action_prefix_len(name_end);
        }
        fprintf(out_stream, "    case %d:  %s();  break;\n",
            (action_number - (start_action - 1)), name_end);
        if (((*name_end >= '0' && *name_end <= '9'))) {
            fatal_error(1119, "Cannot mix numbered actions with named actions");
        }
    }
    fprintf(out_stream, "  }\n}\n");
    fclose(out_stream);
}
static void
write_keywords_file(char* parser_name,
    char* namespace_name,
    uint generate_flags)
{
    register Symbol** symbol;
    int number,
        eof_token_number,
        first_entry;
    Symbol* eof_label;
    FILE* out_stream;
    uchar file_name[32],
        constants_prefix[32] = "",
        * define_name,
        * name;
    char* static_keyword = "static";
    if (generate_flags & 0x00000800) {
        static_keyword = "";
    }
    if (!(generate_flags & 0x00002000)) {
        sprintf(constants_prefix, "%sConstants.", parser_name);
    }
    sprintf(file_name, "%sKeywords.txt", parser_name);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1191, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    fprintf(out_stream, "// Assumes all alpha terminals are keywords, "
        "usually needs manual editing to remove non-keywords.\n\n");
    if (!(generate_flags & 0x00002000)) {
        fprintf(out_stream, "%s %sKeywords {\n\n", active_descriptor.class_keyword, parser_name);
    }
    eof_label = find_symbol("END_OF_SLK_INPUT");
    eof_token_number = eof_label->number;
    fprintf(out_stream, "%s name = %s\n\n", active_descriptor.public_static_string_array, active_descriptor.array_begin);
    first_entry = 0;
    for (symbol = terminals; *++symbol;) {
        number = (*symbol)->number;
        if (number == eof_token_number) {
            continue;
        }
        name = (*symbol)->name;
        if (name && (((*name >= 'a' && *name <= 'z')) || ((*name >= 'A' && *name <= 'Z'))) || (((*(name + 1) >= 'a' && *(name + 1) <= 'z')) || ((*(name + 1) >= 'A' && *(name + 1) <= 'Z')))) {
            if (first_entry) {
                fprintf(out_stream, ",\"%s\"\n", name);
            }
            else {
                fprintf(out_stream, " \"%s\"\n", name);
                first_entry = 1;
            }
        }
    }
    fprintf(out_stream, "%s; \n\n", active_descriptor.array_end);
    if (generate_flags & 0x00002000) {
        fprintf(out_stream, "var token = [\n\n");
    }
    else {
        fprintf(out_stream, "public %s short[] token = {\n\n", static_keyword);
    }
    first_entry = 0;
    for (symbol = terminals; *++symbol;) {
        number = (*symbol)->number;
        if (number == eof_token_number) {
            continue;
        }
        name = (*symbol)->name;
        if (name && (((*name >= 'a' && *name <= 'z')) || ((*name >= 'A' && *name <= 'Z'))) || (((*(name + 1) >= 'a' && *(name + 1) <= 'z')) || ((*(name + 1) >= 'A' && *(name + 1) <= 'Z')))) {
            define_name = (*symbol)->define_name;
            if (first_entry) {
                fprintf(out_stream, ",%s%s \n", constants_prefix, define_name);
            }
            else {
                fprintf(out_stream, " %s%s \n", constants_prefix, define_name);
                first_entry = 1;
            }
        }
    }
    fprintf(out_stream, "%s; \n\n", active_descriptor.array_end);
    if (!(generate_flags & 0x00002000)) {
        fprintf(out_stream, "}; \n\n");
    }
    if (!(generate_flags & 0x00000400)) {
        if (namespace_name) {
            fprintf(out_stream, "\n\n}\n");
        }
    }
    fclose(out_stream);
}
static void
write_constants_file(char* parser_name,
    char* namespace_name,
    uint generate_flags)
{
    register Symbol** symbol;
    int number;
    FILE* out_stream;
    uchar file_name[32],
        * define_name;
    char* prefix = "",
        * suffix = "";
    if (generate_flags & 0x00000002) {
        suffix = parser_name;
    }
    sprintf(file_name, "%sConstants.%s", parser_name, active_descriptor.extension);
    out_stream = fopen(file_name, "w");
    if (!out_stream) {
        perror(file_name);
        fatal_error(1121, "");
    }
    fprintf(out_stream, "\n// %s - generated by the SLK parser generator \n\n", file_name);
    if (namespace_name) {
        if (generate_flags & 0x00000400)
            fprintf(out_stream, "%s %s;\n\n", active_descriptor.package_keyword, namespace_name);
        else
            fprintf(out_stream, "%s %s {\n\n", active_descriptor.package_keyword, namespace_name);
    }
    if (!(generate_flags & 0x00002000)) {
        fprintf(out_stream, "%s %sConstants {\n\n", active_descriptor.class_keyword, parser_name);
    }
    for (symbol = terminals; *++symbol;) {
        number = (*symbol)->number;
        define_name = token_define_name(prefix, suffix, symbol, 1);
        (*symbol)->define_name = str_dup(define_name);
        fprintf(out_stream, "%s  %s = %d;\n", active_descriptor.public_short_const, define_name, number);
    }
    fprintf(out_stream, "\n\n");
    prefix = "NT_";
    for (symbol = nonterminals; *++symbol;) {
        number = (*symbol)->number;
        define_name = token_define_name(prefix, suffix, symbol, 0);
        fprintf(out_stream, "%s  %s = %d;\n", active_descriptor.public_short_const, define_name, number);
    }
    if (!(generate_flags & 0x00002000)) {
        fprintf(out_stream, "\n\n};\n");
    }
    if (!(generate_flags & 0x00000400)) {
        if (namespace_name) {
            fprintf(out_stream, "\n\n}\n");
        }
    }
    fclose(out_stream);
}
static void
write_conditional_managed(register FILE* out_file)
{
    register Symbol** nonterminal;
    int production_number,
        count = 0,
        conditional_threshold;
    if (conditional_count == 0) {
        fprintf(out_file, "%s get_conditional_production ( %s symbol ) "
            "{ return %s 0; }\n\n",
            active_descriptor.private_static_short, active_descriptor.short_type,
            active_descriptor.cast);
    }
    else if (conditional_count == 1) {
        fprintf(out_file, "%s get_conditional_production ( %s symbol )\n"
            "{ return (",
            active_descriptor.private_static_short, active_descriptor.short_type);
        for (nonterminal = nonterminals; *++nonterminal;) {
            if ((*nonterminal)->conditional) {
                production_number = production_number_of(*nonterminal);
                fprintf(out_file, " symbol == %d ? %d :", (*nonterminal)->number,
                    production_number);
            }
        }
        fprintf(out_file, " %s 0 ); }\n\n", active_descriptor.cast);
    }
    else {
        conditional_threshold = start_symbol_number + nonterminal_count - 1 -
            conditional_count;
        fprintf(out_file, "%s Conditional_production = {0\n", active_descriptor.private_static_short_array);
        for (nonterminal = nonterminals; *++nonterminal;) {
            if ((*nonterminal)->conditional) {
                production_number = production_number_of(*nonterminal);
                fprintf(out_file, ",%d", production_number);
                if (++count > 20) {
                    count = 0;
                    fputs("\n", out_file);
                }
            }
        }
        fprintf(out_file, "};\n\n");
        fprintf(out_file,
            "%s get_conditional_production ( %s symbol )\n"
            "{ return ( symbol > %d ? Conditional_production [symbol - %d]"
            " : %s 0 ); }\n\n",
            active_descriptor.private_static_short, active_descriptor.short_type,
            conditional_threshold, conditional_threshold, active_descriptor.cast);
    }
}
static void
patch_managed_templates(char* parser_name,
    uint generate_flags)
{
    char* template_cursor,
        * template_cursor2;
    for (template_cursor = m_predicted_entry_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = m_predicted_entry_body; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    if (!(generate_flags & 0x00000080)) {
        for (template_cursor = m_predicted_entry_body; template_cursor;) {
            template_cursor = strstr(template_cursor, "display != 0");
            if (template_cursor) {
                strncpy(template_cursor, "    false   ", 12);
            }
        }
    }
    if (!(generate_flags & 0x00000001)) {
        for (template_cursor = m_lr_parse; template_cursor;) {
            template_cursor = strstr(template_cursor, "if ( state != Parse_state");
            if (template_cursor) {
                strncpy(template_cursor, "//   ", 5);
            }
        }
    }
    for (template_cursor = m_lr_parse; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = m_ll_parse; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = m_get_production; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = l851_cs; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = l852_cs; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    if (!(generate_flags & 0x00000080)) {
        for (template_cursor = l852_cs; template_cursor;) {
            template_cursor = strstr(template_cursor, "display != 0");
            if (template_cursor) {
                strncpy(template_cursor, "    false   ", 12);
            }
        }
    }
    if (!(generate_flags & 0x00000001)) {
        for (template_cursor = l854_cs; template_cursor;) {
            template_cursor = strstr(template_cursor, "if ( state != Parse_state");
            if (template_cursor) {
                strncpy(template_cursor, "//   ", 5);
            }
        }
    }
    for (template_cursor = l854_cs; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = l853_cs; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = l850_cs; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    if (generate_flags & 0x00000800) {
        for (template_cursor = m_is_nonterminal; template_cursor;) {
            template_cursor = strstr(template_cursor, "ean");
            if (template_cursor) {
                strncpy(template_cursor, "   ", 3);
            }
            break;
        }
        for (template_cursor = m_is_terminal; template_cursor;) {
            template_cursor = strstr(template_cursor, "ean");
            if (template_cursor) {
                strncpy(template_cursor, "   ", 3);
            }
            break;
        }
        for (template_cursor = m_is_action; template_cursor;) {
            template_cursor = strstr(template_cursor, "ean");
            if (template_cursor) {
                strncpy(template_cursor, "   ", 3);
            }
            break;
        }
    }
    for (template_cursor2 = m_get_production_array; template_cursor2;) {
        char count[32];
        sprintf(count, "%d];", max_production_length + 4);
        template_cursor2 = strstr(template_cursor2, "yyy");
        if (template_cursor2) {
            strncpy(template_cursor2, count, strlen(count));
        }
        break;
    }
}
static void
patch_js_templates(char* parser_name,
    uint generate_flags)
{
    char* template_cursor,
        * template_cursor2;
    for (template_cursor = js_predicted_entry_decl; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = js_predicted_entry_body; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    if (!(generate_flags & 0x00000080)) {
        for (template_cursor = js_predicted_entry_body; template_cursor;) {
            template_cursor = strstr(template_cursor, "display != 0");
            if (template_cursor) {
                strncpy(template_cursor, "    false   ", 12);
            }
        }
    }
    if (!(generate_flags & 0x00000001)) {
        for (template_cursor = js_lr_parse; template_cursor;) {
            template_cursor = strstr(template_cursor, "if ( state != Parse_state");
            if (template_cursor) {
                strncpy(template_cursor, "//   ", 5);
            }
        }
    }
    for (template_cursor = js_lr_parse; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = js_ll_parse; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    for (template_cursor = js_get_production; template_cursor;) {
        template_cursor = strstr(template_cursor, "xxx");
        if (template_cursor) {
            strncpy(template_cursor, parser_name, 3);
        }
    }
    if (generate_flags & 0x00000800) {
        for (template_cursor = js_is_nonterminal; template_cursor;) {
            template_cursor = strstr(template_cursor, "ean");
            if (template_cursor) {
                strncpy(template_cursor, "   ", 3);
            }
            break;
        }
        for (template_cursor = js_is_terminal; template_cursor;) {
            template_cursor = strstr(template_cursor, "ean");
            if (template_cursor) {
                strncpy(template_cursor, "   ", 3);
            }
            break;
        }
        for (template_cursor = js_is_action; template_cursor;) {
            template_cursor = strstr(template_cursor, "ean");
            if (template_cursor) {
                strncpy(template_cursor, "   ", 3);
            }
            break;
        }
    }
    for (template_cursor2 = js_get_production_array; template_cursor2;) {
        char count[32];
        sprintf(count, "%d);", max_production_length + 4);
        template_cursor2 = strstr(template_cursor2, "yyy");
        if (template_cursor2) {
            strncpy(template_cursor2, count, strlen(count));
        }
        break;
    }
}
void generate_managed_parser(char* parser_name,
    char* namespace_name,
    int named_actions,
    uint generate_flags,
    FILE* out_file,
    int yacc_grammar)
{
    Symbol* symbol;
    if (generate_flags & 0x00002000) {
        active_descriptor = js_descriptor;
    }
    else if (generate_flags & 0x00000400) {
        active_descriptor = java_descriptor;
    }
    else if (generate_flags & 0x00000800) {
        active_descriptor = cs_descriptor;
    }
    patch_managed_templates(parser_name, generate_flags);
    patch_js_templates(parser_name, generate_flags);
    write_constants_file(parser_name, namespace_name, generate_flags);
    write_keywords_file(parser_name, namespace_name, generate_flags);
    if (named_actions) {
        write_action_execute(parser_name, generate_flags, yacc_grammar);
    }
    write_conditional_managed(out_file);
    symbol = find_symbol("END_OF_SLK_INPUT");
    fprintf(out_file, "%s   %s_ = %d;\n",
        active_descriptor.private_short_const, "END_OF_SLK_INPUT", symbol->number);
    fprintf(out_file, "%s   START_SYMBOL = %d;\n",
        active_descriptor.private_short_const, start_symbol_number);
    fprintf(out_file, "%s   START_STATE = %d;\n",
        active_descriptor.private_short_const, start_state);
    fprintf(out_file, "%s   START_CONFLICT = %d;\n",
        active_descriptor.private_short_const, start_conflict);
    fprintf(out_file, "%s   END_CONFLICT = %d;\n",
        active_descriptor.private_short_const, start_conflict + conflict_count);
    fprintf(out_file, "%s   START_ACTION = %d;\n",
        active_descriptor.private_short_const, start_action);
    fprintf(out_file, "%s   END_ACTION = %d;\n",
        active_descriptor.private_short_const, start_action + action_count);
    fprintf(out_file, "%s   TOTAL_CONFLICTS = %d;\n\n",
        active_descriptor.private_short_const, conflict_count);
    fprintf(out_file, "%s   NOT_A_SYMBOL = 0;\n", active_descriptor.public_int_const);
    fprintf(out_file, "%s   NONTERMINAL_SYMBOL = 1;\n", active_descriptor.public_int_const);
    fprintf(out_file, "%s   TERMINAL_SYMBOL = 2;\n", active_descriptor.public_int_const);
    fprintf(out_file, "%s   ACTION_SYMBOL = 3;\n\n", active_descriptor.public_int_const);
    fprintf(out_file, "%s   PARSE_STACK_SIZE = %d;\n\n", active_descriptor.public_int_const, parse_stack_size);
    fprintf(out_file, "%s\n", active_descriptor.get_production_array_code);
    fprintf(out_file, "%s\n", active_descriptor.get_symbol_type_code);
    fprintf(out_file, "%s\n", active_descriptor.is_nonterminal_code);
    fprintf(out_file, "%s\n", active_descriptor.is_terminal_code);
    fprintf(out_file, "%s\n", active_descriptor.is_action_code);
    fprintf(out_file, "%s\n", active_descriptor.get_terminal_index_code);
    fprintf(out_file, "%s\n", active_descriptor.get_production_code);
    fprintf(out_file, "%s", active_descriptor.predicted_entry_decl_code);
    if (conditional_count > 0) {
        fprintf(out_file, "%s\n", active_descriptor.predicted_entry_body_code);
    }
    else {
        fprintf(out_file, "{\n return  0;\n}\n\n");
    }
    if (generate_flags & 0x00000004) {
        fprintf(out_file, "%s\n", active_descriptor.ll_parse_code);
    }
    else if (generate_flags & 0x00000008) {
        fprintf(out_file, "%s\n", active_descriptor.lr_parse_code);
    }
    if (!(generate_flags & 0x00002000)) {
        fprintf(out_file, "\n\n};\n");
    }
}
#include <stdio.h>
#include <stdlib.h>

static Production(list_next)(ProductionList* list)
{
    if (list->conflict_cursor < list->count) {
        return list->list[list->conflict_cursor++];
    }
    else {
        return NULL;
    }
}
static void(list_append)(ProductionList* list,
    Production production)
{
    if (list->count >= list->capacity) {
        list->list = (Production*)realloc(list->list,
            (list->capacity + 1 + list->increment) * sizeof(Production));
        if (!list->list) {
            puts("list_t: out of memory");
            exit(1);
        }
        list->capacity += list->increment - 1;
    }
    list->list[list->count++] = production;
}
static void(list_print)(ProductionList* list)
{
    int depth;
    for (depth = 0; depth < list->count; ++depth) {
        puts((*(list->list[depth]))->name);
    }
}
static void(list_reset)(ProductionList* list)
{
    list->conflict_cursor = 0;
}
static void(list_free)(ProductionList* list)
{
    free(list->list);
}
void list_init(ProductionList* list)
{
    int increment = 64 * 1024;
    list->conflict_cursor = 0;
    list->count = 0;
    list->increment = increment;
    list->capacity = increment - 1;
    list->list = (Production*)malloc(increment * sizeof(Production));
    list->list_reset = list_reset;
    list->list_next = list_next;
    list->list_append = list_append;
    list->list_print = list_print;
    list->list_free = list_free;
}
extern char* array_close;
typedef struct LRAction
{
    struct LRAction* next;
    uint token;
    uint block;
    struct LRItem* config;
} LRAction;
typedef struct LRItem
{
    struct LRItem* next;
    struct Symbol** lhs,
        ** dot;
    struct SymbolSetNode* follows;
    uint production_number;
    uint expanded;
} LRItem;
typedef struct LRGoto
{
    struct LRGoto* next;
    struct LRState* state;
    Symbol* symbol;
} LRGoto;
typedef struct LRState
{
    struct LRState* next;
    uint number;
    struct LRItem* items;
    struct LRGoto* gotos;
    struct LRAction* row;
    uint action_count;
    uint visited;
} LRState;
uint state_count = 0;
uint symbol_count = 0;
uint start_state = 0;
uint lr_production_count = 0;
uint last_state_number = 0;
static LRState* lr_states = NULL;
static LRState* last_lr_state = NULL;
static LRItem* free_lr_item_nodes = NULL;
static uint reused_item_count = 0;
static void print_lr_item(register LRItem* config);
static LRItem*
alloc_recycled_lr_item(void)
{
    register LRItem* config = free_lr_item_nodes;
    if (config) {
        free_lr_item_nodes = config->next;
        memset(config, 0, sizeof(LRItem));
        ++reused_item_count;
    }
    return config;
}
static void
free_lr_items(LRItem* list)
{
    register LRItem* node,
        * last_node;
    if (!(conserve_memory && list)) {
        return;
    }
    for (node = list; node; node = node->next) {
        last_node = node;
    }
    if (free_lr_item_nodes) {
        last_node->next = free_lr_item_nodes;
    }
    free_lr_item_nodes = list;
}
static LRItem*
new_lr_item(void)
{
    register LRItem* config;
    static int block_left = 0;
    static LRItem* block;
    if (--block_left > 0) {
        ++block;
        config = block;
    }
    else {
        block_left = 0;
        config = alloc_recycled_lr_item();
        if (!config) {
            block_left = 1024;
            block = (LRItem*)calloc(block_left, sizeof(LRItem));
            config = block;
            if (!config) {
                fatal_error(2304, "out of memory");
            }
        }
    }
    return config;
}
static LRAction*
new_lr_action(void)
{
    register LRAction* lr_action;
    static int block_left = 0;
    static LRAction* block;
    if (--block_left > 0) {
        ++block;
        lr_action = block;
    }
    else {
        block_left = 1024;
        block = (LRAction*)calloc(block_left, sizeof(LRAction));
        lr_action = block;
        if (!lr_action) {
            fatal_error(2301, "out of memory");
        }
    }
    return lr_action;
}
static LRGoto*
new_lr_goto(void)
{
    register LRGoto* lr_goto;
    static int block_left = 0;
    static LRGoto* block;
    if (--block_left > 0) {
        ++block;
        lr_goto = block;
    }
    else {
        block_left = 1024;
        block = (LRGoto*)calloc(block_left, sizeof(LRGoto));
        lr_goto = block;
        if (!lr_goto) {
            fatal_error(2302, "out of memory");
        }
    }
    return lr_goto;
}
static LRState*
new_lr_state(void)
{
    register LRState* state;
    static int block_left = 0;
    static LRState* block;
    if (--block_left > 0) {
        ++block;
        state = block;
    }
    else {
        block_left = 1024;
        block = (LRState*)calloc(block_left, sizeof(LRState));
        state = block;
        if (!state) {
            fatal_error(2303, "out of memory");
        }
    }
    return state;
}
static void
add_lr_goto(LRState* state,
    LRState* target_state,
    Symbol* symbol)
{
    register LRGoto* lr_goto;
    for (lr_goto = state->gotos; lr_goto; lr_goto = lr_goto->next) {
        if (lr_goto->state == target_state) {
            return;
        }
    }
    lr_goto = new_lr_goto();
    lr_goto->state = target_state;
    lr_goto->symbol = symbol;
    lr_goto->next = state->gotos;
    state->gotos = lr_goto;
}
static uint
lr_items_equal(register LRItem* dest_configs,
    register LRItem* src_configs,
    uint lr_type)
{
    for (; dest_configs && src_configs; dest_configs = dest_configs->next, src_configs = src_configs->next) {
        if (dest_configs->dot != src_configs->dot) {
            break;
        }
        if (lr_type == 0x00040000) {
            if (!sets_equal_unordered(dest_configs->follows, src_configs->follows)) {
                break;
            }
        }
    }
    return (!(dest_configs || src_configs));
}
static void
print_lr_follows(register SymbolSetNode* follows,
    LRItem* config)
{
    if (config) {
        print_lr_item(config);
    };
    for (; follows; follows = follows->next) {
        ;
    };
    ;
}
static void
compute_lr_follows(LRItem** items)
{
    register LRItem* config;
    register Symbol** dot;
    Symbol* lhs,
        ** rhs_cursor;
    uint changed = 1;
    for (config = *items; config; config = config->next) {
        lhs = *config->lhs;
        lhs->la_follows = NULL;
        for (dot = config->dot; *dot; ++dot) {
            (*dot)->la_follows = NULL;
        }
    }
    while (changed) {
        changed = 0;
        for (config = *items; config; config = config->next) {
            lhs = *config->lhs;
            dot = config->dot;
            for (; *dot && ((*dot)->type == 3); ++dot)
                ;
            if (!*dot) {
                continue;
            }
            rhs_cursor = dot;
            for (++rhs_cursor; *rhs_cursor; ++rhs_cursor) {
                if ((*rhs_cursor)->type == 3) {
                    continue;
                }
                changed |= set_union_front(&(*dot)->la_follows,
                    (*rhs_cursor)->firsts);
                if (!(*rhs_cursor)->nullable) {
                    break;
                }
            }
            if (!*rhs_cursor) {
                changed |= set_union_front(&(*dot)->la_follows, config->follows);
                changed |= set_union_front(&(*dot)->la_follows, lhs->la_follows);
                ;
                ;
                ;
                ;
            }
        }
    }
    config = *items;
    if (config) {
        config = config->next;
    }
    for (; config; config = config->next) {
        lhs = *config->lhs;
        set_union_front(&config->follows, lhs->la_follows);
        ;
        ;
    }
}
static void
clear_visited_flags(void)
{
    register LRState* state;
    for (state = lr_states; state; state = state->next) {
        state->visited = 0;
    }
}
static int
propagate_follows(LRState* state)
{
    register LRItem* config,
        * lr_item;
    register LRGoto* lr_goto;
    LRItem* single_lr_item;
    uint changed = 0;
    for (lr_goto = state->gotos; lr_goto; lr_goto = lr_goto->next) {
        if (lr_goto->state->visited) {
            continue;
        }
        if (lr_goto->state == state) {
            continue;
        }
        lr_goto->state->visited = 1;
        for (config = state->items; config; config = config->next) {
            if (*config->dot != lr_goto->symbol) {
                continue;
            }
            lr_item = lr_goto->state->items;
            for (; lr_item; lr_item = lr_item->next) {
                if (lr_item->production_number == config->production_number) {
                    changed |= set_union_front(&lr_item->follows, config->follows);
                    single_lr_item = lr_item;
                    compute_lr_follows(&single_lr_item);
                    break;
                }
            }
        }
    }
    return changed;
}
static LRState*
find_or_add_lr_state(LRItem* items,
    uint lr_type)
{
    register LRState* state;
    LRItem* existing_item,
        * out_config;
    uint changed = 1;
    for (state = lr_states; state; state = state->next) {
        if (lr_items_equal(state->items, items, lr_type)) {
            if (lr_type == 0x00020000) {
                existing_item = state->items;
                out_config = items;
                while (existing_item && out_config) {
                    set_union_front(&existing_item->follows, out_config->follows);
                    existing_item = existing_item->next;
                    out_config = out_config->next;
                }
                while (changed) {
                    changed = 0;
                    clear_visited_flags();
                    state->visited = 1;
                    changed |= propagate_follows(state);
                }
            }
            free_lr_items(items);
            return state;
        }
    }
    state = new_lr_state();
    state->number = ++state_count;
    state->items = items;
    state->gotos = NULL;
    last_lr_state->next = state;
    last_lr_state = state;
    return state;
}
static uint
add_lr_item(LRItem** list,
    Symbol** lhs,
    Symbol** dot,
    SymbolSetNode* follows,
    uint production_number)
{
    register LRItem* last_node = NULL,
        * conflict_production;
    LRItem* new_node = NULL;
    if (!*list) {
        new_node = new_lr_item();
        new_node->lhs = lhs;
        new_node->dot = dot;
        new_node->follows = follows;
        new_node->production_number = production_number;
        *list = new_node;
        return 1;
    }
    for (conflict_production = *list; conflict_production; conflict_production = conflict_production->next) {
        last_node = conflict_production;
        if (conflict_production->dot == dot) {
            return 0;
        }
    }
    new_node = new_lr_item();
    new_node->lhs = lhs;
    new_node->dot = dot;
    new_node->follows = follows;
    new_node->production_number = production_number;
    last_node->next = new_node;
    return 1;
}
static uint
add_lr_items_from_configs(LRItem** dest_configs,
    register Config* src_configs,
    SymbolSetNode* follows,
    uint production_number)
{
    uint changed = 0;
    for (; src_configs; src_configs = src_configs->next) {
        changed |= add_lr_item(dest_configs, src_configs->lhs, src_configs->dot, follows,
            production_number++);
    }
    return changed;
}
static LRItem*
close_lr_items(LRItem** items)
{
    register LRItem* config;
    register Symbol** dot;
    uint production_number;
    uint changed = 1;
    while (changed) {
        changed = 0;
        for (config = *items; config; config = config->next) {
            dot = config->dot;
            if (*dot && (*dot)->type == 1) {
                production_number = production_number_of(*dot);
                changed |= add_lr_items_from_configs(items, (*dot)->configs,
                    NULL, production_number);
            }
        }
    }
    compute_lr_follows(items);
    return *items;
}
static LRItem*
goto_lr_items(register LRItem* config,
    Symbol* symbol)
{
    register Symbol** dot;
    LRItem* list = NULL;
    for (; config; config = config->next) {
        dot = config->dot;
        if (*dot == symbol) {
            ++dot;
            for (; *dot && ((*dot)->type == 3); ++dot)
                ;
            add_lr_item(&list, config->lhs, dot, config->follows,
                config->production_number);
            config->expanded = 1;
        }
    }
    return close_lr_items(&list);
}
static void
propagate_all_follows(void)
{
    register LRState* state;
    uint changed;
    for (changed = 1; changed;) {
        changed = 0;
        for (state = lr_states; state; state = state->next) {
            clear_visited_flags();
            changed |= propagate_follows(state);
        }
    }
}
static void
build_lr_states(uint lr_type)
{
    register LRItem* config;
    register LRState* state;
    Symbol* symbol;
    LRState* target_state;
    LRItem* out_config;
    Symbol* eof_label;
    state = new_lr_state();
    state->number = ++state_count;
    add_lr_items_from_configs(&state->items, nonterminals[1]->configs, NULL, 1);
    eof_label = find_symbol("END_OF_SLK_INPUT");
    config = state->items;
    set_add_unique(&config->follows, eof_label);
    close_lr_items(&state->items);
    lr_states = state;
    last_lr_state = state;
    for (; state; state = state->next) {
        ;
        if (trace_level == -1) {
            printf("State  %d\n", state->number);
        }
        for (config = state->items; config; config = config->next) {
            if (trace_level == -1) {
                print_lr_item(config);
            }
            symbol = *config->dot;
            if (symbol && !config->expanded) {
                out_config = goto_lr_items(config, symbol);
                target_state = find_or_add_lr_state(out_config, lr_type);
                add_lr_goto(state, target_state, symbol);
            }
        }
    }
    if (lr_type == 0x00020000) {
        propagate_all_follows();
    }
}
static LRAction*
find_lr_action(register LRAction* row,
    register uint token)
{
    for (; row; row = row->next) {
        if (row->token == token) {
            break;
        }
    }
    return row;
}
static void
insert_lr_action(LRAction** row,
    uint token,
    LRItem* config,
    uint entry_value)
{
    register LRAction* new_node,
        * block = *row;
    new_node = new_lr_action();
    new_node->token = token;
    new_node->config = config;
    new_node->block = entry_value;
    if (!block) {
        *row = new_node;
        return;
    }
    if (block->token > token) {
        new_node->next = block;
        *row = new_node;
        return;
    }
    for (; block; block = block->next) {
        if (!block->next) {
            block->next = new_node;
            break;
        }
        else if (block->next->token > token) {
            new_node->next = block->next;
            block->next = new_node;
            break;
        }
    }
}
static Config*
config_from_lr_item(LRItem* config)
{
    return new_config(config->lhs, config->dot, NULL, CONFIG_BASE);
}
static void
add_lr_reduce_actions(LRState* state,
    LRItem* config,
    int slr_grammar)
{
    register SymbolSetNode* follows_node;
    LRAction** row = &state->row;
    LRAction* lr_action_entry;
    Symbol* lhs = *config->lhs;
    uint token;
    uint production_number = config->production_number;
    if (slr_grammar) {
        follows_node = lhs->follows;
    }
    else {
        follows_node = config->follows;
    }
    for (; follows_node; follows_node = follows_node->next) {
        token = follows_node->symbol->number;
        lr_action_entry = find_lr_action(*row, token);
        if (lr_action_entry) {
            if (lr_action_entry->block != production_number) {
                Config* existing_item,
                    * out_config;
                existing_item = config_from_lr_item(lr_action_entry->config);
                out_config = config_from_lr_item(config);
                add_conflict(follows_node->symbol,
                    new_conflict_production(lr_action_entry->config->production_number,
                        lr_action_entry->block, existing_item),
                    new_conflict_production(production_number,
                        production_number, out_config),
                    state->number);
            }
        }
        else {
            insert_lr_action(row, token, config, production_number);
            ++state->action_count;
        }
    }
}
static uint
goto_state_for(register LRGoto* lr_goto,
    Symbol* symbol)
{
    uint state_number = 0;
    for (; lr_goto; lr_goto = lr_goto->next) {
        if (lr_goto->symbol == symbol) {
            state_number = lr_goto->state->number;
            break;
        }
    }
    return state_number;
}
static void
add_lr_shift_action(LRState* state,
    LRItem* config,
    Symbol* symbol)
{
    register LRAction** row = &state->row;
    LRAction* lr_action_entry;
    uint token;
    uint state_number;
    state_number = goto_state_for(state->gotos, symbol);
    state_number += lr_production_count;
    token = symbol->number;
    lr_action_entry = find_lr_action(*row, token);
    if (lr_action_entry) {
        if (lr_action_entry->block != state_number) {
            Config* existing_item, * out_config;
            uint production_number = config->production_number;
            existing_item = config_from_lr_item(lr_action_entry->config);
            out_config = config_from_lr_item(config);
            add_conflict(symbol,
                new_conflict_production(lr_action_entry->config->production_number,
                    lr_action_entry->block, existing_item),
                new_conflict_production(production_number, state_number,
                    out_config),
                state->number);
        }
    }
    else {
        insert_lr_action(row, token, config, state_number);
        ++state->action_count;
    }
}
static void
build_lr_actions(int slr_grammar)
{
    register LRItem* config;
    register LRState* state;
    Symbol* symbol;
    for (state = lr_states; state; state = state->next) {
        for (config = state->items; config; config = config->next) {
            symbol = *config->dot;
            if (symbol) {
                add_lr_shift_action(state, config, symbol);
            }
            else {
                add_lr_reduce_actions(state, config, slr_grammar);
            }
        }
    }
}
int build_lr_parser(int lr_type)
{
    int errors = 0;
    char* lr_name = "SLR";
    switch (lr_type) {
    case 0x00020000:
        lr_name = "LALR";
        break;
    case 0x00040000:
        lr_name = "LR";
        break;
    }
    start_state = production_count + 1;
    lr_production_count = production_count;
    symbol_count = nonterminal_count + terminal_count;
    ;
    ;
    build_lr_states(lr_type);
    start_conflict = production_count + state_count + 1;
    last_state_number = production_count + state_count;
    ;
    ;
    build_lr_actions(lr_type == 0x00010000);
    if (conserve_memory) {
        printf("\tLR reused config count = %u\n", reused_item_count);
    }
    return errors;
}
void resolve_lr_conflict(uint token,
    uint conflict_number)
{
    register LRState* state;
    register LRAction* row = NULL;
    Conflict* conflict;
    uint state_number = 0;
    conflict = find_conflict(conflict_number);
    if (conflict) {
        state_number = conflict->lr_state;
    }
    for (state = lr_states; state; state = state->next) {
        if (state->number == state_number) {
            row = state->row;
            break;
        }
    }
    for (; row; row = row->next) {
        if (row->token == token) {
            row->block = (conflict_number + (start_conflict - 1));
            break;
        }
    }
    if (!row) {
        ;
        ;
    }
}
static int*
compute_production_lengths(FILE* out_file,
    uint generate_flags)
{
    register Symbol*** block = productions,
        ** symbol;
    int index = 0,
        data_size;
    int* production_length;
    production_length = calloc(production_count + 4, sizeof(int));
    if (!production_length) {
        fatal_error(2307, "out of memory");
    }
    while (*++block) {
        symbol = *block;
        for (data_size = 1; *++symbol;) {
            ++data_size;
            if (generate_flags & 0x00000008) {
                if ((*symbol)->type == 3) {
                    --data_size;
                }
            }
        }
        production_length[++index] = data_size;
    }
    return production_length;
}
void write_productions(FILE* out_file,
    uint generate_flags)
{
    register Symbol*** block,
        ** symbol;
    int offset,
        length, index;
    int* production_offsets,
        * entry_value;
    int* production_length;
    if (generate_flags & 0x00002000) {
        fputs("var Production = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static slk_size_t Production[] = {0\n\n", out_file);
    }
    else {
        fputs("private static short[] Production = {0\n\n", out_file);
    }
    production_offsets = calloc(production_count + 4, sizeof(int));
    if (!production_offsets) {
        fatal_error(2308, "out of memory");
    }
    production_length = compute_production_lengths(out_file, generate_flags);
    offset = 1;
    index = 0;
    block = productions;
    entry_value = production_offsets;
    while (*++block) {
        ++entry_value;
        symbol = *block;
        fprintf(out_file, ",%u,%u", *++production_length, (*symbol)->number);
        length = 2;
        while (*++symbol) {
            if (generate_flags & 0x00000008) {
                if ((*symbol)->type == 3) {
                    continue;
                }
            }
            fprintf(out_file, ",%u", (*symbol)->number);
            ++length;
        }
        fputs(" ", out_file);
        *entry_value = offset;
        offset += length;
        index += length;
        if (index >= 16) {
            index = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
    *++entry_value = 0;
    if (generate_flags & 0x00002000) {
        fputs("var Production_row = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static slk_size_t Production_row[] = {0\n\n", out_file);
    }
    else {
        fputs("private static int[] Production_row = {0\n\n", out_file);
    }
    entry_value = production_offsets;
    for (index = 1; *++entry_value; ++index) {
        fprintf(out_file, ",%u", *entry_value);
        if (index >= 16) {
            index = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
}
static void
write_lr_state_file(char* parser_name,
    char* namespace_name,
    uint generate_flags)
{
    register LRState* state;
    register LRItem* config;
    int offset,
        dot_offset,
        index;
    int* state_offsets,
        * entry_value;
    int item_count;
    int language_flag = 0x00000100;
    FILE* out_file;
    char file_name[32];
    if (generate_flags & (0x00000200)) {
        language_flag = 0x00000200;
    }
    else if (generate_flags & (0x00001000)) {
        language_flag = 0x00001000;
    }
    else if (generate_flags & (0x00000800)) {
        language_flag = 0x00000800;
    }
    else if (generate_flags & (0x00000400)) {
        language_flag = 0x00000400;
    }
    else if (generate_flags & (0x00002000)) {
        language_flag = 0x00002000;
    }
    parser_name[3] = '\0';
    strcpy(file_name, parser_name);
    switch (language_flag) {
    case 0x00000200:
        strcat(file_name, "State.cpp");
        break;
    case 0x00000100:
    case 0x00001000:
        strcat(file_name, "State.c");
        break;
    case 0x00000800:
        strcat(file_name, "State.cs");
        break;
    case 0x00000400:
        strcat(file_name, "State.java");
        break;
    case 0x00002000:
        strcat(file_name, "State.js");
        break;
    }
    out_file = fopen(file_name, "w");
    if (!out_file) {
        perror(file_name);
        return;
    }
    fprintf(out_file, "\n// %s - generated by the SLK parser generator \n\n",
        file_name);
    if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fprintf(out_file, "#include \"%sParse.h\" \n\n", parser_name);
    }
    if (namespace_name) {
        switch (language_flag) {
        case 0x00000200:
        case 0x00000800:
            fprintf(out_file, "namespace %s {\n\n", namespace_name);
            break;
        case 0x00000400:
            fprintf(out_file, "package %s;\n\n", namespace_name);
            break;
        }
    }
    switch (language_flag) {
    case 0x00000800:
        fprintf(out_file, "class %sState {\n\n", parser_name);
        break;
    case 0x00000400:
        fprintf(out_file, "public class %sState {\n\n", parser_name);
        break;
    }
    if (generate_flags & 0x00002000) {
        fputs("var State = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static slk_size_t State[] = {0\n\n", out_file);
    }
    else {
        fputs("private static int[] State = {0\n\n", out_file);
    }
    state_offsets = calloc(state_count + 4, sizeof(int));
    if (!state_offsets) {
        fatal_error(2308, "out of memory");
    }
    offset = 1;
    index = 0;
    entry_value = state_offsets;
    for (state = lr_states; state; state = state->next) {
        ++entry_value;
        item_count = 0;
        for (config = state->items; config; config = config->next) {
            ++item_count;
        }
        item_count *= 2;
        fprintf(out_file, ",%u", item_count);
        for (config = state->items; config; config = config->next) {
            dot_offset = config->dot - config->lhs;
            fprintf(out_file, ",%u,%u", config->production_number, dot_offset);
        }
        fputs(" ", out_file);
        *entry_value = offset;
        offset += item_count + 1;
        index += item_count + 1;
        if (index >= 16) {
            index = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
    *++entry_value = 0;
    if (generate_flags & 0x00002000) {
        fputs("var State_row = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static slk_size_t State_row[] = {0\n\n", out_file);
    }
    else {
        fputs("private static int[] State_row = {0\n\n", out_file);
    }
    entry_value = state_offsets;
    for (index = 1; *++entry_value; ++index) {
        fprintf(out_file, ",%u", *entry_value);
        if (index >= 16) {
            index = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
    if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fprintf(out_file, "slk_size_t *%sGetState ( slk_size_t  state_number )\n"
            "{\n"
            "    return   &State [ State_row [state_number] ];\n"
            "}\n\n",
            parser_name);
    }
    else {
    }
    switch (language_flag) {
    case 0x00000800:
    case 0x00000400:
        fprintf(out_file, "\n}\n\n");
        break;
    }
    if (namespace_name) {
        switch (language_flag) {
        case 0x00000200:
        case 0x00000800:
            fprintf(out_file, "\n\n}\n");
            break;
        }
    }
    fclose(out_file);
}
static void
write_action_numbers(FILE* out_file,
    uint generate_flags)
{
    register Symbol*** block = productions,
        ** symbol;
    Symbol* last_action,
        * action_value;
    int action_number,
        index = 0;
    if (generate_flags & 0x00002000) {
        fputs("var Action_number = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static slk_size_t Action_number[] = {0\n\n", out_file);
    }
    else {
        fputs("private static int[] Action_number = {0\n\n", out_file);
    }
    while (*++block) {
        action_number = 0;
        action_value = NULL;
        last_action = NULL;
        for (symbol = *block; *++symbol;) {
            if ((*symbol)->type == 3) {
                action_value = *symbol;
                if (last_action) {
                    printf("Warning: Only last action is executed\n");
                    print_production("   ", symbol);
                }
                action_number = action_value->number;
                last_action = action_value;
            }
        }
        if (action_value) {
            if (*--symbol != action_value) {
                printf("Warning: action is executed at reduction\n");
                print_production("   ", *block);
            }
        }
        fprintf(out_file, ",%u", action_number);
        if (++index >= 16) {
            index = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
}
static void
write_lr_table_plain(FILE* out_file,
    int* row_offsets,
    uint generate_flags)
{
    register int* block;
    register LRState* state;
    register LRAction* row;
    int offset,
        action_count = symbol_count,
        token;
    int count;
    if (generate_flags & 0x00002000) {
        fputs("var Parse = [0,0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static slk_size_t Parse[] = {0,0\n\n", out_file);
    }
    else {
        fputs("private static short[] Parse = {0,0\n\n", out_file);
    }
    offset = 1;
    block = row_offsets;
    for (state = lr_states; state; state = state->next) {
        token = 0;
        *++block = offset;
        for (row = state->row; row; row = row->next) {
            while (++token < row->token) {
                fputs(",0", out_file);
            }
            fprintf(out_file, ",%u", row->block);
        }
        while (++token <= action_count) {
            fputs(",0", out_file);
        }
        offset += action_count;
        fputs("\n", out_file);
    }
    *++block = 0;
    fprintf(out_file, "%s;\n\n", array_close);
    if (generate_flags & 0x00002000) {
        fputs("var Parse_row = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fputs("static int Parse_row[] = {0\n\n", out_file);
    }
    else {
        fputs("private static int[] Parse_row = {0\n\n", out_file);
    }
    block = row_offsets;
    for (count = 1; *++block; ++count) {
        fprintf(out_file, ",%u", *block);
        if (count >= 16) {
            count = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
}
static int
max_action_count(void)
{
    register LRState* state;
    int max_actions = 0;
    for (state = lr_states; state; state = state->next) {
        if (state->action_count > max_actions) {
            max_actions = state->action_count;
        }
    }
    return max_actions;
}
static LRState*
next_state_to_compact(int* max_actions,
    LRState* last_state)
{
    register LRState* state = NULL;
    if (*max_actions <= 0) {
        return NULL;
    }
    if (last_state) {
        state = last_state->next;
    }
    do {
        if (!state) {
            state = lr_states;
        }
        for (; state; state = state->next) {
            if (state->action_count == *max_actions) {
                if (!state->next) {
                    --(*max_actions);
                }
                return state;
            }
        }
    }
    while (--(*max_actions) > 0);
    return NULL;
}
typedef struct LRCell
{
    uint row_index;
    uint block;
} LRCell;
static LRCell*
compact_lr_table(uint original_size,
    LRCell* table,
    uint table_size,
    int* row_offsets)
{
    register LRCell* free_slot;
    register LRAction* row;
    LRState* state = NULL;
    LRCell* table_limit = table +
        table_size - symbol_count,
        * last_used = NULL,
        * saved_slot,
        * cell;
    uint fits;
    int max_actions = max_action_count();
    printf("compacting parse table from %u ", original_size);
    while (state = next_state_to_compact(&max_actions, state)) {
        row = state->row;
        free_slot = table;
        for (;;) {
            while ((++free_slot)->block) {
                if (free_slot > table_limit) {
                    putchar('\n');
                    return NULL;
                }
            }
            row = state->row;
            if (free_slot - row->token <= table) {
                continue;
            }
            saved_slot = free_slot;
            free_slot -= row->token;
            fits = 1;
            for (row = state->row; row; row = row->next) {
                if ((free_slot + row->token)->block) {
                    fits = 0;
                    break;
                }
            }
            if (fits) {
                row_offsets[state->number] = free_slot - table;
                for (row = state->row; row; row = row->next) {
                    cell = free_slot + row->token;
                    cell->row_index = state->number;
                    cell->block = row->block;
                    if (free_slot + symbol_count > last_used) {
                        last_used = free_slot + symbol_count;
                    }
                }
                break;
            }
            free_slot = saved_slot;
        }
    }
    row_offsets[state_count + 1] = 0;
    printf("to %lu\n", 2 * (ulong)(++last_used - table - 1));
    return last_used;
}
static void
write_lr_table(FILE* out_file,
    LRCell* cursor,
    LRCell* table,
    register int* row_offsets,
    uint generate_flags)
{
    register LRCell* cell;
    uint count = 1,
        entries = 1;
    cell = table;
    if (generate_flags & 0x00002000) {
        fprintf(out_file, "var Parse = [\n\n%u", cell->block);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fprintf(out_file, "static slk_size_t Parse[] = {\n\n%u", cell->block);
    }
    else {
        fprintf(out_file, "private static short[] Parse = {\n\n%u", cell->block);
    }
    while (++cell < cursor) {
        ++entries;
        if (++count > 16) {
            count = 0;
            fputs("\n", out_file);
        }
        fprintf(out_file, ",%u", cell->block);
    }
    fprintf(out_file, "\n%s;\n\n", array_close);
    if (generate_flags & 0x00002000) {
        fputs("var Parse_row = [0\n\n", out_file);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        if (entries < (1024 * 64 - 32)) {
            fputs("static slk_size_t Parse_row[] = {0\n\n", out_file);
        }
        else {
            fputs("static int Parse_row[] = {0\n\n", out_file);
        }
    }
    else {
        fputs("private static int[] Parse_row = {0\n\n", out_file);
    }
    for (count = 1; *++row_offsets; ++count) {
        fprintf(out_file, ",%u", *row_offsets);
        if (count >= 16) {
            count = 0;
            fputs("\n", out_file);
        }
    }
    fprintf(out_file, "\n,0%s;\n\n", array_close);
}
static void
write_lr_state_numbers(FILE* out_file,
    LRCell* cursor,
    LRCell* table,
    register int* row_offsets,
    uint generate_flags)
{
    register LRCell* cell;
    uint count = 1,
        entries = 1;
    cell = table;
    if (generate_flags & 0x00002000) {
        fprintf(out_file, "var Parse_state = [\n\n%u", cell->row_index);
    }
    else if (generate_flags & (0x00000100 | 0x00001000 | 0x00000200)) {
        fprintf(out_file, "static slk_size_t Parse_state[] = {\n\n%u",
            cell->row_index);
    }
    else {
        fprintf(out_file, "private static short[] Parse_state = {\n\n%u",
            cell->row_index);
    }
    while (++cell < cursor) {
        ++entries;
        if (++count > 16) {
            count = 0;
            fputs("\n", out_file);
        }
        fprintf(out_file, ",%u", cell->row_index);
    }
    fprintf(out_file, "\n%s;\n\n", array_close);
}
static void
print_lr_entry(uint token,
    uint block)
{
    ;
    ;
    if (block < start_state) {
        ;
        ;
    }
    else if (block < start_conflict) {
        ;
        ;
    }
    else {
        ;
        ;
    }
}
static int
verify_lr_table(LRCell* table_data,
    int* row_offsets)
{
    register LRState* state;
    register LRAction* row;
    int offset,
        token,
        errors = 0,
        entry_number,
        state_value,
        block;
    for (state = lr_states; state; state = state->next) {
        for (row = state->row; row; row = row->next) {
            block = row->block;
            token = row->token;
            offset = row_offsets[state->number];
            offset += token;
            state_value = table_data[offset].row_index;
            entry_number = table_data[offset].block;
            if (state->number != state_value) {
                errors = 1;
                printf("row_number %u != compact_row_number %u at offset %u\n",
                    state->number, state_value, offset);
            }
            if (block != entry_number) {
                errors = 1;
                printf("\n%3d: ", state->number);
                printf("entry %u != compact_entry %u at offset %u\n",
                    block, entry_number, offset);
            }
        }
    }
    return errors;
}
void write_lr_tables(char* parser_name,
    char* namespace_name,
    uint generate_flags,
    FILE* out_file)
{
    LRCell* table_data,
        * cursor;
    int* row_offsets;
    uint original_size = state_count * symbol_count,
        table_size2 = 0;
    write_lr_state_file(parser_name, namespace_name, generate_flags);
    write_action_numbers(out_file, generate_flags);
    row_offsets = calloc(state_count + 2, sizeof(int));
    if (!row_offsets) {
        fatal_error(2309, "out of memory");
    }
    if (generate_flags & 0x00000001) {
        for (;;) {
            table_size2 += 64 * 1024;
            table_data = calloc(table_size2, sizeof(LRCell));
            if (!table_data) {
                fatal_error(2310, "out of memory");
            }
            cursor = compact_lr_table(original_size, table_data,
                table_size2, row_offsets);
            if (!cursor) {
                free(table_data);
                continue;
            }
            write_lr_table(out_file, cursor, table_data, row_offsets,
                generate_flags);
            write_lr_state_numbers(out_file, cursor, table_data, row_offsets,
                generate_flags);
            if (verify_lr_table(table_data, row_offsets)) {
                printf("error 1133: table compacting failed\n");
            }
            free(table_data);
            break;
        }
    }
    else {
        write_lr_table_plain(out_file, row_offsets, generate_flags);
    }
    free(row_offsets);
}
static void
print_lr_item(register LRItem* config)
{
    register Symbol** symbol;
    if (config) {
        symbol = config->lhs;
        printf("   %2d: %s -->", config->production_number, (*symbol)->name);
        while (*++symbol) {
            if (symbol != config->dot) {
                printf("  %s", (*symbol)->name);
            }
            else {
                printf(" %s %s", dot_string, (*symbol)->name);
            }
        }
        if (!*config->dot) {
            printf(" %s", dot_string);
        }
        putchar('\n');
    }
}
static void
print_lr_items(register LRItem* config,
    int slr_grammar)
{
    register Symbol** symbol;
    SymbolSetNode* follows_node;
    Symbol* eof_label;
    Symbol* lhs;
    char* saved_symbol_name;
    eof_label = find_symbol("END_OF_SLK_INPUT");
    saved_symbol_name = eof_label->name;
    if (find_symbol("$")) {
        eof_label->name = "$$$";
    }
    else {
        eof_label->name = "$";
    }
    for (; config; config = config->next) {
        symbol = config->lhs;
        printf("   %2d: %s -->", config->production_number, (*symbol)->name);
        while (*++symbol) {
            if (symbol != config->dot) {
                printf("  %s", (*symbol)->name);
            }
            else {
                printf(" %s %s", dot_string, (*symbol)->name);
            }
        }
        if (!*config->dot) {
            printf(" %s", dot_string);
        }
        putchar('\n');
        if (slr_grammar) {
            lhs = *config->lhs;
            follows_node = lhs->follows;
        }
        else {
            follows_node = config->follows;
        };
        ;
        for (; follows_node; follows_node = follows_node->next) {
            ;
            ;
        };
        ;
    }
    putchar('\n');
    eof_label->name = saved_symbol_name;
}
void print_lr_states(int slr_grammar)
{
    register LRState* state;
    register LRGoto* lr_goto;
    for (state = lr_states; state; state = state->next) {
        printf("State  %d\n", state->number);
        print_lr_items(state->items, slr_grammar);
        for (lr_goto = state->gotos; lr_goto; lr_goto = lr_goto->next) {
            printf("    go to state %d on %s\n", lr_goto->state->number,
                lr_goto->symbol->name);
        }
        if (state->gotos) {
            putchar('\n');
        }
    }
    putchar('\n');
}
void print_lr_state(int number)
{
    register LRState* state;
    register LRGoto* lr_goto;
    int slr_grammar = 0;
    for (state = lr_states; state; state = state->next) {
        if (state->number != number) {
            continue;
        }
        printf("State  %d\n", state->number);
        print_lr_items(state->items, slr_grammar);
        for (lr_goto = state->gotos; lr_goto; lr_goto = lr_goto->next) {
            printf("    go to state %d on %s\n", lr_goto->state->number,
                lr_goto->symbol->name);
        }
        if (state->gotos) {
            putchar('\n');
        }
        break;
    }
    putchar('\n');
}
void print_lr_parse_table(void)
{
    register LRState* state;
    register LRAction* row;
    uint block;
    Symbol* eof_label;
    char* saved_symbol_name;
    eof_label = find_symbol("END_OF_SLK_INPUT");
    saved_symbol_name = eof_label->name;
    if (find_symbol("$")) {
        eof_label->name = "$$$";
    }
    else {
        eof_label->name = "$";
    }
    for (state = lr_states; state; state = state->next) {
        printf("State %d:  ", state->number);
        for (row = state->row; row; row = row->next) {
            printf(" %d:", row->token);
            block = row->block;
            if (block < start_state) {
                printf(" R%d ", block);
            }
            else if (block < start_conflict) {
                printf(" S%d ", block - lr_production_count);
            }
            else {
                printf(" C%d ", block - last_state_number);
            }
        }
        putchar('\n');
    }
    print_productions();
    print_all_symbols();
    eof_label->name = saved_symbol_name;
}
void print_all_symbols(void)
{
    register Symbol** lookahead_tokens = terminals;
    register Symbol** nonterminal = nonterminals;
    int index;
    printf("\n\n\t\t\t ALL GRAMMAR SYMBOLS \n\n");
    for (index = 1; *++lookahead_tokens; ++index) {
        printf("%2d: %s\n", index, (*lookahead_tokens)->name);
    }
    for (; *++nonterminal; ++index) {
        printf("%2d: %s\n", index, (*nonterminal)->name);
    }
    putchar('\n');
}
