#pragma once

#include "Op.h"
#include "Type.h"

class Arith : public Op
{
    public:
        Expr expr1, expr2;
        Arith(Token tok, Expr e1, Expr e2)
         : Op(tok, *(TypeOp::max(e1.type, e2.type))), expr1(e1), expr2(e2) {
            if ( TypeOp::max(e1.type, e2.type) == NULL ) error("type error");
         }

        Expr gen() {
            return Arith(op, expr1.reduce(), expr2.reduce());
        }

        std::string toString() {
            return expr1.toString() + " " + op.toString() + " " + expr2.toString();
        }

};
