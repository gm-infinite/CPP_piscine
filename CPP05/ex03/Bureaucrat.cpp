
#include "Bureaucrat.hpp"
#include "AForm.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Bureaucrat::Bureaucrat(void) : Name("random_employe"), grade(150)
{ }

Bureaucrat::Bureaucrat(const Bureaucrat& other) : Name(other.Name), grade(other.grade)
{ }

Bureaucrat::Bureaucrat(const std::string& name, int grade) : Name(name)
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	this->grade = grade;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Bureaucrat::~Bureaucrat(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
		this->grade = other.grade;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void Bureaucrat::signForm(AForm& f) const
{
	try {
	f.beSigned(*this);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n' << " ^^ the bureaucrat catched an error from form::Besigned() in signForm()" << std::endl;
	}
}

void Bureaucrat::incrementGrade()
{
	if (grade - 1 < 1)
		throw GradeTooHighException();
	this->grade--;
}

void Bureaucrat::decrementGrade()
{
	if (grade + 1 > 150)
		throw GradeTooLowException();
	this->grade++;
}

std::string Bureaucrat::getName(void) const {
	return this->Name;
}

int Bureaucrat::getGrade(void) const {
	return this->grade;
}

void Bureaucrat::setGrade(const int grade) {
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	this->grade = grade;
}

void Bureaucrat::executeForm(const AForm& form) const
{
	try {
		form.execute(*this);
		std::cout << this->Name << " executed " << form.getName() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n' << " ^^ the bureaucrat catched an error from AForm::execute() in executeForm()" << std::endl;
	}
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj) 
{
    os << obj.getName() << ", bureaucrat grade " << obj.getGrade() << ".";  
    return os;
}
