#pragma once
#include "Op.h"
#include "Id.h"

class Access : public Op
{
    public:
        Id array;
        Expr index;
        Access(Id a, Expr i, Type p) : Op(Word("[]", Tag::INDEX), p), array(a), index(i) {}
        Expr gen() { return Access(array, index.reduce(), type); }
        void jumping(int t, int f) { emitjumps(reduce().toString(), t, f); }
        std::string toString() { return array.toString() + "[" + index.toString() + "]"; }
};
