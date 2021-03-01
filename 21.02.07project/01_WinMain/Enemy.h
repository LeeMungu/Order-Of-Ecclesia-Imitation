#pragma once
#include "Unit.h"
class Image;
class Bullet;
class Player;
class BulletManager;
//상속 : 어떤 클래스로 부터 속성(변수,함수)을 이어받아서 클래스를 구현 하는 것
class Enemy : public Unit
{
protected:
	float mAngle;
	int mFrameX;
	int mFrameCount;
	int mFiringFrameCount;		//프레임재는 녀석

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

