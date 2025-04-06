#include "../include/tokenizer.hpp"
#include <cctype>


Token classifyToken(const std::string& str) {
    if (str == "int") return {TokenType::INT_TYPE, str};
    if (str == "float") return {TokenType::FLOAT_TYPE, str};
    if (str == "string") return {TokenType::STRING_TYPE, str};
    if (str == "print") return {TokenType::PRINT, str};
    
    bool isNumber = true;
    bool hasDot = false;
    for (char c : str) {
        if (c == '.' && !hasDot) hasDot = true;
        else if (!std::isdigit(c)) isNumber = false;
    }
    if (isNumber) return {TokenType::NUMBER, str};
    
    return {TokenType::IDENTIFIER, str};
}


std::vector<Token> tokenize(const std::string& line){
    std::vector<Token> tokens;
    std::string current;
    bool inString = false;

    for(size_t i = 0; i < line.length(); i++){
	char c = line[i];

	if(c == '"' && !inString){
	    inString = true;
	    current = "";
	    continue;
	}

	if(c == '"' && inString){
	    inString = false;
	    tokens.push_back({TokenType::STRING, current});
	    current = "";
	    continue;
	}

	else if(inString){
	    current+=c;
	    continue;
	}

	if(std::isspace(c) || c==';' || c=='+' || c=='=' || c=='-'){
	    if(!current.empty()){
		tokens.push_back(classifyToken(current));
		current = "";
	    }
	    
	    TokenType type;
	    if(!std::isspace(c)){
		switch(c){
		    case '=':
			type = TokenType::EQUALS;
			break;
		    case '+':
			type = TokenType::PLUS;
			break;
		    case '-':
			type = TokenType::MINUS;
			break;
		    case ';':
			type = TokenType::SEMICOLON;
			break;
		}
		tokens.push_back({type, std::string(1, c)});
	    }
	}

	else {
	    current += c;
	}
    }

    if(!current.empty() && !inString){
	tokens.push_back(classifyToken(current));
    }

    return tokens;
}
