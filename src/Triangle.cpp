#include "Triangle.h"

Triangle::Triangle(GameMain* gameMain, const Point& p1, const Point& p2, const Point& p3, const float color[3])
    : Shape(gameMain, { p1, p2, p3 }, color)
{
}
