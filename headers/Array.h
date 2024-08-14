#pragma once
#include "Type.h"
class Array : public Type
{
    public:
        Type of;
        int size = 1;
        Array(int sz, Type p) : Type("[]", Tag::INDEX, sz*p.width), size(sz), of(p) {}
        std::string toString() { return "[" + std::to_string(size) + "]" + of.toString();}
};
