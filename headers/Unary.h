#pragma once

#include "Op.h"
#include "Type.h"
class Unary : public Op
{
    public:
        Expr expr;
        Unary(Token tok, Expr x) : Op(tok, *(TypeOp::max(TypeConst::Int, expr.type))), expr(x)
        {
            if ( TypeOp::max(TypeConst::Int, expr.type) == NULL ) error("type error");
        }
        Expr gen()
        {
            return Unary(op, expr.reduce());
        }
        std::string toString()
        {
            return op.toString() + " " + expr.toString();
        }
};
