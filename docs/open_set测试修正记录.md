# `testing/open_set` 测试修正记录

本文档记录在使用 `testing/open_set` 作为回归集时，暴露出的前端问题，以及对应的修正方式。

目标不是罗列所有通过样例，而是说明：

1. 测试集反映出当前真实语言子集比最初文档更大
2. 每类失败是在哪一层出现的
3. 我具体改了哪些代码把它修正

对应代码文件：

- `/frontend/pascal_s_lexer.l`
- `/frontend/pascal_s_parser.y`
- `/frontend/ast.hpp`
- `/frontend/ast.cpp`
- `/semantic/semantic.hpp`
- `/semantic/semantic.cpp`
- `/pascal_s_driver.cpp`

## 1. 回归方式

使用的主回归命令是：

```bash
for f in testing/open_set/*.pas; do
  ./build/bin/pascc -i "$f" >/dev/null
done
```

最开始这批测试并不能全部通过。失败大致分为五类：

- 词法能力缺失
- 语法能力缺失
- AST 节点体系不完整
- 语义规则与测试集不一致
- 长表达式导致的实现级崩溃

## 2. 词法层问题与修正

### 2.1 `//` 行注释不支持

#### 现象

`testing/open_set/05_const_var_defn3.pas`、`testing/open_set/53_skip_spaces.pas` 等文件开头包含：

```pascal
// ...
```

旧词法器只支持 `{...}` 注释，因此在第一个 `/` 处直接报语法错。

#### 修正

在 [pascal_s_lexer.l]中新增：

```lex
"//"[^\n]*                  { advance_position(yytext); }
```

这样整行会被当作注释跳过，同时仍然正确维护列号。

### 2.2 下划线标识符不支持

#### 现象

`testing/open_set/19_if_test4.pas`、`testing/open_set/35_short_circuit3.pas`、`testing/open_set/46_full_conn.pas` 等用例里有诸如：

- `if_ifElse_`
- `set_a`
- `is_valid`

旧规则：

```lex
ID_START [A-Za-z]
ID_CHAR  [A-Za-z0-9]
```

导致 `_` 被识别成非法字符。

#### 修正

把词法规则改为：

```lex
ID_START [A-Za-z_]
ID_CHAR  [A-Za-z0-9_]
```

修正位置仍在 [pascal_s_lexer.l]。

### 2.3 标识符被截断到 8 位

#### 现象

最初实现沿用了“8 位标识符”规则，`normalize_id()` 会截断名字。公开测试里存在大量长函数名和长变量名，这会导致：

- 不同标识符被截断成同名
- 语义分析出现错误的重定义或错误解析

#### 修正

删除 `MAX_ID_LEN` 截断逻辑，让 `normalize_id()` 保留完整名字，只做小写归一化。

修改位置： [pascal_s_lexer.l]

## 3. 语法层问题与修正

### 3.1 缺少 `while`

#### 现象

`testing/open_set/21_while_if_test2.pas`、`testing/open_set/58_many_params2.pas` 明确使用了：

```pascal
while cond do
  stmt
```

旧文法没有 `WHILE` token 和对应产生式，因此直接语法失败。

#### 修正

在 [pascal_s_parser.y] 中：

1. 新增 `WHILE` token
2. 为 `statement` 增加：

```bison
| WHILE expression DO statement
  {
      $$ = ast_make_while_stmt($2, $4, AST_LOC(@$));
  }
```

同时在 AST 中新增 `AST_WHILE_STMT`。

### 3.2 缺少布尔字面量 `true` / `false`

#### 现象

`testing/open_set/26_op_priority4.pas`、`testing/open_set/40_percolation.pas` 等用例有：

```pascal
flag := false;
flag := true;
```

旧实现会把它们当普通标识符，于是语义阶段报“未声明的标识符”。

#### 修正

在 [pascal_s_lexer.l] 中新增：

```lex
"true"  { RETURN_SIMPLE_TOKEN(TRUE); }
"false" { RETURN_SIMPLE_TOKEN(FALSE); }
```

在 [pascal_s_parser.y] 中把它们接到：

- `const_value`
- `factor`

并构造 `ast_make_bool_literal(...)`。

### 3.3 缺少空参数列表 `()`

#### 现象

测试集中大量使用零参调用：

- `func()`
- `loop2()`
- `Dijkstra()`

旧文法只有 `id` 和 `id(expression_list)`，没有 `id()`，因此在 `RPAREN` 处报错。

