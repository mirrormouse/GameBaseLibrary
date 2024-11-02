#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"

class GAMEBASELIB_API Rectangle : public Shape {
public:
    Rectangle(GameMain* gameMain, const Point& topLeft, float width, float height, const float color[3]);

private:
    float width;
    float height;
};

#endif // RECTANGLE_H