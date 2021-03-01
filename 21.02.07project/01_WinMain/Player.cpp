#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Object.h"
#include "Effect.h"

#define STARTJUMPPAWER -20
#define GRAVITY 1
#define STANSLIMITCOUNT 8
#define STARTSTAGE 0

void Player::Init(wstring key, float x, float y, float speed, float angle)
{
	mImage = ImageManager::GetInstance()->FindImage(key);
	mGageImage = ImageManager::GetInstance()->FindImage(L"Gage");
	mHpImage = ImageManager::GetInstance()->FindImage(L"Hp");
	mMpImage = ImageManager::GetInstance()->FindImage(L"Mp");
	mNumImage = ImageManager::GetInstance()->FindImage(L"Number");
	mX = x; 
	mY = y;
	mSizeX = 75;//mImage->GetFrameWidth();
	mSizeY = 150;//mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = speed;
	mFrameCount = 0;
	mLimitCount = STANSLIMITCOUNT;
	mState = State::Stand;
	mPositionState = PositionState::Air;
	mGravity = GRAVITY;
	mIndexX = 0;
	mIndexY = 0;
	mAttackRight = false;
	mAttackLeft = false;

	mCameraX = 0;
	mCameraY = 0;

	//초기화
	mHpMax = 128;
	mMpMax = 80;
	mHp = mHpMax;
	mMp = mMpMax;
	mSpMax = 50;
	mSp = mSpMax;
	mStageNum = STARTSTAGE;
	mStageSet = false;
	mWeaponType = WeaponType::Confodere;
}

void Player::Release()
{
	if (mWeapon != NULL)
	{
	mWeapon->Release();
	SafeDelete(mWeapon);
	}
}

void Player::Update()
{
	mBeforeX = mX;
	mBeforeY = mY;
	//방향키 조작
	Control();
	UpdateFrame();
	UpdateState();
	UpdateFootBord();
	UpdateCamera();

	//Mp자연 회복
	if (mMp < mMpMax && mAttackLeft==false && mAttackRight==false)
	{
		mMp ++;
	}//max값 보정해줘야한다.

	//무기생성
	//if (mAttackLeft==true || mAttackRight == true)
	//{
	//	if (mWeapon == NULL)
	//	{
	//		mWeapon = new Weapon();
	//		mWeapon->SetPlayerPtr(this);
	//		mWeapon->Fire(WeaponType::Confodere);
	//	}
	//}
	//else if (mWeapon != NULL)
	//{
	//	mWeapon->Release();
	//	SafeDelete(mWeapon);
	//}

	//무기 업데이트
	if (mWeapon != NULL )
	{
		mWeapon->Update();
	}

	//플레이어 보정
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	//케릭터
	if (mInvincibility == true && mState!=State::Evasion)
	{
		mImage->AlphaFrameRender(hdc, mRect.left - 75 + mCameraX, mRect.top - 75 + mCameraY, mIndexX, mIndexY, (mInviCount%2)/2+0.5f);
	}
	else
	{
		mImage->FrameRender(hdc, mRect.left - 75 + mCameraX, mRect.top - 75 + mCameraY, mIndexX, mIndexY);
	}

	//무기
	if (mWeapon != NULL)
	{
		mWeapon->Render(hdc, mCameraX, mCameraY);
	}

	//Gage
	mGageImage->Render(hdc, 0, 0);
	mHpImage->Render(hdc, 0, 0,0,0,78+192*mHp/mHpMax,mHpImage->GetHeight());
	mMpImage->Render(hdc, 0, 0,0,0,78+192*mMp/mMpMax,mMpImage->GetHeight());
	//HPnum
	if ((mHp / 100) % 10 != 0)
	{
		mNumImage->FrameRender(hdc, 20, 5, (mHp / 100) % 10, 0);
	}
	if ((mHp / 100) % 10 != 0 || (mHp / 10) % 10 != 0)
	{
		mNumImage->FrameRender(hdc, 20 + mNumImage->GetFrameWidth(), 5, (mHp / 10) % 10, 0);
	}
	mNumImage->FrameRender(hdc, 20 + 2*mNumImage->GetFrameWidth(), 5, (mHp) % 10, 0);
	//MPnum
	if ((mMp / 100) % 10 != 0)
	{
		mNumImage->FrameRender(hdc, 40, 38, (mMp / 100) % 10, 0);
	}
	if ((mMp / 100) % 10 != 0 || (mMp / 10) % 10 != 0)
	{
		mNumImage->FrameRender(hdc, 40 + mNumImage->GetFrameWidth(), 38, (mMp / 10) % 10, 0);
	}
	mNumImage->FrameRender(hdc, 40 + 2 * mNumImage->GetFrameWidth(), 38, (mMp) % 10, 0);
	//SPnum - 잠정중단
	/*if ((mSp / 100) % 10 != 0)
	{
		mNumImage->FrameRender(hdc, 40, 38, (mSp / 100) % 10, 0);
	}
	if ((mSp / 100) % 10 != 0 || (mSp / 10) % 10 != 0)
	{
		mNumImage->FrameRender(hdc, 40 + mNumImage->GetFrameWidth(), 38, (mSp / 10) % 10, 0);
	}
	mNumImage->FrameRender(hdc, 40 + 2 * mNumImage->GetFrameWidth(), 38, (mSp) % 10, 0);*/
	
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RECT Rect = RectMakeCenter(mX + mCameraX, mY + mCameraY, mSizeX, mSizeY);
		RenderRect(hdc, Rect);
	}
}

