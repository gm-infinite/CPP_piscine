

#pragma once
#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>


class Fixed {

public:

	Fixed(void);
	~Fixed(void);
	Fixed(const Fixed& other);
	Fixed& operator=(const Fixed& other);
	int getRawBits( void ) const;
	void setRawBits( int const raw );

private:
		int FPNumberValue;
		static const int Fractional_Bits = 8;

};


#endif /* FIXED_HPP */