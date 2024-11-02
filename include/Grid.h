#pragma once
#ifndef GRID_H
#define GRID_H

#include "Shape.h"
#include "Line.h"
#include <vector>
#include <string>
#include <map>

#ifdef GAMEBASELIB_EXPORTS
#define GAMEBASELIB_API __declspec(dllexport)
#else
#define GAMEBASELIB_API __declspec(dllimport)
#endif

struct GridPoint {
    int x, y;
};

class GAMEBASELIB_API Grid {
public:
    Grid(int width, int height, float cellWidth, float cellHeight, const Point& origin);

    // グリッド座標から実際の描画座標への変換
    Point gridToScreen(int x, int y) const;
    Point gridToScreen(GridPoint p) const;

    // 実際の描画座標からグリッド座標への変換
    void screenToGrid(const Point& screenPos, int& x, int& y) const;
    GridPoint screenToGrid(const Point& screenPos) const;

    // クリックされたグリッド座標を返す
    std::vector<GridPoint> getPressedGrid(GameMain* gameMain, bool clickonly = false, int button = GLFW_MOUSE_BUTTON_LEFT);


    // グリッドの範囲内かどうかをチェック
    bool isInBounds(int x, int y) const;
    bool isInBounds(GridPoint p) const;

    // グリッドのサイズを取得
    int getWidth() const { return width; }
    int getHeight() const { return height; }


    // セルのサイズを取得
    float getCellWidth() const { return cellWidth; }
    float getCellHeight() const { return cellHeight; }


    void addStateLayer(const std::string& layerName, const std::vector<std::vector<int>>& initialState);
    void updateState(const std::string& layerName, int x, int y, int newState);
    void updateState(const std::string& layerName, GridPoint p, int newState);
    int getState(const std::string& layerName, int x, int y) const;
    int getState(const std::string& layerName, GridPoint p) const;

    std::shared_ptr<Line> getLine(GameMain* gameMain, GridPoint start, GridPoint end, float color[3], float thickness=1.0f);

private:
    int width;  // グリッドの横のマス数
    int height;  // グリッドの縦のマス数
    float cellWidth;  // 1マスの横幅
    float cellHeight;  // 1マスの縦幅
    Point origin;  // グリッドの原点（左上）の実際の描画座標

    std::map<std::string, std::vector<std::vector<int>>> stateLayers;//状態情報を保持

};

#endif // GRID_H