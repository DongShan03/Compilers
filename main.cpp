#include "headers/Parser.h"


void emit(std::string s) { std::cout << "\t" << s << std::endl;}
int main()
{
    std::ifstream file("D:\\p_cproject\\Compilers\\test.txt");
    if (!file) {
        std::cerr << "Unable to open file" << std::endl;
        return 0;
    }
    std::streambuf* cin_backup = std::cin.rdbuf(file.rdbuf());
    Lexer lex = Lexer();
    Parser parse = Parser(lex);
    parse.program();
    file.close();
    std::cout << std::endl;
    return 1;
}
