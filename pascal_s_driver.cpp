#include <cstdio>
#include <cstring>

#include "pascal_s_frontend.hpp"
#include "semantic.hpp"

int main(int argc, char **argv) {
    AstNode *root;
    bool dump_ast = false;
    const char *input_path = NULL;

    if (argc > 3) {
        std::fprintf(stderr, "usage: %s [--dump-ast] [source.pas]\n", argv[0]);
        return 1;
    }

    if (argc >= 2 && std::strcmp(argv[1], "--dump-ast") == 0) {
        dump_ast = true;
        if (argc == 3) {
            input_path = argv[2];
        }
    } else if (argc == 2) {
        input_path = argv[1];
    } else if (argc == 3) {
        std::fprintf(stderr, "usage: %s [--dump-ast] [source.pas]\n", argv[0]);
        return 1;
    }

    if (input_path != NULL) {
        root = parse_pascal_file(input_path);
    } else {
        root = parse_pascal_stream(stdin);
    }

    if (root == NULL) {
        return 1;
    }

    if (!ast_validate(stderr, root)) {
        ast_free(root);
        g_ast_root = NULL;
        return 1;
    }

    SemanticAnalyzer analyzer;
    SemanticResult sem = analyzer.analyze(root);
    if (!sem.ok) {
        print_semantic_errors(stderr, sem.errors);
        ast_free(root);
        g_ast_root = NULL;
        return 1;
    }

    if (dump_ast) {
        ast_dump(stdout, root, 0);
    }
    std::fprintf(stdout, "semantic analysis: ok\n");
    ast_free(root);
    g_ast_root = NULL;
    return 0;
}
