#pragma once
#ifndef LINE_H
#define LINE_H
#include "Shape.h"

class  GAMEBASELIB_API Line : public Shape {
public:
    Line(GameMain* gameMain, const Point& startPoint, const Point& endPoint, const float color[3], float thickness = 1.0f);

    void SetStartPoint(const Point& point);
    void SetEndPoint(const Point& point);
    void SetThickness(float thickness);


private:
    float thickness;
    void UpdateLineVertices();
};
#endif