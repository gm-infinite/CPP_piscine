
#include "strReplace.hpp"

int main(int ac, char **av)
{
	if (ac == 4)
	{
		std::string filename(av[1]);
		std::string	s1(av[2]);
		std::string	s2(av[3]);
		
		strreplace(filename, s1, s2);
	}
	else
	{
		std::cerr << "Usage: " << av[0] << " <filename> <string_to_replace> <replacement_string>" << std::endl;
		return (1);
	}
	return (0);
}