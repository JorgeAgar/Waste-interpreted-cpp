#ifndef TOKENS_HPP
#define TOKENS_HPP
#include <cassert>
#include <optional>
#include <string>

enum class TokenType {
    EXIT,
    PAREN_OPEN,
    PAREN_CLOSE,
    SEMICOLON,
    INT_LIT,
    IDENT,
    PLUS,
    MINUS,
    ASTERISK,
    FSLASH,
    MOD,
    PRIM_TYPE,
    EQUALS
};

inline std::string toString(const TokenType type) {
    switch (type) {
        case TokenType::EXIT:
            return "EXIT";
        case TokenType::PAREN_OPEN:
            return "PAREN_OPEN";
        case TokenType::PAREN_CLOSE:
            return "PAREN_CLOSE";
        case TokenType::SEMICOLON:
            return "SEMICOLON";
        case TokenType::INT_LIT:
            return "INT_LIT";
        case TokenType::IDENT:
            return "IDENT";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::ASTERISK:
            return "ASTERISK";
        case TokenType::FSLASH:
            return "FSLASH";
        case TokenType::MOD:
            return "MOD";
        case TokenType::PRIM_TYPE:
            return "PRIM_TYPE";
        case TokenType::EQUALS:
            return "EQUALS";
    }
    assert(false);
}

struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
};

#endif //TOKENS_HPP
