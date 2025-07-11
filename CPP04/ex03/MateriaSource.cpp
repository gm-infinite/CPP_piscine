
#include "MateriaSource.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
MateriaSource::MateriaSource(void) : mem_index(0)
{
	this->Memory[0] = nullptr;
	this->Memory[1] = nullptr;
	this->Memory[2] = nullptr;
	this->Memory[3] = nullptr;
}

MateriaSource::MateriaSource(const MateriaSource& other) : 
mem_index(other.mem_index)
{
	for (int i = 0; i<4; i++)
	{	
		if (other.Memory[i] != nullptr)
			this->Memory[i] = other.Memory[i]->clone();
		else
			this->Memory[i] = nullptr;
	}
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

MateriaSource::~MateriaSource(void)
{
	for (int i = 0; i<4; i++)	
		if (this->Memory[i] != nullptr)
			delete this->Memory[i];
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	for (int i = 0; i<4; i++)
	{	
		if (this->Memory[i] != nullptr)
			delete this->Memory[i];
		if (other.Memory[i] != nullptr)
			this->Memory[i] = other.Memory[i]->clone();
		else
			this->Memory[i] = nullptr;
	}
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void MateriaSource::learnMateria(AMateria* amateria)
{
	if (this->Memory[this->mem_index] != nullptr)
		delete this->Memory[this->mem_index];
	this->Memory[this->mem_index] = amateria->clone();
	mem_index = (mem_index + 1) % 4;
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	for(int i = 0; i < 4; i++)
	{
		if (this->Memory[i] != nullptr && type == this->Memory[i]->getType())
			return this->Memory[i]->clone();
	}
	return 0;
}
