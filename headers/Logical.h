#pragma once
#include "Expr.h"
#include "Type.h"
#include "Temp.h"

//* 逻辑运算符 Or And Not
class Logical : public Expr
{
    public:
        Expr expr1, expr2;
        Logical(Token tok, Expr x1, Expr x2)
        : Expr(tok, *check(expr1.type, expr2.type)), expr1(x1), expr2(x2) {
            if (check(expr1.type, expr2.type) == NULL) error("type error");
        }
        Type* check(Type p1, Type p2) {
            if(p1 == TypeConst::Bool && p2 == TypeConst::Bool) return &TypeConst::Bool;
            else return NULL;
        }

        Expr gen() {
            int f = newlabel(); int a = newlabel();
            Temp temp = Temp(type);
            this->jumping(0, f);
            emit(temp.toString() + " = true");
            emit("goto L" + std::to_string(a));
            emitlabel(f); emit(temp.toString() + " = false");
            emitlabel(a); return temp;
        }
};
