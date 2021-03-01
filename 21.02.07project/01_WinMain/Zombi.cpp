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
				//�Ÿ��� �Ǽ� ���ŵǴ� �����̶� HP���ҷ� ���ŵǴ� ���� �Ѵ� �־���Ѵ�.
			case MonsterState::Extinction://indexY���� ó�� ���� �ɶ� �ޱ��->���°� 2���̹Ƿ�
				if (mIndexY == 2 && mIndexX > 23)
				{
					mIndexY = 3;
					mIndexX = 0;
				}
				else if(mIndexY==3 && mIndexX>18)
				{
					mIndexX = 0;
					//�Ҹ� ����
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
			case MonsterState::Extinction://indexY���� ó�� ���� �ɶ� �ޱ��->���°� 2���̹Ƿ�
				if (mIndexY == 2+4 && mIndexX < 0)
				{
					mIndexY = 3+4;
					mIndexX = 23;
				}
				else if (mIndexY == 3+4 && mIndexX < 23-18)
				{
					mIndexX = 23;
					//�Ҹ� ����
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