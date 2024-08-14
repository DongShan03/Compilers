#pragma once
#include "Expr.h"
#include "Stmt.h"

class Do : public Stmt
{
    public:
        Expr expr; Stmt stmt;
        Do(Expr x = Expr(), Stmt s = Stmt()) : expr(x), stmt(s) {}
        void init(Expr x, Stmt s) {
            expr = x; stmt = s;
            if (x.type != TypeConst::Bool) error("boolean required in do");
        }
        void gen(int b, int a) {
            after = a;
            int label = newlabel();
            stmt.gen(b, label);
            emitlabel(label);
            expr.jumping(b, 0);
        }
};
