
#include "Fixed.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */

Fixed::Fixed(const int value) : FPNumberValue(value<<8)
{ }

Fixed::Fixed(const float value) : FPNumberValue(static_cast<int>(roundf(value * 256)))
{ }

Fixed::Fixed(void) : FPNumberValue(0)
{ }

Fixed::Fixed(const Fixed& other) : FPNumberValue(other.getRawBits())
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Fixed::~Fixed(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

// = overload for Fixed class
Fixed& Fixed::operator=(const Fixed& other)
{
	if (this != &other)
		this->setRawBits(other.getRawBits());
	return *this;
}

// + overload for Fixed class
Fixed Fixed::operator+(const Fixed& other) const
{
	Fixed ret;
	ret.setRawBits(this->getRawBits() + other.getRawBits());
	return ret;
}

// - overload for Fixed class
Fixed Fixed::operator-(const Fixed& other) const
{
	Fixed ret;
	ret.setRawBits(this->getRawBits() - other.getRawBits());
	return ret;
}

// * overload for Fixed class
Fixed Fixed::operator*(const Fixed& other) const
{
	long mult;
	Fixed ret ;
	mult = (static_cast<long>(this->getRawBits()) * other.getRawBits());
	ret.setRawBits(static_cast<int>(mult>>8));
	return ret;
}

// / overload for Fixed class
Fixed Fixed::operator/(const Fixed& other) const
{
	long div;
	Fixed ret ;
	div = (((static_cast<long>(this->getRawBits())) << 8) / other.getRawBits());
	ret.setRawBits(static_cast<int>(div));
	return ret;
}

// == overload for Fixed class
bool Fixed::operator==(const Fixed& other) const
{
	return (this->getRawBits() == other.getRawBits());
}

// <= overload for Fixed class
bool Fixed::operator<=(const Fixed& other) const
{
	return (this->getRawBits() <= other.getRawBits());
}

// >= overload for Fixed class
bool Fixed::operator>=(const Fixed& other) const
{
	return (this->getRawBits() >= other.getRawBits());
}

// != overload for Fixed class
bool Fixed::operator!=(const Fixed& other) const
{
	return (this->getRawBits() != other.getRawBits());
}

// < overload for Fixed class
bool Fixed::operator<(const Fixed& other) const
{
	return (this->getRawBits() < other.getRawBits());
}

// > overload for Fixed class
bool Fixed::operator>(const Fixed& other) const
{
	return (this->getRawBits() > other.getRawBits());
}

// i++ overload for Fixed class
Fixed& Fixed::operator++()
{
	this->setRawBits(this->getRawBits() + 1);
    return *this;
}

// ++i overload for Fixed class
Fixed Fixed::operator++(int)
{
	Fixed old(*this);
	this->setRawBits(this->getRawBits() + 1);
	return old;
}

// i-- overload for Fixed class
Fixed& Fixed::operator--()
{
	this->setRawBits(this->getRawBits() - 1);
    return *this;
}

// --i overload for Fixed class
Fixed Fixed::operator--(int)
{
	Fixed old(*this);
	this->setRawBits(this->getRawBits() - 1);
	return old;
}

// min(a,b) overloaded for Fixed class
Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	if (a < b)
		return a;
	return b;
}

// max(a,b) overloaded for Fixed class
Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	if (a > b)
		return a;
	return b;
}

// const min(a,b) overloaded for Fixed class
const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	if (a < b)
		return a;
	return b;
}

// const max(a,b) overloaded for Fixed class
const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	if (a > b)
		return a;
	return b;
}

Fixed Fixed::operator-() const
{
    Fixed ret;
    ret.setRawBits(-this->getRawBits());
    return ret;
}

// << overload for Fixed class
std::ostream& operator<<(std::ostream& os, const Fixed& obj) 
{
    os << obj.toFloat();  
    return os;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

float Fixed::toFloat( void ) const
{
	return (this->getRawBits() / 256.0f);
}

int Fixed::toInt( void ) const
{
	return this->getRawBits() >> 8;
}

int Fixed::getRawBits( void ) const //this const here is so that any const Fixed ... object can use this fucntion without trowing complier error, it shows that this function will not modify the objects its called upon
{
	return this->FPNumberValue;
}

void Fixed::setRawBits( int const raw )
{
	this->FPNumberValue = raw;
}
