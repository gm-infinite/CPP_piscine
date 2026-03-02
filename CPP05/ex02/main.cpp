#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(0));

	std::cout << "=== Test 1: ShrubberyCreationForm - Execute Success ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 1);
		ShrubberyCreationForm shrub("home");
		std::cout << shrub << std::endl;
		bob.signForm(shrub);
		bob.executeForm(shrub);
		std::cout << "Check for 'home_shrubbery' file!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Execute unsigned form ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 1);
		ShrubberyCreationForm shrub("garden");
		alice.executeForm(shrub);
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Execute with grade too low ===" << std::endl;
	try {
		Bureaucrat intern("Intern", 140);
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("office");
		boss.signForm(shrub);
		intern.executeForm(shrub);
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: RobotomyRequestForm - 50% success ===" << std::endl;
	try {
		Bureaucrat scientist("Scientist", 1);
		RobotomyRequestForm robot("Bender");
		std::cout << robot << std::endl;
		scientist.signForm(robot);
		std::cout << "Attempt 1:" << std::endl;
		scientist.executeForm(robot);
		std::cout << "Attempt 2:" << std::endl;
		scientist.executeForm(robot);
		std::cout << "Attempt 3:" << std::endl;
		scientist.executeForm(robot);
		std::cout << "Attempt 4:" << std::endl;
		scientist.executeForm(robot);
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: PresidentialPardonForm ===" << std::endl;
	try {
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Arthur Dent");
		std::cout << pardon << std::endl;
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: PresidentialPardonForm - grade too low to sign ===" << std::endl;
	try {
		Bureaucrat clerk("Clerk", 100);
		PresidentialPardonForm pardon("Ford Prefect");
		clerk.signForm(pardon);
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 7: RobotomyRequestForm - grade too low to execute ===" << std::endl;
	try {
		Bureaucrat signer("Signer", 50);
		Bureaucrat executor("Executor", 50);
		RobotomyRequestForm robot("Target");
		signer.signForm(robot);
		executor.executeForm(robot);
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 8: Execute at exact grade limit ===" << std::endl;
	try {
		Bureaucrat exact("ExactGrade", 137);
		Bureaucrat signer("Signer", 1);
		ShrubberyCreationForm shrub("exact");
		signer.signForm(shrub);
		exact.executeForm(shrub);
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
