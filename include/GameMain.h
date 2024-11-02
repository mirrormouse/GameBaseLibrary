#ifndef GAMEMAIN_H
#define GAMEMAIN_H
#include "LoopHandler.h"
#include "GameObject.h"
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include "SceneManager.h"
#include "InputManager.h"

#ifdef GAMEBASELIB_EXPORTS
#define GAMEBASELIB_API __declspec(dllexport)
#else
#define GAMEBASELIB_API __declspec(dllimport)
#endif

class GAMEBASELIB_API GameMain {
public:
    GameMain(int width, int height, const char* title);
    ~GameMain();
    void run(int fixedLoopInterval = 1000);

    FT_Face getFace() const { return face; }
    std::vector<int> getKeyInput();
    static std::string KeysToString(const std::vector<int>& keys);

    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    void RemoveGameObject(std::shared_ptr<GameObject> gameObject);
    GLFWwindow* GetWindow() const { return window; }

    SceneManager& GetSceneManager() { return sceneManager; }
    InputManager& GetInputManager() { return inputManager; }

private:
    GLFWwindow* window;
    FT_Library ft;
    FT_Face face;
    std::vector<int> inputBuffer;
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    SceneManager sceneManager;
    InputManager inputManager;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // GAMEMAIN_H