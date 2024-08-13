#pragma once
#include "Token.h"
#include "Tag.h"

class Word : public Token
{
    public:
        std::string lexeme = "";
        Word(std::string s, int tag) : lexeme(s), Token(tag) {}

        std::string toString() {return lexeme;}
};

namespace WordConst
{
    static Word And("&&", Tag::AND);
    static Word Or("||", Tag::OR);
    static Word eq("==", Tag::EQ);
    static Word ne("!=", Tag::NE);
    static Word le("<=", Tag::LE);
    static Word ge(">=", Tag::GE);
    static Word minus("minus", Tag::MINUS);
    static Word True("true", Tag::TRUE);
    static Word False("false", Tag::FALSE);
    static Word temp("t", Tag::TEMP);
} // namespace WordConst
