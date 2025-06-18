
#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap {

public:
	DiamondTrap(void);
	DiamondTrap(const std::string& Name);
	~DiamondTrap(void);
	DiamondTrap(const DiamondTrap& other);
	DiamondTrap& operator=(const DiamondTrap& other);

	const std::string& GetName(void) const;
	void SetName(const std::string& Name);

	void Attack(const std::string& target);
	void whoAmI(void) const;
	

private:
	std::string Name;

};

#endif /* DIAMONDTRAP_HPP */