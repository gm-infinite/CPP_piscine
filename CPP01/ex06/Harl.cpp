
#include "Harl.hpp"

void Harl::debug( void )
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info( void )
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning( void )
{
	std::cout << "I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month." << std::endl;
}

void Harl::error( void )
{
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

Harl::Harl()
{}

Harl::~Harl()
{}

void Harl::complain( std::string level )
{
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	Harlfuncs level_functions[] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error}; // same as writing void (Harl::*level_functions[])() = ...

	for (int i = 0; i < 4; i++)
	{
		if (level == levels[i])
		{
			(this->*level_functions[i])();
			return ;
		}
	}
	std::cout << "invalid string input for complain, please enter one of the following: DEBUG, INFO, WARNING, ERROR" << std::endl;
}