#include <cstdio>
#include <cstring>

#include "pascal_s_frontend.hpp"

int main(int argc, char **argv) {
    AstNode *root;

    if (argc > 2) {
        std::fprintf(stderr, "usage: %s [source.pas]\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        root = parse_pascal_file(argv[1]);
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

    ast_dump(stdout, root, 0);
    ast_free(root);
    g_ast_root = NULL;
    return 0;
}
