#pragma once
#include "Item.h"

enum class EnermyWeaponType
{
	Attack1,//�����
	Attack2,//������
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
	//������ ������ǥ
	float mStartX;
	float mStartY;
	float mStartImageX;
	float mStartImageY;
	//��������� player x,y��ǥ
	float mStartPlayerX;
	float mStartPlayerY;
	//�ޱ�
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

