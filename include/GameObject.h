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

    virtual void Start() {}  // 初期化時に一度だけ呼ばれる
    virtual void Update() {}  // 毎フレーム呼ばれる
    virtual void FixedUpdate() {}  // 固定間隔で呼ばれる
    virtual void Draw() = 0;  // 描画用の純粋仮想関数

    void CheckAndCallFixedUpdate();

    void SetUpdateInterval(int interval) { updateInterval = interval; }
    void SetDrawOrder(int order) { drawOrder = order;  }
    int GetUpdateInterval() const { return updateInterval; }
    int GetDrawOrder() const { return drawOrder; }

private:
    int updateInterval;  // ミリ秒単位
    int drawOrder; //大きいものほど上にくる
    std::chrono::steady_clock::time_point lastUpdateTime;
};

#endif // GAMEOBJECT_H