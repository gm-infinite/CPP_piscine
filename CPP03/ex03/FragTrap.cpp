
#include "FragTrap.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
FragTrap::FragTrap(void)
{
	this->SetName("Default");
	this->SetHitpoints(this->default_hitpoints);
	this->SetEnergypoints(this->default_energypoints);
	this->SetAttackdamage(this->default_attackdamage);
	std::cout << "FragTrap Default constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : 
ClapTrap(other)
{
	this->SetName(other.GetName());
	this->SetHitpoints(other.GetHitpoints());
	this->SetEnergypoints(other.GetEnergypoints());
	this->SetAttackdamage(other.GetAttackdamage());
	std::cout << "FragTrap Copy constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string& Name)
{
	this->SetName(Name);
	this->SetHitpoints(this->default_hitpoints);
	this->SetEnergypoints(this->default_energypoints);
	this->SetAttackdamage(this->default_attackdamage);
	std::cout << "FragTrap String input constructor called" << std::endl;
}


/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap Deconstructor called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << "FragTrap copy assignment (operator=) is called" << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void FragTrap::Attack(const std::string& Target)
{
	int energypoints = this->GetEnergypoints();
	const std::string& name = this->GetName();

	if (this->GetHitpoints() < 1)
		std::cout << "FragTrap " << name << " can't do anything because it has no Hit points" << std::endl;
	else if (energypoints < 1)
		std::cout << "FragTrap " << name << " can't do anything because it has no Energy points" << std::endl;
	else
	{
		std::cout << "FragTrap " << name << " attacks " << Target << ", causing " << this->GetAttackdamage() << " points of damage" << '\n'
				  << "FragTrap " << name << " used an energy point and has " << energypoints - 1 << " energy points left to use" << std::endl;
		this->SetEnergypoints(energypoints - 1);
	}
}

void FragTrap::highFivesGuys(void) const
{
	if (this->GetHitpoints() < 1)
		std::cout << "FragTrap " << this->GetName() << " can't do anything because it has no Hit points" << std::endl;
	else
		std::cout << "Fragtrap " << this->GetName() << " request a high five from the guys" << std::endl;
}

int FragTrap::GetDefaultHitpoints() {
	return default_hitpoints;
}

int FragTrap::GetDefaultEnergypoints() {
	return default_energypoints;
}

int FragTrap::GetDefaultAttackdamage() {
	return default_attackdamage;
}
