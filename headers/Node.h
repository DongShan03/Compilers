#pragma once
#include "Lexer.h"

class Node
{
    public:
        int lexline = 0;
        Node() {lexline = Lexer::line;}    //* 也许有问题
        void error(std::string s) { std::cerr << "near line " << lexline << ": " << s; }
        static int labels;
        int newlabel() {return labels++;}
        void emitlabel(int i) { std::cout << "L" << std::to_string(i) << ":";}
        void emit(std::string s) { std::cout << "\t" << s << std::endl;}
};

int Node::labels = 0;
