# 错误处理 / 错误恢复测试 改动记录

本文记录针对 `code/testing/` 下错误处理与错误恢复测试的扩充与重构。

## 背景

改动前的测试只覆盖编译器**词法/语法**阶段的恢复路径，且只检查退出码非 0，
不比对错误信息内容；语义阶段没有任何回归。具体缺口（基于 `frontend/pascal_s_parser.y`
和 `frontend/pascal_s_lexer.l` 中已实现的错误恢复机制）：

| 阶段 | 已实现的恢复 / 报错点 | 改动前是否覆盖 |
| --- | --- | --- |
| parser | `LPAREN error RPAREN` (形参列表) | ✅ 02 |
| parser | `BEGIN_KW error END_KW` (复合语句) | ❌ |
| parser | `statement_list SEMICOLON error` (跳到下一个分号) | ❌ |
| parser | `statement_list error statement` (缺分号) | ✅ 01 |
| parser | `READ/WRITE LPAREN error RPAREN` | ✅ 01 |
| parser | `LBRACK error RBRACK` (数组下标) | ✅ 03 |
| parser | `procedure_call: ID LPAREN error RPAREN` | ✅ 01 |
| parser | `factor: ID LPAREN error RPAREN` (函数调用表达式) | ❌ |
| parser | `kMaxParseErrors = 20` 熔断 | ❌ |
| lexer | 非法字符 | ✅ 04 |
| lexer | 未闭合注释 | ✅ 05 |
| lexer | 未闭合字符常量 | ❌ |
| lexer | 数字开头非法标识符 | ❌ |
| lexer | `kMaxLexErrors = 20` 熔断 | ✅ 04（仅超阈值一种） |
| semantic | 全部规则 | ❌ |

## 改动概述

1. **新增 8 个错误恢复 / 错误处理样例**到 `testing/error_recovery/`。
2. **新增 `testing/semantic_errors/` 目录**，纳入原有的
   `testing/test_semantic_invalid.pas`（已重命名/移动）并补充 4 个针对性语义错误样例，
   原 `testing/test_semantic_invalid.pas` 已删除。
3. **为每个样例配一份金标准** `*.expected.stderr` 和 `*.expected.exit`。
4. **重写两个脚本**（`run_error_recovery_checks.sh`、`run_tests.py` 中
   `error-recovery` 子命令）：扫描两个目录、加 10 秒硬超时、把实际 stderr
   与金标准 diff、把退出码与 `.expected.exit` 比对，并在任何样例失败时
   以非 0 退出。

## 新增样例清单

### `testing/error_recovery/` 新增（编号 06–12）

| 样例 | 覆盖点 | 触发的恢复规则 / 报错点 |
| --- | --- | --- |
| `06_compound_statement_recovery.pas` | `begin then end.` | `BEGIN_KW error END_KW` |
| `07_statement_skip_to_semicolon.pas` | `y := + ;` 中间语句出错 | `statement_list SEMICOLON error` |
| `08_function_call_expr_recovery.pas` | `y := foo(,)`、`y := foo(1 +)` | `factor: ID LPAREN error RPAREN` |
| `09_unclosed_char_const.pas` | `'a` 跨行未闭合 | lexer `BAD_CHAR_LIT` → "未闭合字符常量" |
| `10_bad_identifier_digit_start.pas` | `123abc` | lexer "非法标识符（以数字开头）" |
| `11_lex_below_threshold.pas` | 5 个非法字符（< 20） | 验证未触发熔断时仍逐条报告 |
| `12_syntax_error_threshold.pas` | 23 个 `foo(,)` 形参错误 | `kMaxParseErrors = 20` 熔断信息 |
| `13_loop_recovery_regression.pas` | `; ) garbage tokens here ;` | 锁住 Bug 2 修复（修复前会死循环吐 137MB stderr） |

### `testing/semantic_errors/` 新建

