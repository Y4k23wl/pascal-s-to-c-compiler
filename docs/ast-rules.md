# Pascal-S AST 规则说明

本文档描述当前工程中 Pascal-S 前端构造的 AST 规则。  
这里的“规则”以实际代码实现为准，而不是参考性方案文档为准。

对应实现文件：

- `code/frontend/ast.hpp`
- `code/frontend/ast.cpp`
- `code/frontend/pascal_s_parser.y`
- `code/frontend/pascal_s_frontend.hpp`

## 1. AST 的定位

当前编译器前端的工作链路是：

```text
Pascal-S 源代码
  -> 词法分析（Flex）
  -> 语法分析 + AST 构造（Bison）
  -> AST
  -> 语义分析 / 符号表 / C 代码生成
```

因此 AST 不是调试附属物，而是后续编译阶段的正式输入。

AST 的设计目标有三点：

- 保留 Pascal-S 的核心语义结构，而不是保留全部语法细节
- 为后续语义分析提供稳定、统一的节点结构
- 为后续 C 代码生成提供可直接遍历的树形表示

## 2. 通用结构

所有节点都使用 `AstNode` 表示，定义在 `code/frontend/ast.hpp` 中。

```cpp
struct AstNode {
    AstKind kind;
    AstLocation loc;
    std::string text;
    long long int_value;
    long long second_int_value;
    double real_value;
    bool flag;
    std::vector<AstNode *> children;
};
```

各字段含义如下：

- `kind`
  - 节点类别，决定该节点表示什么结构
- `loc`
  - 源代码位置，记录起止行列，用于语义错误和代码生成时定位
- `text`
  - 文本属性
  - 主要用于标识符名、类型名、运算符名、过程名、函数名
- `int_value`
  - 整数字面量值
  - 也用于数组区间下界
- `second_int_value`
  - 当前主要用于数组区间上界
- `real_value`
  - 实数字面量值
- `flag`
  - 当前主要用于参数节点，表示该参数组是否为 `var` 引用参数
- `children`
  - 子节点列表
  - 子节点顺序是 AST 规则的重要组成部分，后续阶段必须按约定读取

## 3. 位置信息规则

位置信息来自词法分析器 `code/frontend/pascal_s_lexer.l` 中维护的 `yylloc`。

规则如下：

- 词法分析器为每个 token 设置 `first_line / first_column / last_line / last_column`
- 语法分析器在归约时，通过 `AST_LOC(@$)` 把整个产生式的覆盖范围记录到节点
- 因此大多数 AST 节点的 `loc` 表示该语言结构在源程序中的整体范围，而不是单个关键字范围

语义分析和错误处理应优先使用 `node->loc`，而不是重新回看 token。

## 4. 节点分类

当前实现的节点类型如下：

- 程序与块
  - `AST_PROGRAM`
  - `AST_PROGRAM_HEAD`
  - `AST_BLOCK`
- 标识符与声明
  - `AST_IDENTIFIER`
  - `AST_IDENTIFIER_LIST`
  - `AST_CONST_DECL`
  - `AST_CONST_DECL_LIST`
  - `AST_VAR_DECL`
  - `AST_VAR_DECL_LIST`
- 类型
  - `AST_BASIC_TYPE`
  - `AST_ARRAY_TYPE`
  - `AST_PERIOD`
  - `AST_PERIOD_LIST`
- 子程序
  - `AST_SUBPROGRAM`
  - `AST_SUBPROGRAM_LIST`
  - `AST_PROCEDURE_HEAD`
  - `AST_FUNCTION_HEAD`
  - `AST_PARAM_GROUP`
  - `AST_PARAM_LIST`
- 语句
  - `AST_COMPOUND_STMT`
  - `AST_STATEMENT_LIST`
  - `AST_EMPTY_STMT`
  - `AST_ASSIGN_STMT`
  - `AST_CALL_STMT`
  - `AST_IF_STMT`
  - `AST_WHILE_STMT`
  - `AST_FOR_STMT`
  - `AST_BREAK_STMT`
  - `AST_READ_STMT`
  - `AST_WRITE_STMT`