void Player::Control()
{
	if (Input::GetInstance()->GetKeyDown(VK_UP))
	{
		mState = State::Up;
		if (mMotionRL == 0)
		{
			mIndexX = 0;
		}
		else if (mMotionRL == 1)
		{
			mIndexY = 24;
		}
		mLimitCount = STANSLIMITCOUNT;
	}
	if (Input::GetInstance()->GetKey(VK_UP))
	{
		if ((Input::GetInstance()->GetKeyDown('A') || Input::GetInstance()->GetKeyDown('S')) && mAttackLeft == false && mAttackRight == false)
		{
			if (mMotionRL == 0)
			{
				mIndexX = 0;
			}
			else if (mMotionRL == 1)
			{
				mIndexX = 24;
			}
			mState = State::SpAttack;
			mSp -= 15;
			mAttackLeft = true;
			mAttackRight = true;
		}
	}
	if (Input::GetInstance()->GetKeyUp(VK_UP) && mState != State::SpAttack)
	{
		mState = State::Stand;
		if (mMotionRL == 0)
		{
			mIndexX = 0;
		}
		else if (mMotionRL == 1)
		{
			mIndexX = 24;
		}
	}
	if (mState != State::Up && mAttackLeft == false && mAttackRight == false && mInvincibility==false)
	{
		if (Input::GetInstance()->GetKeyDown(VK_DOWN))
		{
			mState = State::Down;
			if (mMotionRL == 0)
			{
				mIndexX = 0;
			}
			else if (mMotionRL == 1)
			{
				mIndexY = 24;
			}
			mLimitCount = STANSLIMITCOUNT;
		}
		if (Input::GetInstance()->GetKey(VK_DOWN))
		{
			mLimitCount = STANSLIMITCOUNT;
		}
		if (Input::GetInstance()->GetKeyUp(VK_DOWN))
		{
			mState = State::Stand;
		}
		if (Input::GetInstance()->GetKeyDown(VK_LEFT))
		{
			if (mMotionRL == 0)
			{
				mState = State::RightTurnLeft;
				mIndexX = 24;
				mIndexY = 9 + 18;
				mLimitCount = 3;
			}
			if (mState != State::JumpUp && mState != State::JumpDown && mState != State::RightTurnLeft)
			{
				mState = State::Run;
				mIndexX = 24;
				mLimitCount = 1;
			}
			mMotionRL = 1;
			//mMotionRL = 1;//왼쪽방향보기<-
		}
		if (Input::GetInstance()->GetKey(VK_LEFT))//인덱스 초기화를 해주긴 해야하는데...처음 한번만 가능하게 해줘야한다.
		{
			if (mMotionRL == 0 || mState == State::Stop)
			{
				mState = State::RightTurnLeft;
				mIndexX = 24;
				mIndexY = 9 + 18;
				mLimitCount = 3;
				mMotionRL = 1;
			}
			if (mState != State::JumpUp && mState != State::JumpDown && mState != State::RightTurnLeft)
			{
				mState = State::Run;
				mLimitCount = 1;
			}
			Move(-mSpeed, 0);
		}
		if (Input::GetInstance()->GetKeyUp(VK_LEFT))
		{
			mLimitCount = 5;
			mState = State::Stop;
			mIndexX = 24;
		}
		if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
		{
			if (mMotionRL == 1)
			{
				mState = State::LeftTurnRight;
				mIndexX = 0;
				mIndexY = 9;
				mLimitCount = 3;
			}
			if (mState != State::JumpUp && mState != State::JumpDown && mState != State::LeftTurnRight)
			{
				mState = State::Run;
				mIndexX = 0;
				mLimitCount = 1;
			}
			mMotionRL = 0;//오른쪽방향보기->
		}
		if (Input::GetInstance()->GetKey(VK_RIGHT))//인덱스 초기화를 해주긴 해야하는데...처음 한번만 가능하게 해줘야한다.
		{
			if (mMotionRL == 1 || mState == State::Stop)
			{
				mState = State::LeftTurnRight;
				mIndexX = 0;
				mIndexY = 9;
				mLimitCount = 3;
				mMotionRL = 0;
			}
			if (mState != State::JumpUp && mState != State::JumpDown && mState != State::LeftTurnRight)
			{
				mState = State::Run;
				mLimitCount = 1;
			}
			Move(mSpeed, 0);
		}
		if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
		{
			mLimitCount = 5;
			mState = State::Stop;
			mIndexX = 0;
		}
		if ((Input::GetInstance()->GetKeyDown(VK_SPACE) || Input::GetInstance()->GetKeyDown('Z')) && mJumpingCount < 1)
		{
			Jump();
		}
	}
	if (mState != State::Up && mInvincibility == false)
	{
		//공격
		//왼쪽
		if (Input::GetInstance()->GetKeyDown('A'))
		{
			if (mAttackLeft == false && mMp > 8)
			{
				mLimitCount = 2;
				if (mState == State::Stand || mState == State::Run
					|| mState == State::LeftTurnRight || mState == State::RightTurnLeft
					|| mState ==State::Stop || mState == State::StandAttackRight)
				{
					mState = State::StandAttackLeft;
					WeaponGeneration();
				}
				if (mState == State::JumpUp || mState == State::JumpDown)
				{
					mState = State::JumpAttackLeft;
					WeaponGeneration();
				}
				if (mState == State::Down)
				{
					mState = State::DownAttackLeft;
					WeaponGeneration();
				}
				if (mMotionRL == 0)
				{
					mIndexX = 0;
				}
				else if (mMotionRL == 1)
				{
					mIndexX = 24;
				}
				mMp -= 8;
				mAttackLeft = true;
				mAttackRight = false;
			}
		}
		//오른쪽
		if (Input::GetInstance()->GetKeyDown('S'))
		{
			if (mAttackRight == false && mMp > 8)
			{
				if (mState == State::Stand || mState == State::Run
					|| mState == State::LeftTurnRight || mState == State::RightTurnLeft
					|| mState == State::Stop || mState == State::StandAttackLeft)
				{
					mState = State::StandAttackRight;
					WeaponGeneration();
				}
				if (mState == State::JumpUp || mState == State::JumpDown)
				{
					mState = State::JumpAttackRight;
					WeaponGeneration();
				}
				if (mState == State::Down)
				{
					mState = State::DownAttackRight;
					WeaponGeneration();
				}
				if (mMotionRL == 0)
				{
					mIndexX = 0;
				}
				else if (mMotionRL == 1)
				{
					mIndexX = 24;
				}
				mMp -= 8;
				mAttackRight = true;
				mAttackLeft = false;
			}
		}
	}
	//회피
	if (Input::GetInstance()->GetKeyDown('Q'))
	{
		if (mMotionRL == 0)
		{
			Move(-mSpeed * 3, 0);
		}
		else if (mMotionRL == 1)
		{
			Move(mSpeed * 3, 0);
		}
		mState = State::Evasion;
		mAttackLeft = false;
		mAttackRight = false;
		if (mWeapon != NULL)
		{
			mWeapon->SetAppearance(false);
		}
		mInvincibility = true;
		mLimitCount = 4;
	}

	if (Input::GetInstance()->GetKeyDown('X'))
	{

	}
}

