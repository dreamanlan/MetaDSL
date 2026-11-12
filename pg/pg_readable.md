# pg_readable.c 使用说明

`pg_readable.c` 是 `pg.c`（SLK Parser Generator，LL(k) 及可选 SLR/LALR/LR 分析表生成器）的**可读版**：989 个混淆标识符（`l1`~`l991`）全部按语义重命名，并补充了文件头架构说明和 18 个分节注释。**算法逻辑与 `pg.c` 完全一致**，包括 `modified.txt` 中记录的全部本地修改（`cmain`、`-Ps` 栈大小、C# 模板拆分、namespace 处理、`IVisitor.Accept` 等）。

原版 `pg.c` 保持不变，两个文件可以共存、分别编译对照。

## 文件清单

| 文件 | 作用 |
|---|---|
| `pg.c` | 原始混淆源码（不要改） |
| `pg_readable.c` | 去混淆后的可读源码（由脚本生成，不手工编辑） |
| `pg_map_1.json` ~ `pg_map_5.json` | 989 条 `l<N>` → 语义名映射，按编号分段存放（1: l3–l200，2: l201–l400，3: l401–l600，4: l601–l800，5: l801–l991） |
| `pg_deobfuscate.js` | 转换脚本：读取 `pg.c` 和映射表，生成 `pg_readable.c` |
| `main.c` | `cmain` 的简单包装，供 gcc 命令行编译使用 |
| `main.cpp` | 工程原有的 `main`（VS 工程里调用 `cmain`） |
| `modified.txt` | 原版的本地修改记录 |

## 日常使用

### 编译

VS 工程：把 `pg_readable.c` 加入工程替换 `pg.c` 即可（记得 `_CRT_SECURE_NO_WARNINGS` 和关闭 SDL 检查，同原工程设置）。

gcc 命令行：

```bat
gcc -O0 -w -o pg_readable.exe pg_readable.c main.c
```

### 运行

与原版完全相同，例如（在 `D:\syntaxtest\simple` 下）：

```bat
pg_readable -ns=Dsl.Parser -n=Dsl -cs -Ps=65535 simple.txt
pg_readable -C++ -Ps=65535 simple.txt
pg_readable -n=Dsl -js -Ps=65535 simple.txt
```

所有命令行选项见 `usage_text`（`-Ps` 栈大小、`-k` 最大前瞻、`-cs/-js/-C++/-j/-cc` 目标语言、`-LA/-LR/-LRS` LR 类型等）。

## 修改命名的方法

1. 在对应分段的 `pg_map_N.json` 里修改 `"l<N>":"新名字"`。编号分段见上表，**先确认目标条目在哪个文件再改**。
2. 重新生成并编译：

   ```bat
   node pg_deobfuscate.js
   gcc -O0 -w -o pg_readable.exe pg_readable.c main.c
   ```

3. 脚本会打印 `UNMAPPED`（有遗漏的标识符）和横幅锚点缺失等警告，注意检查。

### 命名冲突的处理原则

同一个新名字不能落在同一作用域的两个声明上，否则编译报错。常见几类：

- 同一函数内多个局部变量（如多个 `found`、`status`）→ 加角色前缀区分；
- 全局变量与全局函数同名（如 `free_config_list`、`free_lr_items`）→ 变量改成 `..._nodes`；
- typedef 与函数参数同名（如 `Conflict`）→ 参数改 `conflict_ptr`；
- 结构体字段名与局部变量同名（如 LR 输出函数里的 `table`）→ 局部变量改 `cell`。

脚本末尾的"特殊替换"段就是处理这些固定冲突点的，新增冲突时优先在那里加**精确到声明行/调用行**的替换，**不要**做全局宽泛替换（曾经把 `production->conflict == conflict` 的整数比较误改成指针比较，导致行为偏差；也把 `Symbol->table` 误伤过）。

## 等价性验证方法

分别编译原版和可读版，然后对同一文法、同一选项运行，逐字节比较生成的所有文件和日志：

```bat
rem 在两个空目录里分别执行（可用 D:\syntaxtest 下的文法）
pg_orig.exe     -ns=Dsl.Parser -n=Dsl -cs -Ps=65535 simple.txt > out.log
pg_readable.exe -ns=Dsl.Parser -n=Dsl -cs -Ps=65535 simple.txt > out.log
```

已验证：simple/lua/cpp 文法 × C#/JS/C++ 共 7 组全部一致。

## LR 模式的适用范围与防爆保护

LR 选项写法：`-LR`（全 LR）、`-LALR`（LALR）、`-LRS`（SLR）。注意 `-LA` 不是合法选项（会打印用法说明）。

**`simple.txt` 这类文法不要用 LR 模式**：它不是左递归问题（`-Rr` 无可消递归），而是文法里有大量可空产生式（`NULLABLE_FUNCTION_PARAMS_opt` 等 `_opt`），pg 的广义 k 前瞻冲突求解器会不断生成新冲突——全 LR 时基础冲突 297 个（state 1490），level 2 几分钟内涨到 4800+ 且持续增长；`-LALR` 同样爆炸。该文法请用**默认 LL(k)**（已验证可用）。

`-LR` 本身并非对所有文法都失效，以下两个文法均能快速生成解析器（已随附在 `pg/lr_tests/`，可用 `pg_readable -n=Cal -C++ -LR lr_tests/expr_leftrec.txt` 复测）：

- `expr_ebnf.txt`：文档示例的 EBNF 算术表达式（带语义动作），生成成功；
- `expr_leftrec.txt`：经典左递归 LR 算术文法，`Conflicts were resolved at lookahead level k=1`，39 个状态，生成成功。

**防爆保护（可读版新增，原版没有）**：`extend_conflict` 每创建一个新冲突计数一次，超过 `SLK_CONFLICT_BUDGET`（默认 **10000**）即调用 `fatal_error(1210, ...)` 输出诊断并退出，而不是无限挂起。可在编译时覆盖预算：

```bat
gcc -O0 -w -DSLK_CONFLICT_BUDGET=200 -o pg_readable.exe pg_readable.c main.c
```

报错示例（`simple.txt -LR`）：`error 1210: conflict resolution budget exceeded: the grammar generates too many conflicts for generalized k-lookahead resolution (use default LL(k) or -LA, or reduce -k)`。正常能完成冲突求解的文法不会触发，LL/LALR 常规输出与原版保持一致。该补丁在 `pg_deobfuscate.js` 的 "Fail-fast guard" 段，重新生成时会保留。

## 阅读入口建议

- 文件头注释：整体流水线、数据结构、位掩码约定。
- `cmain`：命令行解析与主流程（分析 → 变换 → FIRST/FOLLOW → 建表 → 冲突解决 → 代码生成）。
- `Symbol`/`Config`/`Conflict`/`LRItem` 四个结构体：理解算法的关键数据模型。
- `LanguageDescriptor`（java/js/cs 三份记录）配合 `modified.txt`：各语言输出模板如何拼装。
