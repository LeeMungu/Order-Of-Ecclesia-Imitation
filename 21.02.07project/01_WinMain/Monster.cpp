#include "pch.h"
#include "Monster.h"
#include "Image.h"
#include "Player.h"

void Monster::Init(wstring key, float x, float y, float speed, float angle)
{
	mKey = key;
	mImage = ImageManager::GetInstance()->FindImage(mKey);
	mX = x;
	mY = y;
	mSpeed = speed;
	mAngle = angle;
	mFrameCount = 0;
	mLimitCount = 20;
	if (mKey == L"Zombi")
	{
		mSizeX = 75;//mImage->GetFrameWidth();
		mSizeY = 150;//mImage->GetFrameHeight();
		mIndexY = 1;
		mAttack = 5;
		mHpMax = 24;
		mHp = mHpMax;
		mStartX = mX;
		mStartY = mY;
		mAngle = -1;
	}
	else if (mKey == L"Bat")
	{
		mSizeX = 75;//mImage->GetFrameWidth();
		mSizeY = 150;//mImage->GetFrameHeight();
		mAttack = 5;
		mHpMax = 5;
		mHp = mHpMax;
	}
	else if (mKey == L"Boss")
	{
		mImageMotion = ImageManager::GetInstance()->FindImage(L"BossAttack2");
		mSizeX = 450;//335;//mImage->GetFrameWidth();
		mSizeY = 280;//335;//mImage->GetFrameHeight();
		mAttack = 10;
		mIndexY = 0;
		mHpMax = 200;
		mHp = mHpMax;
		mLimitCount = 8;
		mStartX = mX;
		mBeamCount = 0;
	}
	
	mState = MonsterState::Generation;
	mIndexX = 0;
	mIsFallow = false;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mExtence = false;
	mExtenceCount = 0;
	mAttackBool = false;
	mAttackCount = 0;
	mDamegeBool = false;
	mDamegeCount = 0;
	InitDate();
}

void Monster::Release()
{

}

void Monster::Update()
{
	if (mHp <= 0)
	{
		mState = MonsterState::Extinction;
		mLimitCount = 3;
	}
	Move();
	UpdateFrame();
	UpdateState();
	UpdateCrash();
	

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Monster::Render(HDC hdc , float cameraX, float cameraY)
{
	if (mDamegeBool == true)
	{
		if (mKey == L"Zombi")
		{
			mImage->AlphaFrameRender(hdc, mRect.left - 75 + cameraX, mRect.top - 75 + cameraY, mIndexX, mIndexY, mDamegeCount % 2);
		}
		else if (mKey == L"Bat")
		{
			mImage->AlphaFrameRender(hdc, mRect.left + cameraX, mRect.top + cameraY, mIndexX, mIndexY, mDamegeCount % 2);
		}
	}
	else if (mDamegeBool==false)
	{
		if (mKey == L"Zombi")
		{
			mImage->FrameRender(hdc, mRect.left - 75 + cameraX, mRect.top - 75 + cameraY, mIndexX, mIndexY);
		}
		else if (mKey == L"Bat")
		{
			mImage->FrameRender(hdc, mRect.left + cameraX, mRect.top  + cameraY, mIndexX, mIndexY);
		}
		
	}

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RECT Rect = { mRect.left + cameraX, mRect.top + cameraY, mRect.right + cameraX, mRect.bottom + cameraY };
		RenderRect(hdc, Rect);
	}
}

void Monster::UpdateCrash()
{
	//공격 했을 때
	if (mAttackBool == true)
	{
		mAttackCount++;
	}
	if (mAttackCount > 200)
	{
		mAttackCount = 0;
		mAttackBool = false;
	}

	//공격 당했을 때
	if (mDamegeBool == true)
	{
		mDamegeCount++;
	}
	else if (mDamegeBool == false)
	{
		mDamegeCount = 0;
	}

	if (mDamegeCount > 30)
	{
		mDamegeCount = 0;
		mDamegeBool = false;
	}
}