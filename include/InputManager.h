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
    std::vector<std::pair<double, double>> GetPressedPositions(int button) const;//�h���b�O���܂�
    std::vector<std::pair<double, double>> GetClickedPositions(int button) const;//�N���b�N�����u�Ԃ̃t���[���̂�
    void GetMousePosition(double& x, double& y) const;

private:
    GLFWwindow* window;
    std::vector<int> pressedButtons;
    std::vector<std::pair<double, double>> pressedPositions;
    double mouseX, mouseY;
    bool prePressed = false; //�O�t���[����press����Ă��邩
    bool currentPressed = false;
};

#endif // INPUT_MANAGER_H