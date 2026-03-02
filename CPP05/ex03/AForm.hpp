
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
	void virtual execute(const Bureaucrat& executor) const = 0;

	class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "AForm: Grade is too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "AForm: Grade is too low (maximum is 150)";
        }
    };

	class FormNotSignedException : public std::exception {
    public:
        const char* what() const throw() {
            return "Aform: Form is not signed!";
        }
    };

private:
	const std::string Name;
	bool IsSigned;
	const int SignGrade;
	const int ExecuteGrade;

};

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif /* AFORM_HPP */