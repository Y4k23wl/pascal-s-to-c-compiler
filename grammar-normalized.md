# Pascal-S Grammar (Normalized from grammar.rtf)

Notes:

- `e` means epsilon (empty production).
- Line breaks in the original RTF are treated as line wrapping, not alternation.
- All `®` are normalized to `->`.
- Full-width punctuation in the original is normalized to ASCII punctuation.
- `assignop`, `relop`, `addop`, and `mulop` are left as named grammar items here; the Bison file expands them into concrete tokens.
- The original uses both `variable assignop expression` and `func_id assignop expression`. In a Bison skeleton, those two forms overlap syntactically when `func_id` is just an identifier, so the parser file merges them into one assignment form and leaves function-result checking to semantics.

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
             | ' letter '

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
           | func_id assignop expression
           | procedure_call
           | compound_statement
           | if expression then statement else_part
           | for id assignop expression to expression do statement
           | read ( variable_list )
           | write ( expression_list )

variable_list -> variable
               | variable_list , variable

variable -> id id_varpart

id_varpart -> e
            | [ expression_list ]

procedure_call -> id
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
        | id ( expression_list )
        | not factor
        | uminus factor
```