#### 修正

在 [pascal_s_parser.y] 中补了：

- `formal_parameter -> ( )`
- `procedure_call -> ID LPAREN RPAREN`
- `factor -> ID LPAREN RPAREN`

这样零参子程序的声明和调用都能被接受。

### 3.4 缺少一元正号 `+`

#### 现象

`testing/open_set/29_unary_op2.pas` 使用：

```pascal
a := a - - 4 + +b;
```

旧文法只支持一元负号，不支持一元正号，因此在第二个 `+` 处语法失败。

#### 修正

在 [pascal_s_parser.y] 的 `factor` 中补了：

```bison
| PLUS factor %prec UMINUS
  {
      $$ = ast_make_unary_expr("+", $2, AST_LOC(@$));
  }
```

## 4. AST 层问题与修正

### 4.1 缺少 `AST_WHILE_STMT`

为了支持 `while`，在 [ast.hpp] 和 [ast.cpp] 中新增：

- `AST_WHILE_STMT`
- `ast_make_while_stmt(...)`
- `ast_kind_name()` 分支
- `ast_validate()` 对应校验

节点布局固定为：

- `children[0]`：条件
- `children[1]`：循环体

### 4.2 缺少 `AST_BOOL_LITERAL`

为了避免把布尔字面量塞进普通标识符或字符串，新增：

- `AST_BOOL_LITERAL`
- `ast_make_bool_literal(...)`

实现上复用了 `AstNode.flag` 字段保存真假值。

这部分修改在：

- [ast.hpp]
- [ast.cpp]

## 5. 语义层问题与修正

### 5.1 零参函数名直接作为表达式值

#### 现象

`testing/open_set/07_var_defn_func.pas` 里有：

```pascal
a := defn;
```

这里 `defn` 是零参函数。旧语义实现把所有 `AST_VAR_REF(function_name)` 都当错误，报：

```text
函数名不能直接当变量使用，应写成函数调用
```

#### 修正

在 [semantic.cpp] 的 `analyze_var_ref()` 中改成：

1. 若命中的是函数符号
2. 且没有下标
3. 且该函数参数列表为空

则允许把它当成零参函数值使用，返回函数返回类型。

如果函数有参数，仍然报错，要求显式写成调用。

### 5.2 语句位置允许忽略函数返回值

#### 现象

测试集中存在这种写法：

```pascal
add;
exgcd(a, b, x[0], y[0]);
```

其中 `add`、`exgcd` 都是函数，但调用结果没有被使用。旧实现坚持“语句位置只能是过程调用”，于是报：

```text
过程调用语句中使用的不是过程
```

#### 修正

在 [semantic.cpp] 的 `analyze_call_stmt()` 中放宽规则：

- `Procedure` 合法
- `Function` 也合法，只是返回值被忽略

参数检查逻辑仍复用 `check_call_arguments()`，没有单独分叉。

### 5.3 `not` 的语义与测试集不一致

#### 现象

`testing/open_set/28_unary_op.pas` 使用：

```pascal
write(not a);
```

而 `a` 是 `integer`。旧实现按照经典布尔语义，只允许 `not boolean`，因此报错。

#### 修正

在 [semantic.cpp] 的一元表达式处理中，把 `not` 放宽为：

- 接受 `boolean`
- 也接受 `integer`
- 结果类型与操作数一致

这是按公开测试集的真实语义要求做的兼容，而不是经典 Pascal 的最严格解释。

### 5.4 新增 `while` 语义检查

为了配合新的 `AST_WHILE_STMT`，在 [semantic.cpp] 中新增 `analyze_while_stmt()`：

- 先分析条件
- 要求条件类型是 `boolean`
- 再递归分析循环体

同时在 `analyze_stmt()` 分派中接入 `AST_WHILE_STMT`。

## 6. 驱动层改动

### 6.1 默认输出太吵，不利于批量回归

#### 现象

旧驱动默认打印整棵 AST。拿它跑 `testing/open_set` 批量回归时，输出量非常大，不适合快速定位失败样例。

#### 修正

在 [pascal_s_driver.cpp] 中改成：

- 默认只输出 `semantic analysis: ok`
- 失败时打印词法 / 语法 / 语义错误
- 若需要 AST，显式加 `--dump-ast`

这样批量回归命令就能直接看成功/失败，而不是被 AST 淹没。

## 7. 长表达式导致的崩溃

### 7.1 现象

