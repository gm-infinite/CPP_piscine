
#include "Zombie.hpp"

int main(void)
{
	Zombie *newZombiek;
	
	newZombiek = newZombie("kuzyilma");
	newZombiek->announce();
	randomChump("emgenc");
	delete newZombiek;
	return (0);
}