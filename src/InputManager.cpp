#include "InputManager.h"
#include <algorithm>
#include <iostream>

InputManager::InputManager(GLFWwindow* window) : window(window), mouseX(0), mouseY(0) {}



void InputManager::Update() {
    pressedButtons.clear();
    pressedPositions.clear();
    prePressed = currentPressed;
    currentPressed = false;
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i) {
        if (glfwGetMouseButton(window, i) == GLFW_PRESS) {
            pressedButtons.push_back(i);
            pressedPositions.push_back({mouseX, mouseY});
            currentPressed = true;
        }
    }
    glfwGetCursorPos(window, &mouseX, &mouseY);
}

bool InputManager::IsMouseButtonPressed(int button) const {
    return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
}

void InputManager::GetMousePosition(double& x, double& y) const {
    x = mouseX;
    y = mouseY;
}

std::vector<std::pair<double, double>> InputManager::GetClickedPositions(int button) const {
    std::vector<std::pair<double, double>> resPositions;
    if (prePressed) {
        return resPositions;
    }
    else {
        return GetPressedPositions(button);
    }
}

std::vector<std::pair<double, double>> InputManager::GetPressedPositions(int button) const {
    int s = pressedButtons.size();
    std::vector<std::pair<double, double>> resPositions;
    for (int i = 0; i < s; i++) {
        if (pressedButtons.at(i) == button) {
            resPositions.push_back(pressedPositions.at(i));
        }
    }
    return resPositions;
}