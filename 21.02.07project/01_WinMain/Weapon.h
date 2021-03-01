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
	//생성시 무기좌표
	float mStartX;
	float mStartY;
	float mStartImageX;
	float mStartImageY;
	//무기생성시 player x,y좌표
	float mStartPlayerX;
	float mStartPlayerY;
	//현제 플레이어 위치
	float mNowPlayerX;
	float mNowPlayerY;
	WeaponType mType;
	bool mAppearance;//나오는 판정

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