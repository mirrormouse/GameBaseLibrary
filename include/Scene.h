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

    // LoopHandler����p��
    virtual void Loop() override; // �V�[���S�̂Ńt���[�����ɍs�����������[�U�[���p�����Ď���
    virtual void FixedLoop() override; // �V�[���S�̂Œ���I�ɍs�����������[�U�[���p�����Ď���

    // �V�[���ŗL�̃��\�b�h
    virtual void Enter() = 0;
    virtual void Exit() = 0;

    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

    // GameObject��FixedUpdate���Ăяo��
    void FixedObjectUpdate();

protected:
    GameMain* gameMain;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};

#endif // SCENE_H