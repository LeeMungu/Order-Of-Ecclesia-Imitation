#include "pch.h"
#include "FrameEffect.h"
#include "Image.h"

void FrameEffect::Init(wstring imageKey, float x, float y, int frameUpdateCount)
{
	mImage = ImageManager::GetInstance()->FindImage(imageKey);
	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mFrameCount = 0;
	mFrameIndexX = 0;
	mFrameUpdateCount = frameUpdateCount;
}

void FrameEffect::Release()
{
}

void FrameEffect::Update()
{
	mFrameCount++;
	if (mFrameCount >= mFrameUpdateCount)
	{
		mFrameIndexX++;

		if (mFrameIndexX >= mImage->GetFrameX())
		{
			mIsEnd = true;
		}

		mFrameCount = 0;
	}
}

void FrameEffect::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mRect.left, mRect.top, mFrameIndexX, 0);
}
