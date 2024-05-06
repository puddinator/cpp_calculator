#ifndef CALCULATOR__CALCULATOR_H
#define CALCULATOR__CALCULATOR_H
#include <unordered_map>

class Calculator {
private:
	constexpr Calculator() = default;
public:
	Calculator(Calculator& other) = delete;
	void operator=(const Calculator&) = delete;
	static Calculator& getInstance();

	int calculate(std::string& infixString);
	int evaluatePostfixVector(const std::vector<std::string>& postfixVector);
};

#endif //CALCULATOR__CALCULATOR_H
