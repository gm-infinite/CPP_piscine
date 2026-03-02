
#ifndef FORM_HPP
#define FORM_HPP

#include <string>

class Bureaucrat;

class Form {

public:
	Form(void);
	~Form(void);
	Form(const std::string& name, int SignGrade, int ExecuteGrade);
	Form(const Form& other);
	Form& operator=(const Form& other);

	std::string getName(void) const;
	bool getIsSigned(void) const;
	int getSignGrade(void) const;
	int getExecuteGrade(void) const;

	void beSigned(const Bureaucrat& b);

	class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Form: Grade is too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Form: Grade is too low (maximum is 150)";
        }
    };

private:
	const std::string Name;
	bool IsSigned;
	const int SignGrade;
	const int ExecuteGrade;

};

std::ostream& operator<<(std::ostream& os, const Form& form);

#endif /* FORM_HPP */