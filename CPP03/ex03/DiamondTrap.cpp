
#include "DiamondTrap.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
DiamondTrap::DiamondTrap(void) :
ClapTrap("Default_clap_name", FragTrap::GetDefaultHitpoints(), ScavTrap::GetDefaultEnergypoints(), FragTrap::GetDefaultAttackdamage()),
FragTrap(),
ScavTrap(),
Name("Default")
{
	std::cout << "DiamondTrap Default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& Name) : 
ClapTrap(Name + "_clap_name", FragTrap::GetDefaultHitpoints(), ScavTrap::GetDefaultEnergypoints(), FragTrap::GetDefaultAttackdamage()),
FragTrap(),
ScavTrap(),
Name(Name)
{
	std::cout << "DiamondTrap String input constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) :
ClapTrap(other),
FragTrap(),
ScavTrap(),
Name(other.GetName())
{
	std::cout << "DiamondTrap Copy constructor called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

DiamondTrap::~DiamondTrap(void)
{
	std::cout << "DiamondTrap Deconstructor called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
	std::cout << "DiamondTrap copy assignment (operator=) is called" << std::endl;
	if (this != &other)
	{
		ClapTrap::operator=(other);
		this->Name = other.Name;
	}
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void DiamondTrap::Attack(const std::string& Target)
{
	ScavTrap::Attack(Target);
}

void DiamondTrap::whoAmI(void) const
{
	std::cout << "my name is " << this->GetName() << ",\nmy ClapTrap name is " << this->ClapTrap::GetName() << std::endl;	
}

const std::string& DiamondTrap::GetName(void) const {
	return this->Name;
}

void DiamondTrap::SetName(const std::string& Name) {
	this->Name = Name;
}
