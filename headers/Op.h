#pragma once

#include "Expr.h"
#include "Temp.h"

class Op : public Expr
{
    public:
        Op(Token tok, Type p) : Expr(tok, p) {}
        Expr reduce()
        {
            Expr x = gen();
            Temp t = Temp(type);
            emit( t.toString() + " = " + x.toString());
            return t;
        }
};
