#include "pch.h"
#include "Zombi.h"
#include "Monster.h"
#include "Player.h"

void Zombi::InitDate()
{
	
}

void Zombi::Move()
{
	if (mIsFallow == false)
	{
		mFallowX = mPlayer->GetX();
		if (mFallowX <= mX)
		{
			if (mMotionLR == 1)
			{
				mIndexX = 23 - mIndexX;
			}
			mMotionLR = 0;
		}
		else
		{
			if (mMotionLR == 0)
			{
				mIndexX = 23 - mIndexX;
			}
			mMotionLR = 1;
		}
		mIsFallow = true;
	}
	if (mState == MonsterState::Move)
	{
		
		if (mMotionLR==0)
		{
			mX -= mSpeed;
		}
		else
		{
			mX += mSpeed;
		}
	}
	if (mState == MonsterState::Generation)
	{
		mLimitCount = 3;
	}
	else if (mState != MonsterState::Extinction)
	{
		mLimitCount = 20;
	}
}
void Zombi::UpdateFrame()
{
	mFrameCount++;
	if (mFrameCount > mLimitCount)
	{
		mFrameCount = 0;
		if (mMotionLR == 0)
		{
			mIndexX++;
			switch(mState)
			{
			case MonsterState::Generation:
				mIndexY=1;
				if (mIndexX > 17)
				{
					mState = MonsterState::Move;
					mIndexX = 0;
					mIndexY = 0;
				}
				break;
			case MonsterState::Move:
				mIndexY = 0;
				if (mIndexX > 11)
				{
					mIndexX = 0;
				}
				break;
				//거리가 되서 제거되는 기작이랑 HP감소로 제거되는 기작 둘다 있어야한다.
			case MonsterState::Extinction://indexY값은 처음 수정 될때 받기로->상태가 2줄이므로
				if (mIndexY == 2 && mIndexX > 23)
				{
					mIndexY = 3;
					mIndexX = 0;
				}
				else if(mIndexY==3 && mIndexX>18)
				{
					mIndexX = 0;
					//소멸 기작
					mExtence = true;
				}
				else if(mIndexY!=3)
				{
					mIndexY = 2;
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
				mIndexY = 1+4;
				if (mIndexX < 23-17)
				{
					mState = MonsterState::Move;
					mIndexX = 23;
					mIndexY = 4;
				}
				break;
			case MonsterState::Move:
				mIndexY = 0+4;
				if (mIndexX < 23-11)
				{
					mIndexX =23;
				}
				break;
			case MonsterState::Extinction://indexY값은 처음 수정 될때 받기로->상태가 2줄이므로
				if (mIndexY == 2+4 && mIndexX < 0)
				{
					mIndexY = 3+4;
					mIndexX = 23;
				}
				else if (mIndexY == 3+4 && mIndexX < 23-18)
				{
					mIndexX = 23;
					//소멸 기작
					mExtence = true;
				}
				else if (mIndexY!=3+4)
				{
					mIndexY = 2+4;
				}
				break;
			}
		}
	}
}
void Zombi::UpdateState()
{
	mExtenceCount++;
	if (mExtenceCount > Random::GetInstance()->RandomInt(800,1200))
	{
		mState = MonsterState::Extinction;
		mLimitCount = 3;
	}
}