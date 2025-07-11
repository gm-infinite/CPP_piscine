
#include "Ice.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Ice::Ice(void) :
AMateria("ice")
{ }

Ice::Ice(const Ice& other) :
AMateria(other.getType())
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Ice::~Ice(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Ice& Ice::operator=(const Ice& other)
{
	this->setType(other.getType());
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

AMateria* Ice::clone() const
{
	return new Ice();
}

void Ice::use(ICharacter& target)
{
	std::cout <<  "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}