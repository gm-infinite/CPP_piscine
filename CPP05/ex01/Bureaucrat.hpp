
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP
#include <string>
#include <iostream>
#include <exception>

class Form;

class Bureaucrat {

public:
	Bureaucrat(void);
	~Bureaucrat(void);
    Bureaucrat(const std::string& name, int grade);
	Bureaucrat(const Bureaucrat& other);
	Bureaucrat& operator=(const Bureaucrat& other);

	std::string getName(void) const;
	int getGrade(void) const;
    void setGrade(const int grade);

    void incrementGrade(void);
    void decrementGrade(void);
    void signForm(Form& f) const;

	class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Bureaucrat: Grade is too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Bureaucrat: Grade is too low (maximum is 150)";
        }
    };

private:
	const std::string Name;
	int grade;
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj);

#endif /* BUREAUCRAT_HPP */