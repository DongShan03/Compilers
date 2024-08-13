#pragma once
#include "Token.h"
#include "Tag.h"
class Real : public Token
{
    public:
        float value;
        Real(float v) : Token(Tag::REAL), value(v) {}
        std::string toString() {return "" + std::to_string(value);}
};
