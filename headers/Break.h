#pragma once
#include "Stmt.h"

class Break : public Stmt
{
    public:
        Stmt stmt;
        Break() {
            if ( &(StmtConst::Enclosing) == &(StmtConst::Null) ) error("unenclosed break");
            stmt = StmtConst::Enclosing;
        }
        void gen(int b, int a) {
            emit("goto L" + std::to_string(stmt.after));
        }
};
