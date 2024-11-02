#include "SceneManager.h"
#include <stdexcept>

SceneManager::SceneManager() : currentScene(nullptr) {}

void SceneManager::AddScene(const std::string& name, std::shared_ptr<Scene> scene) {
    scenes[name] = scene;
}

void SceneManager::ChangeScene(const std::string& name) {
    auto it = scenes.find(name);
    if (it != scenes.end()) {
        if (currentScene) {
            currentScene->Exit();
        }
        currentScene = it->second;
        currentScene->Enter();
    }
    else {
        throw std::runtime_error("Scene not found: " + name);
    }
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() {
    if (!currentScene) {
        throw std::runtime_error("No current scene set");
    }
    return currentScene;
}