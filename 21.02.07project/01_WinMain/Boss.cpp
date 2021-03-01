#include "pch.h"
#include "Boss.h"
#include "Monster.h"
#include "Player.h"

#define STARTLimit 8
void Boss::Release()
{
	if (mEnermyWeapon != NULL)
	{
		mEnermyWeapon->Release();
		SafeDelete(mEnermyWeapon);
	}
}

void Boss::Render(HDC hdc, float cameraX, float cameraY)
{
	if (mDamegeBool == true)
	{
		if (mKey == L"Boss")
		{
			mImage->AlphaFrameRender(hdc, mX - 400 + cameraX, mY - 310 + cameraY, mIndexX, mIndexY, mDamegeCount % 2);
		}
	}
	else if (mDamegeBool == false)
	{
		if (mState == MonsterState::Attack2)
		{
			mImage->FrameRender(hdc, mX - 337 + cameraX, mY - 337 + cameraY, mIndexX, mIndexY);//ATTACK2모션

		}
		else if (mKey == L"Boss")
		{
			mImage->FrameRender(hdc, mX - 400 + cameraX, mY - 310 + cameraY, mIndexX, mIndexY);
		}
	}
	if (mEnermyWeapon != NULL)
	{
		mEnermyWeapon->Render(hdc, cameraX, cameraY);
	}

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RECT Rect = { mRect.left + cameraX, mRect.top + cameraY, mRect.right + cameraX, mRect.bottom + cameraY };
		RenderRect(hdc, Rect);
	}
}

void Boss::Move()
{
	if (mState == MonsterState::Generation)
	{
		if (mRect.bottom < WINSIZEY - 48)
		{
			if (mIndexY != 0)
			{
				mY += 5;
			}
		}
		else if (mRect.bottom >= WINSIZEY - 48)
		{
			mState = MonsterState::Generation2;
			mIndexX = 0;
			mIndexY = 2;
		}
	}
	else if(mState != MonsterState::Attack2 
		&& mState != MonsterState::Attack1 && mState != MonsterState::Attack3)
	{
		mMotionCount++;
		if (mMotionCount > 250)
		{
			mMotionCount = 0;
			if (mState == MonsterState::Stand)
			{
				//int num = Random::GetInstance()->RandomInt(3);
				mFettenNum++;
				if (mFettenNum > 3)
				{
					mFettenNum = 0;
				}
				if (mFettenNum == 1)
				{
					mAttack2Count = 0;
					mState = MonsterState::Attack2;
					mIndexX = 0;
					mIndexY = 0;
					mLimitCount = 3;
					mImage = ImageManager::GetInstance()->FindImage(L"BossAttack2");
					mPlayerX = mPlayer->GetX();
					mPlayerY = mPlayer->GetY();
					//if (mPlayerX < mX)
					//{
					//	mMotionLR = 0;
					//}
					//else
					//{
					//	mMotionLR = 1;
					//}
					mSizeX = 335;
					mSizeY = 335;
					mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
					mAttack = 20;
				}
				else if (mFettenNum == 2)
				{
					mState = MonsterState::Attack1;
					mIndexX = 0;
					mIndexY = 37;
				}
				else if (mFettenNum == 3)
				{
					mState = MonsterState::Attack3;
					mIndexX = 0;
					mIndexY = 37;
				}
			}
		}
	}
	if (mState == MonsterState::Attack2)
	{
		if (mReversCount ==false )
		{
			mX -= 20;
		}
		else if (mReversCount== true)
		{
			mX += 20;
		}

		if(mX < 95+mSizeX/2)
		{
			mReversCount = true;
			mIndexY = 7;
			mIndexX = 1;
			mAttack2Count++;
		}
		if (mX > 1800 - 95 - mSizeX / 2)
		{
			mReversCount = false;
			mAttack2Count++;
		}
		//돌아오는 순간
		if (mAttack2Count > 2 && ((mReversCount==false&& mX < mStartX)||(mReversCount==true&& mX > mStartX)))
		{
			mReversCount = false;
			mState = MonsterState::Stand;
			mImage = ImageManager::GetInstance()->FindImage(L"Boss");
			mSizeX = 450;
			mSizeY = 280;
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			mIndexX = 0;
			mIndexY = 10;
			mLimitCount = STARTLimit;
			mAttack = 10;
		}
	}

	if (mEnermyWeapon != NULL)
	{
		//무기와 충돌시
		RECT tempRect;
		RECT enermyWeaponRect = mEnermyWeapon->GetRect();
		RECT playerRect = mPlayer->GetRect();
		if (IntersectRect(&tempRect, &enermyWeaponRect, &playerRect) && mPlayer->GetInvin()==false)
		{
			//hp깍는 작용
			mPlayer->SetHp(mPlayer->GetHp() - mAttack);
			//데미지 입은 상태
			mPlayer->SetState(State::Damege);
			//플레이어 무적
			mPlayer->SetInvin(true);
			//플레이어 프레임인데 위에 상태데미지와 검토요망
			if (mPlayer->GetX() < mX)
			{
				mPlayer->SetIndexX(8);
				mPlayer->SetMotionRL(0);
			}
			else
			{
				mPlayer->SetIndexX(24 - 8);
				mPlayer->SetMotionRL(1);
			}
		}
		mEnermyWeapon->Update();
		if (mEnermyWeapon->GetEnermyWeaponType() == EnermyWeaponType::Attack1)
		{
			if (mEnermyWeapon->GetY() > WINSIZEY || mEnermyWeapon->GetX() > 1800 || mEnermyWeapon->GetX() < 0
				|| mEnermyWeapon->GetY() < 0 || mEnermyWeapon->GetY() > WINSIZEY)
			{
				//폭발 효과 넣기->벽넘어가면 안넣어도 됨
				mEnermyWeapon->Release();
				SafeDelete(mEnermyWeapon);
			}
		}
		//else if (mEnermyWeapon->GetEnermyWeaponType() == EnermyWeaponType::Attack3)
		//{
		//	if (mBeamCount > 8)
		//	{
		//		mEnermyWeapon->Release();
		//		SafeDelete(mEnermyWeapon);
		//	}
		//}
		
	}
}

