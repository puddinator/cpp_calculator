#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include "Parser.h"

Parser& Parser::getInstance() {
	static Parser instance;
	return instance;
}

const std::unordered_set<char> Parser::allowedCharacters = {' ', '+', '-', '*', '/', '^', '(', ')'};
const std::unordered_map<char, int> Parser::inStackPrecedence = {{'+', 2}, {'-', 2}, {'*', 4}, {'/', 4}, {'^', 5}, {'(', 0} };
const std::unordered_map<char, int> Parser::outStackPrecedence = {{'+', 1}, {'-', 1}, {'*', 3}, {'/', 3}, {'^', 6}, {'(', 7}, {')', 0} };
bool Parser::isOperand(std::string str) {
	if (str.size() == 1 && allowedCharacters.contains(str[0]))
		return false;
	return true;
}

void Parser::handleDisallowedCharacters(const std::string& input) {
	for (char c : input) {
		if (!isdigit(c) && !allowedCharacters.contains(c)) {
			throw std::invalid_argument("Calculator unable to handle `" + std::string(1, c) + "` character.");
		}
	}
}

/**
 * Throws std::invalid_argument if disallowed characters are found.
 */
std::vector<std::string> Parser::infixStringToInfixVector(std::string infixString) {
	handleDisallowedCharacters(infixString);
	std::vector<std::string> infixVector;
	std::erase(infixString, ' ');
	int l = 0;
	for (int r = 0; r < infixString.size(); r++) {
		if (!isdigit(infixString[r])) {
			if (l != 0 && isdigit(infixString[r - 1]))
				infixVector.push_back(infixString.substr(l, r - l));
			infixVector.push_back(infixString.substr(r, 1));
			l = r + 1;
		}
	}
	if (infixString.size() != 0 && isdigit(infixString[infixString.size() - 1]))
		infixVector.push_back(infixString.substr(l, infixString.size() - l));
	return infixVector;
}

std::vector<std::string> Parser::infixVectorToPostfixVector(std::vector<std::string> infixVector) {
	std::stack<char> stack;
	std::vector<std::string> postfixVector;
	int i = 0, j = 0;
	while (i < infixVector.size()) {
		if (isOperand(infixVector[i])) {
			postfixVector.push_back(infixVector[i++]);
		} else if (stack.empty() || outStackPrecedence.at(infixVector[i][0]) > inStackPrecedence.at(stack.top())) {
			stack.push(infixVector[i++][0]);
		} else if (outStackPrecedence.at(infixVector[i][0]) == inStackPrecedence.at(stack.top())) { // handle brackets
			stack.pop();
			i++;
		} else {
			postfixVector.emplace_back(1, stack.top());
			stack.pop();
		}
	}
	while (!stack.empty()) {
		postfixVector.emplace_back(1, stack.top());
		stack.pop();
	}
	printPostfixVector(postfixVector);
	return postfixVector;
}

void Parser::printPostfixVector(const std::vector<std::string>& postfixVector) {
	std::cout << "Postfix: ";
	for (std::string str: postfixVector)
		std::cout << str << ' ';
	std::cout << '\n';
}