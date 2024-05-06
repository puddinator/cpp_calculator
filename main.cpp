#include <iostream>
#include <string>
#include <stdexcept>
#include "Calculator.h"

int main() {
	Calculator& calculator = Calculator::getInstance();

	std::cout << "Calculator Console Application\n\n";
	std::cout << "Please enter your operation. You can use the +, -, *, /, ^, (, ) operators.\n";

	while (true) {
		double result = 0.0;
		std::string infix;
		std::cin >> infix;
		try {
			result = calculator.calculate(infix);
			std::cout << "Result " << "of " << infix << " is: " << result << "\n";
		} catch (std::invalid_argument& e) {
			std::cerr << e.what() << "\n";
		}
	}

	return 0;
}