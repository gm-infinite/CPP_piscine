
#include "Fixed.hpp"

int main( void ) {

		std::cout << std::endl << "########### a and b are NOT equal ###########"<< std::endl;
{
	Fixed a(45.66f);
	Fixed b(299.34f);

	if (b > a)
		std::cout << "if this text is visible than " << b << " > " << a << " returned true" << std::endl;
	if (a < b)
		std::cout << "if this text is visible than " << a << " < " << b << " returned true"<< std::endl;
	if (a >= b)
		std::cout << "if this text is visible than " << a << " >= " << b << " returned true"<< std::endl;
	if (a <= b)
		std::cout << "if this text is visible than " << a << " <= " << b << " returned true"<< std::endl;
	if (a == b)
		std::cout << "if this text is visible than " << a << " == " << b << " returned true"<< std::endl;
	if (a != b)
		std::cout << "if this text is visible than " << a << " != " << b << " returned true"<< std::endl;
}
	std::cout << std::endl << "########### a and b are equal ###########"<< std::endl;
{
	Fixed a(42.424242f);
	Fixed b( a );

	if (a > b)
		std::cout << "if this text is visible than " << a << " > " << b << " returned true"<< std::endl;
	if (a < b)
		std::cout << "if this text is visible than " << a << " < " << b << " returned true"<< std::endl;
	if (a >= b)
		std::cout << "if this text is visible than " << a << " >= " << b << " returned true"<< std::endl;
	if (a <= b)
		std::cout << "if this text is visible than " << a << " <= " << b << " returned true"<< std::endl;
	if (a == b)
		std::cout << "if this text is visible than " << a << " == " << b << " returned true"<< std::endl;
	if (a != b)
		std::cout << "if this text is visible than " << a << " != " << b << " returned true"<< std::endl;
}

std::cout << std::endl << "########### a and b arithmetic operators ###########"<< std::endl;
{
	Fixed a(5.2f);
	Fixed b( 5 );

	
	std::cout << "value of a is " << a << std::endl;
	std::cout << "value of b is " << b << std::endl;
	std::cout << "value of a + b is " << a + b << std::endl;
	std::cout << "value of a - b is " << a - b << std::endl;
	std::cout << "value of a * b is " << a * b << std::endl;
	std::cout << "value of a / b is " << a / b << std::endl;
}

std::cout << std::endl << "########### a increment/decrement operators ###########"<< std::endl;
{
	Fixed a(0);

	std::cout << "value of a is " << a << std::endl;
	std::cout << "when a++ in cout the new value is here: " << a++ << std::endl;
	std::cout << "value of a is " << a << std::endl;
	std::cout << "when ++a in cout the new value is here: " << ++a << std::endl;
	std::cout << "value of a is " << a << std::endl;
	std::cout << "when a-- in cout the new value is here: " << a-- << std::endl;
	std::cout << "value of a is " << a << std::endl;
	std::cout << "when --a in cout the new value is here: " << --a << std::endl;
	std::cout << "value of a is " << a << std::endl;

}

std::cout << std::endl << "########### a min/max operators ###########"<< std::endl;
{
	Fixed a(34);
	Fixed b( 2 );

	
	std::cout << "value of a is " << a << std::endl;
	std::cout << "value of b is " << b << std::endl;
	std::cout << "value of min(a,b) is " << Fixed::min(a,b) << std::endl;
	std::cout << "value of max(a,b) is " << Fixed::max(a,b) << std::endl;

}

std::cout << std::endl << "########### a min/max operators ###########"<< std::endl;
{
	const Fixed a(34);
	const Fixed b( 2 );

	
	std::cout << "value of a is " << a << std::endl;
	std::cout << "value of b is " << b << std::endl;
	std::cout << "value of min(a,b) is " << Fixed::min(a,b) << std::endl;
	std::cout << "value of max(a,b) is " << Fixed::max(a,b) << std::endl;

}

return 0;
}
