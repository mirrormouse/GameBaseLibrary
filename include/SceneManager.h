#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include <unordered_map>
#include <string>
#include <memory>

class GAMEBASELIB_API SceneManager {
public:
    SceneManager();

    // シーンを追加
    void AddScene(const std::string& name, std::shared_ptr<Scene> scene);

    // シーンを変更
    void ChangeScene(const std::string& name);

    // 現在のシーンを取得
    std::shared_ptr<Scene> GetCurrentScene();

private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> currentScene;
};

#endif // SCENE_MANAGER_H