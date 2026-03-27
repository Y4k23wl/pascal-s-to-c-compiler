# Testing

这个目录收拢了 `code` 仓库自带的测试资产，避免和编译器源码混在一起。

包含内容：

- `open_set/`
  - Pascal 样例集及其配套 `.in` 输入文件
- `run_output_consistency.sh`
  - 端到端对拍脚本

## 用法

在 `code/` 仓库根目录执行：

```bash
./testing/run_output_consistency.sh
```

脚本会自动：

1. 重新编译当前源码生成 `./pascc`
2. 用 `./pascc` 把 `testing/open_set/*.pas` 翻译为 C
3. 用 `cc -std=c99` 编译生成的 C 程序
4. 用 `fpc` 编译同一份 Pascal 源程序
5. 运行两边可执行文件并逐样例比对标准输出

## 依赖

- `cc`
- `fpc`

## 输出

默认输出目录：

- `testing/output_consistency_results/`

其中：

- `summary.txt`
  - 人类可读汇总
- `summary.tsv`
  - 便于进一步处理的表格结果
- `logs/`
  - 编译和 diff 日志
- `cases/`
  - 每个样例的独立工作目录
