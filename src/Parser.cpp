#include <queue>
#include <iostream>
#include <ostream>
#include <stack>
#include <utility>

#include "parsenodes.hpp"
#include "tokens.hpp"
#include "Executer.cpp"

class Parser {
    public:
    Parser() = default;

    void parseStmt() {
        if (peek().has_value() && peek().value().type == TokenType::EXIT) {
            consume();
            try_consume_err(TokenType::PAREN_OPEN);
            if (const auto expLit = parseExpr()) {
                try_consume_err(TokenType::PAREN_CLOSE);
                try_consume_err(TokenType::SEMICOLON);
                //interpret the instruction
                executer.exit_(NodeStmtExit(expLit.value()));
            }
        }
    }

    std::optional<NodeExpr> parseExpr() {
        return NodeExpr(parseIntLit().value());
    }

    std::optional<NodeIntLit> parseIntLit() {
        std::optional<Token> token = try_consume_err(TokenType::INT_LIT);
        if (!token.has_value()) {
            return {};
        }
        return NodeIntLit{ token.value() };
    }

    void setTokens(std::queue<Token> tokens) {
        this->tokens = std::move(tokens);
    }

    private:
    void error_expected(const std::string& msg)
    {
        std::cerr << "[Parse Error] Expected " << msg << " on line " << peek(-1).value().line << std::endl;
        exit(EXIT_FAILURE);
    }

    [[nodiscard]] std::optional<Token> peek(const int offset = 0)
    {
        if (offset >= tokens.size()) {
            return {};
        }
        if (offset == 0) {
            return tokens.front();
        }
        std::stack<Token> aux;
        for (int i = 0; i < offset; i++) {
            aux.push(tokens.front());
            tokens.pop();
        }
        Token token = tokens.front();
        for (int i = 0; i < offset; i++) {
            tokens.push(aux.top());
            aux.pop();
        }
        return token;
    }

    Token consume()
    {
        Token token = tokens.front();
        tokens.pop();
        return token;
    }

    Token try_consume_err(const TokenType type)
    {
        if (peek().has_value() && peek().value().type == type) {
            return consume();
        }
        error_expected(toString(type));
        return {};
    }

    std::optional<Token> try_consume(const TokenType type)
    {
        if (peek().has_value() && peek().value().type == type) {
            return consume();
        }
        return {};
    }

    std::queue<Token> tokens;
    Executer executer;
};