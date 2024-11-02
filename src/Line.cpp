#include "Line.h"
#include <cmath>

Line::Line(GameMain* gameMain, const Point& startPoint, const Point& endPoint, const float color[3], float thickness)
    : Shape(gameMain, {startPoint, endPoint}, color), thickness(thickness)
{
    UpdateLineVertices();
}

void Line::SetStartPoint(const Point& point)
{
    pixelVertices[0] = point;
    UpdateLineVertices();
}

void Line::SetEndPoint(const Point& point)
{
    pixelVertices[1] = point;
    UpdateLineVertices();
}

void Line::SetThickness(float thickness)
{
    this->thickness = thickness;
    UpdateLineVertices();
}

void Line::UpdateLineVertices()//始点と終点をもとに、細長い矩形として解釈
{
    Point start = pixelVertices[0];
    Point end = pixelVertices[1];

    //線の方向
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    //線の長さ
    float length = std::sqrt(dx * dx + dy * dy);

    //start,endは短辺の中点なため、矩形の頂点までの幅はthicknessの半分
    float nx;
    float ny;

    if (length < 0.0001f) {//長さが極端に短い場合、描画しない
        nx = 0;
        ny = 0;
    }
    else {
        nx = -dy / length * (thickness / 2.0f);
        ny = dx / length * (thickness / 2.0f);
    }




    // 4つの頂点を設定
    std::vector<Point> newVertices = {
        Point{start.x + nx, start.y + ny},  // 左上
        Point{end.x + nx, end.y + ny},      // 右上
        Point{end.x - nx, end.y - ny},      // 右下
        Point{start.x - nx, start.y - ny}   // 左下
    };

    pixelVertices = newVertices;

    
}
