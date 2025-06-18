
#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
public:
	
	FragTrap(void);
	FragTrap(const std::string& Name);
	~FragTrap(void);
	FragTrap(const FragTrap& other);
	FragTrap& operator=(const FragTrap& other);

	void Attack(const std::string& target);
	void highFivesGuys(void) const;

	static int GetDefaultHitpoints();
	static int GetDefaultEnergypoints();
	static int GetDefaultAttackdamage();
	
	private:
		static const int default_hitpoints = 100;
		static const int default_energypoints = 100;
		static const int default_attackdamage = 30;
};


#endif /* FragTRAP_HPP */