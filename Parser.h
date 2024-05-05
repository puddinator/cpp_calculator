#ifndef CPP_CALCULATOR__PARSER_H
#define CPP_CALCULATOR__PARSER_H
#include <vector>
#include <unordered_set>

class Parser {
private:
	constexpr Parser() = default;
	static const std::unordered_set<char> allowedCharacters;
	void handleDisallowedCharacters(const std::string& input);
public:
	Parser(Parser& other) = delete;
	void operator=(const Parser&) = delete;
	static Parser& getInstance();
	std::vector<std::string> infixStringToInfixVector(std::string infix);
};

#endif //CPP_CALCULATOR__PARSER_H
