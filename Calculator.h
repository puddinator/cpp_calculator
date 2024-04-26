#ifndef CALCULATOR__CALCULATOR_H
#define CALCULATOR__CALCULATOR_H
#include <unordered_map>

class Calculator {
private:
	const static std::unordered_map<char, int> inStackPrecedence;
	const static std::unordered_map<char, int> outStackPrecedence;
	constexpr Calculator() = default;
public:
	static Calculator& getInstance();
	double calculate(std::string infix);
	std::string convertToPostfix(std::string infix);
	double evaluatePostfix(std::string postfix);
};

#endif //CALCULATOR__CALCULATOR_H
