// parser.h
#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

// Base class for AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual int evaluate() = 0;
};

class VarNode : public ASTNode {
public:
    std::string name;
    explicit VarNode(const std::string& name) : name(name) {}
    int evaluate() override;
};

class AssignNode : public ASTNode {
public:
    std::string name;
    std::unique_ptr<ASTNode> value;
    AssignNode(const std::string& name, std::unique_ptr<ASTNode> value) 
        : name(name), value(std::move(value)) {}
    int evaluate() override;
};

class NumberNode : public ASTNode {
public:
    int value;
    explicit NumberNode(int value) : value(value) {}
    int evaluate() override { return value; }
};

class PrintNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> expression;

    explicit PrintNode(std::unique_ptr<ASTNode> expr) : expression(std::move(expr)) {}

    int evaluate() override {
        if (auto stringNode = dynamic_cast<StringNode*>(expression.get())) {
            std::cout << stringNode->value << std::endl;  // Print string
        } else {
            int result = expression->evaluate();
            std::cout << result << std::endl;  // Print evaluated expression
        }
        return 0;
    }
};

class StringNode : public ASTNode {
public:
    std::string value;

    explicit StringNode(const std::string& value) : value(value) {}

    int evaluate() override {
        std::cout << value << std::endl;
        return 0;
    }
};

class BinOpNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    TokenType op;

    BinOpNode(std::unique_ptr<ASTNode> left, TokenType op, std::unique_ptr<ASTNode> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    int evaluate() override;
};

class Parser {
public:
    explicit Parser(Tokenizer& tokenizer);
    std::unique_ptr<ASTNode> parse();

private:
    Tokenizer& tokenizer;
    Token currentToken;

    void eat(TokenType type);
    std::unique_ptr<ASTNode> expression();
    std::unique_ptr<ASTNode> term();
    std::unique_ptr<ASTNode> factor();
};

#endif
