#pragma once
#include "Lexer.h"

class Node
{
    public:
        int lexline = 0;
        Node() {lexline = Lexer().line;}    //* 也许有问题
        void error(std::string s) { std::cerr << "near line " << lexline << ": " << s; }
        static int labels = 0;
        int newlabel() {return labels++;}
        void emitlabel(int i) { std::cout << "L" << i << ":";}
        void emit(std::string s) { std::cout << "\t" << s << std::endl;}
};
