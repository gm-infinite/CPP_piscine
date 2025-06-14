

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
	Fixed operator+(const Fixed& other) const;
	Fixed operator-(const Fixed& other) const;
	Fixed operator*(const Fixed& other) const;
	Fixed operator/(const Fixed& other) const;

	bool operator==(const Fixed& other) const;
	bool operator<=(const Fixed& other) const;
	bool operator>=(const Fixed& other) const;
	bool operator!=(const Fixed& other) const;
	bool operator<(const Fixed& other) const;
	bool operator>(const Fixed& other) const;

	Fixed& operator++();
	Fixed operator++(int);
	Fixed& operator--();
	Fixed operator--(int);
	Fixed operator-() const;

	int getRawBits( void ) const;
	void setRawBits( int const raw );
	float toFloat( void ) const;
	int toInt( void ) const;
	
	static Fixed& min(Fixed& a, Fixed& b);
	static Fixed& max(Fixed& a, Fixed& b);
	static const Fixed& min(const Fixed& a, const Fixed& b);
	static const Fixed& max(const Fixed& a, const Fixed& b);
	
private:
		int FPNumberValue;
		static const int Fractional_Bits = 8;

};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif /* FIXED_HPP */