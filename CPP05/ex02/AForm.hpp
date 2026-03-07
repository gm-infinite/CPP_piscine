
#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>

class Bureaucrat;

class AForm {

public:
	AForm(void);
	virtual ~AForm(void);
	AForm(const std::string& name, int SignGrade, int ExecuteGrade);
	AForm(const AForm& other);
	AForm& operator=(const AForm& other);

	std::string getName(void) const;
	bool getIsSigned(void) const;
	int getSignGrade(void) const;
	int getExecuteGrade(void) const;
	
	void setIsSigned(const bool a);

	void beSigned(const Bureaucrat& b);
	virtual void execute(const Bureaucrat& executor) const = 0;

	class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

	class FormNotSignedException : public std::exception {
    public:
        const char* what() const throw();
    };

private:
	const std::string Name;
	bool IsSigned;
	const int SignGrade;
	const int ExecuteGrade;

};

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif /* AFORM_HPP */