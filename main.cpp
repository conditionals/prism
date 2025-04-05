#include "include/tokenizer.hpp"
#include "include/parser.hpp"
#include "include/interpreter.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if(argc < 2) throw std::runtime_error("must provide input file");
    std::ifstream file(argv[1]);
    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string code = buffer.str();
    std::vector<Token> tokens = tokenize(code);

    Parser parser(tokens);
    ASTNode ast = parser.parse();

    Interpreter interpreter;
    Value result = interpreter.interpret(ast);


    
    return 0;
}
