#ifndef LOOPHANDLER_H
#define LOOPHANDLER_H

#ifdef GAMEBASELIB_EXPORTS
#define GAMEBASELIB_API __declspec(dllexport)
#else
#define GAMEBASELIB_API __declspec(dllimport)
#endif

class GAMEBASELIB_API LoopHandler {
public:
    virtual void Loop() = 0; // ユーザーがオーバーライドする仮想関数
    virtual void FixedLoop() {} // 固定間隔で呼び出される（デフォルトは空の実装）
};

#endif // LOOPHANDLER_H

