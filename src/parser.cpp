#include <unordered_map>
#include <string>
#include "tokenizer.cpp"
#include "parser.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(Tokenizer& tokenizer) : tokenizer(tokenizer), currentToken(tokenizer.getNextToken()) {}

void Parser::eat(TokenType type) {
    if (currentToken.type == type) {
        currentToken = tokenizer.getNextToken();
    } else {
        throw std::runtime_error("Unexpected token");
    }
}

std::unique_ptr<ASTNode> Parser::factor() {
    Token token = currentToken;
    if (token.type == TokenType::NUMBER) {
        eat(TokenType::NUMBER);
        return std::make_unique<NumberNode>(token.value);
    } else if (token.type == TokenType::LEFT_PAREN) {
        eat(TokenType::LEFT_PAREN);
        auto node = expression();
        eat(TokenType::RIGHT_PAREN);
        return node;
    }
    throw std::runtime_error("Invalid factor");
}

std::unique_ptr<ASTNode> Parser::term() {
    auto node = factor();
    while (currentToken.type == TokenType::MULTIPLY || currentToken.type == TokenType::DIVIDE) {
        Token token = currentToken;
        if (token.type == TokenType::MULTIPLY) {
            eat(TokenType::MULTIPLY);
        } else {
            eat(TokenType::DIVIDE);
        }
        node = std::make_unique<BinOpNode>(std::move(node), token.type, factor());
    }
    return node;
}

std::unique_ptr<ASTNode> Parser::expression() {
    auto node = term();
    while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
        Token token = currentToken;
        if (token.type == TokenType::PLUS) {
            eat(TokenType::PLUS);
        } else {
            eat(TokenType::MINUS);
        }
        node = std::make_unique<BinOpNode>(std::move(node), token.type, term());
    }
    return node;
}

std::unique_ptr<ASTNode> Parser::parse() {
    if (currentToken.type == TokenType::PRINT) {
        eat(TokenType::PRINT);
        auto expr = expression();
        return std::make_unique<PrintNode>(std::move(expr));
    } else if (currentToken.type == TokenType::IDENTIFIER) {
        std::string varName = currentToken.strValue;
        eat(TokenType::IDENTIFIER);

        if (currentToken.type == TokenType::ASSIGN) {
            eat(TokenType::ASSIGN);
            auto value = expression();
            return std::make_unique<AssignNode>(varName, std::move(value));
        } else {
            throw std::runtime_error("Expected '=' after variable name");
        }
    } else {
        return expression();
    }
}
