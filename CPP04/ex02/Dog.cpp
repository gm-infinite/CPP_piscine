
#include "Dog.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Dog::Dog(void) : 
Animal("Dog"),
brain(new Brain())
{
	std::cout << "Dog default constructor is called" << std::endl;
}

Dog::Dog(const Dog& other) :
Animal(other),
brain(new Brain(*other.brain))
{
	std::cout << "Dog copy constructor is called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Dog::~Dog(void)
{
	std::cout << "Dog deconstructor is called" << std::endl;
	delete brain;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Dog& Dog::operator=(const Dog& other)
{
	this->setType(other.getType());
	*this->brain = *other.brain;
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

const Brain* Dog::getBrain(void) const
{
	return this->brain;
}

void Dog::setBrainIdea(int i, const std::string& idea)
{
	this->brain->setIdea(i, idea);
}