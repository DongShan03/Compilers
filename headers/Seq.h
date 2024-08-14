#pragma once
#include "Stmt.h"

class Seq : public Stmt
{
    public:
        Stmt stmt1, stmt2;
        Seq(Stmt s1, Stmt s2) : stmt1(s1), stmt2(s2) {}
        void gen(int b, int a) {
            if ( &stmt1 == &(StmtConst::Null) ) stmt2.gen(b, a);
            else if ( &stmt2 == &(StmtConst::Null) ) stmt1.gen(b, a);
            else {
                int label = newlabel();
                stmt1.gen(b, label);
                emitlabel(label);
                stmt2.gen(label, a);
            }
        }
};
