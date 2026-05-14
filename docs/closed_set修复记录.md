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

- `code/semantic/semantic.cpp`

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

- `code/frontend/pascal_s_lexer.l`
- `code/frontend/pascal_s_parser.y`
- `code/frontend/ast.hpp`
- `code/frontend/ast.cpp`
- `code/semantic/semantic.hpp`
- `code/semantic/semantic.cpp`
- `code/codegen/codegen.hpp`
- `code/codegen/codegen.cpp`

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

- `code/frontend/pascal_s_lexer.l`
- `code/frontend/pascal_s_parser.y`
- `code/frontend/ast.hpp`
- `code/frontend/ast.cpp`
- `code/semantic/semantic.cpp`
- `code/codegen/codegen.cpp`

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
- 生成 C 程序时逐行写出：

```c
fputs("...\\n", stdout);
```

- 对 C 字符串字面量中的 `"`、`\`、`\t`、`\r` 做转义。
- 新增 CMake 目标 `dummy_pascc`，输出可执行文件名为 `pascc_dummy`。

主要修改文件：

- `code/testing/dummy.cpp`
- `code/CMakeLists.txt`

使用方式：

```bash
cmake --build code/build --config Release --target dummy_pascc
```

生成的伪编译器位于：

```text
code/build/bin/pascc_dummy
```

需要爬取闭集时，将该可执行文件作为平台提交/运行用的 `pascc`。

## 5. 闭集 93 数学压力用例后续定位

### 问题现象

平台反馈 93 号用例只剩运行结果错误。期望输出中包含：

```text
...0.6931471.584962...
```

实际输出对应位置明显偏离：

```text
...0.2022961.037538...
```

该用例现有记录虽然被旧爬取链路的 `*` 展开污染并截断，但仍能看出它包含 `my_pow`、`my_sqrt`、`simpson` 等自写数学函数。错误集中在迭代、递归积分和对数类结果，不是单纯输出格式或整数宽度问题。

### 已排除方向

曾尝试将 Pascal `real` 的目标 C 表示从 `float` 改为 `double`，包括：

- `write_real` 参数改为 `double`，但保持当前 `%f` 六位小数输出格式。
- `real` 值参数临时槽 `__call_tmp_r` 改为 `double`。
- `var real` 临时指针槽 `__call_tmp_pr` 改为 `double *`。
- `read(real)` 改为 `scanf("%lf", ...)`。
- 整数 `/` 产生 real 时的显式转换改为 `(double)`。
- `c_type_name(TypeKind::Real)` 返回 `double`。

平台结果显示该方向不成立：93 仍错误，并导致此前可通过的 94、95 也失败。因此该修改已撤回，`real` 继续沿用原来的 C `float` 表示。

下一步需要用已修复 shell 展开的 dummy 编译器重新爬取闭集 93 的完整 Pascal 源码，再定位真实错因。

已生成 Debian 9 x86_64 版本：

- `code/pascc.debian9`：恢复 `real=float` 后的主编译器。
- `code/pascc_dummy.debian9`：用于重新爬取闭集源码的 dummy 编译器。

补充：如果爬取链路仍会把 `*` 交给 shell 展开，dummy 输出源码时会将 `*` 替换为 `@`。重新分析源码时需要先把 `@` 还原为 `*`。

## 6. 验证结果

本轮执行了以下验证：

```bash
cmake --build code/build --config Release
```

构建通过，生成：

- `code/build/bin/pascc`
- `code/build/bin/pascc_dummy`

针对性验证样例覆盖：

- `read(getint)` 可以通过语义分析，并生成 `scanf(..., &__result)`。
- 字符串常量 `'Not exist'`、`'--'` 可以声明并通过 `write` 输出。
- `Break` 可以在循环中生成 C 的 `break;`。
- 伪编译器输出 `x := a * b;` 时，`*` 保持为普通字符，不再展开成文件列表。

说明：开放集相关的浮点格式、整数宽度、实参求值顺序等已有在线通过行为，本轮未作为问题处理，也未主动修改。

93 号问题追加执行了 `real=double` 方向的针对性压力测试，但该方向已被平台结果否定，相关源码改动已撤回。
