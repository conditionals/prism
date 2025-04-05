#pragma once

#include <string>
#include <vector>

enum class TokenType {
    INT_TYPE,    // "int"
    FLOAT_TYPE,  // "float"
    STRING_TYPE, // "string"
    IDENTIFIER,  // variable names
    NUMBER,      // numeric values
    STRING,      // string literals
    EQUALS,      // "="
    PLUS,        // "+"
    PRINT,       // "print"
    SEMICOLON    // ";"
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string&);
