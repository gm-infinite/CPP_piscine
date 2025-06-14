#pragma once
#ifndef POINT_HPP
#define POINT_HPP
#include "Fixed.hpp"


class Point {

public:

	Point(void);
	Point(Fixed x, Fixed y);
	~Point(void);
	Point(const Point& other);

	Point& operator=(const Point& other);

	const Fixed& getY() const;
	const Fixed& getX() const;
	void setY(const Fixed& y);
	void setX(const Fixed& x);
	
	static Fixed dotProduct(const Point& a,const Point& b);
	static Point Perpendicular(const Point& b);
	static bool isonrightside(const Point& a, const Point& b, const Point& point);

private:
		Fixed X;
		Fixed Y;

};

bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif /* POINT_HPP */