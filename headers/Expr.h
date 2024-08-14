#pragma once
#include "Word.h"
#include "Node.h"
#include "Token.h"
#include "Type.h"

class Expr : public Node
{
    public:
        Token op;
        Type type;
        Expr(Token tok = Token(), Type p = Type()) : op(tok), type(p) {}
        Expr gen() {return *this;}
        Expr reduce() {return *this;}
        void jumping(int t, int f) { emitjumps(toString(), t, f); }
        std::string toString() { return op.toString(); }
        void emitjumps(std::string test, int t, int f)
        {
            if (t!=0 && f!=0)
            {
                emit("if " + test + " goto L" + std::to_string(t));
                emit("goto L" + std::to_string(f));
            }
            else if (t!=0) emit("if " + test + " goto L" + std::to_string(t));
            else if (f!=0) emit("iffalse " + test + " goto L" + std::to_string(f));
            else ;
        }

};
