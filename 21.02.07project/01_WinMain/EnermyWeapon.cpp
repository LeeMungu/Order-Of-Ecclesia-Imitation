#include "pch.h"
#include "EnermyWeapon.h"

void EnermyWeapon::Fire(float x, float y, float playerX, float playerY, EnermyWeaponType type)
{
	mType = type;
	if (mType == EnermyWeaponType::Attack1)
	{
		mImage = ImageManager::GetInstance()->FindImage(L"PointEffect");
		mX = x;
		mY = y;
		mSizeX = mImage->GetFrameWidth();
		mSizeY = mImage->GetFrameHeight();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mAngle = Math::GetAngle(mX, mY, playerX, playerY);

		mFrameCount = 0;
		mIndexX = 0;
		mIndexY = 0;
		mStartPlayerX = playerX;
		mStartPlayerY = playerY;
	}
	if (mType == EnermyWeaponType::Attack3)
	{
		mImage = ImageManager::GetInstance()->FindImage(L"BossAttack3");
		mX = x;
		mY = y;
		mSizeX = mImage->GetFrameWidth();
		mSizeY = 5;//mImage->GetFrameHeight();
		mRect = RectMakeCenter(mX-mSizeX/2, mY, mSizeX, mSizeY);

		mFrameCount = 0;
		mIndexX = 0;
		mIndexY = 0;
	}
}

void EnermyWeapon::Release()
{

}

void EnermyWeapon::Update()
{
	if (mType == EnermyWeaponType::Attack1)
	{
		mX += 5 * cosf(mAngle);
		mY -= 5 * sinf(mAngle);

		/*if (mX > mStartPlayerX)
		{
			mX -= 3;
		}
		else
		{
			mX += 3;
		}*/
		//y=-(-a(x^2)+b)
		//float a =(mY-mStartPlayerY)/(powf(mStartPlayerX,2)-powf(mX,2));
		//float b =mStartPlayerY+a*powf(mStartPlayerX,2);
		//mY = (-a)*powf((mX), 2) +b;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mFrameCount++;
		if (mFrameCount > 5)
		{
			mFrameCount = 0;
			mIndexX++;
			if (mIndexX > 2)
			{
				mIndexX = 0;
			}
		}
	}
	if (mType == EnermyWeaponType::Attack3)
	{
		mFrameCount++;
		{
			if (mFrameCount > 10)
			{
				mFrameCount = 0;
				mIndexY++;
				if (mIndexY > 3)
				{
					mIndexX++;
					if (mIndexX>2)
					{
						mIndexX = 0;
					}
				}
			}
		}
		if (mSizeY < 280)
		{
			mSizeY+=5;
		}
		mRect = RectMakeCenter(mX - mSizeX / 2, mY, mSizeX, mSizeY);
	}
}

void EnermyWeapon::Render(HDC hdc, float cameraX, float cameraY)
{
	if (mType == EnermyWeaponType::Attack1)
	{
		mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY);
	}
	else if (mType == EnermyWeaponType::Attack3)
	{
		mImage->ScaleFrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY, mSizeX, mSizeY);
	}
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RECT Rect = { mRect.left + cameraX, mRect.top + cameraY, mRect.right + cameraX, mRect.bottom + cameraY };
		RenderRect(hdc, Rect);
	}
}
