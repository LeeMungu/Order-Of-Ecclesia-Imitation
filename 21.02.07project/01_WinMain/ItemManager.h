#pragma once
#include "Player.h"
#include "Item.h"
#include "FieldWeapon.h"

class ItemManager
{
private:
	Player* mPlayer;
	vector<FieldWeapon*> mItemList;

public:
	void Init(int stage);
	void Release();
	void Update();
	void Render(HDC hdc, float cameraX, float cameraY);

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	vector<FieldWeapon*> GetObjectList() const { return mItemList; }
};

