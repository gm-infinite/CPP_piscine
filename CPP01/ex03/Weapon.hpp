#pragma once
#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <string>


class Weapon {

public:

	const std::string& getType(void) const;
	void setType(std::string type);
	Weapon(std::string type);
	~Weapon();

private:

	std::string type;

};



#endif /* WEAPON_HPP */