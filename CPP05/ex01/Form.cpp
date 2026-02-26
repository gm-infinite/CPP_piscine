
#include "Form.hpp"

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

