#pragma once
#include "Stmt.h"
#include "Id.h"
#include "Expr.h"
#include "Rel.h"
class Set : public Stmt
{
    public:
        Id id; Expr expr;
        Set(Id i, Expr x) : id(i), expr(x) {
            if ( check(i.type, x.type) == NULL ) error("type error");
        }
        Type* check(Type &p1, Type &p2) {
            if ( TypeOp::numeric(p1) && TypeOp::numeric(p2) ) return &p2;
            else if ( p1 == TypeConst::Bool && p2 == TypeConst::Bool ) return &p2;
            else return NULL;
        }

        void gen(int b, int a) {
            emit( id.toString() + " = " + expr.gen().toString());
        }
};
