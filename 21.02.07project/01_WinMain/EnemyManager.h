#pragma once
class Enemy;
class Player;
class BulletManager;
class EnemyManager
{
	vector<Enemy*> mEnemyList;
	Player* mPlayer;
	BulletManager* mBulletManager;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetBulletManagerPtr(BulletManager* manager) { mBulletManager = manager; }
};

