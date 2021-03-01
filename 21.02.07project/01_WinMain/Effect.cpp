#include "pch.h"
#include "Effect.h"
#include "Image.h"

//num은 한자리수만
void Effect::Init(EffectType type, float x, float y, int num)
{
	mType = type;
	if (mType == EffectType::NumberEffect)
	{
		mImage = ImageManager::GetInstance()->FindImage(L"Number");
		mNum = num;
		mIndexY = 0;
	}
	else if (mType == EffectType::WeaponEffect)
	{
		mImage = ImageManager::GetInstance()->FindImage(L"WeaponEffect");
		mIndexY = num;//좌우 구분용
		if (mIndexY == 0)
		{
			mIndexX = 0;
		}
		else if (mIndexY == 1)
		{
			mIndexX = 4;
		}
	}
	else if (mType == EffectType::HitEffect)
	{
		mImage = ImageManager::GetInstance()->FindImage(L"HitEffect");
		mIndexY = num;//0 ->, 1 <- 
		if (mIndexY == 0)
		{
			mIndexX = 0;
		}
		else if (mIndexY == 1)
		{
			mIndexX = 10;
		}
	}
	else if (mType == EffectType::PointEffect)
	{
		mImage = ImageManager::GetInstance()->FindImage(L"PointEffect");
		mIndexY = 0;
		mIndexX = 0;
	}
	else if (mType == EffectType::MapEffect)
	{
		mImage = ImageManager::GetInstance()->FindImage(L"PointEffect");
		mIndexY = 0;
		mIndexX = 6;
	}
	else if (mType == EffectType::DestroyEffect)
	{
		mImage = ImageManager::GetInstance()->FindImage(L"Explosion");
		mIndexY = 0;
		mIndexX = 0;
	}
	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mCount = 0;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	if (mType == EffectType::PointEffect || mType == EffectType::MapEffect)
	{
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	if (mType == EffectType::MapEffect)
	{
		mStartX = mX;
		mStartY = mY;
	}
	else if (mType == EffectType::DestroyEffect)
	{
		mSizeX = 300;
		mSizeY = 400;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	
	mExtence = false;
}

void Effect::Release()
{
}

void Effect::Update()
{
	if (mType == EffectType::NumberEffect)
	{
		mY -= 1;
		mCount++;
		if (mCount > 50)
		{
			mCount = 0;
			mExtence = true;
		}
	}
	else if (mType == EffectType::WeaponEffect)
	{
		mCount++;
		if (mCount > 4)
		{
			mCount = 0;
			if (mIndexY == 0)
			{
				mIndexX++;
			}
			else if (mIndexY == 1)
			{
				mIndexX--;
			}
		}
		if (mIndexY == 0)
		{
			if (mIndexX > 4)
			{
				mExtence = true;
			}
		}
		else if (mIndexY == 1)
		{
			if (mIndexX < 0)
			{
				mExtence = true;
			}
		}
	}
	else if (mType == EffectType::HitEffect)
	{
		mCount++;
		if (mCount > 3)
		{
			mCount = 0;
			if(mIndexY==0)
			{
				mIndexX++;
				if (mIndexX > 10)
				{
					mExtence = true;
				}
			}
			else if(mIndexY==1)
			{ 
				mIndexX--;
				if (mIndexX < 0)
				{
					mExtence = true;
				}
			}
		}
	}
	else if (mType == EffectType::PointEffect)
	{
		mAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
		mX += cosf(mAngle) * 5;
		mY -= sinf(mAngle) * 5;
		mCount++;
		if (mCount > 2)
		{
			mCount = 0;
			mIndexX++;
			if(mIndexX>9)
			{
				mIndexX = 0;
			}
		}
	}
	else if (mType == EffectType::MapEffect)
	{
		if (mPlayer->GetStageSet() == true)
		{
			mStartX = mX;
			mStartY = mY;

			//mStartX -= 20;

			//if (mPlayer->GetDoorType() == DoorType::Front)
			//{
			//	mStartX += 1000;
			//
			//}
			if (mPlayer->GetDoorType() == DoorType::Back)
			{
				mStartX -= 38;
				if (mPlayer->GetStageNum() == 1)
				{
					mStartY += 38;
				}
			}
		}
		else if(mPlayer->GetStageNum()==0)
		{
			mX = mStartX-( mPlayer->GetCameraX() / 2565 * (35+40));
		}
		else if(mPlayer->GetStageNum() == 1)
		{
			mY = mStartY - (mPlayer->GetCameraY() / 1680 * 54);
		}
		else if(mPlayer->GetStageNum() == 2)
		{
			mX = mStartX - (mPlayer->GetCameraX() / 5000 * (75+60));
		}
		else if(mPlayer->GetStageNum() == 3)
		{
			mX = mStartX - (mPlayer->GetCameraX() / 1800 * 28);
		}
		mCount++;
		if (mCount > 5)
		{
			mCount = 0;
			mIndexX++;
			if (mIndexX>7)
			{
				mIndexX = 6;
			}
		}
	}
	else if (mType == EffectType::DestroyEffect)
	{
		mCount++;
		if (mCount > 3)
		{
			mCount = 0;
			mIndexX++;
			if (mIndexX > 25)
			{
				mExtence=true;
			}
		}
	}
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	if (mType == EffectType::PointEffect || mType == EffectType::MapEffect
		||mType == EffectType::DestroyEffect)
	{
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
}

void Effect::Render(HDC hdc, float cameraX, float cameraY)
{
	if (mType == EffectType::NumberEffect)
	{
		if (mNum < 10)
		{
			mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mNum, mIndexY);
		}
		else if (mNum < 100)
		{
			mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mNum / 10, mIndexY);
			mImage->FrameRender(hdc, mRect.right + cameraX, mRect.top + cameraY, mNum % 10, mIndexY);
		}
	}
	else if (mType == EffectType::WeaponEffect)
	{
		mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY);
	}
	else if (mType == EffectType::HitEffect)
	{
		mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY);
	}
	else if (mType == EffectType::PointEffect)
	{
		mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY);
	}
	else if (mType == EffectType::MapEffect)
	{
		mImage->FrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY);
	}
	else if (mType == EffectType::DestroyEffect)
	{
		mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY,300,400);
	}
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RECT Rect = { mRect.left + cameraX, mRect.top + cameraY, mRect.right + cameraX, mRect.bottom + cameraY };
		RenderRect(hdc, Rect);
	}
}
