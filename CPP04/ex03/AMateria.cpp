


#include "AMateria.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
AMateria::AMateria(void) : type("default")
{ }

AMateria::AMateria(std::string const &type) : type(type)
{ }

AMateria::AMateria(const AMateria& other) : type(other.getType())
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

AMateria::~AMateria(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

AMateria& AMateria::operator=(const AMateria& other)
{
	
	if (this != &other)
		this->type = other.getType();
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

std::string const & AMateria::getType() const
{
	return this->type;
}