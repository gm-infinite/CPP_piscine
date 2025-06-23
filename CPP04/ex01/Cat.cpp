
#include "Cat.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Cat::Cat(void) : 
Animal("Cat"),
brain(new Brain())
{
	std::cout << "Cat default constructor is called" << std::endl;
}

Cat::Cat(const Cat& other) :
Animal(other),
brain(new Brain(*other.brain))
{
	std::cout << "Cat copy constructor is called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Cat::~Cat(void)
{
	std::cout << "Cat deconstructor is called" << std::endl;
	delete brain;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Cat& Cat::operator=(const Cat& other)
{
	if (this != &other) 
	{
        this->setType(other.getType());
        delete this->brain;
        this->brain = new Brain(*other.brain);
        std::cout << "Cat assignment operator is called" << std::endl;
    }
    return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void Cat::makeSound(void) const
{
	std::cout << "Meow" << std::endl;
}

const Brain* Cat::getBrain(void) const
{
	return this->brain;
}

void Cat::setBrainIdea(int i, const std::string& idea)
{
	this->brain->setIdea(i, idea);
}