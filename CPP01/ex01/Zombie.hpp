


#pragma once
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <string>


class Zombie {

public:

	void announce( void );
	void setName(std::string name);
	
	Zombie (std::string name);
	Zombie ();
	~Zombie();

private:

	std::string name;


};

Zombie* zombieHorde( int N, std::string name );


#endif /* __ZOMBIE_HPP__ */
