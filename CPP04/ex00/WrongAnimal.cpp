
#include "WrongAnimal.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
WrongAnimal::WrongAnimal(void) : type("WrongAnimal")
{
	std::cout << "WrongAnimal default constructor is called" << std::endl;
}

WrongAnimal::WrongAnimal(const std::string& type) : type(type)
{
	std::cout << "WrongAnimal custom constructor is called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) : type(other.getType())
{
	std::cout << "WrongAnimal copy constructor is called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "WrongAnimal deconstructor is called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	this->setType(other.getType());
	std::cout << "WrongAnimal assignment operator is called" << std::endl;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void WrongAnimal::makeSound(void) const
{
	std::cout << "*Wrong Animal noises*" << std::endl;
}

const std::string& WrongAnimal::getType(void) const {
	return this->type;
}

void WrongAnimal::setType(const std::string& type) {
	this->type = type;
}

