#include "../include/parser.hpp"

Token Parser::currentToken() const {
    return (pos < tokens.size()) ? tokens[pos] : Token{TokenType::SEMICOLON, ";"};
}

void Parser::advance() {
    pos++;
}

ASTNode Parser::parse() {
    ASTNode root{NodeType::PROGRAM, ""};
    while(pos < tokens.size()){
	ASTNode stmt = parseStatement();
	if(!stmt.value.empty() || !stmt.children.empty()){
	    root.children.push_back(stmt);
	}
    }

    return root;
}

ASTNode Parser::parseStatement() {
    Token t = currentToken();
    switch(t.type){
	case TokenType::INT_TYPE:
        case TokenType::FLOAT_TYPE:
        case TokenType::STRING_TYPE:
	    return parseVarDecl();
	case TokenType::PRINT:
	    return parsePrint();
	default:
	    advance();
	    return {NodeType::PROGRAM, ""};
        }
}

ASTNode Parser::parseVarDecl() {
    Token typeToken = currentToken();
    advance(); // skip type
    Token idToken = currentToken();
    if(idToken.type != TokenType::IDENTIFIER) return {NodeType::VAR_DECL, ""};
    advance(); // skip identifier
    if(currentToken().type != TokenType::EQUALS) return {NodeType::VAR_DECL, ""};
    advance(); // skip =
    
    ASTNode expr = parseExpression();
    ASTNode node = {NodeType::VAR_DECL, typeToken.value};
    node.children.push_back({NodeType::IDENTIFIER, idToken.value});
    node.children.push_back(expr);
    advance(); // skip semicolon
    return node; 
}

ASTNode Parser::parsePrint() {
    advance(); // skip print
    ASTNode expr = parseExpression();

    ASTNode node{NodeType::PRINT, ""};
    node.children.push_back(expr);
    advance(); // skip semicolon
    return node;
}

ASTNode Parser::parseExpression() {
    Token t = currentToken();
    ASTNode node{NodeType::EXPRESSION, ""};

    if(t.type == TokenType::IDENTIFIER){
	node.children.push_back({NodeType::IDENTIFIER, t.value});
	advance();
    }
    else if(t.type == TokenType::NUMBER){
	node.children.push_back({NodeType::NUMBER, t.value});
	advance();
    }
    else if(t.type == TokenType::STRING){
	node.children.push_back({NodeType::STRING, t.value});
	advance();
    }

    if(currentToken().type == TokenType::PLUS){
	node.value = "+";
	advance(); // skip +
	node.children.push_back(parseExpression());
    }

    return node;
}
