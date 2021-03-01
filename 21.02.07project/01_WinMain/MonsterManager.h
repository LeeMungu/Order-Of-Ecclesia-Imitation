#pragma once
#include "Monster.h"
#include "Player.h"
#include "Weapon.h"
#include "Effect.h"

class Monster;
class Player;

class MonsterManager
{
private:
	vector<Monster*> mMonsterList;
	vector<Effect*> mEffectList;
	Player* mPlayer;
	Weapon* mWeapon;
	int mFrameCount;
public:
	void Init(int stage);
	void Release();
	void Update(int stage);
	void Render(HDC hdc, float cameraX, float cameraY);

	void UpdatePlayerMonsterCrash();
	void UpdateWeaponMonsterCrash();
	void UpdatePlayerWeaponCrash();
	void UpdateEffect();

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetWeaponPtr(Weapon* weapon) { mWeapon = weapon; }
};

