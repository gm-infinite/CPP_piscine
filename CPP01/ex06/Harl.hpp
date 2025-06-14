#pragma once
#ifndef HARL_HPP
#define HARL_HPP
#include <string>
#include <iostream>

class Harl
{
	private:
		typedef void (Harl::*Harlfuncs)(); // the reason its in private is that so not anyone that includes Harl.hpp gets this typedef, its only made to be used in Harl.cpp

		void debug( void );
		void info( void );
		void warning( void );
		void error( void );

	public:
		Harl();
		~Harl();
		void complain( std::string level );
};

#endif /* HARL_HPP */

