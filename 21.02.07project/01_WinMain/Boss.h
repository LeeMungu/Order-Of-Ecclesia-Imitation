#pragma once
#include "Monster.h"
#include "EnermyWeapon.h"

class Monster;

class Boss : public Monster
{
	EnermyWeapon* mEnermyWeapon;
	float mPlayerX, mPlayerY;
	float mAttack2Count;
	bool mReversCount;
	int mFettenNum;
public:
	void Release()override;
	void Render(HDC hdc, float cameraX, float cameraY) override;
	void Move() override;
	void UpdateFrame() override;
	void UpdateState() override;

	EnermyWeapon* GetEnermyWeapon()const { return mEnermyWeapon; }
};

