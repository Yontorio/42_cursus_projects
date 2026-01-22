#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main(void)
{
    Point a(0, 0);
    Point b(8, 0);
    Point c(0, 8);

    Point p1(2, 2);
    Point p2(8, 8);
    Point p3(0, 4);
    Point p4(4, 4);
    Point p5(3.3, 1.5);

    std::cout << std::boolalpha;
    std::cout << bsp(a, b, c, p1) << std::endl;
    std::cout << bsp(a, b, c, p2) << std::endl;
    std::cout << bsp(a, b, c, p3) << std::endl;
    std::cout << bsp(a, b, c, p4) << std::endl;
    std::cout << bsp(a, b, c, p5) << std::endl;

    return 0;
}
