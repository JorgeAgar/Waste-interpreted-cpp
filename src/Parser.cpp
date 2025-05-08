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
            else {
                std::cerr << "Error parsing expression" << std::endl;
            }
        }
        else if (peek().has_value() && peek().value().type == TokenType::PRIM_TYPE) {
            if (const auto declaration = parseDecl()) {
                //interpret the instruction
                executer.declare(declaration.value());
            }
            else {
                std::cerr << "Error parsing declaration" << std::endl;
            }
        }
        else if (peek().has_value() && peek().value().type == TokenType::IDENT) {
            if (const auto assignment = parseAssig()) {
                //interpret the instruction
                executer.assign(assignment.value());
            }
            else {
                std::cerr << "Error parsing assignment" << std::endl;
            }
        }
    }

    std::optional<NodeExpr> parseExpr() {
        if (const auto binExpr = parseBinExpr()) {
            return NodeExpr(binExpr.value());
        }
        if (const auto term = parseTerm()) {
            return NodeExpr(term.value());
        }
        return std::nullopt;
    }

    //TODO: finish
    /*
    número de una a la salida
    si hay un operador de igual o mayor precedencia en el tope de la pila, a la salida
    si es de menor precedencia a la salida
    si hay paréntesis igual, pero los operadores tienen mayor precedencia que el resto
    al final se vacía la pila a la salida (en orden obvio)
    -------------------------------------------------------------------------------------------------------------------
    numero a pila de números
    si hay un operador de igual o mayor precedencia en el tope de la pila -> pilaNum(tope-1) *operador* pilaNum(tope)
        y se mete el resultado a la pila de números (y se borra el operador de la pila de operadores)
    si hay paréntesis igual pero los operadores tienen mayor precedencia que el resto
    al final se vacian las pilas en orden
    -----------------------------------------------------------------------------------------------------------------
    tener en cuenta variables y eso
     */
    std::optional<NodeBinExpr> parseBinExpr() {
        NodeBinExpr left;
        NodeBinExpr right;

        std::stack<Token> numbers;
        std::stack<Token> operators;

        while (peek().has_value()) {
            if (peek().value().type == TokenType::INT_LIT || peek().value().type == TokenType::IDENT) {
                numbers.push(consume());
            }
            else if (isOperator(peek().value().type)) {
                if (operators.empty()) {
                    operators.push(consume());
                }
                else if (opPrec(peek().value().type) < opPrec(operators.top().type)) {
                    switch (peek().value().type) {
                        case TokenType::PLUS:
                            operators.pop();
                            std::optional<NodeTerm> rhs;
                            std::optional<NodeTerm> lhs;
                            if (rhs = parseTerm(numbers.top())) {
                                numbers.pop();
                                if (lhs = parseTerm(numbers.top())) {
                                    numbers.pop();
                                    //aca es cuando se hace una operacion y se vuelve a meter a la pila de numeros
                                }

                            }
                    }
                }
            }
            else {
                break;
            }
        }
    }

    std::optional<NodeTerm> parseTerm() {
        if (const auto int_lit = try_consume(TokenType::INT_LIT)) {
            NodeTermIntLit term(int_lit.value());
            return NodeTerm(term);
        }
        if (const auto ident = try_consume(TokenType::IDENT)) {
            NodeIdent term(ident.value());
            return NodeTerm(term);
        }
        return std::nullopt;
    }

    std::optional<NodeTerm> parseTerm(const Token& term_token) {
        if (term_token.type == TokenType::INT_LIT) {
            NodeTermIntLit term(term_token);
            return NodeTerm(term);
        }
        if (term_token.type == TokenType::IDENT) {
            NodeIdent term(term_token);
            return NodeTerm(term);
        }
        return std::nullopt;
    }

    std::optional<NodeDecl> parseDecl() {
        Type type = fromString(try_consume_err(TokenType::PRIM_TYPE).value.value());
        Token ident = try_consume_err(TokenType::IDENT);
        if (auto expr = parseExpr()) {
            try_consume_err(TokenType::SEMICOLON);
            NodeIdent ndIdent = NodeIdent(ident);
            return NodeDecl{ndIdent, type, &expr.value()};
        }
        return std::nullopt;
    }

    std::optional<NodeAssig> parseAssig() {
        Token ident =  try_consume_err(TokenType::IDENT);
        if (auto expr = parseExpr()) {
            try_consume_err(TokenType::SEMICOLON);
            NodeIdent ndIdent = NodeIdent(ident);
            return NodeAssig{ndIdent, &expr.value()};
        }
        return std::nullopt;
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
            return std::nullopt;
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
        return std::nullopt;
    }

    std::queue<Token> tokens;
    Executer executer;
};