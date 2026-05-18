#pragma once

#include <cstdio>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../frontend/ast.hpp"

enum class TypeKind {
    Integer,
    Real,
    Boolean,
    Char,
    String,
    Array,
    Void,
    Invalid
};

struct ArrayBound {
    int low;
    int high;
};

struct SemType {
    TypeKind kind;
    std::vector<ArrayBound> bounds;
    std::shared_ptr<SemType> element_type;
};

bool is_numeric(const SemType &type);
bool is_scalar(const SemType &type);
bool same_type(const SemType &a, const SemType &b);
bool assignment_compatible(const SemType &lhs, const SemType &rhs);
std::string type_to_string(const SemType &type);

enum class SymbolKind {
    Const,
    Var,
    Param,
    Procedure,
    Function
};

struct ParamInfo {
    std::string name;
    SemType type;
    bool by_ref;
    std::string c_name;
};

struct Symbol {
    std::string name;
    SymbolKind kind;
    SemType type;
    bool by_ref;
    const AstNode *decl_node;
    std::vector<ParamInfo> params;
    std::string c_name;
};

struct Scope {
    Scope *parent;
    std::unordered_map<std::string, Symbol *> symbols;
    const AstNode *owner;
    int depth;
};

struct ExprInfo {
    SemType type;
    bool is_lvalue;
    bool is_assignable;
    const Symbol *symbol;
};

struct SemanticError {
    AstLocation loc;
    std::string message;
};

struct SemanticResult {
    bool ok;
    std::vector<SemanticError> errors;
    std::unordered_map<const AstNode *, ExprInfo> expr_info;
    std::unordered_map<const AstNode *, const Symbol *> resolved_symbols;
    std::unordered_set<const AstNode *> function_result_refs;
    std::vector<std::unique_ptr<Scope> > scope_storage;
    std::vector<std::unique_ptr<Symbol> > symbol_storage;
    const Scope *global_scope;

    SemanticResult() : ok(false), global_scope(NULL) {}
};

class SemanticAnalyzer {
public:
    SemanticResult analyze(const AstNode *root);
};

void print_semantic_errors(FILE *out, const std::vector<SemanticError> &errors);
void dump_symbols(FILE *out, const SemanticResult &result);
