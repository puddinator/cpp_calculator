#include <string>
#include <stack>
#include <iostream>
#include <stdexcept>
#include "Calculator.h"

const std::unordered_map<char, int> Calculator::inStackPrecedence = {{'+', 2}, {'-', 2}, {'*', 4}, {'/', 4}, {'^', 5}, {'(', 0} };
const std::unordered_map<char, int> Calculator::outStackPrecedence = {{'+', 1}, {'-', 1}, {'*', 3}, {'/', 3}, {'^', 6}, {'(', 7}, {')', 0} };

Calculator& Calculator::getInstance() {
	static Calculator instance;
	return instance;
}

double Calculator::calculate(std::string infix) {
	std::string postfix = Calculator::convertToPostfix(infix);
	return Calculator::evaluatePostfix(postfix);
}

bool isOperand(char c) {
	if (0 <= c - '0' && c - '0' <= 9)
		return true;
	return false;
}

std::string Calculator::convertToPostfix(std::string infix) {
	std::stack<char> stack;
	std::string postfix(infix.size(), 0);
	int j = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (isOperand(infix[i])) {
			postfix[j++] = infix[i];
		} else if (!outStackPrecedence.contains(infix[i])) {
			throw std::invalid_argument("Calculator unable to handle `" + std::string(1, infix[i]) + "` character.");
		} else if (stack.empty() || outStackPrecedence.at(infix[i]) > inStackPrecedence.at(stack.top())) {
			stack.push(infix[i]);
		} else if (outStackPrecedence.at(infix[i]) == inStackPrecedence.at(stack.top())) { // handle brackets
			stack.pop();
		} else {
			postfix[j++] = stack.top();
			stack.pop();
		}
	}
	while (!stack.empty()) {
		postfix[j++] = stack.top();
		stack.pop();
	}
	return postfix;
}

double Calculator::evaluatePostfix(std::string postfix) {
	std::stack<char> stack;

	int x, y, res;
	for (int i = 0; postfix[i] != '\0'; i++) {
		if (!inStackPrecedence.contains(postfix[i])) {
			stack.push(postfix[i] - '0');
		} else {
			y = stack.top();
			stack.pop();
			x = stack.top();
			stack.pop();
			switch (postfix[i]) {
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
				res = pow(x, y);
				break;
			}
			stack.push(res);
		}
	}
	return stack.top();
}