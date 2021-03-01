#include "pch.h"
#include "Map.h"

void Map::Init()
{
	mImageMapBack = ImageManager::GetInstance()->FindImage(L"MapBack");
	mBackSizeX = mImageMapBack->GetFrameWidth();
	mBackSizeY = mImageMapBack->GetFrameHeight();
	mBackX = WINSIZEX - mBackSizeX / 2;
	mBackY = 0 + mBackSizeY / 2;
	mBackRect = RectMakeCenter(mBackX, mBackY, mBackSizeX, mBackSizeY);

	mImageMap = ImageManager::GetInstance()->FindImage(L"Map");
	mSizeX = mImageMap->GetFrameWidth();
	mSizeY = mImageMap->GetFrameHeight();
	mX = mBackX;
	mY = mBackY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mPlayerSpot = new Effect();
	mPlayerSpot->Init(EffectType::MapEffect, mRect.left+10, mRect.bottom-10, 0);
}

void Map::Release()
{
	mPlayerSpot->Release();
	SafeDelete(mPlayerSpot);
}

void Map::Update()
{
	mPlayerSpot->SetPlayer(mPlayer);
	mPlayerSpot->Update();
}

void Map::Render(HDC hdc)
{
	mImageMapBack->AlphaFrameRender(hdc, mBackRect.left, mBackRect.top,0,0,0.7f);
	mImageMap->AlphaFrameRender(hdc, mRect.left, mRect.top, 0, 0, 0.7f);
	mPlayerSpot->Render(hdc, 0, 0);
}
