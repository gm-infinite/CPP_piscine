
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
	// Optional: check if already signed
    // if (this->_isSigned)
    //     throw std::runtime_error("Form is already signed");
	if (!(b.getGrade() <= this->SignGrade))
		throw Form::GradeTooLowException();
	std::cout << "the form has been signed" << std::endl;
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

std::ostream& operator<<(std::ostream& os, const Form& f)
{
	os << "Form: " << f.getName() << '\n'
       << "Signed: " << (f.getIsSigned() ? "yes" : "no") << '\n'
       << "Grade to sign: " << f.getSignGrade() << '\n'
       << "Grade to execute: " << f.getExecuteGrade() << std::endl;
	return os;
}