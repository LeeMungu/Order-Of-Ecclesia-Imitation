#include "pch.h"
#include "SpecialEnemy.h"

void SpecialEnemy::Update()
{
	//Enemy::Update();

	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	if (mRect.left < 0)
	{
		mX = 0 + mSizeX / 2;

		mAngle = Random::GetInstance()->RandomInt(360);
		mAngle = mAngle * (PI / 180.f);
	}
	else if (mRect.right > WINSIZEX)
	{
		mX = WINSIZEX - mSizeX / 2;
		mAngle = Random::GetInstance()->RandomInt(360);
		mAngle = mAngle * (PI / 180.f);
	}
	else if (mRect.top < 0)
	{
		mY = 0 + mSizeY / 2;
		mAngle = Random::GetInstance()->RandomInt(360);
		mAngle = mAngle * (PI / 180.f);
	}
	else if (mRect.bottom > WINSIZEY)
	{
		mY = WINSIZEY - mSizeY / 2;
		mAngle = Random::GetInstance()->RandomInt(360);
		mAngle = mAngle * (PI / 180.f);
	}

	UpdateFrame();
	UpdateBullet();
}

void SpecialEnemy::Render(HDC hdc)
{
	Enemy::Render(hdc);
}
