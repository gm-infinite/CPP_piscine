
#include "Point.hpp"

static bool isTriangle(const Point& a, const Point& b, const Point& c) {
    Fixed area = a.getX() * (b.getY() - c.getY()) +
                 b.getX() * (c.getY() - a.getY()) +
                 c.getX() * (a.getY() - b.getY());
    return area != Fixed(0);
}

bool bsp( Point const a, Point const b, Point const c, Point const point)
{
	if (!isTriangle(a, b, c))
	{
		std::cerr << "(the points does not make a triangle, so always outside) ";
		return false;
	}
    bool side1 = Point::isonrightside(a, b, point);
    bool side2 = Point::isonrightside(b, c, point);
    bool side3 = Point::isonrightside(c, a, point);

    return (side1 == side2) && (side2 == side3);
}