#include "pch.h"
#include "FieldWeapon.h"

void FieldWeapon::Fire(float x, float y, WeaponType type)
{
	mImage = ImageManager::GetInstance()->FindImage(L"FieldWeapon");
	mImage2 = ImageManager::GetInstance()->FindImage(L"FieldWeaponBack");
	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mSizeX2 = mImage2->GetFrameWidth();
	mSizeY2 = mImage2->GetFrameHeight();
	mRect = RectMakeCenter(mX,mY,mSizeX,mSizeY);
	mRect2 = RectMakeCenter(mX,mY,mSizeX2,mSizeY2);

	mType = type;
	if (mType==WeaponType::Confodere)
	{
		mIndexY = 0;
	}
	else if (mType==WeaponType::Secare)
	{
		mIndexY = 1;
	}
	mFrameCount = 0;
	mAlpha = 0;
	mAppear=false;
	mAppear2=false;
	mIndexX2 = 0;
}

void FieldWeapon::Release()
{
	if (mEffect != nullptr)
	{
		mEffect->Release();
		SafeDelete(mEffect);
	}
}

void FieldWeapon::Update()
{
	mFrameCount++;
	if (mFrameCount > 13)
	{
		mFrameCount = 0;
		mIndexX = 0;
		mAlpha += 0.2f;
		if (mAlpha > 1)
		{
			mAlpha = 0;
		}
		mIndexX2++;
		if (mIndexX2 > 7)
		{
			mIndexX2 = 0;
		}
	}
	if (mAppear == true)
	{
		if (mEffect == nullptr)
		{
			mEffect = new Effect;
			mEffect->Init(EffectType::PointEffect,mX,mY,0);
			mEffect->SetPlayer(mPlayer);
		}
	}
	else if (mAppear == false)//아에 지워질까?
	{
		if (mEffect != nullptr)
		{
			mEffect->Release();
			SafeDelete(mEffect);
		}
	}
	if (mEffect != nullptr)
	{
		mEffect->Update();
	}

	if (mEffect != nullptr)
	{
		POINT pt = { mPlayer->GetX(),mPlayer->GetY() };
		RECT effectRect = mEffect->GetRect();
		if (PtInRect(&effectRect, pt)==true)
		{
			mAppear2 = true;
		}
	}
}

void FieldWeapon::Render(HDC hdc, float cameraX, float cameraY)
{
	//for (int i = 0; i < 7; i++)
	//{
	//	mImage2->AlphaFrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, i, 0, mAlpha);
	//}
	mImage2->FrameRender(hdc, mRect2.left + cameraX, mRect2.top + cameraY, mIndexX2, 0);

	mImage->AlphaFrameRender(hdc, mRect.left + cameraX, mRect.top +cameraY, 0, mIndexY, mFrameCount % 2);
	if (mAppear == false)
	{
		mImage->AlphaFrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, 1, mIndexY, 1);
	}
	//이펙트 그려주기
	if (mEffect != nullptr)
	{
		mEffect->Render(hdc, cameraX, cameraY);
	}

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		//RECT Rect = { mRect.left + cameraX, mRect.top + cameraY, mRect.right + cameraX, mRect.bottom + cameraY };
		//RenderRect(hdc, Rect);
		RECT Rect = { mRect2.left + cameraX, mRect2.top + cameraY, mRect2.right + cameraX, mRect2.bottom + cameraY };
		RenderRect(hdc, Rect);
	}
}
