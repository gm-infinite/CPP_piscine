
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
ShrubberyCreationForm::ShrubberyCreationForm(void):
AForm("Shrubbery_Creation_Form", 145, 137),
Target("default")
{ }

ShrubberyCreationForm::ShrubberyCreationForm(const std::string Target) :
AForm("Shrubbery_Creation_Form", 145, 137),
Target(Target)
{ }

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) :
AForm(other),
Target(other.Target)
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
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

void ShrubberyCreationForm::execute(const Bureaucrat& b) const
{
	if (!this->getIsSigned())
		throw FormNotSignedException();
	if (this->getExecuteGrade() < b.getGrade())
		throw GradeTooLowException();
	
	std::ofstream file((this->Target + "_shrubbery").c_str());
	if (!file.is_open())
        throw std::runtime_error("Could not create file");
    
    file << "       _-_" << std::endl;
    file << "    /~~   ~~\\" << std::endl;
    file << " /~~         ~~\\" << std::endl;
    file << "{               }" << std::endl;
    file << " \\  _-     -_  /" << std::endl;
    file << "   ~  \\\\ //  ~" << std::endl;
    file << "_- -   | | _- _" << std::endl;
    file << "  _ -  | |   -_" << std::endl;
    file << "      // \\\\" << std::endl;

	file.close();
}

std::string ShrubberyCreationForm::getTarget(void) const {
	return this->Target;
}

std::ostream& operator<<(std::ostream& os, const ShrubberyCreationForm& f)
{
	os << "Form: " << f.getName() << '\n'
       << "Signed: " << (f.getIsSigned() ? "yes" : "no") << '\n'
       << "Grade to sign: " << f.getSignGrade() << '\n'
       << "Grade to execute: " << f.getExecuteGrade() << '\n'
	   << "Target: " << f.getTarget() << std::endl;
	return os;
}