
#include "AForm.hpp"
#include "Bureaucrat.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
AForm::AForm(void) : 
Name("default"), 
IsSigned(false), 
SignGrade(1), 
ExecuteGrade(1)
{ }

AForm::AForm(const AForm& other) :
Name(other.Name), 
IsSigned(other.IsSigned), 
SignGrade(other.SignGrade), 
ExecuteGrade(other.ExecuteGrade)
{ }

AForm::AForm(const std::string& name, int SignGrade, int ExecuteGrade): 
Name(name),
IsSigned(false),
SignGrade(SignGrade),
ExecuteGrade(ExecuteGrade)
{
    if (SignGrade < 1 || ExecuteGrade < 1)
        throw AForm::GradeTooHighException();
    if (SignGrade > 150 || ExecuteGrade > 150)
        throw AForm::GradeTooLowException();
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

AForm::~AForm(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

AForm& AForm::operator=(const AForm& other)
{
	if (this != &other)
		this->IsSigned = other.IsSigned;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void AForm::beSigned(const Bureaucrat& b)
{
    if (this->IsSigned) {
        throw std::runtime_error("Form is already signed");
	}
	if (!(b.getGrade() <= this->SignGrade)) {
		throw AForm::GradeTooLowException();
	}
	std::cout << "the form has been signed" << std::endl;
	this->IsSigned = true;
}

std::string AForm::getName(void) const {
	return this->Name;
}

bool AForm::getIsSigned(void) const {
	return this->IsSigned;
}

int AForm::getSignGrade(void) const {
	return this->SignGrade;
}

int AForm::getExecuteGrade(void) const {
	return this->ExecuteGrade;
}

void AForm::setIsSigned(const bool a) {
	this->IsSigned = a;
}

std::ostream& operator<<(std::ostream& os, const AForm& f)
{
	os << "Form: " << f.getName() << '\n'
       << "Signed: " << (f.getIsSigned() ? "yes" : "no") << '\n'
       << "Grade to sign: " << f.getSignGrade() << '\n'
       << "Grade to execute: " << f.getExecuteGrade() << std::endl;
	return os;
}