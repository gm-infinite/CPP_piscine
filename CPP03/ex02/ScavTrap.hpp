
#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap{

public:
	ScavTrap(void);
	ScavTrap(const std::string& Name);
	~ScavTrap(void);
	ScavTrap(const ScavTrap& other);
	ScavTrap& operator=(const ScavTrap& other);

	void GuardGate(void) const;
	void Attack(const std::string& target);

private:

};

#endif /* SCAVTRAP_HPP */
