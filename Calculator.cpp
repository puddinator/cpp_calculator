#include <string>
#include <stack>
#include <iostream>
#include <stdexcept>
#include "Calculator.h"
#include "Parser.h"

Calculator& Calculator::getInstance() {
	static Calculator instance;
	return instance;
}

int Calculator::calculate(std::string& infixString) {
	Parser& parser = Parser::getInstance();
	std::vector<std::string> infixVector = parser.infixStringToInfixVector(infixString);
	std::vector<std::string> postfixVector = parser.infixVectorToPostfixVector(infixVector);
	return Calculator::evaluatePostfixVector(postfixVector);
}

int Calculator::evaluatePostfixVector(const std::vector<std::string>& postfixVector) {
	std::stack<int> stack;

	int x, y, res;
	for (int i = 0; i < postfixVector.size(); i++) {
		if (Parser::isOperand(postfixVector[i])) {
			stack.push(stoi(postfixVector[i]));
		} else {
			y = stack.top();
			stack.pop();
			x = stack.top();
			stack.pop();
			switch (postfixVector[i][0]) {
			case '+':
				res = x + y;
				break;
			case '-':
				res = x - y;
				break;
			case '*':
				res = x * y;
				break;
			case '/':
				res = x / y;
				break;
			case '^':
				res = (int) pow(x, y);
				break;
			}
			stack.push(res);
		}
	}
	return stack.empty() ? 0 : stack.top();
}