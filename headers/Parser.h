#pragma once
#include "Lexer.h"
#include "Env.h"
#include "Access.h"
#include "Expr.h"
#include "Token.h"
#include "Stmt.h"
#include "If.h"
#include "Else.h"
#include "Break.h"
#include "Or.h"
#include "And.h"
#include "While.h"
#include "Set.h"
#include "Rel.h"
#include "Do.h"
#include "Not.h"
#include "Unary.h"
#include "Array.h"
#include "Seq.h"
#include "Constant.h"
#include "Arith.h"
#include "SetElem.h"
class Parser
{
    private:
        Lexer lex;
        Token look;

    public:
        Env* envBegin = new Env(0);
        Env* top = new Env(envBegin);
        int used = 0;
        Parser(Lexer l) : lex(l) { move(); }
        void move() { look = lex.scan(); }
        void error(std::string s) { std::cerr << "near line " << lex.line << ": " << s; }
        void match(int t) {
            if ( look.tag == t ) move();
            else error("syntax error");
        }
        void program() {
            //
            Stmt s = block();
            int begin = s.newlabel(); int after = s.newlabel();
            s.emitlabel(begin); s.gen(begin, after);
            s.emitlabel(after);
        }

        Stmt block() {
            match('{'); Env savedEnv = *top; top = new Env(*top);
            decls(); Stmt s = stmts();
            match('}'); top = &savedEnv;
            return s;
        }

        void decls() {
            while ( look.tag == Tag::BASIC) {
                Type p = type(); Token tok = look; match(Tag::ID); match(';');
                Id id = Id(*(static_cast<Word*>(&tok)), p, used);
            }
        }

        Type type() {
            Type p = *(static_cast<Type*>(&look));
            match(Tag::BASIC);
            if (look.tag != '[') return p;
            else return dims(p);
        }

        Type dims(Type p) {
            match('['); Token tok = look; match(Tag::NUM); match(']');
            if (look.tag == '[')
                p = dims(p);
            return Array(static_cast<Num*>(&tok)->value, p);
        }

        Stmt stmts() {
            if (look.tag == '}') return StmtConst::Null;
            else return Seq(stmt(), stmts());
        }

        Stmt stmt() {
            Expr x;
            Stmt s, s1, s2;
            Stmt savedStmt;
            While whilenode = While();
            Do donode = Do();
            switch (look.tag) {
                case ';':
                    move();
                    return StmtConst::Null;
                case Tag::IF:
                    match(Tag::IF); match('('); x=Bool(); match(')');
                    s1 = stmt(); if (look.tag!=Tag::ELSE) return If(x, s1);
                    match(Tag::ELSE); s2 = stmt(); return Else(x, s1, s2);
                case Tag::WHILE:
                    // While whilenode = While();
                    savedStmt = StmtConst::Enclosing; StmtConst::Enclosing = whilenode;
                    match(Tag::WHILE); match('('); x = Bool(); match(')');
                    s1 = stmt(); whilenode.init(x, s1);
                    StmtConst::Enclosing = savedStmt;
                    return whilenode;
                case Tag::DO:
                    // Do donode = Do();
                    savedStmt = StmtConst::Enclosing;
                    StmtConst::Enclosing = donode; match(Tag::DO);
                    s1 = stmt(); match(Tag::WHILE); match('('); x = Bool();
                    match(')'); match(';'); donode.init(x, s1); //* 也许有问题
                    StmtConst::Enclosing = savedStmt;
                    return donode;
                case Tag::BREAK:
                    match(Tag::BREAK); match(';');
                    return Break();
                case '{':
                    return block();
                default:
                    return assign();
            }
        }

        Stmt assign() {     //* 赋值语句
            Stmt stmt; Token t = look;
            match(Tag::ID);
            Id* id = top->get(t);
            if (id == NULL) error(t.toString() + " undeclared");
            if (look.tag == '=') {
                move(); stmt = Set(*id, Bool());
            } else {
                Access x = offset(*id);
                match('='); stmt = SetElem(x, Bool());
            }
            match(';');
            return stmt;
        }


        Expr Bool() {
            Expr x = join();
            while (look.tag == Tag::OR) {
                Token tok = look; move();
                x = Or(tok, x, join());
            }
            return x;
        }

        Expr join() {
            Expr x = equality();
            while (look.tag == Tag::AND) {
                Token tok = look; move();
                x = And(tok, x, equality());
            }
            return x;
        }

        Expr equality() {
            Expr x = rel();
            while (look.tag == Tag::EQ || look.tag == Tag::NE) {
                Token tok = look; move();
                x = Rel(tok, x, rel());
            }
            return x;
        }

        Expr rel() {
            Expr x = expr();
            Token tok;
            switch( look.tag ) {
                case '<': case Tag::LE: case Tag::GE: case '>':
                    tok = look;
                    move();
                    return Rel(tok, x, expr());
                default:
                    return x;
            }
        }

        Expr expr() {
            Expr x = term();
            Token tok;
            while (look.tag == '+' || look.tag == '-') {
                 tok = look; move(); x = Arith(tok, x, term());
            }
            return x;
        }

        Expr term() {
            Expr x = unary();
            Token tok;
            while (look.tag == '*' || look.tag == '/') {
                tok = look; move(); x = Arith(tok, x, unary());
            }
            return x;
        }

        Expr unary() {
            if (look.tag == '-') {
                move(); return Unary(WordConst::minus, unary());
            } else if (look.tag == '!') {
                Token tok = look; move();
                return Not(tok, unary());
            } else {
                return factor();
            }
        }

        Expr factor() {
            Expr x; Id* id; std::string s;
            switch (look.tag)
            {
            case '(':
                move(); x = Bool(); match(')');
                return x;
            case Tag::NUM:
                x = Constant(look, TypeConst::Int);
                move();
                return x;
            case Tag::REAL:
                x = Constant(look, TypeConst::Float);
                move();
                return x;
            case Tag::TRUE:
                x = ConstantConst::True, move();
                return x;
            case Tag::FALSE:
                x = ConstantConst::False, move();
                return x;
            case Tag::ID:
                s = look.toString();
                id = top->get(look);
                if (id == NULL) error(look.toString() + " undeclared");
                move();
                if (look.tag != '[') return *id;
                else return offset(*id);
            default:
                error("syntax error");
                return x;
            }
        }

        Access offset(Id a) {
            Expr i, w, t1, t2, loc;
            Type type = a.type;
            match('['); i = Bool(); match(']');
            type = static_cast<Array*>(&type)->of;
            w = Constant(type.width);
            t1 = Arith(Token('*'), i, w);
            loc = t1;
            while(look.tag == '[') {
                match('['); i = Bool(); match(']');
                type = static_cast<Array*>(&type)->of;
                w = Constant(type.width);
                t1 = Arith(Token('*'), i, w);
                t2 = Arith(Token('+'), loc, t1);
                loc = t2;
            }
            return Access(a, loc, type);
        }

};
