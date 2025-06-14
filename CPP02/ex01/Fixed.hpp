

#pragma once
#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>
#include <cmath>


class Fixed {

public:

	Fixed(void);
	~Fixed(void);
	Fixed(const int value);
	Fixed(const float value);
	Fixed(const Fixed& other);

	Fixed& operator=(const Fixed& other);
	float toFloat( void ) const;
	int toInt( void ) const;
	int getRawBits( void ) const;
	void setRawBits( int const raw );

private:
		int FPNumberValue;
		static const int Fractional_Bits = 8;

};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif /* FIXED_HPP */