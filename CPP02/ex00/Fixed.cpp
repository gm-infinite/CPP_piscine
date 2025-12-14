
#include "Fixed.hpp"

Fixed::Fixed(void) : FPNumberValue(0)
{ 
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called" << std::endl;
	this->FPNumberValue = other.getRawBits();
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;

	if (this != &other)
		this->setRawBits(other.getRawBits());
	return *this;
}

int Fixed::getRawBits( void ) const //this const here is so that any const Fixed ... object can use this fucntion without trowing complier error, it shows that this function will not modify the objects its called upon
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->FPNumberValue;
}

void Fixed::setRawBits( int const raw )
{
	this->FPNumberValue = raw;
}