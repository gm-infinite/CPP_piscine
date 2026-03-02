#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(0));

	Intern someRandomIntern;
	Bureaucrat boss("Boss", 1);

	std::cout << "=== Test 1: Intern creates RobotomyRequestForm ===" << std::endl;
	{
		AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf) {
			std::cout << *rrf << std::endl;
			boss.signForm(*rrf);
			boss.executeForm(*rrf);
			delete rrf;
		}
	}

	std::cout << "\n=== Test 2: Intern creates ShrubberyCreationForm ===" << std::endl;
	{
		AForm* scf = someRandomIntern.makeForm("shrubbery creation", "garden");
		if (scf) {
			boss.signForm(*scf);
			boss.executeForm(*scf);
			delete scf;
		}
	}

	std::cout << "\n=== Test 3: Intern creates PresidentialPardonForm ===" << std::endl;
	{
		AForm* ppf = someRandomIntern.makeForm("presidential pardon", "Marvin");
		if (ppf) {
			boss.signForm(*ppf);
			boss.executeForm(*ppf);
			delete ppf;
		}
	}

	std::cout << "\n=== Test 4: Intern tries to create invalid form ===" << std::endl;
	{
		AForm* invalid = someRandomIntern.makeForm("coffee request", "Office");
		if (!invalid) {
			std::cout << "Form creation failed as expected" << std::endl;
		}
	}

	std::cout << "\n=== Test 5: Execute unsigned form ===" << std::endl;
	{
		AForm* form = someRandomIntern.makeForm("shrubbery creation", "unsigned");
		if (form) {
			boss.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== Test 6: Grade too low to execute ===" << std::endl;
	{
		Bureaucrat lowGrade("Intern", 140);
		AForm* form = someRandomIntern.makeForm("shrubbery creation", "lowgrade");
		if (form) {
			boss.signForm(*form);
			lowGrade.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== Test 7: Multiple robotomy attempts (50% success) ===" << std::endl;
	{
		AForm* robot = someRandomIntern.makeForm("robotomy request", "Target");
		if (robot) {
			boss.signForm(*robot);
			std::cout << "Attempt 1: ";
			boss.executeForm(*robot);
			std::cout << "Attempt 2: ";
			boss.executeForm(*robot);
			std::cout << "Attempt 3: ";
			boss.executeForm(*robot);
			std::cout << "Attempt 4: ";
			boss.executeForm(*robot);
			delete robot;
		}
	}

	return 0;
}
