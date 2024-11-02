#include "Rectangle.h"
#include<iostream>

Rectangle::Rectangle(GameMain* gameMain, const Point& topLeft, float width, float height, const float color[3])
    : Shape(gameMain, {
        topLeft,
        {topLeft.x + width, topLeft.y},
        {topLeft.x + width, topLeft.y + height},
        {topLeft.x, topLeft.y + height}
        }, color), width(width), height(height)
{
}

