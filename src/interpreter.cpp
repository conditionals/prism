#include "../include/interpreter.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>

Value Interpreter::interpret(const ASTNode& root){
    return evaluateNode(root);
}

Value Interpreter::evaluateNode(const ASTNode& node) {
    switch (node.type) {
    case NodeType::PROGRAM:
        return evalProgram(node);
    case NodeType::VAR_DECL:
        return evalVarDecl(node);
    case NodeType::PRINT:
        return evalPrint(node);
    case NodeType::EXPRESSION:
        return evalExpression(node);
    case NodeType::IDENTIFIER:
        return evalIdentifier(node);
    case NodeType::NUMBER:
        return evalNumber(node);
    case NodeType::STRING:
        return evalStringLiteral(node);
    }

    // Fallback if we encounter an unrecognized node
    throw std::runtime_error("Interpreter error: Unrecognized node type.");
}

Value Interpreter::evalProgram(const ASTNode& node) {
   Value lastVal;
    for (auto& child : node.children) {
        lastVal = evaluateNode(child);
    }
    return lastVal; 
}


Value Interpreter::evalVarDecl(const ASTNode& node) {
    if(node.children.size() < 2) throw std::runtime_error("invalid variable declaration, expected 2 children");
    
    const auto& identNode = node.children[0];
    const auto& exprNode = node.children[1];

    if(identNode.type != NodeType::IDENTIFIER) throw std::runtime_error("var_decl first child must be identifier");

    Value val = evaluateNode(exprNode);
    variables[identNode.value] = val;

    return val;
}

Value Interpreter::evalPrint(const ASTNode& node) {
    if(node.children.empty()) throw std::runtime_error("print: missing child expression");

    Value val = evaluateNode(node.children[0]);
    std::cout << val.toString() << std::endl;

    return val;
}


Value Interpreter::evalExpression(const ASTNode& node) {
    if(node.children.size() == 1) {
	Value operand = evaluateNode(node.children[0]);
	if(node.value == "-"){
	    return negateValue(operand);
	}

	return operand;
    }
    if(node.children.empty()) throw std::runtime_error("no children in expr");

    Value lVal = evaluateNode(node.children[0]);
    Value rVal = evaluateNode(node.children[1]);

    const std::string& op = node.value;

    if(op == "+") return addValues(lVal, rVal);
    if(op == "-") return subValues(lVal, rVal);

    throw std::runtime_error("unrecognized operator: " + op);
}

Value Interpreter::evalIdentifier(const ASTNode& node) {
    auto it = variables.find(node.value);
    if(it == variables.end()) throw std::runtime_error("error: undefined variable: " + node.value);

    return it->second;
}

Value Interpreter::evalNumber(const ASTNode& node){
    if(node.value.find('.') != std::string::npos){
	return Value(std::stof(node.value));
    }

    return Value(std::stoi(node.value));
}

Value Interpreter::evalStringLiteral(const ASTNode& node) {
    return Value(node.value);
}

Value Interpreter::addValues(const Value& lVal, const Value& rVal){
    if(lVal.type == Value::Type::String && rVal.type == Value::Type::String){
	return Value(lVal.stringVal + rVal.stringVal);
    }

    if(lVal.type == Value::Type::Float || rVal.type == Value::Type::Float){
	float l = (lVal.type == Value::Type::Float ? lVal.floatVal : (float) lVal.intVal);
	float r = (rVal.type == Value::Type::Float ? rVal.floatVal : (float) rVal.intVal);

	return Value(l + r);
    }

    // TODO: better checking on types
    return Value(lVal.intVal + rVal.intVal);
}

Value Interpreter::subValues(const Value& lVal, const Value& rVal) {
   if(lVal.type == Value::Type::String || rVal.type == Value::Type::String) throw std::runtime_error("cannot perform subtraction on type string"); 

   if(lVal.type == Value::Type::Float || rVal.type == Value::Type::Float){
	float l = lVal.type == Value::Type::Float ? lVal.floatVal : static_cast<float>(lVal.intVal);
	float r = rVal.type == Value::Type::Float ? rVal.floatVal : static_cast<float>(rVal.intVal);
	return l - r;
   }

   return lVal.intVal - rVal.intVal;
}

Value Interpreter::negateValue(const Value& val){
    switch(val.type){
	case Value::Type::Int:
	    return Value(-val.intVal);
        case Value::Type::Float:
	    return Value(-val.floatVal);
	default:
	    throw std::runtime_error("cannot apply urnary minus to type");
    }
}