void Boss::UpdateFrame()
{
	mFrameCount++;
	if (mFrameCount > mLimitCount)
	{
		mFrameCount = 0;
		if (mMotionLR == 0)
		{
			if (mReversCount == false)
			{
				mIndexX++;
			}
			else if (mReversCount == true)
			{
				mIndexX--;
			}
			switch (mState)
			{
			case MonsterState::Generation:
				if (mIndexX > 1)
				{
					mIndexX = 0;
					mIndexY++;
				}
				if (mIndexY > 1)
				{
					mIndexY = 1;
				}
				break;
			case MonsterState::Generation2:
				if (mIndexX > 1)
				{
					mIndexX = 0;
					mIndexY++;
				}
				if (mIndexY > 9)
				{
					mState = MonsterState::Stand;
					mIndexX = 0;
				}
				break;
			case MonsterState::Stand://10
				if (mIndexX > 1)
				{
					mIndexX = 0;
					mIndexY++;
				}
				if (mIndexY > 17)
				{
					mIndexX = 0;
					mIndexY = 10;
				}
				break;
			case MonsterState::Move:
				if (mIndexX > 1)
				{
					mIndexX = 0;
					mIndexY++;
				}
				if (mIndexY > 37)
				{
					mIndexY = 10;
				}
				break;
			case MonsterState::Attack1://37~
				if (mReversCount == false)
				{
					if (mIndexX > 1)
					{
						mIndexX = 0;
						mIndexY++;
					}
					if (mIndexY > 40)
					{
						mReversCount = true;
						mIndexY = 40;
						//탄환 생성
						if (mEnermyWeapon != nullptr)
						{
							//Null이 아닐때
							mEnermyWeapon->Release();
							SafeDelete(mEnermyWeapon);
						}
						mPlayerX = mPlayer->GetX();
						mPlayerY = mPlayer->GetY();
						mEnermyWeapon = new EnermyWeapon();
						mEnermyWeapon->Fire(mX - mSizeX / 2, mY, mPlayerX, mPlayerY, EnermyWeaponType::Attack1);
						
					}
				}
				else if (mReversCount == true)
				{
					if (mIndexX<0)
					{
						mIndexX = 1;
						mIndexY--;
					}
					if (mIndexY < 37)
					{
						mReversCount = false;
						mState = MonsterState::Stand;
						mIndexX = 0;
						mIndexY = 10;
					}
				}
				break;
			case MonsterState::Attack2://파일 새로불러오고 모션 끝날때
				if (mReversCount == false)
				{
					if (mIndexX > 1)
					{
						mIndexX = 0;
						mIndexY++;
					}
					if (mIndexY > 7)
					{
						mIndexY = 0;
					}
				}
				else if (mReversCount == true)
				{
					if (mIndexX < 0)
					{
						mIndexX = 1;
						mIndexY--;
					}
					if (mIndexY < 0)
					{
						mIndexY = 7;
					}
				}
				break;
			case MonsterState::Attack3://37~
				if (mReversCount == false)
				{
					if (mIndexX > 1)
					{
						mIndexX = 0;
						mIndexY++;
					}
					if (mIndexY > 40)
					{
						mBeamCount++;
						if (mBeamCount > 10)
						{
							mBeamCount = 0;
							mReversCount = true;
						}
						mIndexY = 40;
						//탄환 생성
						if (mBeamCount < 8)
						{
							if (mEnermyWeapon != NULL)
							{
								mEnermyWeapon->Release();
								SafeDelete(mEnermyWeapon);
							}
							mPlayerX = mPlayer->GetX();
							mPlayerY = mPlayer->GetY();
							mEnermyWeapon = new EnermyWeapon();
							mEnermyWeapon->Fire(mX - mSizeX / 2, mY, mPlayerX, mPlayerY, EnermyWeaponType::Attack3);
						}
					}
				}
				else if (mReversCount == true)
				{
					if (mEnermyWeapon != NULL)
					{
						mEnermyWeapon->Release();
						SafeDelete(mEnermyWeapon);
					}
					if (mIndexX < 0)
					{
						mIndexX = 1;
						mIndexY--;
					}
					if (mIndexY < 37)
					{
						mReversCount = false;
						mState = MonsterState::Stand;
						mIndexX = 0;
						mIndexY = 10;
					}
				}
				break;
			case MonsterState::Extinction:
				if (mIndexX > 1)
				{
					mIndexX = 0;
					mIndexY++;
				}
				if (mIndexY > 17)
				{
					mIndexX = 0;
					mIndexY = 10;
					mExtence = true;
				}
				break;
			}
		}
	}
}

void Boss::UpdateState()
{
}
