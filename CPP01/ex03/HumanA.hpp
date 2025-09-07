#pragma once
#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanA {

public:
	
	HumanA(std::string name, Weapon& weapon);
	~HumanA();
	void attack();

private:

	std::string name;
	Weapon& weapon;

};



#endif /* HUMANA_HPP */
