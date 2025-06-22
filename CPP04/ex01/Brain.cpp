
#include "Brain.hpp"


/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Brain::Brain(void)
{
	std::cout << "Brain default constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "Default idea";
}

Brain::Brain(const Brain& other)
{
	std::cout << "Brain copy constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = other.ideas[i];
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Brain::~Brain(void)
{
	std::cout << "Brain deconstructor called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Brain& Brain::operator=(const Brain& other)
{
	std::cout << "Brain assignment constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = other.ideas[i];
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

const std::string& Brain::getIdea(int i) const {
	return this->ideas[i];
}

void Brain::setIdea(int i, const std::string& idea) {
	this->ideas[i] = idea;
}