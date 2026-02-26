#include "Bureaucrat.hpp"

int main()
{
	std::cout << "--- Test 1: Valid bureaucrat ---" << std::endl;
	try {
		Bureaucrat bob("Bob", 50);
		std::cout << bob << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 2: Grade too high (0) ---" << std::endl;
	try {
		Bureaucrat alice("Alice", 0);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 3: Grade too low (151) ---" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 151);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 4: Increment at grade 1 ---" << std::endl;
	try {
		Bureaucrat dave("Dave", 1);
		std::cout << dave << std::endl;
		dave.incrementGrade();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 5: Decrement at grade 150 ---" << std::endl;
	try {
		Bureaucrat eve("Eve", 150);
		std::cout << eve << std::endl;
		eve.decrementGrade();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 6: Normal increment/decrement ---" << std::endl;
	try {
		Bureaucrat frank("Frank", 75);
		std::cout << frank << std::endl;
		frank.incrementGrade();
		std::cout << frank << std::endl;
		frank.decrementGrade();
		std::cout << frank << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
