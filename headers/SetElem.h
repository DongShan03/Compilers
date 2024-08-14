#pragma once
#include "Stmt.h"
#include "Id.h"
#include "Expr.h"
#include "Access.h"
#include "Array.h"
class SetElem : public Stmt
{
    public:
        Id array; Expr index; Expr expr;
        SetElem(Access x, Expr y) : array(x.array), index(x.index), expr(y) {
            if (check(x.type, expr.type) == NULL) error("type error");
        }
        Type* check(Type &p1, Type &p2) {
            if ( static_cast<Array*>(&p1) || static_cast<Array*>(&p2)) return NULL;
            else if (p1 == p2) return &p2;
            else if(TypeOp::numeric(p1)&&TypeOp::numeric(p2)) return &p2;
            else return NULL;
        }

        void gen(int b, int a) {
            std::string s1 = index.reduce().toString();
            std::string s2 = expr.reduce().toString();
            emit(array.toString() + " [ " + s1 + " ] = " + s2);
        }
};
