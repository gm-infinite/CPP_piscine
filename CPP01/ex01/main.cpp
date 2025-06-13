
#include "Zombie.hpp"

int main(void)
{
	Zombie *zombiehorde1 = zombieHorde(5, "kuzey");
	Zombie *zombiehorde2 = zombieHorde(3, "emir");

	for (int i = 0; i < 5; i++)
		zombiehorde1[i].announce();
	delete[] zombiehorde1;
	
	for (int i = 0; i < 3; i++)
		zombiehorde2[i].announce();
	delete[] zombiehorde2;
	
}