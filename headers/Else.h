#pragma once
#include "Stmt.h"
#include "Expr.h"

class Else : public Stmt
{
    public:
        Expr expr; Stmt stmt1, stmt2;
        Else(Expr x, Stmt s1, Stmt s2) : expr(x), stmt1(s1), stmt2(s2) {
            if (x.type != TypeConst::Bool) error("boolean required in if");
        }
        void gen(int b, int a) {
            int label1 = newlabel();
            int label2 = newlabel();
            expr.jumping(0, label2);    //*条件为真的时候控制流穿越到stmt1
            emitlabel(label1);
            stmt1.gen(label1, a); emit("goto L" + std::to_string(a));
            emitlabel(label2);
            stmt2.gen(label2, a);
        }
};
