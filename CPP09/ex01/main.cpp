
#include "RPN.hpp"

int main (int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Error: invalid arguments. Usage: ./RPN <expression>" << std::endl;
		return 1;
	}
	if(!input_validator(av[1]))
		return 1;
	std::cout << RPN_calculator(av[1]) << std::endl;
	return 0;
}