- 表达式与引用
  - `AST_VAR_REF`
  - `AST_VARIABLE_LIST`
  - `AST_EXPRESSION_LIST`
  - `AST_CALL_EXPR`
  - `AST_BINARY_EXPR`
  - `AST_UNARY_EXPR`
  - `AST_BOOL_LITERAL`
  - `AST_INT_LITERAL`
  - `AST_REAL_LITERAL`
  - `AST_CHAR_LITERAL`
  - `AST_STRING_LITERAL`

## 5. 节点规则总表

下面定义每种节点的语义和子节点布局。

### 5.1 程序与块

#### `AST_PROGRAM`

表示整个 Pascal-S 程序。

- `children[0]`：`AST_PROGRAM_HEAD`
- `children[1]`：`AST_BLOCK`

#### `AST_PROGRAM_HEAD`

表示程序头。

- `text`：程序名
- `children.size()`：
  - `0` 或 `1`
- `children[0]`：
  - 若存在，则为 `AST_IDENTIFIER_LIST`
  - 对应 `program p(input, output)` 这种参数表

#### `AST_BLOCK`

统一表示程序体或子程序体。

- `children[0]`：`AST_CONST_DECL_LIST`
- `children[1]`：`AST_VAR_DECL_LIST`
- `children[2]`：`AST_SUBPROGRAM_LIST`
- `children[3]`：`AST_COMPOUND_STMT`

说明：

- 主程序体和子程序体都用同一结构
- 后续语义分析进入一个新作用域时，可直接把 `AST_BLOCK` 看作作用域单元

### 5.2 标识符与声明

#### `AST_IDENTIFIER`

表示单个标识符。

- `text`：标识符名
- 无子节点

#### `AST_IDENTIFIER_LIST`

表示标识符列表。

- `children[i]`：每个元素都是 `AST_IDENTIFIER`

#### `AST_CONST_DECL`

表示单个常量声明。

- `text`：常量名
- `children[0]`：常量值节点
  - 可能是 `AST_BOOL_LITERAL`
  - 可能是 `AST_INT_LITERAL`
  - 可能是 `AST_REAL_LITERAL`
  - 可能是 `AST_CHAR_LITERAL`
  - 可能是 `AST_STRING_LITERAL`
  - 可能是 `AST_UNARY_EXPR("-") + 数字`
  - 可能是 `AST_UNARY_EXPR("+") + 数字`

#### `AST_CONST_DECL_LIST`

表示常量声明列表。

- `children[i]`：每个元素都是 `AST_CONST_DECL`

#### `AST_VAR_DECL`

表示单组变量声明。

- `children[0]`：`AST_IDENTIFIER_LIST`
- `children[1]`：类型节点
  - `AST_BASIC_TYPE` 或 `AST_ARRAY_TYPE`

#### `AST_VAR_DECL_LIST`

表示变量声明列表。

- `children[i]`：每个元素都是 `AST_VAR_DECL`

### 5.3 类型

#### `AST_BASIC_TYPE`

表示基本类型。

- `text`：
  - `"integer"`
  - `"real"`
  - `"boolean"`
  - `"char"`

#### `AST_ARRAY_TYPE`

表示数组类型。

- `children[0]`：`AST_PERIOD_LIST`
- `children[1]`：`AST_BASIC_TYPE`

说明：

- 当前文法只支持数组元素类型为基本类型
- 多维数组通过 `AST_PERIOD_LIST` 中多个区间实现

#### `AST_PERIOD`

表示一个数组下标区间。

- `int_value`：下界
- `second_int_value`：上界
- 无子节点

例如 `1..10`：

- `int_value = 1`
- `second_int_value = 10`

#### `AST_PERIOD_LIST`

表示数组维度区间列表。

- `children[i]`：每个元素都是 `AST_PERIOD`

例如 `array[1..10, 0..5] of integer` 会形成：

- `AST_ARRAY_TYPE`
  - `AST_PERIOD_LIST`
    - `AST_PERIOD(1, 10)`
    - `AST_PERIOD(0, 5)`
  - `AST_BASIC_TYPE("integer")`

### 5.4 子程序

#### `AST_SUBPROGRAM`

表示一个过程或函数定义。

- `children[0]`：头部
  - `AST_PROCEDURE_HEAD` 或 `AST_FUNCTION_HEAD`
- `children[1]`：`AST_BLOCK`

