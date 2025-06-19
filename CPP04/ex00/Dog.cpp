
#include "Dog.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Dog::Dog(void) : 
Animal("Dog")
{
	std::cout << "Dog default constructor is called" << std::endl;
}

Dog::Dog(const Dog& other) :
Animal(other)
{
	std::cout << "Dog copy constructor is called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Dog::~Dog(void)
{
	std::cout << "Dog deconstructor is called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Dog& Dog::operator=(const Dog& other)
{
	this->setType(other.getType());
	std::cout << "Dog assignment operator is called" << std::endl;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void Dog::makeSound(void) const
{
	std::cout << "woof" << std::endl;
}