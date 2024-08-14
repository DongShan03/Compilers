#pragma once
#include "Expr.h"
#include "Stmt.h"

class While : public Stmt
{
    public:
        Expr expr; Stmt stmt;
        While(Expr x = Expr(), Stmt s = Stmt()) : expr(x), stmt(s) {}
        void init(Expr x, Stmt s) {
            expr = x; stmt = s;
            if( x.type != TypeConst::Bool ) error("boolean required in while");
        }
        void gen(int b, int a) {
            after = a; //保留标号
            expr.jumping(0, a);
            int label = newlabel();
            emitlabel(label);
            stmt.gen(label, b);
            emit("goto L" + std::to_string(b));
        }
};
