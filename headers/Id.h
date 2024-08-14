#pragma once
#include "Expr.h"
class Id : public Expr
{
    public:
        int offset;
        Id(Word id, Type p, int b) : Expr(id, p), offset(b) {}
        Id() = default;
};
