#include "pch.h"
#include "Weapon.h"

void Weapon::Fire(WeaponType type)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Weapon");
	mType = type;
	//mIndexY값
	switch (mType)
	{
	case WeaponType::Confodere:
		mIndexY = 0;
		mDamege = 8;
		break;
	case WeaponType::Secare:
		mIndexY = 1;
		mDamege = 12;
		break;
	}
	if (mPlayer->GetMotionRL() == 1)
	{
		mIndexY += 2;
	}

	if (mPlayer->GetMotionRL()==0)//오른쪽
	{
		mX = mPlayer->GetRect().left - 75;
		mY = mPlayer->GetRect().top - 75;
		mImageX = mX;
		mImageY = mY;
		switch (mPlayer->GetState())
		{
		case State::StandAttackLeft:
			mX += 200;
			mY += 112;
			mIndexX = 0;
			break;
		case State::StandAttackRight:
			mX += 156;
			mY += 120;
			mIndexX = 1;
			break;
		case State::DownAttackLeft:
			mX += 187;
			mY += 161;
			mIndexX = 2;
			break;
		case State::DownAttackRight:
			mX += 150;
			mY += 169;
			mIndexX = 3;
			break;
		case State::JumpAttackLeft:
			mX += 187;
			mY += 102;
			mIndexX = 4;
			break;
		case State::JumpAttackRight:
			mX += 162;
			mY += 113;
			mIndexX = 5;
			break;
		}
	}
	else if (mPlayer->GetMotionRL() == 1)//왼쪽
	{
		mX = mPlayer->GetRect().right+75;
		mY = mPlayer->GetRect().top-75;
		mImageX = mPlayer->GetRect().left - 75 - 75;
		mImageY = mPlayer->GetRect().top - 75;
		switch (mPlayer->GetState())
		{
		case State::StandAttackLeft:
			mX -= 200;
			mY += 112;
			mIndexX = 5;
			break;
		case State::StandAttackRight:
			mX -= 156;
			mY += 120;
			mIndexX = 4;
			break;
		case State::DownAttackLeft:
			mX -= 187;
			mY += 161;
			mIndexX = 3;
			break;
		case State::DownAttackRight:
			mX -= 150;
			mY += 169;
			mIndexX = 2;
			break;
		case State::JumpAttackLeft:
			mX -= 187;
			mY += 102;
			mIndexX = 1;
			break;
		case State::JumpAttackRight:
			mX -= 162;
			mY += 113;
			mIndexX = 0;
			break;
		}
		mX -= 85;
	}
	mSizeX = 85;
	mSizeY = 30;

	mStartImageX = mImageX;
	mStartImageY = mImageY;
	mStartX = mX;
	mStartY = mY;
	mStartPlayerX = mPlayer->GetX();
	mStartPlayerY = mPlayer->GetY();
	mRect = RectMake(mX,mY,mSizeX,mSizeY);
	mAppearance = false;
}

void Weapon::Release()
{
}

void Weapon::Update()
{
	mNowPlayerX = mPlayer->GetX();
	mNowPlayerY = mPlayer->GetY();

	mX = mStartX+mNowPlayerX - mStartPlayerX;
	mY = mStartY+mNowPlayerY - mStartPlayerY;
	mImageX = mStartImageX + mNowPlayerX - mStartPlayerX;
	mImageY = mStartImageY + mNowPlayerY - mStartPlayerY;

	mRect = RectMake(mX, mY, mSizeX, mSizeY);
}

void Weapon::Render(HDC hdc, float cameraX, float cameraY)
{
	if (mAppearance == true)
	{
		mImage->FrameRender(hdc, mImageX + cameraX, mImageY + cameraY, mIndexX, mIndexY);
	}
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RECT Rect = { mRect.left + cameraX, mRect.top + cameraY, mRect.right + cameraX, mRect.bottom + cameraY };
		RenderRect(hdc, Rect);
	}
}