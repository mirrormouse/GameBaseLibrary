#ifndef SCENE_H
#define SCENE_H

#include "LoopHandler.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class GameMain;

class GAMEBASELIB_API Scene : public LoopHandler {
public:
    Scene(GameMain* gameMain);
    virtual ~Scene() = default;

    // LoopHandlerから継承
    virtual void Loop() override; // シーン全体でフレーム毎に行う処理をユーザーが継承して実装
    virtual void FixedLoop() override; // シーン全体で定期的に行う処理をユーザーが継承して実装

    // シーン固有のメソッド
    virtual void Enter() = 0;
    virtual void Exit() = 0;

    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

    // GameObjectのFixedUpdateを呼び出す
    void FixedObjectUpdate();

protected:
    GameMain* gameMain;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};

#endif // SCENE_H