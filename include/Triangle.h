#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class GAMEBASELIB_API Triangle : public Shape {
public:
    Triangle(GameMain* gameMain, const Point& p1, const Point& p2, const Point& p3, const float color[3]);

};

#endif // TRIANGLE_H