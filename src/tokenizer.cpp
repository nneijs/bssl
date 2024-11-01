// tokenizer.cpp
#include "tokenizer.h"
#include <cctype>
#include <stdexcept>

Tokenizer::Tokenizer(const std::string& input) : input(input), pos(0), currentChar(input[0]) {}

void Tokenizer::advance() {
    pos++;
    if (pos < input.length()) {
        currentChar = input[pos];
    } else {
        currentChar = '\0';
    }
}

void Tokenizer::skipWhitespace() {
    while (currentChar != '\0' && std::isspace(currentChar)) {
        advance();
    }
}

int Tokenizer::integer() {
    int result = 0;
    while (currentChar != '\0' && std::isdigit(currentChar)) {
        result = result * 10 + (currentChar - '0');
        advance();
    }
    return result;
}

Token Tokenizer::getNextToken() {
    while (currentChar != '\0') {
        if (std::isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (std::isdigit(currentChar)) {
            return Token(TokenType::NUMBER, integer());
        }

        if (std::isalpha(currentChar)) {
            std::string word;
            while (currentChar != '\0' && std::isalnum(currentChar)) {
                word += currentChar;
                advance();
            }
            if (word == "print") {
                return Token(TokenType::PRINT);
            }
            return Token(TokenType::IDENTIFIER, 0);
        }

        if (currentChar == '"') {
    advance();
    std::string strValue;
    while (currentChar != '"' && currentChar != '\0') {
        strValue += currentChar;
        advance();
    }
    if (currentChar == '"') advance();
    return Token(TokenType::STRING, strValue);
}


        if (currentChar == '+') { advance(); return Token(TokenType::PLUS); }
        if (currentChar == '-') { advance(); return Token(TokenType::MINUS); }
        if (currentChar == '*') { advance(); return Token(TokenType::MULTIPLY); }
        if (currentChar == '/') { advance(); return Token(TokenType::DIVIDE); }
        if (currentChar == '(') { advance(); return Token(TokenType::LEFT_PAREN); }
        if (currentChar == ')') { advance(); return Token(TokenType::RIGHT_PAREN); }
        if (currentChar == '=') { advance(); return Token(TokenType::ASSIGN); }

        throw std::runtime_error("Unknown character");
    }

    return Token(TokenType::END);
}

