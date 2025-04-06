#pragma once

#include "tokenizer.hpp"

enum class NodeType {
    PROGRAM,
    VAR_DECL,
    PRINT,
    EXPRESSION,
    IDENTIFIER,
    NUMBER,
    STRING
};

struct ASTNode {
    NodeType type;
    std::string value;
    std::vector<ASTNode> children;
};

class Parser {
    std::vector<Token> tokens;
    size_t pos;

    public:
	Parser(const std::vector<Token>& t): tokens(t), pos(0) {}
	ASTNode parse();
    private:
	Token currentToken() const;
	void advance();
	ASTNode parseStatement();
	ASTNode parseVarDecl();
	ASTNode parsePrint();
	ASTNode parseExpression();
	ASTNode parseUrnary();
	ASTNode parsePrimary();
};
