
#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap{

public:
	ScavTrap(void);
	ScavTrap(const std::string& Name);
	~ScavTrap(void);
	ScavTrap(const ScavTrap& other);
	ScavTrap& operator=(const ScavTrap& other);

	void GuardGate(void) const;
	void Attack(const std::string& target);

	static int GetDefaultHitpoints();
	static int GetDefaultEnergypoints();
	static int GetDefaultAttackdamage();

	
private:
	static const int default_hitpoints = 100;
	static const int default_energypoints = 50;
	static const int default_attackdamage = 20;

};

#endif /* SCAVTRAP_HPP */