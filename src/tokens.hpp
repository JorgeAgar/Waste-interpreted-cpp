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
    INT_LIT
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
    }
    assert(false);
}

struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
};

#endif //TOKENS_HPP
