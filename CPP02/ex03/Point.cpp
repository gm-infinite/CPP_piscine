
#include "Point.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */

Point::Point(void) : X(0), Y(0) 
{ }

Point::Point(Fixed x, Fixed y) : X(x), Y(y) 
{ }

Point::Point(const Point& other) : X(other.getX()), Y(other.getY())
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Point::~Point(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Point& Point::operator=(const Point& other)
{
	if (this != &other)
	{
		this->setX(other.getX());
		this->setY(other.getY());
	}
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

const Fixed& Point::getY() const
{
	return this->Y;
}

const Fixed& Point::getX() const
{
	return this->X;
}

void Point::setY(const Fixed& y)
{
	this->Y = y;
}

void Point::setX(const Fixed& x)
{
	this->X = x;
}

Fixed Point::dotProduct(const Point& a,const Point& b)
{
	return (a.getX() * b.getX()) + (a.getY() * b.getY());
}

Point Point::Perpendicular(const Point& b)
{
	Point ret(b.getY(), -b.getX());
	return ret;
}

bool Point::isonrightside(const Point& a, const Point& b, const Point& point)
{
    Point ab(b.getX() - a.getX(), b.getY() - a.getY());
    Point ap(point.getX() - a.getX(), point.getY() - a.getY());

    return (Point::dotProduct(ap, Point::Perpendicular(ab)) > Fixed());
}