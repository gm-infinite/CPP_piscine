
#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap{

public:
	FragTrap(void);
	FragTrap(const std::string& Name);
	~FragTrap(void);
	FragTrap(const FragTrap& other);
	FragTrap& operator=(const FragTrap& other);

	void Attack(const std::string& target);
	void highFivesGuys(void) const;
	
private:

};

#endif /* FragTRAP_HPP */