| 样例 | 覆盖点 |
| --- | --- |
| `01_kitchen_sink.pas` | 原 `test_semantic_invalid.pas` 内容，11 条混合语义错误 |
| `02_undeclared_identifier.pas` | 未声明的标识符 |
| `03_duplicate_declaration.pas` | 同作用域重复声明 |
| `04_break_outside_loop.pas` | `break` 出现在循环外 |
| `05_array_bounds_reversed.pas` | 数组下界 > 上界 |

## 金标准文件

每个 `.pas` 样例旁会有两份同名文件：

- `*.expected.stderr` — 编译器期望写入 stderr 的完整内容（含错误条、恢复条、汇总条）。
- `*.expected.exit` — 期望退出码（多数为 `1`；纯词法错误目前编译器会以 `0` 退出，
  样例 10、11 即据此设定，详见下方"已知问题"）。

如果未来修改了编译器的错误诊断文案、行列号策略或熔断阈值，需要同步更新这些
金标准文件，否则脚本会以 `STDERR_MISMATCH` 失败。

## 脚本改动

### `run_error_recovery_checks.sh`

- 同时遍历 `testing/error_recovery/` 和 `testing/semantic_errors/`。
- 每个样例运行带 10 秒硬超时（用后台 PID + watcher 实现），超时记为 `TIMEOUT`。
- 增加 stderr diff 与 `.expected.exit` 对比；状态扩展为
  `PASS / STDERR_MISMATCH / EXIT_MISMATCH / MISSING_GOLDEN / TIMEOUT`。
- `summary.tsv` 列扩展为 `case, category, status, exit_code, expected_exit, stderr_log`。
- 任一样例非 `PASS` 时整体退出码为 1（可直接用于 CI 闸口）。

### `run_tests.py` 的 `error_recovery`

- 与 shell 版行为对齐：双目录扫描、`subprocess.run(..., timeout=10)`、stderr diff、
  退出码对比、最终非 0 退出。

## 编译器修复（与本次测试一起做的）

测试过程中暴露了两个真实的编译器 bug，已一并修复并被测试锁住：

1. **纯词法错误不致命**（[pascal_s_driver.cpp](code/pascal_s_driver.cpp)）。
   原代码只在 AST 为 NULL 时检查词法错误，结果像 `123abc` 这种非法标识符被词法器
   丢弃后 parser 仍能完成解析，root 非空，于是直接走进 semantic / codegen，
   exit=0。修复：把词法错误检查提到 `root == NULL` 分支之外，发现词法错误就打
   "编译终止：词法阶段共发现 N 个错误" 并以 1 退出。被样例 10、11 锁住
   （它们的 `expected.exit` 已改为 1，stderr 含汇总条）。
2. **`statement_list` 错误恢复死循环**（[pascal_s_parser.y:434](code/frontend/pascal_s_parser.y:434)）。
   `statement_list SEMICOLON error` 规则的 action 里调了 `yyerrok`，把 Bison
   的错误状态清掉，导致 Bison 自带的"出错后静默丢弃 token 直到 3 个成功 shift"
   抑制机制失效。错误 token 不能被立刻消费时，规则反复 reduce、错误反复重报，
   直到 `kMaxParseErrors=20` 才停止报新错；而恢复注释不受该阈值约束，会持续
   打印（亲测产生 137 MB stderr）。修复：去掉这条规则里的 `yyerrok`，让 Bison
   默认抑制接管，循环自然终止。被新增的
   `13_loop_recovery_regression.pas` 锁住——同一份输入在修复前是死循环，
   现在干净地报 3 个错误并以 1 退出。

注：另一条 `statement_list error statement` 规则的 `yyerrok` 保留不动，
样例 01 依赖它来串起"缺分号 + 接着写下一句"的恢复路径。

## 验证

```bash
bash testing/run_error_recovery_checks.sh
python3 testing/run_tests.py error-recovery
```

两者均输出 `passed: 18/18  failed: 0/18`。

开放集对拍 (`bash testing/run_output_consistency.sh`) 在修复前后均为 `passed: 65/70`，
5 个 `OUTPUT_MISMATCH` 是与本次修复无关的、修复前就存在的输出偏差。
