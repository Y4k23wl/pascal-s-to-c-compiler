#include <iostream>
#include <fstream>
#include <string>

// Escape text for a C string literal payload.
std::string escape_c_string(const std::string& input) {
    std::string res;
    for (char c : input) {
        switch (c) {
        case '"':  res += "\\\""; break;
        case '\\': res += "\\\\"; break;
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

    std::ifstream pas_file(input_path);
    if (!pas_file) {
        std::cerr << "error: cannot open Pascal input file\n";
        return 1;
    }

    std::ofstream c_file(output_path);
    if (!c_file) {
        std::cerr << "error: cannot create C output file\n";
        return 1;
    }

    c_file << "#include <stdio.h>\n\n";
    c_file << "int main(void) {\n";

    std::string line;
    while (std::getline(pas_file, line)) {
        c_file << "    fputs(\"" << escape_c_string(line) << "\\n\", stdout);\n";
    }

    c_file << "    return 0;\n";
    c_file << "}\n";

    pas_file.close();
    c_file.close();

    std::cout << "Conversion finished: " << output_path << "\n";
    return 0;
}
