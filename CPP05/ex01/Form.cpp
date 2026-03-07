
#include "Form.hpp"
#include "Bureaucrat.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Form::Form(void) : 
Name("default"), 
IsSigned(false), 
SignGrade(1), 
ExecuteGrade(1)
{ }

Form::Form(const Form& other) :
Name(other.Name), 
IsSigned(other.IsSigned), 
SignGrade(other.SignGrade), 
ExecuteGrade(other.ExecuteGrade)
{ }

Form::Form(const std::string& name, int SignGrade, int ExecuteGrade): 
Name(name),
IsSigned(false),
SignGrade(SignGrade),
ExecuteGrade(ExecuteGrade)
{
    if (SignGrade < 1 || ExecuteGrade < 1)
        throw Form::GradeTooHighException();
    if (SignGrade > 150 || ExecuteGrade > 150)
        throw Form::GradeTooLowException();
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Form::~Form(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Form& Form::operator=(const Form& other)
{
	if (this != &other)
		this->IsSigned = other.IsSigned;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void Form::beSigned(const Bureaucrat& b)
{
	if (this->IsSigned) {
		throw std::runtime_error("Form is already signed");
	}
	if (!(b.getGrade() <= this->SignGrade)) {
		throw Form::GradeTooLowException();
	}
	this->IsSigned = true;
}

std::string Form::getName(void) const {
	return this->Name;
}

bool Form::getIsSigned(void) const {
	return this->IsSigned;
}

int Form::getSignGrade(void) const {
	return this->SignGrade;
}

int Form::getExecuteGrade(void) const {
	return this->ExecuteGrade;
}

const char* Form::GradeTooHighException::what() const throw() {
	return "Form: Grade is too high (minimum is 1)";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Form: Grade is too low (maximum is 150)";
}

std::ostream& operator<<(std::ostream& os, const Form& f)
{
	os << "Form: " << f.getName() << '\n'
       << "Signed: " << (f.getIsSigned() ? "yes" : "no") << '\n'
       << "Grade to sign: " << f.getSignGrade() << '\n'
       << "Grade to execute: " << f.getExecuteGrade() << std::endl;
	return os;
}