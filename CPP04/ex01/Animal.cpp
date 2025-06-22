
#include "Animal.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Animal::Animal(void) : type("Animal")
{
	std::cout << "Animal default constructor is called" << std::endl;
}

Animal::Animal(const std::string& type) : type(type)
{
	std::cout << "Animal custom constructor is called" << std::endl;
}

Animal::Animal(const Animal& other) : type(other.getType())
{
	std::cout << "Animal copy constructor is called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Animal::~Animal(void)
{
	std::cout << "Animal deconstructor is called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Animal& Animal::operator=(const Animal& other)
{
	this->setType(other.getType());
	std::cout << "Animal assignment operator is called" << std::endl;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void Animal::makeSound(void) const
{
	std::cout << "*Animal noises*" << std::endl;
}

const std::string& Animal::getType(void) const {
	return this->type;
}

void Animal::setType(const std::string& type) {
	this->type = type;
}

