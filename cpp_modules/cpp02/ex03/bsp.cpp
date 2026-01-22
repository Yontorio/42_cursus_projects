#include "Point.hpp"

static Fixed sign(Point const &p1, Point const &p2, Point const &p3)
{
    return (p1.getX() - p3.getX()) * (p2.getY() - p3.getY())
         - (p2.getX() - p3.getX()) * (p1.getY() - p3.getY());
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
    Fixed d1 = sign(point, a, b);
    Fixed d2 = sign(point, b, c);
    Fixed d3 = sign(point, c, a);

    bool all_neg = (d1 < Fixed(0)) && (d2 < Fixed(0)) && (d3 < Fixed(0));
    bool all_pos = (d1 > Fixed(0)) && (d2 > Fixed(0)) && (d3 > Fixed(0));

    if (all_neg || all_pos)
        return true;

    return false;
}
