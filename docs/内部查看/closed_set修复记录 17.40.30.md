# closed_set 修复记录

本文记录根据 `封闭集爬取代码.md` 定位出的闭集问题及本轮修复内容。测试程序保证合法，因此本轮修复目标是补齐编译器对闭集实际语言特性的支持，并修正闭集源码爬取链路。

## 1. `read(函数名)` 误报不可赋值

### 问题现象

闭集样例中存在如下写法：

```pascal
function getint: integer;
begin
  read(getint);
end;
```

原实现只在赋值语句左侧识别函数返回值变量，例如 `getint := ...`。当函数名出现在 `read(...)` 参数中时，语义分析仍把它当成普通函数表达式，导致报错：

```text
read 参数必须是可赋值左值
```

### 修复方式

在语义分析中抽出统一的赋值目标分析逻辑：

- 赋值语句左侧继续支持函数返回值变量。
- `read(...)` 参数也复用同一逻辑。
- 当前函数体内出现无下标、未被局部符号遮蔽的本函数名时，将其标记为 `function_result_refs`。

主要修改文件：

- `semantic/semantic.cpp`

## 2. 不支持 Pascal 字符串常量

### 问题现象

闭集样例中出现：

```pascal
const ne = 'Not exist';
const split = '--';
```

原词法器只支持单字符常量，例如 `'a'`，因此遇到多字符的单引号字面量会把 `'` 报为非法字符，并进一步触发语法错误。

### 修复方式

新增字符串常量支持：

- 词法阶段新增 `STRING_CONST`。
- AST 新增 `AST_STRING_LITERAL`。
- 语义类型新增 `TypeKind::String`。
- 常量声明允许字符串值。
- `write(string)` 允许输出字符串。
- 代码生成将 Pascal 单引号字符串转为 C 字符串字面量，并用 `printf("%s", ...)` 输出。

主要修改文件：

- `frontend/pascal_s_lexer.l`
- `frontend/pascal_s_parser.y`
- `frontend/ast.hpp`
- `frontend/ast.cpp`
- `semantic/semantic.hpp`
- `semantic/semantic.cpp`
- `codegen/codegen.hpp`
- `codegen/codegen.cpp`

说明：本轮只为闭集需要支持字符串常量和 `write(string)`，没有扩大到 `read(string)` 或字符串参与一般运算，避免影响开放集已有行为。

## 3. 不支持 `Break`

### 问题现象

闭集图着色样例中有：

```pascal
Break;
```

原 lexer/parser 没有 `break` 关键字和对应语句节点。修复字符串常量后，该样例会继续暴露 `Break` 不支持的问题。

### 修复方式

新增 `Break` 语句：

- lexer 识别 `break`，大小写不敏感。
- parser 新增 `BREAK` 语句。
- AST 新增 `AST_BREAK_STMT`。
- 语义分析维护 `loop_depth`，只允许 `break` 出现在 `for` 或 `while` 内。
- 代码生成直接输出 C 的 `break;`。

主要修改文件：

- `frontend/pascal_s_lexer.l`
- `frontend/pascal_s_parser.y`
- `frontend/ast.hpp`
- `frontend/ast.cpp`
- `semantic/semantic.cpp`
- `codegen/codegen.cpp`

## 4. 闭集源码爬取中 `*` 被展开成文件列表

### 问题现象

`封闭集爬取代码.md` 中部分长程序出现大量文件名，例如：

```text
00_comment2.c 00_comment2.pas ...
```

这些位置原本应是乘号 `*`。这说明爬取闭集源码时，输出链路经过了 shell 的通配符展开。

### 修复方式

修复伪编译器：

- 不使用 shell `echo` 或未加引用的变量输出源码。
- 生成 C 程序时通过 `fputs` 输出需要观察的源码内容：

```c
fputs("...\\n", stdout);
```

- 对 C 字符串字面量中的 `"`、`\`、`\t`、`\r` 做转义。
- 新增 CMake 目标 `dummy_pascc`，输出可执行文件名为 `pascc_dummy`。

主要修改文件：

- `testing/dummy.cpp`
- `CMakeLists.txt`

使用方式：

```bash
cmake --build code/build --config Release --target dummy_pascc
```

生成的伪编译器位于：

```text
code/build/bin/pascc_dummy
```

需要爬取闭集源码时，将该可执行文件作为平台提交/运行用的 `pascc`。

## 5. 闭集 93 递归调用实参临时槽污染

### 问题现象

平台反馈 93 号用例运行结果错误。期望输出中包含：

```text
...0.6931471.584962...
```

实际输出对应位置明显偏离：

```text
...0.2022961.037538...
```

该用例包含 `my_pow`、`my_sqrt`、`simpson`、`asr5` 等自写数学函数。前几个直接计算项正确，错误从 `my_ln -> asr4 -> asr5 -> simpson` 这条递归 Simpson 积分链开始出现。

本地 macOS / clang 编译生成 C 后能得到正确结果，而 Debian 9 / GCC 6.3 上同一份 C 输出错误，因此问题不是浮点输出格式，也不是单纯精度差异，而是生成 C 代码依赖了平台相关的求值行为。

### 根因

调用实参修正阶段曾使用文件作用域的 `static __call_tmp_*` 数组保存实参求值结果。普通调用可以工作，但递归函数中会复用同一批静态槽。

93 的关键语句是：

```pascal
asr5 := asr5(a, c, eps/2, L, flag) + asr5(c, b, eps/2, R, flag);
```

C 语言中 `+` 两侧操作数求值顺序未指定。递归调用进入 `asr5` 后又会写入同一批 `static __call_tmp_*`，导致外层另一侧调用尚未消费的实参槽被深层递归覆盖。clang 的求值策略碰巧没有暴露问题，GCC 6.3 暴露了这个未指定行为。

### 修复方式

将 `__call_tmp_*` 从文件作用域 `static` 数组改为每个函数体内部的局部数组：

- `emit_call_temp_decls()` 改为 `emit_local_call_temp_decls()`。
- `emit_subprogram()` 针对当前子程序体统计调用临时槽容量，并在函数体内声明局部 `__call_tmp_*`。
- `emit_main()` 同样只为主程序体生成局部临时槽。
- 每次函数调用都有独立栈帧，递归调用不再共享上一层的临时槽。

主要修改文件：

- `codegen/codegen.hpp`
- `codegen/codegen.cpp`

曾尝试将 Pascal `real` 的目标 C 表示从 `float` 改为 `double`，但该方向在平台上没有修复 93，并导致其它用例回退，因此已撤回。当前 `real` 仍沿用 C `float` 表示。

## 6. 验证结果

本轮执行了以下验证：

```bash
cmake --build /build --config Release
```

构建通过，生成：

- `/build/bin/pascc`
- `/build/bin/pascc_dummy`

针对性验证样例覆盖：

- `read(getint)` 可以通过语义分析，并生成 `scanf(..., &__result)`。
- 字符串常量 `'Not exist'`、`'--'` 可以声明并通过 `write` 输出。
- `Break` 可以在循环中生成 C 的 `break;`。
- 伪编译器可以用于爬取闭集源码，避免源码内容被 shell 通配符展开污染。
- 93 号用例在 Debian 9 / GCC 6.3 下不再出现递归积分结果偏差。

说明：开放集相关的浮点格式、整数宽度、实参求值顺序等已有在线通过行为，本轮未作为问题处理，也未主动修改。