#### `AST_SUBPROGRAM_LIST`

表示子程序列表。

- `children[i]`：每个元素都是 `AST_SUBPROGRAM`

#### `AST_PROCEDURE_HEAD`

表示过程头。

- `text`：过程名
- `children[0]`：`AST_PARAM_LIST`

#### `AST_FUNCTION_HEAD`

表示函数头。

- `text`：函数名
- `children[0]`：`AST_PARAM_LIST`
- `children[1]`：返回类型 `AST_BASIC_TYPE`

#### `AST_PARAM_GROUP`

表示同一组参数声明，如 `a, b : integer` 或 `var x : integer`。

- `flag`
  - `true`：`var` 参数
  - `false`：值参数
- `children[0]`：`AST_IDENTIFIER_LIST`
- `children[1]`：`AST_BASIC_TYPE`

#### `AST_PARAM_LIST`

表示参数组列表。

- `children[i]`：每个元素都是 `AST_PARAM_GROUP`

### 5.5 语句

#### `AST_COMPOUND_STMT`

表示 `begin ... end` 复合语句。

- `children[0]`：`AST_STATEMENT_LIST`

#### `AST_STATEMENT_LIST`

表示语句序列。

- `children[i]`：各语句节点

说明：

- 空语句会显式表示为 `AST_EMPTY_STMT`
- 因此语句表中可能出现空语句节点

#### `AST_EMPTY_STMT`

表示空语句。

- 无子节点

#### `AST_ASSIGN_STMT`

表示赋值语句。

- `children[0]`：左值 `AST_VAR_REF`
- `children[1]`：右值表达式

说明：

- 当前文法已经把“函数体内对函数名赋值”并入普通赋值
- 是否允许给函数名赋值，要在语义分析中判断当前作用域和函数定义

#### `AST_CALL_STMT`

表示语句位置的子程序调用。

- `text`：被调用名字
- `children.size()`：
  - `0` 或 `1`
- `children[0]`：
  - 若存在，则为 `AST_EXPRESSION_LIST`

说明：

- 当前实现允许过程调用
- 也允许函数调用结果被忽略
- 零参调用既可以写成 `f`，也可以写成 `f()`

#### `AST_IF_STMT`

表示条件语句。

- `children[0]`：条件表达式
- `children[1]`：`then` 分支语句
- `children[2]`：
  - 若存在，则为 `else` 分支语句

#### `AST_WHILE_STMT`

表示 `while ... do ...`。

- `children[0]`：条件表达式
- `children[1]`：循环体语句

#### `AST_FOR_STMT`

表示 `for` 循环。

- `text`：循环变量名
- `children[0]`：起始表达式
- `children[1]`：终止表达式
- `children[2]`：循环体语句

说明：

- 当前语法只支持 `for id := expr to expr do stmt`
- 暂未包含 `downto`

#### `AST_BREAK_STMT`

表示 `break` 语句。

- 无子节点

#### `AST_READ_STMT`

表示 `read(...)`。

- `children[0]`：`AST_VARIABLE_LIST`

#### `AST_WRITE_STMT`

表示 `write(...)`。

- `children[0]`：`AST_EXPRESSION_LIST`

### 5.6 表达式与引用

#### `AST_VAR_REF`

表示变量引用，也用于数组元素访问。

- `text`：变量名
- `children.size()`：
  - `0` 或 `1`
- `children[0]`：
  - 若存在，则为下标表达式列表 `AST_EXPRESSION_LIST`

例如：

- `x` -> `AST_VAR_REF(text="x")`
- `a[i, j]` -> `AST_VAR_REF(text="a") + AST_EXPRESSION_LIST(i, j)`

#### `AST_VARIABLE_LIST`

表示变量列表，仅用于 `read(...)`。

- `children[i]`：每个元素都是 `AST_VAR_REF`

#### `AST_EXPRESSION_LIST`

表示表达式列表。

- `children[i]`：每个元素都是表达式节点

用途包括：

- 过程调用实参
- 函数调用实参
- 数组下标列表
- `write(...)` 参数列表

#### `AST_CALL_EXPR`

表示函数调用表达式。

- `text`：函数名
- `children.size()`：
  - `0` 或 `1`
- `children[0]`：
  - 若存在，则为 `AST_EXPRESSION_LIST`

