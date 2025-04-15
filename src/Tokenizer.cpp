#include <queue>
#include "Tokens.hpp"

class Tokenizer {
    public:
    Tokenizer() = default;

    std::queue<Token> tokenize() {
        std::queue<Token> tokens;
        std::string buffer;

        while (peek().has_value()) {
            if (peek().value() == '\n') {
                m_lineNum++;
                consume();
            }
            else if (std::isalpha(peek().value())) {
                buffer.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buffer.push_back(consume());
                }
                if (buffer == "exit") {
                    tokens.push(Token(TokenType::EXIT, m_lineNum));
                    buffer.clear();
                }
            } else if (std::isdigit(peek().value())) {
                buffer.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buffer.push_back(consume());
                }
                tokens.push(Token(TokenType::INT_LIT, m_lineNum, buffer));
                buffer.clear();
            }
            else if (peek().value() == '(') {
                consume();
                tokens.push(Token(TokenType::PAREN_OPEN, m_lineNum));
            }
            else if (peek().value() == ')') {
                consume();
                tokens.push(Token(TokenType::PAREN_CLOSE, m_lineNum));
            }
            else if (peek().value() == ';') {
                consume();
                tokens.push(Token(TokenType::SEMICOLON, m_lineNum));
            }
        }

        return tokens;
    }

    void setSource(std::string source) {
        m_src = std::move(source);
    }

    private:

    [[nodiscard]] std::optional<char> peek(const int offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index + offset);
    }

    char consume()
    {
        return m_src.at(m_index++);
    }

    std::string m_src;
    int m_lineNum = 0;
    int m_index = 0;
};