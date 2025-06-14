
#include "Harl.hpp"

int main(int ac, char** av)
{
	if (ac == 2)
	{
		std::string level_str(av[1]);
		int level = 100;
		Harl harl;
		if (level_str == "DEBUG")
			level = 0;
		else if (level_str == "INFO")
			level = 1;
		else if (level_str == "WARNING")
			level = 2;
		else if (level_str == "ERROR")
			level = 3;

		switch (level)
		{
		case (0):
			harl.complain("DEBUG");
			// fall through
		case (1):
			harl.complain("INFO");
			// fall through
		case (2):
			harl.complain("WARNING");
			// fall through
		case (3):
			harl.complain("ERROR");
			break;
		default:
		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			break;
		}
	}
}