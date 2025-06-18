
#include "ScavTrap.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
ScavTrap::ScavTrap(void) : 
ClapTrap("Default", 100, 50, 20)
{
	std::cout << "ScavTrap Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : 
ClapTrap(other)
{
	std::cout << "ScavTrap Copy constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string& Name) : 
ClapTrap(Name, 100, 50, 20)
{
	std::cout << "ScavTrap String input constructor called" << std::endl;
}


/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap Deconstructor called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << "ScavTrap copy assignment (operator=) is called" << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void ScavTrap::Attack(const std::string& Target)
{
	int energypoints = this->GetEnergypoints();
	const std::string& name = this->GetName();

	if (this->GetHitpoints() < 1)
		std::cout << "ScavTrap " << name << " can't do anything because it has no Hit points" << std::endl;
	else if (energypoints < 1)
		std::cout << "ScavTrap " << name << " can't do anything because it has no Energy points" << std::endl;
	else
	{
		std::cout << "ScavTrap " << name << " attacks " << Target << ", causing " << this->GetAttackdamage() << " points of damage" << '\n'
				  << "ScavTrap " << name << " used an energy point and has " << energypoints - 1 << " energy points left to use" << std::endl;
		this->SetEnergypoints(energypoints - 1);
	}
}


void ScavTrap::GuardGate(void) const
{
	if (this->GetHitpoints() < 1)
		std::cout << "ScavTrap " << this->GetName() << " can't do anything because it has no Hit points" << std::endl;
	else
		std::cout << "ScavTrap " << this->GetName() << " is now on gate keeper mode" << std::endl;
}