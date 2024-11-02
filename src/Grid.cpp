#include "Grid.h"
#include <algorithm>
#include <stdexcept>

Grid::Grid(int width, int height, float cellWidth, float cellHeight, const Point& origin)
    : width(width), height(height), cellWidth(cellWidth), cellHeight(cellHeight), origin(origin)
{
}

Point Grid::gridToScreen(int x, int y) const
{
    return Point{
        origin.x + x * cellWidth,
        origin.y + y * cellHeight 
    };
}

Point Grid::gridToScreen(GridPoint p) const
{
    return gridToScreen(p.x, p.y);
}


void Grid::screenToGrid(const Point& screenPos, int& x, int& y) const
{
    x = static_cast<int>((screenPos.x - origin.x) / cellWidth);
    y = static_cast<int>((screenPos.y - origin.y) / cellHeight); 
}

GridPoint Grid::screenToGrid(const Point& screenPos) const
{
    int x = static_cast<int>((screenPos.x - origin.x) / cellWidth);
    int y = static_cast<int>((screenPos.y - origin.y) / cellHeight);
    return GridPoint{ x,y };
}


bool Grid::isInBounds(int x, int y) const
{
    return x >= 0 && x < width&& y >= 0 && y < height;
}
bool Grid::isInBounds(GridPoint p) const
{
    return isInBounds(p.x, p.y);
}


void Grid::addStateLayer(const std::string& layerName, const std::vector<std::vector<int>>& initialState) {
    if (initialState.size() != height || initialState[0].size() != width) {
        throw std::invalid_argument("Initial state dimensions do not match grid dimensions");
    }
    stateLayers[layerName] = initialState;
}

void Grid::updateState(const std::string& layerName, int x, int y, int newState) {
    if (!isInBounds(x, y)) {
        throw std::out_of_range("Coordinates out of grid bounds");
    }
    if (stateLayers.find(layerName) == stateLayers.end()) {
        throw std::invalid_argument("State layer does not exist");
    }
    stateLayers.at(layerName).at(y).at(x) = newState;
}
void Grid::updateState(const std::string& layerName, GridPoint p, int newState) {
    updateState(layerName, p.x, p.y, newState);
}

int Grid::getState(const std::string& layerName, int x, int y) const {
    if (!isInBounds(x, y)) {
        throw std::out_of_range("Coordinates out of grid bounds");
    }
    if (stateLayers.find(layerName) == stateLayers.end()) {
        throw std::invalid_argument("State layer does not exist");
    }
    return stateLayers.at(layerName).at(y).at(x);
}
int Grid::getState(const std::string& layerName, GridPoint p) const {
    return getState(layerName, p.x, p.y);
}


std::vector<GridPoint> Grid::getPressedGrid(GameMain* gameMain, bool clickonly, int button) {

    std::vector<GridPoint> resPoints;
    std::vector<std::pair<double, double>> pressedPositions;

    if (clickonly) {
        pressedPositions = gameMain->GetInputManager().GetClickedPositions(button);
    }
    else {
        pressedPositions = gameMain->GetInputManager().GetPressedPositions(button);
    }
    

    for (auto ps : pressedPositions) {
        GridPoint gridPoint = screenToGrid(Point{ static_cast<float>(ps.first), static_cast<float>(ps.second) });
        if (isInBounds(gridPoint.x, gridPoint.y)) {
            resPoints.push_back(gridPoint);
        }
    }

    return resPoints;

}

std::shared_ptr<Line> Grid::getLine(GameMain* gameMain, GridPoint start, GridPoint end, float color[3], float thickness) {
    std::shared_ptr<Line> line = std::make_shared<Line>(gameMain, gridToScreen(start), gridToScreen(end), color, thickness);
    return line;
}