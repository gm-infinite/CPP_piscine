
#include "Weapon.hpp"

Weapon::Weapon(std::string type)
{
	setType(type);
}

Weapon::~Weapon(){}

const std::string& Weapon::getType(void) const
{
	const std::string& typeREF = this->type;

	return typeREF;
}

void Weapon::setType(std::string type)
{
	this->type = type;
}