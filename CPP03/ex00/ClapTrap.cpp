#include "ClapTrap.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */

ClapTrap::ClapTrap(void) : 
Name("Default"), 
Hit_points(10), 
Energy_points(10), 
Attack_damage(0)
{
	std::cout << "ClapTrap Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& Name) : 
Name(Name), 
Hit_points(10), 
Energy_points(10), 
Attack_damage(0)
{
	std::cout << "ClapTrap String input constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) : 
Name(other.GetName()), 
Hit_points(other.GetHitpoints()), 
Energy_points(other.GetEnergypoints()), 
Attack_damage(other.GetAttackdamage())
{
	std::cout << "ClapTrap Copy constructor called" << std::endl;
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap Deconstructor called" << std::endl;
}

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	this->SetName(other.GetName());
	this->SetHitpoints(other.GetHitpoints());
	this->SetEnergypoints(other.GetEnergypoints());
	this->SetAttackdamage(other.GetAttackdamage());
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void ClapTrap::Attack(const std::string& Target)
{
	int energypoints = this->GetEnergypoints();
	const std::string& name = this->GetName();

	if (this->GetHitpoints() < 1)
		std::cout << name << " can't do anything because it has no Hit points" << std::endl;
	else if (energypoints < 1)
		std::cout << name << " can't do anything because it has no Energy points" << std::endl;
	else
	{
		std::cout << name << " attacks " << Target << ", causing " << this->GetAttackdamage() << " points of damage" << '\n'
				  << name << " used an enegy point and has " << energypoints - 1 << " energy points left to use" << std::endl;
		this->SetEnergypoints(energypoints - 1);
	}
}

void ClapTrap::TakeDamage(unsigned int amount)
{
	int hitpoints = this->GetHitpoints();
	const std::string& name = this->GetName();

	if (hitpoints < 1)
		std::cout << name << " already has 0 Hit points left, takes " << amount << " damage but this doesn't effect anything" << std::endl;
	else
	{
		int after_damage_HP = hitpoints - amount;

		after_damage_HP = after_damage_HP < 0 ? 0 : after_damage_HP;
		this->SetHitpoints(after_damage_HP);
		std::cout << name << " takes " << amount << " damage, it has " << after_damage_HP << " Hit points left" << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	int hitpoints = this->GetHitpoints();
	int energypoints = this->GetEnergypoints();
	const std::string& name = this->GetName();

	if (hitpoints < 1)
		std::cout << name << " can't do anything because it has no Hit points" << std::endl;
	else if (energypoints < 1)
		std::cout << name << " can't do anything because it has no Energy points" << std::endl;
	else
	{
		hitpoints += amount;
		std::cout << name << " repaired itself by " << amount << ", it now has " << hitpoints << " Hit points" << '\n'
				  << name << " used an enegy point and has " << energypoints - 1 << " energy points left to use" << std::endl;
		this->SetHitpoints(hitpoints);
		this->SetEnergypoints(energypoints - 1);
	}
}

const std::string& ClapTrap::GetName(void) const
{
	return this->Name;
}

int ClapTrap::GetHitpoints(void) const
{
	return this->Hit_points;
}

int ClapTrap::GetEnergypoints(void) const
{
	return this->Energy_points;
}

int ClapTrap::GetAttackdamage(void) const
{
	return this->Attack_damage;
}

void ClapTrap::SetName(const std::string& Name)
{
	this->Name = Name;
}

void ClapTrap::SetHitpoints(const int Hit_points)
{
	this->Hit_points = Hit_points;
}

void ClapTrap::SetEnergypoints(const int Energy_points)
{
	this->Energy_points = Energy_points;
}

void ClapTrap::SetAttackdamage(const int Attack_damage)
{
	this->Attack_damage = Attack_damage;
}
