#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
PresidentialPardonForm::PresidentialPardonForm(void):
AForm("Presidential_Pardon_Form", 25, 5),
Target("default")
{ }

PresidentialPardonForm::PresidentialPardonForm(const std::string Target) :
AForm("Presidential_Pardon_Form", 25, 5),
Target(Target)
{ }

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) :
AForm(other),
Target(other.Target)
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

PresidentialPardonForm::~PresidentialPardonForm(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
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

void PresidentialPardonForm::execute(const Bureaucrat& b) const
{
	if (!this->getIsSigned())
		throw FormNotSignedException();
	if (this->getExecuteGrade() < b.getGrade())
		throw GradeTooLowException();

   std::cout << this->Target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

std::string PresidentialPardonForm::getTarget(void) const {
	return this->Target;
}

std::ostream& operator<<(std::ostream& os, const PresidentialPardonForm& f)
{
	os << "Form: " << f.getName() << '\n'
       << "Signed: " << (f.getIsSigned() ? "yes" : "no") << '\n'
       << "Grade to sign: " << f.getSignGrade() << '\n'
       << "Grade to execute: " << f.getExecuteGrade() << '\n'
	   << "Target: " << f.getTarget() << std::endl;
	return os;
}
