#ifndef CALCULATOR__CALCULATOR_H
#define CALCULATOR__CALCULATOR_H
#include <unordered_map>

class Calculator {
private:
	constexpr Calculator() = default;
	static const std::unordered_map<char, int> inStackPrecedence;
	static const std::unordered_map<char, int> outStackPrecedence;
public:
	Calculator(Calculator& other) = delete;
	void operator=(const Calculator&) = delete;
	static Calculator& getInstance();
	int calculate(std::vector<std::string> infix);
	std::vector<std::string> convertToPostfixVector(std::vector<std::string> infixVector);
	int evaluatePostfixVector(std::vector<std::string> postfixVector);
};

#endif //CALCULATOR__CALCULATOR_H
