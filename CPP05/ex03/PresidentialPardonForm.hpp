#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP
#include "AForm.hpp"

class PresidentialPardonForm : public AForm{

public:
	PresidentialPardonForm(void);
	~PresidentialPardonForm(void);
	PresidentialPardonForm(const std::string Target);
	PresidentialPardonForm(const PresidentialPardonForm& other);
	PresidentialPardonForm& operator=(const PresidentialPardonForm& other);

	std::string getTarget(void) const;

	void execute(Bureaucrat const& executor) const;

private:
	std::string Target;
};

std::ostream& operator<<(std::ostream& os, const PresidentialPardonForm& form);

#endif /* PRESIDENTIALPARDONFORM_HPP */
