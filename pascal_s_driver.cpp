#include <cstdio>
#include <cstring>
#include <string>

#include "codegen/codegen.hpp"
#include "frontend/pascal_s_frontend.hpp"
#include "semantic/semantic.hpp"

namespace {

void print_usage(const char *argv0) {
    std::fprintf(stderr,
                 "usage: %s -i source.pas [--dump-ast] [--dump-symbols] "
                 "[--stop-after=parse|semantic]\n",
                 argv0);
}

std::string replace_extension_with_c(const char *input_path) {
    std::string path(input_path);
    std::string::size_type slash_pos = path.find_last_of("/\\");
    std::string::size_type dot_pos = path.find_last_of('.');

    if (dot_pos == std::string::npos ||
        (slash_pos != std::string::npos && dot_pos < slash_pos)) {
        path += ".c";
    } else {
        path.replace(dot_pos, std::string::npos, ".c");
    }
    return path;
}

bool write_text_file(const std::string &path, const std::string &content) {
    FILE *out = std::fopen(path.c_str(), "wb");
    if (out == NULL) {
        std::perror(path.c_str());
        return false;
    }

    const size_t bytes_to_write = content.size();
    const size_t bytes_written = std::fwrite(content.data(), 1, bytes_to_write, out);
    if (std::fclose(out) != 0) {
        std::perror(path.c_str());
        return false;
    }
    if (bytes_written != bytes_to_write) {
        std::fprintf(stderr, "failed to write complete output file: %s\n", path.c_str());
        return false;
    }
    return true;
}

}  // namespace

int main(int argc, char **argv) {
    AstNode *root;
    bool dump_ast = false;
    bool dump_symbols_flag = false;
    enum { STOP_NONE, STOP_PARSE, STOP_SEMANTIC } stop_after = STOP_NONE;
    const char *input_path = NULL;
    std::string output_path;

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--dump-ast") == 0) {
            dump_ast = true;
            continue;
        }
        if (std::strcmp(argv[i], "--dump-symbols") == 0) {
            dump_symbols_flag = true;
            continue;
        }
        if (std::strcmp(argv[i], "--stop-after=parse") == 0) {
            stop_after = STOP_PARSE;
            continue;
        }
        if (std::strcmp(argv[i], "--stop-after=semantic") == 0) {
            stop_after = STOP_SEMANTIC;
            continue;
        }
        if (std::strcmp(argv[i], "-i") == 0) {
            if (i + 1 >= argc || input_path != NULL) {
                print_usage(argv[0]);
                return 1;
            }
            input_path = argv[++i];
            continue;
        }

        print_usage(argv[0]);
        return 1;
    }

    if (input_path == NULL) {
        print_usage(argv[0]);
        return 1;
    }

    output_path = replace_extension_with_c(input_path);
    root = parse_pascal_file(input_path);

    if (pascal_s_had_lexical_error()) {
        std::fprintf(stderr,
                     "编译终止：词法阶段共发现 %d 个错误\n",
                     pascal_s_lexical_error_count());
        if (pascal_s_had_syntax_error()) {
            std::fprintf(stderr,
                         "编译终止：语法阶段共发现 %d 个错误\n",
                         pascal_s_syntax_error_count());
        }
        if (root != NULL) {
            ast_free(root);
            g_ast_root = NULL;
        }
        return 1;
    }

    if (root == NULL) {
        if (pascal_s_had_syntax_error()) {
            std::fprintf(stderr,
                         "编译终止：语法阶段共发现 %d 个错误\n",
                         pascal_s_syntax_error_count());
        }
        return 1;
    }

    if (!ast_validate(stderr, root)) {
        ast_free(root);
        g_ast_root = NULL;
        return 1;
    }

    if (dump_ast) {
        ast_dump(stderr, root, 0);
    }

    if (stop_after == STOP_PARSE) {
        ast_free(root);
        g_ast_root = NULL;
        return 0;
    }

    SemanticAnalyzer analyzer;
    SemanticResult sem = analyzer.analyze(root);
    if (!sem.ok) {
        print_semantic_errors(stderr, sem.errors);
        std::fprintf(stderr,
                     "编译终止：语义阶段共发现 %zu 个错误\n",
                     sem.errors.size());
        ast_free(root);
        g_ast_root = NULL;
        return 1;
    }

    if (dump_symbols_flag) {
        dump_symbols(stderr, sem);
    }

    if (stop_after == STOP_SEMANTIC) {
        ast_free(root);
        g_ast_root = NULL;
        return 0;
    }

    CodeGenerator generator;
    std::string c_code = generator.generate(root, sem);
    if (!write_text_file(output_path, c_code)) {
        ast_free(root);
        g_ast_root = NULL;
        return 1;
    }

    ast_free(root);
    g_ast_root = NULL;
    return 0;
}
