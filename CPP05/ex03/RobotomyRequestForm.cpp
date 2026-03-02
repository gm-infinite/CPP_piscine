#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
RobotomyRequestForm::RobotomyRequestForm(void):
AForm("Robotomy_Request_Form", 72, 45),
Target("default")
{ }

RobotomyRequestForm::RobotomyRequestForm(const std::string Target) :
AForm("Robotomy_Request_Form", 72, 45),
Target(Target)
{ }

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) :
AForm(other),
Target(other.Target)
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

RobotomyRequestForm::~RobotomyRequestForm(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	if (this != &other) {
		this->setIsSigned(other.getIsSigned());
		this->Target = other.Target;
	}
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void RobotomyRequestForm::execute(const Bureaucrat& b) const
{
	if (!this->getIsSigned())
		throw FormNotSignedException();
	if (this->getExecuteGrade() < b.getGrade())
		throw GradeTooLowException();

    std::cout << "* DRILLING NOISES * Bzzzzz... Vrrrrrr..." << std::endl;
    if (std::rand() % 2 == 0)
        std::cout << this->Target << " has been robotomized successfully!" << std::endl;
    else
        std::cout << "Robotomy of " << this->Target << " failed!" << std::endl;
}

std::string RobotomyRequestForm::getTarget(void) const {
	return this->Target;
}

std::ostream& operator<<(std::ostream& os, const RobotomyRequestForm& f)
{
	os << "Form: " << f.getName() << '\n'
       << "Signed: " << (f.getIsSigned() ? "yes" : "no") << '\n'
       << "Grade to sign: " << f.getSignGrade() << '\n'
       << "Grade to execute: " << f.getExecuteGrade() << '\n'
	   << "Target: " << f.getTarget() << std::endl;
	return os;
}
