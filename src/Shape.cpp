#include "Shape.h"
#include "CoordinateConverter.h"
#include <iostream>

Shape::Shape(GameMain* gameMain, const std::vector<Point>& pixelVertices, const float color[3])
    : gameMain(gameMain), pixelVertices(pixelVertices), isVisible(true)
{
    for (int i = 0; i < 3; ++i) {
        this->color[i] = color[i];
    }
    UpdateNormalizedVertices();
}


void Shape::Draw()
{

    UpdateNormalizedVertices();

    if (!isVisible) return;

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POLYGON);

    for (const auto& point : normalizedVertices) {
        glVertex2f(point.x, point.y);

    }
    glEnd();
}


void Shape::Move(float dx, float dy)
{
    for (auto& point : pixelVertices) {
        point.x += dx;
        point.y += dy;
    }
    UpdateNormalizedVertices();
}

void Shape::SetPosition(float x, float y)
{
    Point currentPos = GetPosition();
    float dx = x - currentPos.x;
    float dy = y - currentPos.y;
    Move(dx, dy);
}

Point Shape::GetPosition() const
{
    // 図形の位置を最初の頂点の位置とする
    return pixelVertices[0];
}

//ピクセル座標を正規化座標に変換
void Shape::UpdateNormalizedVertices()
{
    normalizedVertices.clear();
    for (const auto& pixelPoint : pixelVertices) {
        float normalizedX, normalizedY;
        CoordinateConverter::PixelToNormalized(gameMain->GetWindow(), pixelPoint.x, pixelPoint.y, normalizedX, normalizedY);
        normalizedVertices.push_back({ normalizedX, normalizedY });
    }
}