
#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP
#include "AForm.hpp"

class ShrubberyCreationForm : public AForm{

public:
	ShrubberyCreationForm(void);
	~ShrubberyCreationForm(void);
	ShrubberyCreationForm(const std::string Name);
	ShrubberyCreationForm(const ShrubberyCreationForm& other);
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);

	std::string getTarget(void) const;

	void execute(Bureaucrat const& executor) const;

private:
	std::string Target;
};

std::ostream& operator<<(std::ostream& os, const ShrubberyCreationForm& form);

#endif /* SHRUBBERYCREATIONFORM_HPP */