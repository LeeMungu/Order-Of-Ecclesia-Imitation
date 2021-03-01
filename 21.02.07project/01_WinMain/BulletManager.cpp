#include "pch.h"
#include "BulletManager.h"

#include "Bullet.h"
void BulletManager::Release()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		SafeDelete(mBullets[i]);
	}
}

void BulletManager::Update()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Update();
	}
}

void BulletManager::Render(HDC hdc)
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Render(hdc);
	}
}

void BulletManager::Fire(wstring key, float x, float y, float speed, float angle)
{
	Bullet* bullet = new Bullet();
	Image* image = ImageManager::GetInstance()->FindImage(key);
	bullet->Fire(image, x, y, speed, angle);
	mBullets.push_back(bullet);
}
