#include "pch.h"
#include "Enemy.h"

#include "Image.h"
#include "Bullet.h"
#include "Player.h"
#include "BulletManager.h"

void Enemy::Init(int x, int y)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Enemy");

	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 5.f;
	mAngle = 0.f;

	mFrameCount = mFrameX = 0;
	mFiringFrameCount = 0;
}

void Enemy::Release()
{

}

void Enemy::Update()
{
	UpdateMove();
	UpdateFrame();
	UpdateBullet();
}

void Enemy::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mRect.left, mRect.top, mFrameX, 0);
}

void Enemy::UpdateMove()
{
	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	if (mRect.left <= 0)mAngle = 0;
	else if (mRect.right >= WINSIZEX)mAngle = PI;
}

void Enemy::UpdateFrame()
{
	mFrameCount++;
	if (mFrameCount >= 5)
	{
		mFrameCount = 0;
		mFrameX = (mFrameX + 1) % 10;
	}
}

void Enemy::UpdateBullet()
{
	mFiringFrameCount++;
	if (mFiringFrameCount >= 1)
	{
		float angle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
		mBulletManager->Fire(L"CircleBullet", mX, mY, 10.f, angle);
		mFiringFrameCount = 0;
	}


}
