#include "pch.h"
#include "Object.h"
#include "Image.h"

void Object::Init(wstring key, float x, float y, int type, int indexX, int indexY, Position position)
{
	mImage = ImageManager::GetInstance()->FindImage(key);
	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	if (position == Position::Center)
	{
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	else if (position == Position::Edge)
	{
		mRect = RectMake(mX, mY, mSizeX, mSizeY);
	}
	mType = type;
	mIndexX = indexX;
	mIndexY = indexY;
	mMulty = true;
	mKey = key;
	if (mType == 2|| mType==3)
	{
		mImageOpen = ImageManager::GetInstance()->FindImage(mKey+L"Open");
		mOpenSizeX = 0;
		mIsPlayerNear = false;
	}
}
void Object::Init(wstring key, float x, float y, int type)
{
	mImage = ImageManager::GetInstance()->FindImage(key);
	mX = x;
	mY = y;
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mType = type;
	mMulty = false;
	mKey = key;
	if (mType == 2 || mType == 3)
	{
		mImageOpen = ImageManager::GetInstance()->FindImage(mKey + L"Open");
		mOpenSizeX = 0;
		mIsPlayerNear = false;
	}
}

void Object::Release()
{
	
}

void Object::Update()
{
	if (mIsPlayerNear == true  )
	{
		if (mOpenSizeX < mImageOpen->GetFrameWidth())
		{
			mFrameCount++;
			if (mFrameCount > 1)
			{
				mFrameCount = 0;
				mOpenSizeX += mImageOpen->GetFrameWidth() / 10;
			}
		}
	}
	else if (mIsPlayerNear == false && mOpenSizeX > 0)
	{
		mFrameCount++;
		if (mFrameCount > 1)
		{
			mFrameCount = 0;
			mOpenSizeX -= mImageOpen->GetFrameWidth() / 10;
		}
	}
}

void Object::Render(HDC hdc ,float cameraX, float cameraY)
{
	if (mType==2)
	{
		if (mOpenSizeX <= 0)
		{
			mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY);
		}
		else
		{
			mImageOpen->Render(hdc, mRect.left - mOpenSizeX + cameraX, mRect.top + cameraY,
				mImageOpen->GetFrameWidth() - mOpenSizeX, 0,mOpenSizeX,mSizeY);
		}
	}
	else if (mType == 3)
	{
		if (mOpenSizeX <= 0)
		{
			mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY);
		}
		else
		{
			mImageOpen->Render(hdc, mRect.right + cameraX, mRect.top + cameraY,
				0, 0, mOpenSizeX, mSizeY);
		}
	}
	else if (mMulty)
	{
		mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY);
	}
	else
	{
		mImage->Render(hdc, mRect.left + cameraX, mRect.top + cameraY);
	}
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RECT Rect = {mRect.left +cameraX, mRect.top + cameraY, mRect.right + cameraX, mRect.bottom + cameraY };
		RenderRect(hdc, Rect);
	}
}
