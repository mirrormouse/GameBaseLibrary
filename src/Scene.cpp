#include "Scene.h"
#include "GameMain.h"
#include <algorithm>
#include <iostream>

Scene::Scene(GameMain* gameMain) : gameMain(gameMain) {}

void Scene::Loop() {
    // ���̃��\�b�h�͋�B���[�U�[���p���N���X�Ŏ����B
}

void Scene::FixedLoop() {
    // ���̃��\�b�h�͋�B���[�U�[���p���N���X�Ŏ����B
}

void Scene::FixedObjectUpdate() {

    // �`�揈���͕`�揇�Ń\�[�g���Ă�����s
    struct DrawOrderCompare {
        bool operator()(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const {
            return a->GetDrawOrder() < b->GetDrawOrder();
        }
    };

    // �ꎞ�I�ȃx�N�^�[���쐬���ă\�[�g
    std::vector<std::shared_ptr<GameObject>> sortedObjects = gameObjects;
    std::sort(sortedObjects.begin(), sortedObjects.end(), DrawOrderCompare());

    for (auto& gameObject : sortedObjects) {
        gameObject->Update();
        gameObject->CheckAndCallFixedUpdate();
        gameObject->Draw();
    }
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObjects.push_back(gameObject);
    gameObject->Start();
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObjects.erase(
        std::remove(gameObjects.begin(), gameObjects.end(), gameObject),
        gameObjects.end()
    );
}