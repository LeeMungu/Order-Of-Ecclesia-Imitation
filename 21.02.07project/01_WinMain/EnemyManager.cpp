#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"

void EnemyManager::Init()
{
	for (int i = 0; i < 1; ++i)
	{
		for (int j = 0; j < 1; ++j)
		{
			float x = j * 100;
			float y = 50 + i * 50;
			Enemy* enemy = new Enemy();
			enemy->Init(x, y);
			enemy->SetPlayerPtr(mPlayer);
			enemy->SetBulletManagerPtr(mBulletManager);
			mEnemyList.push_back(enemy);
		}
	}
}

void EnemyManager::Release()
{
	for (int i = 0; i < mEnemyList.size(); ++i)
	{
		mEnemyList[i]->Release();
		SafeDelete(mEnemyList[i]);
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < mEnemyList.size(); ++i)
	{
		mEnemyList[i]->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i < mEnemyList.size(); ++i)
	{
		mEnemyList[i]->Render(hdc);
	}
}
