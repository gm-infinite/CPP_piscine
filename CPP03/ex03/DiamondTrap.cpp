
#include "DiamondTrap.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
DiamondTrap::DiamondTrap(void) :
ClapTrap(),
FragTrap(),
ScavTrap(),
Name("Default")
{
	this->SetName("Default_clap_name");
	this->SetAttackdamage(FragTrap::GetDefaultAttackdamage());
	this->SetEnergypoints(ScavTrap::GetDefaultEnergypoints());
	this->SetHitpoints(FragTrap::GetDefaultHitpoints());
	std::cout << "DiamondTrap Default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& Name) : 
ClapTrap(),
FragTrap(),
ScavTrap(),
Name(Name)
{
	this->ClapTrap::SetName(Name + "_clap_name");
	this->SetAttackdamage(FragTrap::GetDefaultAttackdamage());
	this->SetEnergypoints(ScavTrap::GetDefaultEnergypoints());
	this->SetHitpoints(FragTrap::GetDefaultHitpoints());
	std::cout << "DiamondTrap String input constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) :
ClapTrap(),
FragTrap(),
ScavTrap(),
Name(other.GetName())
{
	this->SetName(other.ClapTrap::GetName());
	this->SetHitpoints(other.GetHitpoints());
	this->SetEnergypoints(other.GetEnergypoints());
	this->SetAttackdamage(other.GetAttackdamage());
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
		ClapTrap::operator=(other);
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