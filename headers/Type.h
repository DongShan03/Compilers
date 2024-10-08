#pragma once
#include "Word.h"

class Type : public Word
{
    public:
        int width = 0;
        Type(std::string s = "", int tag = 0, int w = 0) : Word(s, tag), width(w) {}
        bool operator==(const Type &p) const {return (lexeme == p.lexeme)&&(width == p.width)&&(tag == p.tag);}
        bool operator!=(const Type &p) const {return !(*this == p);}
};

namespace TypeConst
{
    static Type Int("int", Tag::BASIC, 4);
    static Type Float("real", Tag::BASIC, 8);
    static Type Bool("bool", Tag::BASIC, 1);
    static Type Char("char", Tag::BASIC, 1);
}

namespace TypeOp
{
    bool numeric(Type p)
    {
        if (p==TypeConst::Char || p==TypeConst::Int || p==TypeConst::Float) return true;
        else return false;
    }

    Type* max(Type p1, Type p2)
    {
        if (!numeric(p1) || !numeric(p2)) return NULL;
        else if (p1 == TypeConst::Float || p2 == TypeConst::Float) return &TypeConst::Float;
        else if (p1 == TypeConst::Int || p2 == TypeConst::Int) return &TypeConst::Int;
        else return &TypeConst::Char;
    }
}
