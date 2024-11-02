#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <chrono>

#ifdef GAMEBASELIB_EXPORTS
#define GAMEBASELIB_API __declspec(dllexport)
#else
#define GAMEBASELIB_API __declspec(dllimport)
#endif

class GAMEBASELIB_API GameObject {
public:
    GameObject(int updateInterval = 0, int drawOrder = 0);
    virtual ~GameObject() = default;

    virtual void Start() {}  // ���������Ɉ�x�����Ă΂��
    virtual void Update() {}  // ���t���[���Ă΂��
    virtual void FixedUpdate() {}  // �Œ�Ԋu�ŌĂ΂��
    virtual void Draw() = 0;  // �`��p�̏������z�֐�

    void CheckAndCallFixedUpdate();

    void SetUpdateInterval(int interval) { updateInterval = interval; }
    void SetDrawOrder(int order) { drawOrder = order;  }
    int GetUpdateInterval() const { return updateInterval; }
    int GetDrawOrder() const { return drawOrder; }

private:
    int updateInterval;  // �~���b�P��
    int drawOrder; //�傫�����̂قǏ�ɂ���
    std::chrono::steady_clock::time_point lastUpdateTime;
};

#endif // GAMEOBJECT_H