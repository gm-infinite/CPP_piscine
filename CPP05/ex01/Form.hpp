
#ifndef FORM_HPP
#define FORM_HPP

#include <string>

class Form {

public:
	Form(void);
	~Form(void);
	Form(const std::string& Name, const bool IsSigned, const int SignGrade, const int ExecuteGrade);
	Form(const Form& other);
	Form& operator=(const Form& other);

	std::string getName(void) const;
	bool getIsSigned(void) const;
	int getSignGrade(void) const;
	int getExecuteGrade(void) const;

	class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too low (maximum is 150)";
        }
    };

private:
	const std::string Name;
	bool IsSigned;
	const int SignGrade;
	const int ExecuteGrade;

};

#endif /* FORM_HPP */