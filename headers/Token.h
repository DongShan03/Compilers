#pragma once

#include <string>
class Token
{
    public:
        int tag;
        Token(int t = 0) : tag(t) {}
        std::string toString() {return std::string(1, (char)tag);;}
        bool operator==(const Token &p) const { return (tag == p.tag); }
};

namespace std {
    template <>
    struct hash<Token> {
        std::size_t operator()(const Token& token) const noexcept {
            return std::hash<int>()(token.tag);
        }
    };
}
