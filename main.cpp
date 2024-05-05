#include <iostream>
#include <string>
#include <stdexcept>
#include "Parser.h"
#include "Calculator.h"

int main() {
	Parser& parser = Parser::getInstance();
	Calculator& calculator = Calculator::getInstance();

	std::cout << "Calculator Console Application\n\n";
	std::cout << "Please enter your operation. You can use the +, -, *, /, ^, (, ) operators.\n";

	while (true) {
		double result = 0.0;
		std::string infix;
		std::cin >> infix;
		std::vector<std::string> infixVector;
		try {
			infixVector = parser.infixStringToInfixVector(infix);
			result = calculator.calculate(infixVector);
			std::cout << "Result " << "of " << infix << " is: " << result << "\n";
		} catch (std::invalid_argument& e) {
			std::cerr << e.what() << "\n";
		}
	}

	return 0;
}