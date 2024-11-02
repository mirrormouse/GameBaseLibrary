#include "Scene.h"
#include "GameMain.h"
#include <algorithm>
#include <iostream>

Scene::Scene(GameMain* gameMain) : gameMain(gameMain) {}

void Scene::Loop() {
    // このメソッドは空。ユーザーが継承クラスで実装。
}

void Scene::FixedLoop() {
    // このメソッドは空。ユーザーが継承クラスで実装。
}

void Scene::FixedObjectUpdate() {

    // 描画処理は描画順でソートしてから実行
    struct DrawOrderCompare {
        bool operator()(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const {
            return a->GetDrawOrder() < b->GetDrawOrder();
        }
    };

    // 一時的なベクターを作成してソート
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