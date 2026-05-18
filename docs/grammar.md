# Pascal-S 实现文法

说明：

- 本文件记录当前编译器实现实际接受的 Pascal-S 文法。它以课程给出的原始 Pascal-S 文法为基础，并根据本地测试集和在线测试集的实际输入做了扩展。
- `e` 表示空产生式。
- `assignop`、`relop`、`addop`、`mulop` 在本文中保留为具名运算符类别；在 `pascal_s_parser.y` 中会展开为具体 token。
- `num` 表示整数或实数数字字面量。
- `char_const` 表示 Pascal 单字符常量。
- `string_const` 表示 Pascal 单引号字符串常量；实现支持字符串内部用两个连续单引号表示一个单引号字符。
- 标识符大小写不敏感，允许包含下划线，且不会被截断。
- 词法分析同时支持 `{ ... }` 块注释和 `// ...` 行注释。
- 错误恢复产生式没有写入本文法。它们属于 `pascal_s_parser.y` 中的实现细节。

```text
programstruct -> program_head ; program_body .

program_head -> program id ( idlist )
              | program id

program_body -> const_declarations
                var_declarations
                subprogram_declarations
                compound_statement

idlist -> id
        | idlist , id

const_declarations -> e
                    | const const_declaration ;

const_declaration -> id = const_value
                   | const_declaration ; id = const_value

const_value -> + num
             | - num
             | num
             | char_const
             | string_const
             | true
             | false

var_declarations -> e
                  | var var_declaration ;

var_declaration -> idlist : type
                 | var_declaration ; idlist : type

type -> basic_type
      | array [ period ] of basic_type

basic_type -> integer
            | real
            | boolean
            | char

period -> digits .. digits
        | period , digits .. digits

subprogram_declarations -> e
                         | subprogram_declarations subprogram ;

subprogram -> subprogram_head ; subprogram_body

subprogram_head -> procedure id formal_parameter
                 | function id formal_parameter : basic_type

formal_parameter -> e
                  | ( )
                  | ( parameter_list )

parameter_list -> parameter
                | parameter_list ; parameter

parameter -> var_parameter
           | value_parameter

var_parameter -> var value_parameter

value_parameter -> idlist : basic_type

subprogram_body -> const_declarations
                   var_declarations
                   compound_statement

compound_statement -> begin statement_list end

statement_list -> statement
                | statement_list ; statement

statement -> e
           | variable assignop expression
           | procedure_call
           | break
           | compound_statement
           | if expression then statement else_part
           | while expression do statement
           | for id assignop expression to expression do statement
           | read ( variable_list )
           | write ( expression_list )

variable_list -> variable
               | variable_list , variable

variable -> id id_varpart

id_varpart -> e
            | [ expression_list ]

procedure_call -> id
                | id ( )
                | id ( expression_list )

else_part -> e
           | else statement

expression_list -> expression
                 | expression_list , expression

expression -> simple_expression
            | simple_expression relop simple_expression

simple_expression -> term
                   | simple_expression addop term

term -> factor
      | term mulop factor

factor -> num
        | variable
        | ( expression )
        | id ( )
        | id ( expression_list )
        | true
        | false
        | string_const
        | not factor
        | uplus factor
        | uminus factor
```

具名运算符：

```text
assignop -> :=

relop -> =
       | <>
       | <
       | <=
       | >
       | >=

addop -> +
       | -
       | or

mulop -> *
       | /
       | div
       | mod
       | and
```