void Player::Move(float moveX, float moveY)
{
	mX += moveX;
	mY += moveY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Jump()
{
	mY -= 100;
	mJumpingPawer = STARTJUMPPAWER;
	mPositionState = PositionState::Jumping;
	mJumpingCount++;
	mState = State::JumpUp;

	//벽에 있을때 점프 판정 신경써야함-좌,우 나눠서 내려올때 갈라주기
	
	//공중(air-구체적으로는 낙하시)에 있을때는 점프가 안되야지-조건이 맞으면 아무것도 안한다.-낙하 점프? 1단은 가능
	if (mPositionState == PositionState::Air)
	{
		mJumpingCount++;
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::UpdateState()
{
	//무적판정
	if (mInvincibility == true)
	{
		mAttackLeft = false;
		mAttackRight = false;
		mInviCount++;
	}
	if (mInviCount > 30)
	{
		mInviCount = 0;
		mInvincibility = false;
	}
	//점핑상태일때 계속되는부분
	if (mPositionState == PositionState::Jumping)
	{
		mY += mJumpingPawer; //떨어지는 원동력 = onGround가 아닐때도 적용하고 싶다.
		mJumpingPawer += mGravity;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		if (mState == State::JumpUp && mJumpingPawer == 0)
		{
			mState = State::JumpDown;
		}
	}
	//점핑 상태가 아니면 점프횟수, 점프파워(유사중력-초기에는 up을 도와준다 ->그라운드나 벽타는 중일때 해줘야함
	//낙하시 차이 때문에 다른곳에서 초기화해줘야 한다.->바닥에 다을때?, 벽에 부딧혔을때

	//땅x, 벽x -> 중력	Air라는 공중에 있는 상태를 따로 만들자\
	//AIR 판정
	if (mPositionState == PositionState::Air)
	{
		//낙하상태므로 jumpingPawer가 0부터 시작해야한다. -앞에서 Air로 변할때 한번 초기화해줘야함
		//mPlayer.y += mPlayer.jumpingPawer; //떨어지는 원동력 = onGround가 아닐때도 적용하고 싶다.
		//mPlayer.jumpingPawer += mPlayer.gravity;
		//그냥 그래비티를 더해줘도 된다? - > 안된다...
		mY += mJumpingPawer;
		mJumpingPawer += mGravity;
		mState = State::JumpDown;
	}

	
}

void Player::UpdateFrame()
{
	//이미지 위치 잡기
	mFrameCount++;

	if (mFrameCount > mLimitCount)
	{
		mFrameCount = 0;
		if (mMotionRL == 0)//우측봄
		{
			mIndexX++;
			switch (mState)
			{
			case State::Stand: //10
				mIndexY = 0;
				if (mIndexX > 9)
				{
					mIndexX = 0;
					//mPlayer.attackMotion = false;
					
				}
				break;
			case  State::Run: //Limit 2// 버튼up할때 limitcount 0으로 리셋해줘도 된다.
				mIndexY = 2;
				if (mIndexX > 23)
				{
					mIndexX = 2;
				}
				break;
			case State::Stop:
				mIndexY = 3;
				if (mIndexX > 5)
				{
					mIndexX = 0;
					mIndexY = 0;
					mState=State::Stand;
					mLimitCount = STANSLIMITCOUNT;
				}
				break;
			case  State::JumpUp:
				mIndexY = 4;
				if (mIndexX > 11)
				{
					mIndexX = 0;
				}
				break;
			case State::JumpDown:
				mIndexY = 5;
				if (mIndexX > 3)//바닥에 닫기전에 보정한번해줘야한다.
				{
					mIndexX = 2;
				}
				break;
			case State::JumpDrop:
				mIndexY = 5;
				if (mIndexX == 1)
				{
					if (mWeapon != NULL && mWeapon->GetAppearance() == true)
					{
						mWeapon->SetAppearance(false);
					}
				}
				if (mIndexX > 6)
				{
					mState = State::Stand;
					mIndexX = 0;
				}
				break;
			case State::Down:
				mIndexY = 6;
				if (mIndexX > 11)
				{
					mIndexX = 11;
				}
				break;
			case State::Up: //10
				mIndexY = 7;
				if (mIndexX > 13)
				{
					mIndexX = 10;
				}
				break;
			case State::Evasion: // 회피 후에 무적판정 추가 좀더 빠른 템포 2?
				mIndexY = 8;
				if (mIndexX == 1)
				{
					if (mWeapon != NULL && mWeapon->GetAppearance() == true)
					{
						mWeapon->SetAppearance(false);
					}
				}
				if (mIndexX > 8)
				{
					mState=State::Stand;
					mIndexX = 0;
					mLimitCount = STANSLIMITCOUNT;
					mInvincibility = false;
				}
				break;
			case State::LeftTurnRight: //모션이 더빨라야함 1?
				mIndexY = 9;
				if (mIndexX > 9)
				{
					mState = State::Run;
					mIndexX = 0;
					mMotionRL = 0;
				}
				break;
			case State::StandAttackLeft:
				mIndexY = 10;
				if (mIndexX > 10)
				{
					mState = State::Stand;
					mIndexX = 0;
					mLimitCount = STANSLIMITCOUNT;
					mAttackLeft = false;
					mAttackRight = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX == 4)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::StandAttackRight:
				mIndexY = 11;
				if (mIndexX > 9)
				{
					mState = State::Stand;
					mIndexX = 0;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX == 2)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::DownAttackLeft://다운시 시작지점
				mIndexY = 12;
				if (mIndexX > 10)
				{
					mState = State::Down;
					mIndexX = 8;
					mLimitCount = STANSLIMITCOUNT;
					mAttackLeft = false;
					mAttackRight = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX == 7)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::DownAttackRight:
				mIndexY = 13;
				if (mIndexX > 10)
				{
					mState = State::Down;
					mIndexX = 11;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX == 2)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::JumpAttackLeft://업다운 구분해야한다.
				mIndexY = 14;
				if (mIndexX > 10)
				{
					mState = State::JumpDown;
					mIndexX = 0;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX == 5)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::JumpAttackRight:
				mIndexY = 15;
				if (mIndexX > 10)
				{
					mState = State::JumpDown;
					mIndexX = 0;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX == 2)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::Damege://처음 mIndexX=8
				mIndexY = 8;
				if(mIndexX==9)
				{ 
					mX -= 1;
					if (mWeapon != NULL && mWeapon->GetAppearance()==true)
					{
						mWeapon->SetAppearance(false);
					}
				}
				else if(mIndexX==10)
				{
					mX += 1;
				}
				if (mIndexX > 11)
				{
					if (mInvincibility == false)
					{
						mState = State::Stand;
						mIndexX = 0;
					}
					else
					{
						mIndexX = 8;
					}
				}
				break;
			case State::SpAttack:
				mIndexY = 17;
				if (mIndexX > 8)
				{
					mState = State::Stand;
					mIndexX = 0;
					mAttackRight = false;
					mAttackLeft = false;
				}
				break;
			}
		}
		else if (mMotionRL == 1)//좌측봄
		{//모션별로 길이가 다르기 때문에 --처리로는 예외처리 하나 더해줘야한다.
			//밑의 ||연산뒤에 오는 것들 같은것
			mIndexX--;
			switch (mState)
			{
			case State::Stand: //10
				mIndexY = 0+18;
				if (mIndexX < 24-9)//9)
				{
					mIndexX = 24;
					//mPlayer.attackMotion = false;
				}
				break;
			case  State::Run: //Limit 2// 버튼up할때 limitcount 0으로 리셋해줘도 된다.
				mIndexY = 2+18;
				if (mIndexX < 24-23)
				{
					mIndexX = 24-2;
				}
				break;
			case State::Stop:
				mIndexY = 3+18;
				if (mIndexX < 24-5)
				{
					mIndexX = 24-0;
					mIndexY = 0+18;
					mState = State::Stand;
					mLimitCount = STANSLIMITCOUNT;
				}
				break;
			case  State::JumpUp:
				mIndexY = 4+18;
				if (mIndexX < 24-11)
				{
					mIndexX = 24-0;
				}
				break;
			case State::JumpDown:
				mIndexY = 5+18;
				if (mIndexX < 24-3)//바닥에 닫기전에 보정한번해줘야한다.
				{
					mIndexX = 24-2;
				}
				break;
			case State::JumpDrop:
				mIndexY = 5+18;
				if (mIndexX == 24 - 1)
				{
					if (mWeapon != NULL && mWeapon->GetAppearance() == true)
					{
						mWeapon->SetAppearance(false);
					}
				}
				if (mIndexX < 24-6)
				{
					mState = State::Stand;
					mIndexX = 24;
				}
				break;
			case State::Down:
				mIndexY = 6+18;
				if (mIndexX < 24-11)
				{
					mIndexX = 24-11;
				}
				break;
			case State::Up: //10
				mIndexY = 7+18;
				if (mIndexX < 24-13)
				{
					mIndexX = 24-10;
				}
				break;
			case State::Evasion: // 회피 후에 무적판정 추가 좀더 빠른 템포 4?
				mIndexY = 8+18;
				if (mIndexX == 24 - 1)
				{
					if (mWeapon != NULL && mWeapon->GetAppearance() == true)
					{
						mWeapon->SetAppearance(false);
					}
				}
				if (mIndexX < 24-8)
				{
					mState = State::Stand;
					mIndexX = 24-0;
					mLimitCount = STANSLIMITCOUNT;
					mInvincibility = false;
				}
				break;
			case State::RightTurnLeft : //모션이 더빨라야함 1?
				mIndexY = 9+18;
				if (mIndexX < 24-9)
				{
					mState = State::Run;
					mIndexX = 24-0;
					mMotionRL = 1;
				}
				break;
			case State::StandAttackLeft:
				mIndexY = 10+18;
				if (mIndexX < 24-10)
				{
					mState = State::Stand;
					mIndexX = 24-0;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX < 24 - 4)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::StandAttackRight:
				mIndexY = 11+18;
				if (mIndexX < 24-9)
				{
					mState = State::Stand;
					mIndexX = 24-0;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX < 24 - 2)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::DownAttackLeft://다운시 시작지점
				mIndexY = 12+18;
				if (mIndexX < 24-10)
				{
					mState = State::Down;
					mIndexX = 24-8;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX < 24 - 7)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::DownAttackRight:
				mIndexY = 13+18;
				if (mIndexX < 24-10)
				{
					mState = State::Down;
					mIndexX = 24-11;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX < 24 - 2)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::JumpAttackLeft://업다운 구분해야한다.
				mIndexY = 14+18;
				if (mIndexX > 24-10)
				{
					mState = State::JumpDown;
					mIndexX = 24-0;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX < 24 - 5)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::JumpAttackRight:
				mIndexY = 15+18;
				if (mIndexX > 24-10)
				{
					mState = State::JumpDown;
					mIndexX = 24-0;
					mLimitCount = STANSLIMITCOUNT;
					mAttackRight = false;
					mAttackLeft = false;
					mWeapon->SetAppearance(false);
				}
				else if (mIndexX > 24 - 2)
				{
					mWeapon->SetAppearance(true);
				}
				break;
			case State::Damege://처음 mIndexX=24-8
				mIndexY = 8+18;
				if (mIndexX == 24-9)
				{
					mX += 1;
					if (mWeapon != NULL && mWeapon->GetAppearance() == true)
					{
						mWeapon->SetAppearance(false);
					}
				}
				else if (mIndexX == 24-10)
				{
					mX -= 1;
				}
				if (mIndexX > 24-11)
				{
					if (mInvincibility == false)
					{
						mState = State::Stand;
						mIndexX = 24 - 0;
					}
					else
					{
						mIndexX = 24 - 8;
					}
					
				}
				break;
			case State::SpAttack:
				mIndexY = 17+18;
				if (mIndexX > 24-8)
				{
					mState = State::Stand;
					mIndexX = 24-0;
					mAttackRight = false;
					mAttackLeft = false;
				}
				break;
			}
			
		}
	}

	//점프착지시 어택초기화
	if (mState == State::JumpDrop)
	{
		mAttackRight = false;
		mAttackLeft = false;
		if (mWeapon != NULL)
		{
			mWeapon->SetAppearance(false);
		}
	}

	//q로 회피시 뒤로
	if (mState == State::Evasion)
	{
		if (mMotionRL == 0)
		{
			Move(-mSpeed , 0);
		}
		else if (mMotionRL == 1)
		{
			Move(mSpeed , 0);
		}
	}
}

void Player::UpdateFootBord()
{
	if (mObjectList.size() != NULL)
	{
		for (int i = 0; i < mObjectList.size(); i++)
		{
			RECT temp;
			RECT footRect;//0번은 기본발판
			footRect = mObjectList[i]->GetRect();
			//벽타기 == 점프를 하고 있고?(공중에 있고?==Air), 벽과 충돌 했을때 (좌, 우, 상단==ground)
			if (//(mPlayer.positionState==PositionState::Jumping|| mPlayer.positionState == PositionState::Air) && 
				IntersectRect(&temp, &footRect, &mRect))
			{
				if (mObjectList[i]->GetType() == 0)
				{
					if (mPositionState == PositionState::Jumping)
					{
						if (mJumpingPawer >= 0)
						{
							//벽위에 서있기
							if (mY < footRect.top)// && mRect.right>footRect.left && mRect.left < footRect.right)
							{
								//보정시 내려앉으면 위치(rc.)보정까지 해주기
								mY = footRect.top - (mSizeY / 2);
								mPositionState = PositionState::OnGround;//그라운드 다시 돌리기
								mJumpingPawer = STARTJUMPPAWER;
								mJumpingCount = 0;
								mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
								mFootNum = i; //현제 있는 벽이 뭔지 구별하는것 반복문이면 후에 brack로 나오자
								break;
							}
						}
					}
					else if (mPositionState == PositionState::Air)
					{
						//벽위에 서있기
						if (mY < footRect.top)// && mRect.right>footRect.left && mRect.left < footRect.right)
						{
							//보정시 내려앉으면 위치(rc.)보정까지 해주기
							mY = footRect.top - (mSizeY / 2);
							mPositionState = PositionState::OnGround;//그라운드 다시 돌리기
							mJumpingPawer = STARTJUMPPAWER;
							mJumpingCount = 0;
							mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
							mFootNum = i; //현제 있는 벽이 뭔지 구별하는것 반복문이면 후에 brack로 나오자
							break;
						}
					}
				}
				else if (mObjectList[i]->GetType() == 1)
				{
					//벽위에 서있기
					if (mRect.top < footRect.top)// && mRect.right>footRect.left && mRect.left < footRect.right)
					{
						//보정시 내려앉으면 위치(rc.)보정까지 해주기
						mY = footRect.top - (mSizeY / 2);
						mPositionState = PositionState::OnGround;//그라운드 다시 돌리기
						mJumpingPawer = STARTJUMPPAWER;
						mJumpingCount = 0;
						mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
						mFootNum = i; //현제 있는 벽이 뭔지 구별하는것 반복문이면 후에 brack로 나오자
						break;
					}
					if (mPositionState == PositionState::Jumping || mPositionState == PositionState::Air)
					{
						//바닥의 스타일에 따라서 점프가 되고-안되고 정해야한다.
						int y;
						if (mPositionState == PositionState::Jumping)
						{
							y = mRect.bottom;
						}
						else
						{
							y = mY;//?
						}
						if (footRect.bottom < y)
						{
							mY = mObjectList[i]->GetRect().bottom + mSizeY / 2;
							mPositionState = PositionState::Air;
						}
						//벽왼쪽 부딛히기-부딧혔다고 점프 초기화 되면 안됨
						else if (mObjectList[i]->GetRect().right > mRect.right)
						{
							mX = mObjectList[i]->GetRect().left - mSizeX / 2;
						}
						//벽오른쪽 부딛히기- 부딧혔다고 점프 초기화 하면 안됨
						else if (mObjectList[i]->GetRect().left < mRect.left)
						{
							mX = mObjectList[i]->GetRect().right + mSizeX / 2;
						}
					}
					else
					{
						//벽왼쪽 부딧히기-점프 안했을때
						if (mObjectList[i]->GetRect().right > mRect.right)
						{
							mX = mObjectList[i]->GetRect().left - mSizeX / 2;
						}
						//벽오른쪽 부딧히기
						else if (mObjectList[i]->GetRect().left < mRect.left)
						{
							mX = mObjectList[i]->GetRect().right + mSizeX / 2;
						}
					}
				}
				else if (mObjectList[i]->GetType() == 2 && mStageSet==false)
				{
					mStageNum++;
					mStageSet = true;
					mStageCameraX = mCameraX;
					mStageCameraY = mCameraY;
					mCameraX = 0;
					mCameraY = 0;
					mDoorType = DoorType::Front;
					mStageStartX = mX;
					mStageStartY = mY;
				}
				else if (mObjectList[i]->GetType() == 3 && mStageSet == false)
				{
					mStageNum--;
					mStageSet = true;
					mCameraX = mStageCameraX;
					mCameraY = mStageCameraY;
					mDoorType = DoorType::Back;
				}
				mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			}
		}
	
	}

	if (mPositionState == PositionState::OnGround)//지면에 착지 할때
	{
		if (mObjectList[mFootNum]->GetRect().left > mRect.right || mObjectList[mFootNum]->GetRect().right < mRect.left)
		{
			mPositionState = PositionState::Air;
			mJumpingPawer = 0;
		}
		if (mState == State::JumpDown || mState == State::JumpUp || 
			//점프공격시에도 착지모션, 공격초기화 챙겨주기
			mState==State::JumpAttackLeft || mState==State::JumpAttackRight)
		{
			mState = State::JumpDrop;
			if(mMotionRL==0)
			{
				mIndexX = 4;
			}
			else if(mMotionRL==1)
			{ 
				mIndexX = 24 - 4;
			}
			mAttackLeft = false;
			mAttackRight = false;
		}
	}
}

void Player::UpdateCamera()
{
	int findNum = 4;
	for (int i = 0; i < mObjectList.size(); i++)
	{
		if (mObjectList[i]->GetKey() == L"Buttom"
			||mObjectList[i]->GetKey() == L"Buttom2"
			||mObjectList[i]->GetKey() == L"Buttom3"
			||mObjectList[i]->GetKey() == L"Buttom4")
		{
			findNum = i;
			break;
		}
	}

	if ((mX > WINSIZEX / 2 &&
		mObjectList[findNum]->GetRect().right-mX >= WINSIZEX/2))
	{
		mCameraX += mBeforeX - mX;
	}
	
	if (mStageNum == 1)
	{
		mCameraY += mBeforeY - mY;
	}
}

void Player::WeaponGeneration()
{
	if (mWeapon != NULL)
	{
		mWeapon->Release();
		SafeDelete(mWeapon);
	}
	mWeapon = new Weapon();
	mWeapon->SetPlayerPtr(this);
	mWeapon->Fire(mWeaponType);
}