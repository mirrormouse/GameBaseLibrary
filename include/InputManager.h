#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <vector>

#ifdef GAMEBASELIB_EXPORTS
#define GAMEBASELIB_API __declspec(dllexport)
#else
#define GAMEBASELIB_API __declspec(dllimport)
#endif


class GAMEBASELIB_API InputManager {
public:
    InputManager(GLFWwindow* window);

    void Update();
    bool IsMouseButtonPressed(int button) const;
    std::vector<std::pair<double, double>> GetPressedPositions(int button) const;//ドラッグを含む
    std::vector<std::pair<double, double>> GetClickedPositions(int button) const;//クリックした瞬間のフレームのみ
    void GetMousePosition(double& x, double& y) const;

private:
    GLFWwindow* window;
    std::vector<int> pressedButtons;
    std::vector<std::pair<double, double>> pressedPositions;
    double mouseX, mouseY;
    bool prePressed = false; //前フレームでpressされているか
    bool currentPressed = false;
};

#endif // INPUT_MANAGER_H