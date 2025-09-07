
#include "WrongCat.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
WrongCat::WrongCat(void) : 
WrongAnimal("not a Cat")
{
	std::cout << "WrongCat default constructor is called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) :
WrongAnimal(other)
{
	std::cout << "WrongCat copy constructor is called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

WrongCat::~WrongCat(void)
{
	std::cout << "WrongCat deconstructor is called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	this->setType(other.getType());
	std::cout << "WrongCAt assignment operator is called" << std::endl;
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void WrongCat::makeSound(void) const
{
	std::cout << "Neigh" << std::endl;
}
