#include <string>
#include <stack>
#include <iostream>
#include <stdexcept>
#include "Calculator.h"

Calculator& Calculator::getInstance() {
	static Calculator instance;
	return instance;
}

const std::unordered_map<char, int> Calculator::inStackPrecedence = {{'+', 2}, {'-', 2}, {'*', 4}, {'/', 4}, {'^', 5}, {'(', 0} };
const std::unordered_map<char, int> Calculator::outStackPrecedence = {{'+', 1}, {'-', 1}, {'*', 3}, {'/', 3}, {'^', 6}, {'(', 7}, {')', 0} };

int Calculator::calculate(std::vector<std::string> infixVector) {
	std::vector<std::string> postfixVector = Calculator::convertToPostfixVector(infixVector);
	return Calculator::evaluatePostfixVector(postfixVector);
}

bool isOperand(char c) {
	if (0 <= c - '0' && c - '0' <= 9)
		return true;
	return false;
}

std::vector<std::string> Calculator::convertToPostfixVector(std::vector<std::string> infix) {
	std::stack<char> stack;
	std::string postfix(infix.size(), 0);
	int i = 0, j = 0;
	while (i < infix.size()) {
		if (isOperand(infix[i])) {
			postfix[j++] = infix[i++];
		} else if (infix[i] == ' ') {
			i++;
		} else if (stack.empty() || outStackPrecedence.at(infix[i]) > inStackPrecedence.at(stack.top())) {
			stack.push(infix[i++]);
		} else if (outStackPrecedence.at(infix[i]) == inStackPrecedence.at(stack.top())) { // handle brackets
			stack.pop();
			i++;
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

int Calculator::evaluatePostfixVector(std::vector<std::string> postfixVector) {
	std::stack<int> stack;

	int x, y, res;
	for (int i = 0; postfix[i] != '\0'; i++) {
		if (isOperand(postfix[i])) {
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
	return stack.empty() ? 0 : stack.top();
}