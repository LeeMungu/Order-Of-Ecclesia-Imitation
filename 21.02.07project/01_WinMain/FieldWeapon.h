#pragma once
#include "Item.h"
#include "Player.h"
#include "Effect.h"

class Player;
class FieldWeapon : public Item
{
	Effect* mEffect;
	Player* mPlayer;
	WeaponType mType;
	Image* mImage2;
	float mSizeX2;
	float mSizeY2;
	int mIndexX2;
	RECT mRect2;
	float mAlpha;
	bool mAppear;//Èí¼ö
	bool mAppear2;//Á¦°Å
public:
	void Fire(float x, float y, WeaponType type);
	void Release()override;
	void Update()override;
	void Render(HDC hdc, float cameraX, float cameraY)override;
	
	bool GetAppear()const { return mAppear; }
	bool GetAppear2()const { return mAppear2; }
	WeaponType GetWeaponType()const { return mType; }

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetAppear(bool appear) { mAppear = appear; }
	void SetAppear2(bool appear) { mAppear2 = appear; }
};

