
#include "Cat.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Cat::Cat(void) : 
Animal("Cat")
{
	std::cout << "Cat default constructor is called" << std::endl;
}

Cat::Cat(const Cat& other) :
Animal(other)
{
	std::cout << "Cat copy constructor is called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Cat::~Cat(void)
{
	std::cout << "Cat deconstructor is called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Cat& Cat::operator=(const Cat& other)
{
	this->setType(other.getType());
	std::cout << "CAt assignment operator is called" << std::endl;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void Cat::makeSound(void) const
{
	std::cout << "Meow" << std::endl;
}