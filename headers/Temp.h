#pragma once
#include "Expr.h"

class Temp : public Expr
{
    public:
        static int count;
        int number = 0;
        Temp(Type p) : Expr(WordConst::temp, p), number(count++) {}

};

int Temp::count = 0;
