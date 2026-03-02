#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "--- Test 1: Create valid Form ---" << std::endl;
	try {
		Form taxForm("Tax Form", 50, 25);
		std::cout << taxForm << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 2: Form grade too high (0) ---" << std::endl;
	try {
		Form badForm("Bad Form", 0, 25);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 3: Form grade too low (151) ---" << std::endl;
	try {
		Form badForm("Bad Form", 151, 25);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 4: Bureaucrat signs Form successfully ---" << std::endl;
	try {
		Bureaucrat boss("Boss", 10);
		Form easyForm("Easy Form", 50, 25);
		std::cout << boss << std::endl;
		std::cout << easyForm << std::endl;
		boss.signForm(easyForm);
		std::cout << easyForm << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 5: Bureaucrat fails to sign (grade too low) ---" << std::endl;
	try {
		Bureaucrat intern("Intern", 100);
		Form hardForm("Hard Form", 10, 5);
		std::cout << intern << std::endl;
		std::cout << hardForm << std::endl;
		intern.signForm(hardForm);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n--- Test 6: Bureaucrat at exact grade limit ---" << std::endl;
	try {
		Bureaucrat exactGrade("ExactGrade", 50);
		Form exactForm("Exact Form", 50, 25);
		std::cout << exactGrade << std::endl;
		std::cout << exactForm << std::endl;
		exactGrade.signForm(exactForm);
		std::cout << exactForm << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
