#pragma once
#include "Expr.h"
#include "Num.h"

class Constant : public Expr
{
    public:
        Constant(Token tok, Type p) : Expr(tok, p) {}
        Constant(int i) : Expr(Num(i), TypeConst::Int) {}
        void jumping(int t, int f);
        bool operator==(const Constant &p) const
        {
            return (op == p.op && type == p.type);
        }
};

namespace ConstantConst
{
    static Constant True = Constant(WordConst::True, TypeConst::Bool);
    static Constant False = Constant(WordConst::False, TypeConst::Bool);
}


void Constant::jumping(int t, int f) {
    if ( *this == ConstantConst::True && t != 0 ) emit("goto L" + std::to_string(t));
    else if ( *this == ConstantConst::False && f != 0 ) emit("goto L" + std::to_string(f));
    else error("Constant jumping error");
}
