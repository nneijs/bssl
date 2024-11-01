// tokenizer.h
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

enum class TokenType {
    NUMBER,
    STRING,
    IDENTIFIER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LEFT_PAREN,
    RIGHT_PAREN,
    PRINT,
    ASSIGN,
    END
};

struct Token {
    TokenType type;
    int value;           // For numeric tokens
    std::string strValue; // For string literals

    Token(TokenType type, int value = 0) : type(type), value(value) {}
    Token(TokenType type, const std::string& str) : type(type), strValue(str) {} // Constructor for string tokens
};

class Tokenizer {
public:
    explicit Tokenizer(const std::string& input);
    Token getNextToken();

private:
    std::string input;
    size_t pos;
    char currentChar;

    void advance();
    void skipWhitespace();
    int integer();
};

#endif
