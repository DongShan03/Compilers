#pragma once
#include <unordered_map>
#include "Token.h"
#include "Id.h"
//* 符号表的定义
class Env
{
    public:
        std::unordered_map<Token, Id>* table;
        Env* pred;
        Env(Env* n) { table = new std::unordered_map<Token, Id>(); pred = n; }
        void put(Token w, Id i) { (*table).insert({w, i}); }
        Id* get(Token w)
        {
            for (Env* e = this; e != nullptr; e = e->pred)
            {
                auto found = e->table->find(w);
                if (found != e->table->end()) return &(found->second);
                else return nullptr;
            }
            return nullptr;
        }
};

Env* envBegin = new Env(0);
