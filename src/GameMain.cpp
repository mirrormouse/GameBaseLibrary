#include "GameMain.h"
#include "LoopHandler.h"
#include <iostream>
#include <format>
#include <iomanip>
#include <algorithm>


static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {


    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 常に左上(-1,1)、右下(1,-1)となる座標系を設定
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


GameMain::GameMain(int width, int height, const char* title) : inputManager(nullptr) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-2);
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);


    // フレームバッファサイズ変更コールバックの設定
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // 初期サイズでの座標系の設定
    framebufferSizeCallback(window, width, height);


    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Could not init FreeType library\n";
        exit(-3);
    }

    if (FT_New_Face(ft, "resource/font/NotoSansJP-Black.ttf", 0, &face)) {
        std::cerr << "Could not open font\n";
        exit(-4);
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    inputManager = InputManager(window);
}

GameMain::~GameMain() {
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void GameMain::run(int fixedLoopInterval) {


    auto lastFixedLoopTime = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {

        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFixedLoopTime).count();

        glClear(GL_COLOR_BUFFER_BIT);
        inputManager.Update();

        if (auto currentScene = sceneManager.GetCurrentScene()) {
            currentScene->Loop();
            currentScene->FixedObjectUpdate(); // GameObjectの定期更新

            if (elapsedTime >= fixedLoopInterval) {
                currentScene->FixedLoop();
                lastFixedLoopTime = currentTime;
            }
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GameMain::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObject->Start();  // Start メソッドを呼び出す
    gameObjects.push_back(gameObject);
}

void GameMain::RemoveGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObjects.erase(
        std::remove(gameObjects.begin(), gameObjects.end(), gameObject),
        gameObjects.end()
    );
}

std::vector<int> GameMain::getKeyInput() {
    std::vector<int> temp = inputBuffer;
    inputBuffer.clear();
    return temp;
}


void GameMain::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GameMain* game = static_cast<GameMain*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_BACKSPACE && !game->inputBuffer.empty()) {
            game->inputBuffer.pop_back();
        }
        else {
            game->inputBuffer.push_back(key);
        }
    }
}

std::string GameMain::KeysToString(const std::vector<int>& keys) {
    std::string res = "";
    for (int key : keys) {
        if (key >= 32 && key <= 126) {  // 印字可能ASCII範囲
            char c = static_cast<char>(key);
        }
    }
    return res;
}


