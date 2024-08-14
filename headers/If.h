#pragma once
#include "Stmt.h"
#include "Expr.h"
class If : public Stmt
{
    public:
        Expr expr; Stmt stmt;
        If (Expr x, Stmt s) : expr(x), stmt(s) {
            if ( x.type != TypeConst::Bool ) error("boolean required in if");
        }

        void gen(int b, int a) {
            int label = newlabel();
            expr.jumping(0, a);
            emitlabel(label);
            stmt.gen(label, a);
        }
};
