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

    // �O���b�h���W������ۂ̕`����W�ւ̕ϊ�
    Point gridToScreen(int x, int y) const;
    Point gridToScreen(GridPoint p) const;

    // ���ۂ̕`����W����O���b�h���W�ւ̕ϊ�
    void screenToGrid(const Point& screenPos, int& x, int& y) const;
    GridPoint screenToGrid(const Point& screenPos) const;

    // �N���b�N���ꂽ�O���b�h���W��Ԃ�
    std::vector<GridPoint> getPressedGrid(GameMain* gameMain, bool clickonly = false, int button = GLFW_MOUSE_BUTTON_LEFT);


    // �O���b�h�͈͓̔����ǂ������`�F�b�N
    bool isInBounds(int x, int y) const;
    bool isInBounds(GridPoint p) const;

    // �O���b�h�̃T�C�Y���擾
    int getWidth() const { return width; }
    int getHeight() const { return height; }


    // �Z���̃T�C�Y���擾
    float getCellWidth() const { return cellWidth; }
    float getCellHeight() const { return cellHeight; }


    void addStateLayer(const std::string& layerName, const std::vector<std::vector<int>>& initialState);
    void updateState(const std::string& layerName, int x, int y, int newState);
    void updateState(const std::string& layerName, GridPoint p, int newState);
    int getState(const std::string& layerName, int x, int y) const;
    int getState(const std::string& layerName, GridPoint p) const;

    std::shared_ptr<Line> getLine(GameMain* gameMain, GridPoint start, GridPoint end, float color[3], float thickness=1.0f);

private:
    int width;  // �O���b�h�̉��̃}�X��
    int height;  // �O���b�h�̏c�̃}�X��
    float cellWidth;  // 1�}�X�̉���
    float cellHeight;  // 1�}�X�̏c��
    Point origin;  // �O���b�h�̌��_�i����j�̎��ۂ̕`����W

    std::map<std::string, std::vector<std::vector<int>>> stateLayers;//��ԏ���ێ�

};

#endif // GRID_H