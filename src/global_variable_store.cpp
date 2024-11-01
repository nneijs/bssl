// global_variable_store.cpp

#include "parser.h"
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>

// Define the global map to store variables
std::unordered_map<std::string, int> variables;  // Ensure this has a semicolon at the end

int VarNode::evaluate() {
    if (variables.find(name) != variables.end()) {
        return variables[name];
    }
    throw std::runtime_error("Undefined variable: " + name);
}

int AssignNode::evaluate() {
    int val = value->evaluate();
    variables[name] = val;
    return val;
}
