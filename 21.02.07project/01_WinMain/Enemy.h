#pragma once
#include "Unit.h"
class Image;
class Bullet;
class Player;
class BulletManager;
//��� : � Ŭ������ ���� �Ӽ�(����,�Լ�)�� �̾�޾Ƽ� Ŭ������ ���� �ϴ� ��
class Enemy : public Unit
{
protected:
	float mAngle;
	int mFrameX;
	int mFrameCount;
	int mFiringFrameCount;		//��������� �༮

	Player* mPlayer;
	BulletManager* mBulletManager;
public:
	void Init(int x, int y);
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetBulletManagerPtr(BulletManager* manager) { mBulletManager = manager; }

	void UpdateMove();
	void UpdateFrame();
	void UpdateBullet();
};

