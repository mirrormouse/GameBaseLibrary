#ifndef LOOPHANDLER_H
#define LOOPHANDLER_H

#ifdef GAMEBASELIB_EXPORTS
#define GAMEBASELIB_API __declspec(dllexport)
#else
#define GAMEBASELIB_API __declspec(dllimport)
#endif

class GAMEBASELIB_API LoopHandler {
public:
    virtual void Loop() = 0; // ���[�U�[���I�[�o�[���C�h���鉼�z�֐�
    virtual void FixedLoop() {} // �Œ�Ԋu�ŌĂяo�����i�f�t�H���g�͋�̎����j
};

#endif // LOOPHANDLER_H

