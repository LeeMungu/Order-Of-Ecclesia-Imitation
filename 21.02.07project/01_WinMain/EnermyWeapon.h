#pragma once
#include "Item.h"

enum class EnermyWeaponType
{
	Attack1,//공쏘기
	Attack2,//구르기
	Attack3
};

class Boss;
class EnermyWeapon : public Item
{
private:
	Boss* mBoss;
	float mImageX;
	float mImageY;
	int mDamege;
	//생성시 무기좌표
	float mStartX;
	float mStartY;
	float mStartImageX;
	float mStartImageY;
	//무기생성시 player x,y좌표
	float mStartPlayerX;
	float mStartPlayerY;
	//앵글
	float mAngle;
	EnermyWeaponType mType;
public:
	void Fire(float x, float y, float playerX, float playerY, EnermyWeaponType type);
	void Release()override;
	void Update()override;
	void Render(HDC hdc, float cameraX, float cameraY)override;

	int GetDamege()const { return mDamege; }

	EnermyWeaponType GetEnermyWeaponType() const { return mType; }
	void SetPlayerPtr(Boss* boss) { mBoss = boss; }
};