说明：

- 零参函数写成 `f()` 时构造 `AST_CALL_EXPR`
- 若零参函数直接写成 `f`，语法阶段会先构造 `AST_VAR_REF("f")`，后续由语义分析识别成零参函数值引用

#### `AST_BINARY_EXPR`

表示二元运算表达式。

- `text`：运算符
- `children[0]`：左操作数
- `children[1]`：右操作数

当前可能出现的 `text` 包括：

- 关系运算
  - `"="`
  - `"<>"`
  - `"<"`
  - `"<="`
  - `">"`
  - `">="`
- 加法层
  - `"+"`
  - `"-"`
  - `"or"`
- 乘法层
  - `"*"`
  - `"/"`
  - `"div"`
  - `"mod"`
  - `"and"`

#### `AST_UNARY_EXPR`

表示一元运算表达式。

- `text`：运算符
- `children[0]`：操作数

当前可能的 `text`：

- `"+"`
- `"-"`
- `"not"`

#### `AST_BOOL_LITERAL`

表示布尔字面量。

- `flag`
  - `true` 表示 `true`
  - `false` 表示 `false`
- 无子节点

#### `AST_INT_LITERAL`

表示整数字面量。

- `int_value`：整数值

#### `AST_REAL_LITERAL`

表示实数字面量。

- `real_value`：实数值

#### `AST_CHAR_LITERAL`

表示字符字面量。

- `text`：原始字符常量文本

说明：

- 当前词法器直接把字符常量文本传入 AST
- 若后续语义分析或代码生成需要转义后的字符值，可在专门的辅助函数中统一解码

#### `AST_STRING_LITERAL`

表示字符串字面量。

- `text`：原始字符串常量文本

## 6. 列表节点统一规则

下列节点都属于“列表节点”：

- `AST_IDENTIFIER_LIST`
- `AST_CONST_DECL_LIST`
- `AST_VAR_DECL_LIST`
- `AST_PERIOD_LIST`
- `AST_SUBPROGRAM_LIST`
- `AST_PARAM_LIST`
- `AST_STATEMENT_LIST`
- `AST_VARIABLE_LIST`
- `AST_EXPRESSION_LIST`

统一规则如下：

- 列表本身不通过 `text`、`int_value` 承载业务含义
- 列表元素按出现顺序保存在 `children` 中
- 空列表允许存在
  - 例如没有常量声明时，仍然会创建一个空的 `AST_CONST_DECL_LIST`
  - 这使后续遍历逻辑更稳定，不需要到处判空

## 7. 构造规则

AST 的构造发生在 `code/frontend/pascal_s_parser.y` 的归约动作中。

基本原则如下：

- 每个重要非终结符归约时都构造对应节点
- 语法中的分隔符和大多数关键字不进入 AST
  - 例如分号、括号、冒号、`begin/end`、`var`、`const` 等只影响结构，不单独建节点
- 同类序列统一折叠成列表节点
- 运算表达式统一折叠为一元/二元表达式节点
- 过程调用和函数调用分成两类
  - 出现在语句位置的是 `AST_CALL_STMT`
  - 出现在表达式位置的是 `AST_CALL_EXPR`
- `while` 单独建模为 `AST_WHILE_STMT`
- 布尔字面量单独建模为 `AST_BOOL_LITERAL`

这意味着 AST 保留的是“语义结构”，不是逐 token 的语法树。

## 8. 校验规则

`code/frontend/ast.cpp` 中实现了 `ast_validate(FILE *out, const AstNode *node)`，用于检查 AST 结构是否符合约定。

当前校验重点包括：

- 程序节点必须恰好有 2 个孩子
- 块节点必须恰好有 4 个孩子
- 赋值、变量声明、数组类型、参数组、二元表达式等节点必须有固定数量的孩子
- 过程头、函数头、调用、变量引用等节点必须满足名称字段存在
- `if` 节点必须有 2 或 3 个孩子
- `for` 节点必须有 3 个孩子且循环变量名存在

这个校验器的作用不是替代语义分析，而是保证“树的形状正确”。

也就是说：

- `ast_validate` 负责检查 AST 是否符合结构约定
- 语义分析负责检查类型、作用域、声明使用关系、参数匹配等语义约束

