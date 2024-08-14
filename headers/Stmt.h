#pragma once
#include "Node.h"

class Stmt : public Node
{
    public:
        Stmt() {};
        void gen(int b, int a) {}   //*调用的参数是语句开始处的标号和语句的下一条指令的标号
        int after = 0;              //* 保存语句的下一条指令的标号
};

namespace StmtConst {
    static Stmt Null = Stmt();
    static Stmt Enclosing = Null;
}
