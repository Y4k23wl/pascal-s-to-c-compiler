# Testing

这个目录收拢了 `code` 仓库自带的测试资产，避免和编译器源码混在一起。

包含内容：

- `open_set/`
  - Pascal 样例集及其配套 `.in` 输入文件
- `error_recovery/`
  - 专门用于错误恢复验证的错误样例
- `run_output_consistency.sh`
  - 端到端对拍脚本
- `run_error_recovery_checks.sh`
  - 错误恢复回归脚本，收集错误输出日志

## 用法

在 `code/` 仓库根目录执行：

```bash
./testing/run_output_consistency.sh
```

脚本会自动：

1. 通过 `cmake` 配置并构建当前源码生成 `build/bin/pascc`
2. 用构建出的 `pascc` 把 `testing/open_set/*.pas` 翻译为 C
3. 用 `cc -std=c99` 编译生成的 C 程序
4. 用 `fpc` 编译同一份 Pascal 源程序
5. 运行两边可执行文件并逐样例比对标准输出

错误恢复样例可在 `code/` 仓库根目录执行：

```bash
./testing/run_error_recovery_checks.sh
```

该脚本会：

1. 通过 `cmake` 配置并构建当前源码生成 `build/bin/pascc`
2. 逐个运行 `testing/error_recovery/*.pas`
3. 将每个样例的标准输出、标准错误和退出码写入结果目录

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

## 依赖

- `cmake`
- `c++`
- `flex`
- `bison`
- `cc`
- `fpc`

## 输出

默认输出目录：

- `testing/output_consistency_results/`
- `testing/error_recovery_results/`

其中：

- `summary.txt`
  - 人类可读汇总
- `summary.tsv`
  - 便于进一步处理的表格结果
- `logs/`
  - 构建、编译和 diff 日志
- `cases/`
  - 每个样例的独立工作目录
