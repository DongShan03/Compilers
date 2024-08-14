#pragma once
#include "Logical.h"
#include "Array.h"
class Rel : public Logical
{
    public:
        Rel(Token tok, Expr x1, Expr x2) : Logical(tok, x1, x2) {}
        Type* check(Type p1, Type p2) {
            if ( static_cast<Array*>(&p1) || static_cast<Array*>(&p2) ) return NULL;
            else if (p1 == p2) return &TypeConst::Bool;
            else return NULL;
        }
        void jumping(int t, int f) {
            Expr a = expr1.reduce();
            Expr b = expr2.reduce();
            std::string test = a.toString() + " " + op.toString() + " " + b.toString();
            emitjumps(test, t, f);
        }
};
