

#ifndef INTERN_HPP
#define INTERN_HPP
#include "AForm.hpp"

class Intern {

public:
	Intern(void);
	~Intern(void);
	Intern(const Intern& other);
	Intern& operator=(const Intern& other);

	AForm* makeForm(std::string formName, std::string target) const;

private:

};

#endif /* INTERN_HPP */