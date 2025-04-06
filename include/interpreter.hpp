#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "parser.hpp"


class Value {
    public:
	enum class Type {
	    Int,
	    Float,
	    String,
	    None
	};

	Type type;

	int intVal;
	float floatVal;
	std::string stringVal;

	Value() : type(Type::None), intVal(0), floatVal(0.0) {};
	Value(int i)   : type(Type::Int),   intVal(i),    floatVal(0.0f) {}
	Value(float f) : type(Type::Float), floatVal(f),  intVal(0)      {}
	Value(const std::string& s) : type(Type::String), stringVal(s), intVal(0), floatVal(0.0f) {}

	std::string toString() const {
	    switch(type){
		case Type::Int:
		    return std::to_string(intVal);
                case Type::Float:
		    return std::to_string(floatVal);
                case Type::String:
		    return stringVal;
                case Type::None:
		    return "None";
            };
        };
};

class Interpreter {
    public:
	Value interpret(const ASTNode& root);
    private:
	std::unordered_map<std::string, Value> variables;

	Value evaluateNode(const ASTNode& node);

	Value evalProgram(const ASTNode& node);
	Value evalVarDecl(const ASTNode& node);
	Value evalPrint(const ASTNode& node);
	Value evalExpression(const ASTNode& node);
	Value evalIdentifier(const ASTNode& node);
	Value evalNumber(const ASTNode& node);
	Value evalStringLiteral(const ASTNode& node);

	Value addValues(const Value& left, const Value& right);
	Value subValues(const Value& left, const Value& right);
	
	Value negateValue(const Value& value);
};
