#include "pch.h"
#include "Bullet.h"

#include "Image.h"
void Bullet::Fire(Image * image, float x, float y, float speed, float angle)
{
	mImage = image;
	mX = x;
	mY = y;
	mSpeed = speed;
	mAngle = angle;
	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
}

void Bullet::Update()
{
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	mRect= RectMakeCenter(mX, mY, 
		mImage->GetFrameWidth(), mImage->GetFrameHeight());
}

void Bullet::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mRect.left, mRect.top,0,0);
}
