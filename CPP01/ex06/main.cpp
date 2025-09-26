
#include "Harl.hpp"

int main(int ac, char** av)
{
	if (ac == 2)
	{
		std::string level_str(av[1]);
		int level = 100;
		std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
		Harl harl;
		for(int i = 0; i < 4; i++)
		{
			if (level_str == levels[i])
			{
				level = i;
				break;
			}
		}
		switch (level)
		{
		case (0):
			std::cout << "[ DEBUG ]" << std::endl;
			harl.complain("DEBUG");
			std::cout << std::endl;
		case (1):
			std::cout << "[ INFO ]" << std::endl;
			harl.complain("INFO");
			std::cout << std::endl;
		case (2):
			std::cout << "[ WARNING ]" << std::endl;
			harl.complain("WARNING");
			std::cout << std::endl;
		case (3):
			std::cout << "[ ERROR ]" << std::endl;
			harl.complain("ERROR");
			std::cout << std::endl;
			break;
		default:
		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			break;
		}
	}
}