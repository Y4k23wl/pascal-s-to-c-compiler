# Testing

这个目录收拢了 `code` 仓库自带的测试资产，避免和编译器源码混在一起。

包含内容：

- `open_set/`
  - Pascal 样例集及其配套 `.in` 输入文件
- `error_recovery/`
  - 词法 / 语法错误样例（含恢复路径与错误熔断阈值）
- `semantic_errors/`
  - 语义错误样例
- `test_ast/`
  - 用于语法阶段 AST dump 的小规模样例（含一个故意写错的 `test.pas`，用来观察解析失败的样子）
- `test_semantic/`
  - 用于语义阶段符号表 dump 的小规模样例
- `*.expected.stderr` / `*.expected.exit`
  - 与 `.pas` 同名的金标准 stderr 和退出码，脚本会做 diff（仅 `error_recovery/` 和 `semantic_errors/` 用到）
- `run_output_consistency.sh`
  - 端到端对拍脚本
- `run_error_recovery_checks.sh`
  - 错误恢复回归脚本，收集错误输出日志
- `run_stage_dumps.sh`
  - 阶段性中间产物 dump 脚本（AST / 符号表），无金标准，只收集输出
- `run_tests.py`
  - Python 测试驱动脚本，提供 Windows 测试入口


# 这个测试（所谓的开放集对拍）在做什么事？
### 对于我们的编译器：
对每个pascal源代码`program.pas`，生成`program.c`，再用gcc编译出`program.exe`
### 对于pascal编译器：
对每个pascal源代码`program.pas`，用pascal编译器直接生成`program.exe`，这说明<u>**你需要装一个pascal编译器**</u>  

之后比对这两个程序的<u>**输出结果是否一致**</u>


## 用法

在 `code/` 仓库根目录执行，可任选 shell 脚本或 Python 脚本。

开放集对拍：

Shell 入口（适合Mac和Linux）：

```bash
./testing/run_output_consistency.sh
```

Python 入口（适合Windows）：

```bash
python ./testing/run_tests.py output-consistency
```

脚本会自动：

1. 通过 `cmake` 配置并构建当前源码生成 `build/bin/pascc`
2. 用构建出的 `pascc` 把 `testing/open_set/*.pas` 翻译为 C
3. 用 `cc -std=c99` 编译生成的 C 程序
4. 用 `fpc` 编译同一份 Pascal 源程序
5. 运行两边可执行文件并逐样例比对标准输出

错误恢复样例可在 `code/` 仓库根目录执行：

Shell 入口：

```bash
./testing/run_error_recovery_checks.sh
```

Python 入口：

```bash
python ./testing/run_tests.py error-recovery
```

该脚本会：

1. 通过 `cmake` 配置并构建当前源码生成 `build/bin/pascc`
2. 逐个运行 `testing/error_recovery/*.pas` 和 `testing/semantic_errors/*.pas`，每个样例带 10 秒超时
3. 把实际 stderr 与同名 `.expected.stderr` 做 diff，把退出码与 `.expected.exit` 做对比
4. 将每个样例的标准输出、标准错误、退出码和差异写入结果目录；任一样例失败则脚本退出码非 0

阶段性中间产物 dump（AST / 符号表）：

Shell 入口（适合 Mac 和 Linux）：

```bash
./testing/run_stage_dumps.sh
```

Python 入口（适合 Windows）：

```bash
python ./testing/run_tests.py stage-dumps
```

该脚本会：

1. 通过 `cmake` 配置并构建当前源码生成 `build/bin/pascc`
2. 对 `testing/test_ast/*.pas` 跑 `--stop-after=parse --dump-ast`，把 AST 落到 `stage_dump_results/ast/<name>.parse`
3. 对 `testing/test_semantic/*.pas` 跑 `--stop-after=semantic --dump-symbols`，把符号表落到 `stage_dump_results/symbols/<name>.semantic`
4. 不做金标准 diff——产物用于人工检视；样例在对应阶段就出错的会标 `[FAIL]`，stderr 留在 `logs/` 下

## 单独构建

如果只想先构建编译器本体，在 `code/` 根目录执行：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

如果需要从干净目录重新配置并全量重建：

```bash
rm -rf build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

构建成功后，可执行文件默认位于：

```bash
build/bin/pascc
```

## 程序怎么用

基本用法（在 `code/` 根目录，假设源程序是 `a.pas`）：

```bash
./build/bin/pascc -i a.pas        # 生成 a.c
```

阶段性中间产物 dump 选项（dump 都写到 **stderr**，不会污染落盘的 `.c`）：

| 选项 | 作用 |
|---|---|
| `--dump-ast` | 在语法分析（含 `ast_validate`）之后，把 AST 打印出来 |
| `--dump-symbols` | 在语义分析成功之后，把全部作用域和符号表打印出来 |
| `--stop-after=parse` | 语法分析完成后立即退出，不跑语义、不生成 `.c` |
| `--stop-after=semantic` | 语义分析完成后立即退出，不生成 `.c` |

常见组合：

```bash
# 只看 AST（语法成功即可，语义有错也能拿到）
./build/bin/pascc -i a.pas --stop-after=parse --dump-ast 2> a.ast

# 只看符号表（需要语法 + 语义都通过）
./build/bin/pascc -i a.pas --stop-after=semantic --dump-symbols 2> a.sym

# 两个都打，并保留完整编译到 .c
./build/bin/pascc -i a.pas --dump-ast --dump-symbols 2> a.dump

# 同时在终端看 + 存文件
./build/bin/pascc -i a.pas --stop-after=parse --dump-ast 2>&1 | tee a.ast
```

不加 `2>` 时 dump 内容会直接打到终端，跟编译器自身的提示混排——分析时建议重定向到文件。

AST dump 里每个节点末尾形如 `[起始行:起始列-结束行:结束列]` 的方括号是该节点对应的源代码位置区间，由词法/语法阶段填入，后续语义错误的行列号也来自这里。

## 依赖

- `cmake`
- `c++`
- `flex`
- `bison`
- `python3`
- `cc`
- `fpc`

## 输出

默认输出目录：

- `testing/output_consistency_results/`
- `testing/error_recovery_results/`
- `testing/stage_dump_results/`

`output_consistency_results/` 和 `error_recovery_results/` 下：

- `summary.txt`
  - 人类可读汇总
- `summary.tsv`
  - 便于进一步处理的表格结果
- `logs/`
  - 构建、编译和 diff 日志
- `cases/`
  - 每个样例的独立工作目录

`stage_dump_results/` 下：

- `ast/<name>.parse`
  - 语法阶段 AST dump
- `symbols/<name>.semantic`
  - 语义阶段符号表 dump
- `logs/`
  - 构建日志，以及 dump 失败时的 stderr
