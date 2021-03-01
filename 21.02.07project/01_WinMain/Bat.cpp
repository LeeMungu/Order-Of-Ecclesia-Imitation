#include "pch.h"
#include "Bat.h"
#include "Monster.h"
#include "Player.h"

void Bat::Move()
{
	if (mIsFallow == true && mAngle==-1)
	{
		mAngle = Math::GetAngle(mPlayer->GetX(), mPlayer->GetY(), mX, mY);
	}
	if (mState == MonsterState::Move)
	{
		mX += cosf(mAngle) * mSpeed;
		mY -= sinf(mX/180*PI) * mSpeed;
		if (mX > 770)
		{
			mX = mStartX;
		}
	}
		//위아래로 이동하는것도 구현할것
	if (mAngle<PI / 2 || mAngle>PI / 2 * 3)
	{
		mMotionLR = 1;
	}
	else
	{
		mMotionLR = 0;
	}

}

void Bat::UpdateFrame()
{
	mFrameCount++;
	if (mFrameCount > mLimitCount)
	{
		mFrameCount = 0;
		if (mMotionLR == 0)
		{
			mIndexX++;
			switch (mState)
			{
			case MonsterState::Generation:
				mIndexY = 0;
				if (mIndexX > 2)
				{
					mIndexX = 0;
				}
				break;
			case MonsterState::Move:
				mIndexY = 1;
				if (mIndexX > 12)
				{
					mIndexX = 0;
				}
				break;
			case MonsterState::Extinction:
				if (mIndexX > 12)
				{
					mExtence = true;
				}
				break;
			}
		}
		else if (mMotionLR == 1)
		{
			mIndexX--;
			switch (mState)
			{
			case MonsterState::Generation:
				mIndexY = 0 + 2;
				if (mIndexX < 12 - 2)
				{
					mIndexX = 12;
				}
				break;
			case MonsterState::Move:
				mIndexY = 1 + 2;
				if (mIndexX < 12 - 12)
				{
					mIndexX = 12;
				}
				break;
			case MonsterState::Extinction:
				if (mIndexX < 0)
				{
					mExtence = true;
				}
				break;
			}
		}
	}
}

void Bat::UpdateState()
{
	if (sqrtf(powf(mY-mPlayer->GetY(),2)) < 150 && mIsFallow == false)//후에 y축 보정도 해줄것
	{
		//전환될때 만 한번실행
		mIsFallow = true;
		if (mMotionLR == 0)
		{
			mIndexX = 0;
		}
		else if (mMotionLR == 1)
		{
			mIndexX = 12;
		}
	}
	else if (Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY()) > 300)
	{
		mIsFallow = false;
	}
	if (mIsFallow == true)
	{
		mState = MonsterState::Move;
		mLimitCount = 5;
	}
}
