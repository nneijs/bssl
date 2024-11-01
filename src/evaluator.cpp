// evaluator.cpp
#include "parser.h"

int BinOpNode::evaluate() {
    int leftVal = left->evaluate();
    int rightVal = right->evaluate();

    switch (op) {
        case TokenType::PLUS: return leftVal + rightVal;
        case TokenType::MINUS: return leftVal - rightVal;
        case TokenType::MULTIPLY: return leftVal * rightVal;
        case TokenType::DIVIDE: return leftVal / rightVal;
        default: throw std::runtime_error("Invalid operator");
    }
}
