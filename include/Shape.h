#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include <GLFW/glfw3.h>
#include <ft2build.h>
#include "GameObject.h"
#include "GameMain.h"
#include <vector>

struct Point {
    float x, y;
};

class GAMEBASELIB_API Shape : public GameObject {
public:
    Shape(GameMain* gameMain, const std::vector<Point>& vertices, const float color[3]);
    virtual ~Shape() = default;

    virtual void Draw() override;

    void Move(float dx, float dy);
    void SetPosition(float x, float y);
    Point GetPosition() const;
    void Update() {};

    // 可視性制御のための新しいメソッド
    void SetVisible(bool visible) { isVisible = visible; }
    bool IsVisible() const { return isVisible; }


protected:
    std::vector<Point> pixelVertices;
    std::vector<Point> normalizedVertices;
    float color[3];
    bool isVisible;
    GameMain* gameMain;

    void UpdateNormalizedVertices();
};

#endif // SHAPE_H