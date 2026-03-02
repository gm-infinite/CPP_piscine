
#include "Intern.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Intern::Intern(void)
{ }

Intern::Intern(const Intern& other)
{
	(void)other;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Intern::~Intern(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

AForm* Intern::makeForm(std::string formName, std::string target) const
{
	std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    int formIndex = -1;
    for (int i = 0; i < 3; i++) {
        if (formNames[i] == formName) {
            formIndex = i;
            break;
        }
    }
    
    AForm* form = NULL;
    switch (formIndex) {
        case 0:
            form = new ShrubberyCreationForm(target);
            break;
        case 1:
            form = new RobotomyRequestForm(target);
            break;
        case 2:
            form = new PresidentialPardonForm(target);
            break;
        default:
            std::cout << "Error: Intern cannot create form '" << formName 
                      << "' - form does not exist" << std::endl;
            return NULL;
    }
    
    std::cout << "Intern creates " << form->getName() << " with target " << target << std::endl;
    return form;
}