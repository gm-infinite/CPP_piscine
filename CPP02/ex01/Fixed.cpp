
#include "Fixed.hpp"

Fixed::Fixed(const int value)
{
	std::cout << "Int constructor called" << std::endl;
	this->setRawBits(value<<8);
}

Fixed::Fixed(const float value)
{
	std::cout << "Float constructor called" << std::endl;
	this->setRawBits(static_cast<int>(roundf(value * 256)));
}

Fixed::Fixed(void) : FPNumberValue(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called" << std::endl;
	this->FPNumberValue = other.getRawBits();
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;

	if (this != &other)
		this->FPNumberValue = other.getRawBits();
	return *this;
}

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

std::ostream& operator<<(std::ostream& os, const Fixed& obj) 
{
    os << obj.toFloat();  
    return os;
}