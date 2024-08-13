#include "headers/Lexer.h"

int main()
{
    Lexer lex = Lexer();
    Token tok = lex.scan();
    std::cout << tok.tag << std::endl;
}
