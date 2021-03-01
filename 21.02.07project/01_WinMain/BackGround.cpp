#include "pch.h"
#include "BackGround.h"
#include "Image.h"

void BackGround::Init(wstring key, BackGroundType type)
{
	mType = type;
	mImage=ImageManager::GetInstance()->FindImage(key);
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mX = 0;
	mY = WINSIZEY - mSizeY-48;//48Àº ¹Ù´Ú ³ôÀÌ
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
}

void BackGround::Release()
{
}

void BackGround::Update()
{
}

void BackGround::Render(HDC hdc, float cameraX, float cameraY)
{
	if (mType == BackGroundType::BackGroundBack)
	{
		mCorrection = 30;
	}
	else if (mType == BackGroundType::BackGround)
	{
		mCorrection = 15;
	}
	else
	{
		mCorrection = 1;
	}

	float tempX;
	float tempY;
	float cameraTempY;
	if (cameraY < 400)
	{
		cameraTempY = 0;
	}
	else
	{
		cameraTempY = cameraY;
	}

	if (mType == BackGroundType::BackGroundBack1)
	{
		tempX = mRect.left + cameraX / mCorrection + 64;
		tempY = mRect.top + cameraY*0.9f;
	}
	else if (mType == BackGroundType::BackGroundBack2)
	{
		tempX = mRect.left + cameraX / mCorrection + 64;
		tempY = mRect.top + cameraY*0.75f + 130;
	}
	else if (mType == BackGroundType::BackGroundBack3)
	{
		tempX = mRect.left + cameraX / mCorrection + 64;
		tempY = mRect.top + cameraY *0.9f +110;
	}
	else
	{
		tempX = mRect.left + cameraX / mCorrection;
		tempY = mRect.top + cameraY / mCorrection;
	}

	mImage->Render(hdc, tempX, tempY);
}