`testing/open_set/56_long_code2.pas` 中有一个极长的加法链，重复项约 4000 次：

```pascal
ans := a[...] + a[...] + a[...] + ...
```

这个样例在语义分析阶段直接退出，返回码 `139`。  
通过临时阶段定位后，确认问题不在 `parse`、不在 `ast_validate`，而是在 `SemanticAnalyzer::analyze()` 内部的表达式递归。

### 7.2 根因

旧实现中：

- `analyze_expr()`
- `analyze_binary_expr()`

会对左孩子、右孩子递归调用。  
当表达式被语法分析构造成极深的左递归树时，会把 C++ 调用栈压爆。

### 7.3 修正

在 [semantic.cpp] 中把深表达式分析改成显式栈：

1. `analyze_expr()` 对 `AST_UNARY_EXPR` / `AST_BINARY_EXPR` 走 `analyze_expr_iterative()`
2. `analyze_expr_iterative()` 使用 `std::vector<std::pair<const AstNode *, bool> >` 做后序遍历
3. 子节点结果先写入 `result_.expr_info`
4. 当前节点再通过 `compute_expr_info()` 组合出最终结果

这样表达式深度不再受 C++ 调用栈限制，`56_long_code2.pas` 随后即可通过。

## 8. 端到端输出对拍中暴露的代码生成问题

前面的回归主要验证“能否通过词法、语法、语义阶段”。在把 `testing/open_set` 进一步升级成端到端输出对拍后，又额外暴露出三类代码生成问题。

本轮对拍方式是：

1. 用当前 `pascc` 把 `.pas` 翻译成 `.c`
2. 用 `cc -std=c99` 把生成的 C 编译成可执行文件
3. 用 Free Pascal Compiler 3.2.2 直接编译同一份 Pascal 源程序
4. 若存在同名 `.in` 文件，则两边都喂同一份标准输入
5. 精确比对两个程序的标准输出

对应自动化脚本是 [testing/run_output_consistency.sh]。

### 8.1 `write(real)` 格式与精度不一致

#### 现象

`14_div.pas`、`51_var_name.pas`、`65_float.pas` 都暴露了这个问题：

- `2.0` 被打印成 `2`
- 浮点结果只保留了很短的有效数字

#### 根因

旧代码生成曾直接发射：

```c
printf("%g", expr);
```

这会让常规小数输出不稳定，和评测期望不一致。

#### 修正

在 [codegen.cpp] 中新增 `write_real()` 辅助函数，当前统一用 `%f` 输出 `real`。

### 8.2 `integer` 运行时表示

当前最终实现中，Pascal `integer` 变量、数组元素、参数和函数返回值统一映射成 C `int`，整型常量声明也使用 `const int`。

整数读写格式串对应使用 `%d`。

### 8.3 调用实参的求值顺序被错误交给了 C

#### 现象

`57_many_params.pas` 中存在大量带副作用的调用实参：

```pascal
param16(getint(i), getint(i), ..., getint(i))
```

旧生成器直接发射成 C 调用后，得到的结果与 Pascal 参考程序不一致。

#### 根因

C 语言函数调用实参的求值顺序未指定；如果直接生成：

```c
fn(getint(&i), getint(&i), ...);
```

就会把 Pascal 语义泄漏成宿主 C 的不确定行为。

另外，用 FPC 做最小验证后可确认：当前环境下参考 Pascal 编译器对这类实参求值采用的是“从右到左”顺序。

#### 修正

在 [codegen.cpp] 的 `emit_call()` 中，不再直接拼实参表达式，而是：

1. 先为值参和 `var` 参分别准备 `__call_tmp_*` 临时槽
2. 按“从右到左”的顺序把每个实参求值进临时槽
3. 再按原参数位置调用真正的 C 函数

这些临时槽由当前函数体内的局部数组承载，避免递归调用共享同一批文件作用域临时槽。

## 9. 最终结果

完成以上修正后，使用下面的端到端脚本回归：

```bash
./testing/run_output_consistency.sh
```

当前 `testing/open_set/*.pas` 已全部通过词法、语法和语义阶段；在端到端输出对拍下，`70/70` 个样例也已全部与 Pascal 参考程序输出一致。

需要注意的是：

- 这仍然不是完整 Pascal
- 但它已经明显超出最初文档中的“最小 Pascal-S”
- 因此后续设计和文档都应继续以真实测试集和现有实现为准，而不是只参考最早的课程文法摘要
