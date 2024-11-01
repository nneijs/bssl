#include <iostream>
#include <fstream>
#include "parser.h"
#include "tokenizer.h"

void interpretLine(const std::string& line) {
    try {
        Tokenizer tokenizer(line);
        Parser parser(tokenizer);
        std::unique_ptr<ASTNode> root = parser.parse();
        root->evaluate();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string filename = argv[1];
        std::ifstream file(filename);

        if (!file) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(file, line)) {
            interpretLine(line);
        }
        file.close();
    } else {
        std::string input;
        while (true) {
            std::cout << "Enter an expression (or type 'exit' to quit): ";
            std::getline(std::cin, input);

            if (input == "exit") break;

            interpretLine(input);
        }
    }

    return 0;
}
