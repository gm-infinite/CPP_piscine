
#include "Harl.hpp"

int main(int ac, char** av)
{
	std::string level;
	Harl harl;
	for (int i = 1; i < ac; i++)
	{
		level.assign(av[i]);
		harl.complain(level);
	}
}