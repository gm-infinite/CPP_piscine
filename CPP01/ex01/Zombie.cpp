
#include "Zombie.hpp"
#include <iostream>

void Zombie::announce( void )
{
	std::cout 	<< this->name
			  	<< ": BraiiiiiiinnnzzzZ..."
				<< std::endl;
}
Zombie::Zombie (void)
{
	this->name = "zombie";
}

Zombie::Zombie (std::string name)
{
	this->name = name;
}

Zombie::~Zombie()
{
	std::cout 	<< this->name << ": called deconstructor (got destroyed)"
				<< std::endl;
}

void Zombie::setName(std::string name)
{
	this->name = name;
}