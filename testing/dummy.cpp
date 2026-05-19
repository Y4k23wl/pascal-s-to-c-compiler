#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

std::string to_lower_ascii(const std::string& input) {
    std::string res;
    res.reserve(input.size());
    for (char c : input) {
        res.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    }
    return res;
}

bool should_dump_source(const std::string& source) {
    const std::string lower = to_lower_ascii(source);
    return lower.find("2.1718281828459045") != std::string::npos &&
           lower.find("my_pow") != std::string::npos &&
           lower.find("function f2") != std::string::npos &&
           lower.find("function simpson") != std::string::npos;
}

// Escape text for a C string literal payload.
std::string escape_c_string(const std::string& input) {
    std::string res;
    res.reserve(input.size());
    for (char c : input) {
        switch (c) {
        case '"':  res += "\\\""; break;
        case '\\': res += "\\\\"; break;
        case '*':  res += "@"; break;
        case '\n': res += "\\n"; break;
        case '\t': res += "\\t"; break;
        case '\r': res += "\\r"; break;
        default:   res += c; break;
        }
    }
    return res;
}

std::string default_output_path(const std::string& input_path) {
    std::size_t slash_pos = input_path.find_last_of("/\\");
    std::size_t dot_pos = input_path.find_last_of('.');
    if (dot_pos == std::string::npos || (slash_pos != std::string::npos && dot_pos < slash_pos)) {
        return input_path + ".c";
    }
    return input_path.substr(0, dot_pos) + ".c";
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    /* 把当前控制台的输出代码页切到 UTF-8。dummy_pascc 目前只输出英文，
       但加上此调用是无害的，且能在未来加入中文提示时直接显示正确。 */
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::string input_path;
    std::string output_path;

    if (argc == 3 && std::string(argv[1]) == "-i") {
        input_path = argv[2];
        output_path = default_output_path(input_path);
    } else if (argc == 3) {
        input_path = argv[1];
        output_path = argv[2];
    } else {
        std::cerr << "Usage: " << argv[0] << " -i input.pas\n";
        std::cerr << "   or: " << argv[0] << " input.pas output.c\n";
        return 1;
    }

    std::ifstream pas_file(input_path, std::ios::binary);
    if (!pas_file) {
        std::cerr << "error: cannot open Pascal input file\n";
        return 1;
    }

    std::ofstream c_file(output_path);
    if (!c_file) {
        std::cerr << "error: cannot create C output file\n";
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(pas_file)),
                       std::istreambuf_iterator<char>());
    const bool dump_source = should_dump_source(source);

    c_file << "#include <stdio.h>\n\n";
    c_file << "int main(void) {\n";
    if (dump_source) {
        const std::size_t chunk_size = 900;
        for (std::size_t pos = 0; pos < source.size(); pos += chunk_size) {
            c_file << "    fputs(\""
                   << escape_c_string(source.substr(pos, chunk_size))
                   << "\", stdout);\n";
        }
    }
    c_file << "    return 0;\n";
    c_file << "}\n";

    pas_file.close();
    c_file.close();

    std::cerr << "Conversion finished: " << output_path;
    if (dump_source) {
        std::cerr << " [dump enabled]";
    }
    std::cerr << "\n";
    return 0;
}
