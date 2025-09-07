
#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <string>
#include <iostream>

class ClapTrap {

public:
	ClapTrap(void);
	ClapTrap(const std::string& Name);
	~ClapTrap(void);
	ClapTrap(const ClapTrap& other);
	ClapTrap& operator=(const ClapTrap& other);

	const std::string& GetName(void) const;
	int GetHitpoints(void) const;
	int GetEnergypoints(void) const;
	int GetAttackdamage(void) const;

	void SetName(const std::string& Name);
	void SetHitpoints(const int Hit_points);
	void SetEnergypoints(const int Energy_points);
	void SetAttackdamage(const int Attack_damage);

	void Attack(const std::string& target);
	void TakeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

private:
	std::string Name;
	int Hit_points;
	int Energy_points;
	int Attack_damage;

};

#endif /* CLAPTRAP_HPP */
