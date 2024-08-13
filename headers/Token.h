#pragma once

#include <string>
class Token
{
    public:
        int tag;
        Token(int t) : tag(t) {}
        std::string toString() {return "" + (char)tag;}
};
