
#include "Point.hpp"

int main()
{
    {
        std::cout << "=== BSP Test ===\n";

        Point a(Fixed(0), Fixed(0));
        Point b(Fixed(10), Fixed(0));
        Point c(Fixed(0), Fixed(10));
        
        Point inside(Fixed(3), Fixed(3));
        Point outside(Fixed(10), Fixed(10));
        Point vertex(Fixed(0), Fixed(0));
        Point onEdge(Fixed(5), Fixed(0));

        std::cout << "Inside point: " << (bsp(a, b, c, inside) ? "inside\n" : "outside\n");
        std::cout << "Outside point: " << (bsp(a, b, c, outside) ? "inside\n" : "outside\n");
        std::cout << "Vertex point: " << (bsp(a, b, c, vertex) ? "inside\n" : "outside\n");
        std::cout << "On edge point: " << (bsp(a, b, c, onEdge) ? "inside\n" : "outside\n");
    }

    std::cout << "\n";

    {
        std::cout << "=== Triangle Existence Test ===\n";

        Point p1(Fixed(0), Fixed(0));
        Point p2(Fixed(1), Fixed(1));
        Point p3(Fixed(2), Fixed(2)); // Collinear points

        Point p4(Fixed(0), Fixed(0));
        Point p5(Fixed(1), Fixed(0));
        Point p6(Fixed(0), Fixed(1)); // Proper triangle

		Point point(Fixed(0.5f), Fixed(0.5f));

        std::cout << "p1, p2, p3: " << (bsp(p1, p2, p3, point) ? "inside\n" : "outside\n");
        std::cout << "p4, p5, p6: " << (bsp(p4, p5, p6, point) ? "inside\n" : "outside\n");
    }

    return 0;
}