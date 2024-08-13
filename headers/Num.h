#pragma once
#include "Token.h"
#include "Tag.h"

class Num : public Token
{
    public:
        int value;
        Num(int v) : Token(Tag::NUM), value(v) {}
        std::string toString() {return "" + std::to_string(value);}
};
