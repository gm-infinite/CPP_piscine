#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP
#include "AForm.hpp"

class RobotomyRequestForm : public AForm{

public:
	RobotomyRequestForm(void);
	~RobotomyRequestForm(void);
	RobotomyRequestForm(const std::string Target);
	RobotomyRequestForm(const RobotomyRequestForm& other);
	RobotomyRequestForm& operator=(const RobotomyRequestForm& other);

	std::string getTarget(void) const;

	void execute(Bureaucrat const& executor) const;

private:
	std::string Target;
};

std::ostream& operator<<(std::ostream& os, const RobotomyRequestForm& form);

#endif /* ROBOTOMYREQUESTFORM_HPP */
