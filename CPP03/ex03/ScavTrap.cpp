
#include "ScavTrap.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
ScavTrap::ScavTrap(void)
{
	this->SetName("Default");
	this->SetHitpoints(this->default_hitpoints);
	this->SetEnergypoints(this->default_energypoints);
	this->SetAttackdamage(this->default_attackdamage);
	std::cout << "ScavTrap Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) :
	ClapTrap(other)
{
	this->SetName(other.GetName());
	this->SetHitpoints(other.GetHitpoints());
	this->SetEnergypoints(other.GetEnergypoints());
	this->SetAttackdamage(other.GetAttackdamage());
	std::cout << "ScavTrap Copy constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string& Name)
{
	this->SetName(Name);
	this->SetHitpoints(this->default_hitpoints);
	this->SetEnergypoints(this->default_energypoints);
	this->SetAttackdamage(this->default_attackdamage);
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

int ScavTrap::GetDefaultHitpoints() {
	return default_hitpoints;
}

int ScavTrap::GetDefaultEnergypoints() {
	return default_energypoints;
}

int ScavTrap::GetDefaultAttackdamage() {
	return default_attackdamage;
}