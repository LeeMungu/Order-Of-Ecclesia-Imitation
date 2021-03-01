#pragma once
#include "Item.h"
#include "Player.h"

class Player;
class Weapon : public Item
{
	Player* mPlayer;
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
	//���� �÷��̾� ��ġ
	float mNowPlayerX;
	float mNowPlayerY;
	WeaponType mType;
	bool mAppearance;//������ ����

public:
	void Fire(WeaponType type);
	void Release()override;
	void Update()override;
	void Render(HDC hdc, float cameraX, float cameraY)override;
	
	int GetDamege()const { return mDamege; }
	bool GetAppearance()const { return mAppearance; }

	
	void SetAppearance(bool appearance) { mAppearance = appearance; }
	void SetPlayerPtr(Player* player) { mPlayer = player; }
};