## 9. 与语义分析的接口约定

语义分析阶段不应重新解析源程序，而应直接接收 AST 根节点。

当前对外接口在 `code/frontend/pascal_s_frontend.hpp`：

- `parse_pascal_stream(FILE *input)`
- `parse_pascal_file(const char *path)`
- `pascal_s_get_ast_root()`
- `pascal_s_had_lexical_error()`
- `pascal_s_lexical_error_count()`
- `pascal_s_had_syntax_error()`
- `pascal_s_syntax_error_count()`

推荐语义分析入口形式：

```cpp
AstNode *root = parse_pascal_file(path);
if (root == nullptr) {
    // 前端已发现词法/语法错误
}

if (!ast_validate(stderr, root)) {
    // AST 结构异常
}

SemanticAnalyzer analyzer;
analyzer.analyze(root);
```

错误恢复接入后，接口约定补充为：

- 词法或语法阶段即使进行了恢复，只要最终出现错误，`parse_pascal_*` 仍返回 `nullptr`
- 恢复期间构造的占位节点仍应满足 AST 结构约束，避免把错误传播成空指针崩溃
- 语句恢复优先使用空语句、空参数列表、空表达式列表这类现有节点，而不是额外引入复杂错误节点

当前驱动 `code/pascal_s_driver.cpp` 额外支持：

- 默认只输出语义阶段结果
- 加 `--dump-ast` 时输出 AST

语义分析应依赖以下字段：

- `kind`
  - 决定当前节点类别
- `text`
  - 标识符名、函数名、运算符名
- `flag`
  - 是否为 `var` 参数
- `int_value / second_int_value / real_value`
  - 常量值与数组边界
- `loc`
  - 报错位置
- `children`
  - 结构关系

## 10. 与 C 代码生成的接口约定

C 代码生成阶段同样不应重新解析 Pascal-S 文本，而应遍历 AST。

建议映射关系如下：

- `AST_PROGRAM`
  - 生成整个 C 文件结构
- `AST_CONST_DECL_LIST`
  - 生成常量定义
- `AST_VAR_DECL_LIST`
  - 生成变量定义
- `AST_SUBPROGRAM_LIST`
  - 生成函数/过程定义
- `AST_ASSIGN_STMT`
  - 生成赋值语句
- `AST_IF_STMT`
  - 生成 `if` / `else`
- `AST_FOR_STMT`
  - 生成 `for`
- `AST_BREAK_STMT`
  - 生成 `break`
- `AST_CALL_STMT` / `AST_CALL_EXPR`
  - 生成调用
- `AST_BINARY_EXPR` / `AST_UNARY_EXPR`
  - 生成表达式

数组、参数传递方式、函数返回值赋值规则等，需要在语义分析后再决定具体的 C 映射细节。

## 11. 当前 AST 不负责的内容

当前 AST 规则不直接解决以下问题：

- 标识符是否已声明
- 标识符是否重复声明
- 变量与常量是否被正确使用
- 类型是否匹配
- 过程/函数参数是否匹配
- 函数体中对函数名赋值是否合法
- Pascal-S 结构如何最优翻译为 C

这些都属于 AST 之后的语义分析和代码生成阶段。

## 12. 示例

Pascal-S：

```pascal
x := a + b * 2;
```

对应 AST 结构：

```text
AssignStmt
  VarRef("x")
  BinaryExpr("+")
    VarRef("a")
    BinaryExpr("*")
      VarRef("b")
      IntLiteral(2)
```

Pascal-S：

```pascal
for i := 1 to 5 do
  write(i)
```

对应 AST 结构：

```text
ForStmt("i")
  IntLiteral(1)
  IntLiteral(5)
  WriteStmt
    ExpressionList
      VarRef("i")
```

## 13. 使用建议

后续开发时建议遵守以下规则：

- 若修改文法并影响 AST 结构，必须同步更新本文档
- 语义分析与代码生成只依赖 AST 规则，不依赖 Bison 产生式文本
- 新增节点类型时，至少同步更新：
  - `AstKind`
  - `ast_kind_name`
  - 构造函数
  - `ast_validate`
  - 本文档

这样可以保证 AST 始终作为整个 Pascal-S 到 C 编译器的稳定中间表示。
