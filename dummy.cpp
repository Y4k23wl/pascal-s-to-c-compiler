#include <iostream>
#include <fstream>
#include <string>

// ×ªÒå C ×Ö·û´®ÖÐµÄÌØÊâ×Ö·û£¨±£Ö¤Éú³ÉµÄ C ´úÂëºÏ·¨£©
std::string escape_c_string(const std::string& input) {
    std::string res;
    for (char c : input) {
        switch (c) {
        case '"':  res += "\\\""; break;  // Ë«ÒýºÅ×ªÒå
        case '\\': res += "\\\\"; break;  // ·´Ð±¸Ü×ªÒå
        case '\n': res += "\\n\"\""; break; // »»ÐÐ×ªÒå + Æ´½Ó×Ö·û´®
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

    // ´ò¿ª Pascal ÊäÈëÎÄ¼þ
    std::ifstream pas_file(input_path);
    if (!pas_file) {
        std::cerr << "´íÎó£ºÎÞ·¨´ò¿ª Pascal ÎÄ¼þ\n";
        return 1;
    }

    // ´ò¿ª C Êä³öÎÄ¼þ
    std::ofstream c_file(output_path);
    if (!c_file) {
        std::cerr << "´íÎó£ºÎÞ·¨´´½¨ C ÎÄ¼þ\n";
        return 1;
    }

    // Éú³É C ´úÂëÍ·²¿£¨±ê×¼Ö÷º¯Êý + ´òÓ¡£©
    c_file << "#include <stdio.h>\n\n";
    c_file << "int main() {\n";
    c_file << "    // ´Ë³ÌÐòÓÉ Pascal ×ª C Éú³ÉÆ÷×Ô¶¯Éú³É\n";
    c_file << "    // ÔËÐÐºóÊä³öÔ­Ê¼ Pascal ´úÂë\n";
    c_file << "    printf(\"";

    // ÖðÐÐ¶ÁÈ¡ Pascal ´úÂë£¬×ªÒåºóÐ´Èë C µÄ printf ×Ö·û´®
    std::string line;
    while (std::getline(pas_file, line)) {
        c_file << escape_c_string(line) << "\\n\"\"";
    }

    // Éú³É C ´úÂëÎ²²¿
    c_file << "\");\n";
    c_file << "    return 0;\n";
    c_file << "}\n";

    // ¹Ø±ÕÎÄ¼þ
    pas_file.close();
    c_file.close();

    std::cout << "Conversion finished: " << output_path << "\n";
    return 0;
}
