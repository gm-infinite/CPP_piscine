
#include "Cure.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Cure::Cure(void) :
AMateria("cure")
{ }

Cure::Cure(const Cure& other) :
AMateria(other.getType())
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Cure::~Cure(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Cure& Cure::operator=(const Cure& other)
{
	this->setType(other.getType());
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

AMateria* Cure::clone() const
{
	return new Cure();
}

void Cure::use(ICharacter& target)
{
	std::cout <<  "* heals " << target.getName() << "'s wounds *" << std::endl;
}