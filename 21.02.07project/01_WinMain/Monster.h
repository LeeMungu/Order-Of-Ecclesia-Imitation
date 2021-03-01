#pragma once
#include "Unit.h"
#include "Player.h"

class Player;

enum class MonsterState
{
	Generation,//����
	Generation2,
	Stand,//��û���
	Move,//�̵�
	Attack1,//�����
	Attack2,//������
	Attack3,//��
	Extinction//���� - ��ǳ��� Extinction bool���� true�� ���´�
};


class Monster : public Unit
{
protected:
	Image* mImageMotion;
	int mMotionLR;//�¿�
	float mAngle;
	bool mIsFallow;
	wstring mKey;
	Player* mPlayer;
	MonsterState mState;
	bool mAttackBool;//���ݿ���
	int mAttack;//���ݵ�����
	int mAttackCount;//������
	bool mDamegeBool;//���� ��������
	int mDamegeCount;//���ݴ� ������ ��
	bool mExtence;
	int mExtenceCount;
	int mFallowCount;// ���� ��
	float mFallowX, mFallowY;
	int mMotionCount;//�����ȯ ��
	float mStartX;//���� ���ڸ� ���ÿ� - ���㵵 ��
	float mStartY;
	int mBeamCount;
public:
	virtual void Init(wstring key, float x, float y, float speed, float angle);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, float cameraX, float cameraY);
	virtual void UpdateCrash();
	
	virtual void InitDate() {};
	virtual void Move() {};
	virtual void UpdateFrame() {};
	virtual void UpdateState() {};
	
	wstring GetKey()const { return mKey; }
	MonsterState GetState()const { return mState; }
	bool GetExtence()const { return mExtence; }
	bool GetAttackBool()const { return mAttackBool; }
	int GetAttack()const { return mAttack; }
	bool GetDamegeBool()const { return mDamegeBool; }

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetExtence(bool ex) { mExtence = ex; }
	void SetAttackBool(bool attack) { mAttackBool = attack; }
	void SetDamegeBool(bool damegeBool) { mDamegeBool = damegeBool; }
};

