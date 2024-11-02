#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include <unordered_map>
#include <string>
#include <memory>

class GAMEBASELIB_API SceneManager {
public:
    SceneManager();

    // �V�[����ǉ�
    void AddScene(const std::string& name, std::shared_ptr<Scene> scene);

    // �V�[����ύX
    void ChangeScene(const std::string& name);

    // ���݂̃V�[�����擾
    std::shared_ptr<Scene> GetCurrentScene();

private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> currentScene;
};

#endif // SCENE_MANAGER_H