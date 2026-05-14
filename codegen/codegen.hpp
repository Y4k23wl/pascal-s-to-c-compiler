#pragma once

#include <sstream>
#include <string>
#include <unordered_map>

#include "../frontend/ast.hpp"
#include "../semantic/semantic.hpp"

class CodeGenerator {
public:
    std::string generate(const AstNode *root, const SemanticResult &sem);

private:
    struct CallTempState {
        size_t int_values;
        size_t real_values;
        size_t bool_values;
        size_t char_values;
        size_t int_refs;
        size_t real_refs;
        size_t bool_refs;
        size_t char_refs;

        CallTempState()
            : int_values(0),
              real_values(0),
              bool_values(0),
              char_values(0),
              int_refs(0),
              real_refs(0),
              bool_refs(0),
              char_refs(0) {}
    };

    void reset(const SemanticResult &sem);

    void emit_program(const AstNode *node);
    void emit_helpers();
    void plan_call_temps(const AstNode *node);
    void emit_call_temp_decls();
    void emit_global_decls(const AstNode *block);
    void emit_prototypes(const AstNode *subprogram_list);
    void emit_subprograms(const AstNode *subprogram_list);
    void emit_subprogram(const AstNode *subprogram);
    void emit_main(const AstNode *program);
    void emit_local_decls(const AstNode *block, const Scope *scope);
    void emit_const_decls(const AstNode *const_list, const Scope *scope, bool is_global);
    void emit_var_decls(const AstNode *var_list, const Scope *scope, bool is_global);
    void emit_stmt(const AstNode *node);
    void emit_stmt_as_block(const AstNode *node);
    void emit_statement_list(const AstNode *node);

    std::string emit_expr(const AstNode *node);
    std::string emit_expr_with_parent(const AstNode *node,
                                      int parent_precedence,
                                      bool is_right_child);
    std::string emit_var_ref(const AstNode *node);
    std::string emit_call(const Symbol &callee, const AstNode *arg_list);
    std::string emit_address_of(const AstNode *node);
    std::string emit_assignment_target(const AstNode *node);
    std::string emit_default_value(const SemType &type) const;
    std::string emit_decl(const Symbol &symbol, bool with_const, const std::string *init) const;
    std::string emit_signature(const Symbol &symbol) const;
    std::string c_type_name(const SemType &type) const;
    std::string binary_op_to_c(const std::string &op) const;
    std::string string_literal_to_c(const std::string &text) const;
    std::string format_real_literal(double value) const;
    std::string next_call_value_temp(const SemType &type);
    std::string next_call_ref_temp(const SemType &type);
    int expr_precedence(const AstNode *node) const;

    const Symbol *lookup_symbol(const Scope *scope, const std::string &name) const;
    const Symbol *lookup_global_symbol(const std::string &name) const;
    const Symbol *resolved_symbol(const AstNode *node) const;
    const ExprInfo *expr_info(const AstNode *node) const;
    const Scope *scope_for_owner(const AstNode *owner) const;
    const AstNode *child_at(const AstNode *node, size_t index) const;

    void emit_indent();
    void emit_line(const std::string &text = std::string());

private:
    std::ostringstream out_;
    const SemanticResult *sem_;
    int indent_level_;
    int for_temp_counter_;
    CallTempState call_temp_capacity_;
    CallTempState call_temp_usage_;
    std::unordered_map<const AstNode *, const Scope *> owner_scopes_;
};
