#pragma once
#include "GameObject.h"
#include "Effect.h"
#include "Player.h"

class GameObject;

class Map:public GameObject
{
	Player* mPlayer;
	Image* mImageMap;
	Image* mImageMapBack;
	Effect* mPlayerSpot;
	float mBackX;
	float mBackY;
	float mBackSizeX;
	float mBackSizeY;
	RECT mBackRect;
 public:
	void Init() override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetPlayer(Player* player) { mPlayer = player; }
};

