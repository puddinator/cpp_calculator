#include "Parser.h"
#include <vector>
#include "unordered_set"

Parser& Parser::getInstance() {
	static Parser instance;
	return instance;
}

const std::unordered_set<char> Parser::allowedCharacters = {' ', '+', '-', '*', '/', '^', '(', ')'};

void Parser::handleDisallowedCharacters(const std::string& input) {
	for (char c : input) {
		if (!isdigit(c) || !allowedCharacters.contains(c)) {
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
			infixVector.push_back(infixString.substr(l, r - l));
			infixVector.push_back(infixString.substr(r, 1));
			l = r + 1;
		}
	}
	infixVector.push_back(infixString.substr(l, infixString.size() - l));
	return infixVector;
}