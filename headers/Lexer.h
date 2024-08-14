#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Word.h"
#include "Type.h"
#include "Num.h"
#include "Real.h"
#include "Character.h"
class Lexer
{
    public:
        static int line;
        char peek = ' ';
        std::unordered_map<std::string, Word> words;
        void reserve(Word w) {words.insert({w.lexeme, w});}
        Lexer()
        {
            reserve( Word("if", Tag::IF) );
            reserve( Word("else", Tag::ELSE) );
            reserve( Word("while", Tag::WHILE) );
            reserve( Word("do", Tag::DO) );
            reserve( Word("break", Tag::BREAK) );
            reserve( WordConst::True );
            reserve( WordConst::False );
            reserve( TypeConst::Int );
            reserve( TypeConst::Float );
            reserve( TypeConst::Char );
            reserve( TypeConst::Bool );
        }
        void readch() { peek = std::cin.get(); std::cout << peek << ""; }
        bool readch(char c)
        {
            readch();
            if ( peek != c) return false;
            peek = ' ';
            return true;
        }

        Token scan()
        {
            for ( ; ; readch())
            {
                if (peek == ' ' || peek == '\t') continue;
                else if (peek == '\n') line++;
                else break;
            }
            switch(peek)
            {
                case '&':
                    if (readch('&')) return WordConst::And; else return Token('&');
                case '|':
                    if (readch('|')) return WordConst::Or; else return Token('|');
                case '=':
                    if (readch('=')) return WordConst::eq; else return Token('=');
                case '!':
                    if (readch('=')) return WordConst::ne; else return Token('!');
                case '<':
                    if (readch('=')) return WordConst::le; else return Token('<');
                case '>':
                    if (readch('=')) return WordConst::ge; else return Token('>');
            }
            if (Character::isDigit(peek))
            {
                int v = 0;
                do {
                    v = 10 * v + Character::digit(peek, 10); readch();
                } while(Character::isDigit(peek));
                if (peek != '.')
                    return Num(v);
                float x = v; float d = 10;
                for(;;)
                {
                    readch();
                    if (!Character::isDigit(peek)) break;
                    x = x + Character::digit(peek, 10) / d; d *= 10;
                }
                return Real(x);
            }
            if (Character::isLetter(peek))
            {
                std::string buf;
                do {
                    buf += peek; readch();
                } while (Character::isLetterOrDigit(peek));
                Word* w;
                try {
                    w = &(words.at(buf));
                }
                catch (...){
                    w = nullptr;
                }
                if (w !=nullptr) return *w;
                w = new Word(buf, Tag::ID);
                words.insert({buf, *w});
                return *w;
            }

            Token tok = Token(peek); peek = ' ';
            return tok;
        }
};

int Lexer::line = 1;
