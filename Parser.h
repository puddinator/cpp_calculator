#ifndef CPP_CALCULATOR__PARSER_H
#define CPP_CALCULATOR__PARSER_H
#include <vector>
#include <unordered_set>

class Parser {
private:
	constexpr Parser() = default;
	static void handleDisallowedCharacters(const std::string& input);
	void printPostfixVector(const std::vector<std::string>& postfixVector);
public:
	Parser(Parser& other) = delete;
	void operator=(const Parser&) = delete;
	static Parser& getInstance();

	static const std::unordered_set<char> allowedCharacters;
	static const std::unordered_map<char, int> inStackPrecedence;
	static const std::unordered_map<char, int> outStackPrecedence;
	static bool isOperand(std::string str);

	std::vector<std::string> infixStringToInfixVector(std::string infix);
	std::vector<std::string> infixVectorToPostfixVector(std::vector<std::string> infixVector);
};

#endif //CPP_CALCULATOR__PARSER_H
