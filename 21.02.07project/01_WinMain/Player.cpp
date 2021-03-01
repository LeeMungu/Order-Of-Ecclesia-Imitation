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

	//�ʱ�ȭ
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
	//����Ű ����
	Control();
	UpdateFrame();
	UpdateState();
	UpdateFootBord();
	UpdateCamera();

	//Mp�ڿ� ȸ��
	if (mMp < mMpMax && mAttackLeft==false && mAttackRight==false)
	{
		mMp ++;
	}//max�� ����������Ѵ�.

	//�������
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

	//���� ������Ʈ
	if (mWeapon != NULL )
	{
		mWeapon->Update();
	}

	//�÷��̾� ����
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	//�ɸ���
	if (mInvincibility == true && mState!=State::Evasion)
	{
		mImage->AlphaFrameRender(hdc, mRect.left - 75 + mCameraX, mRect.top - 75 + mCameraY, mIndexX, mIndexY, (mInviCount%2)/2+0.5f);
	}
	else
	{
		mImage->FrameRender(hdc, mRect.left - 75 + mCameraX, mRect.top - 75 + mCameraY, mIndexX, mIndexY);
	}

	//����
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
	//SPnum - �����ߴ�
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
			//mMotionRL = 1;//���ʹ��⺸��<-
		}
		if (Input::GetInstance()->GetKey(VK_LEFT))//�ε��� �ʱ�ȭ�� ���ֱ� �ؾ��ϴµ�...ó�� �ѹ��� �����ϰ� ������Ѵ�.
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
			mMotionRL = 0;//�����ʹ��⺸��->
		}
		if (Input::GetInstance()->GetKey(VK_RIGHT))//�ε��� �ʱ�ȭ�� ���ֱ� �ؾ��ϴµ�...ó�� �ѹ��� �����ϰ� ������Ѵ�.
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
		//����
		//����
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
		//������
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
	//ȸ��
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

	//���� ������ ���� ���� �Ű�����-��,�� ������ �����ö� �����ֱ�
	
	//����(air-��ü�����δ� ���Ͻ�)�� �������� ������ �ȵǾ���-������ ������ �ƹ��͵� ���Ѵ�.-���� ����? 1���� ����
	if (mPositionState == PositionState::Air)
	{
		mJumpingCount++;
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::UpdateState()
{
	//��������
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
	//���λ����϶� ��ӵǴºκ�
	if (mPositionState == PositionState::Jumping)
	{
		mY += mJumpingPawer; //�������� ������ = onGround�� �ƴҶ��� �����ϰ� �ʹ�.
		mJumpingPawer += mGravity;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		if (mState == State::JumpUp && mJumpingPawer == 0)
		{
			mState = State::JumpDown;
		}
	}
	//���� ���°� �ƴϸ� ����Ƚ��, �����Ŀ�(�����߷�-�ʱ⿡�� up�� �����ش� ->�׶��峪 ��Ÿ�� ���϶� �������
	//���Ͻ� ���� ������ �ٸ������� �ʱ�ȭ����� �Ѵ�.->�ٴڿ� ������?, ���� �ε�������

	//��x, ��x -> �߷�	Air��� ���߿� �ִ� ���¸� ���� ������\
	//AIR ����
	if (mPositionState == PositionState::Air)
	{
		//���ϻ��¹Ƿ� jumpingPawer�� 0���� �����ؾ��Ѵ�. -�տ��� Air�� ���Ҷ� �ѹ� �ʱ�ȭ�������
		//mPlayer.y += mPlayer.jumpingPawer; //�������� ������ = onGround�� �ƴҶ��� �����ϰ� �ʹ�.
		//mPlayer.jumpingPawer += mPlayer.gravity;
		//�׳� �׷���Ƽ�� �����൵ �ȴ�? - > �ȵȴ�...
		mY += mJumpingPawer;
		mJumpingPawer += mGravity;
		mState = State::JumpDown;
	}

	
}

void Player::UpdateFrame()
{
	//�̹��� ��ġ ���
	mFrameCount++;

	if (mFrameCount > mLimitCount)
	{
		mFrameCount = 0;
		if (mMotionRL == 0)//������
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
			case  State::Run: //Limit 2// ��ưup�Ҷ� limitcount 0���� �������൵ �ȴ�.
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
				if (mIndexX > 3)//�ٴڿ� �ݱ����� �����ѹ�������Ѵ�.
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
			case State::Evasion: // ȸ�� �Ŀ� �������� �߰� ���� ���� ���� 2?
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
			case State::LeftTurnRight: //����� ��������� 1?
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
			case State::DownAttackLeft://�ٿ�� ��������
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
			case State::JumpAttackLeft://���ٿ� �����ؾ��Ѵ�.
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
			case State::Damege://ó�� mIndexX=8
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
		else if (mMotionRL == 1)//������
		{//��Ǻ��� ���̰� �ٸ��� ������ --ó���δ� ����ó�� �ϳ� ��������Ѵ�.
			//���� ||����ڿ� ���� �͵� ������
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
			case  State::Run: //Limit 2// ��ưup�Ҷ� limitcount 0���� �������൵ �ȴ�.
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
				if (mIndexX < 24-3)//�ٴڿ� �ݱ����� �����ѹ�������Ѵ�.
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
			case State::Evasion: // ȸ�� �Ŀ� �������� �߰� ���� ���� ���� 4?
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
			case State::RightTurnLeft : //����� ��������� 1?
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
			case State::DownAttackLeft://�ٿ�� ��������
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
			case State::JumpAttackLeft://���ٿ� �����ؾ��Ѵ�.
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
			case State::Damege://ó�� mIndexX=24-8
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

	//���������� �����ʱ�ȭ
	if (mState == State::JumpDrop)
	{
		mAttackRight = false;
		mAttackLeft = false;
		if (mWeapon != NULL)
		{
			mWeapon->SetAppearance(false);
		}
	}

	//q�� ȸ�ǽ� �ڷ�
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
			RECT footRect;//0���� �⺻����
			footRect = mObjectList[i]->GetRect();
			//��Ÿ�� == ������ �ϰ� �ְ�?(���߿� �ְ�?==Air), ���� �浹 ������ (��, ��, ���==ground)
			if (//(mPlayer.positionState==PositionState::Jumping|| mPlayer.positionState == PositionState::Air) && 
				IntersectRect(&temp, &footRect, &mRect))
			{
				if (mObjectList[i]->GetType() == 0)
				{
					if (mPositionState == PositionState::Jumping)
					{
						if (mJumpingPawer >= 0)
						{
							//������ ���ֱ�
							if (mY < footRect.top)// && mRect.right>footRect.left && mRect.left < footRect.right)
							{
								//������ ���������� ��ġ(rc.)�������� ���ֱ�
								mY = footRect.top - (mSizeY / 2);
								mPositionState = PositionState::OnGround;//�׶��� �ٽ� ������
								mJumpingPawer = STARTJUMPPAWER;
								mJumpingCount = 0;
								mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
								mFootNum = i; //���� �ִ� ���� ���� �����ϴ°� �ݺ����̸� �Ŀ� brack�� ������
								break;
							}
						}
					}
					else if (mPositionState == PositionState::Air)
					{
						//������ ���ֱ�
						if (mY < footRect.top)// && mRect.right>footRect.left && mRect.left < footRect.right)
						{
							//������ ���������� ��ġ(rc.)�������� ���ֱ�
							mY = footRect.top - (mSizeY / 2);
							mPositionState = PositionState::OnGround;//�׶��� �ٽ� ������
							mJumpingPawer = STARTJUMPPAWER;
							mJumpingCount = 0;
							mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
							mFootNum = i; //���� �ִ� ���� ���� �����ϴ°� �ݺ����̸� �Ŀ� brack�� ������
							break;
						}
					}
				}
				else if (mObjectList[i]->GetType() == 1)
				{
					//������ ���ֱ�
					if (mRect.top < footRect.top)// && mRect.right>footRect.left && mRect.left < footRect.right)
					{
						//������ ���������� ��ġ(rc.)�������� ���ֱ�
						mY = footRect.top - (mSizeY / 2);
						mPositionState = PositionState::OnGround;//�׶��� �ٽ� ������
						mJumpingPawer = STARTJUMPPAWER;
						mJumpingCount = 0;
						mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
						mFootNum = i; //���� �ִ� ���� ���� �����ϴ°� �ݺ����̸� �Ŀ� brack�� ������
						break;
					}
					if (mPositionState == PositionState::Jumping || mPositionState == PositionState::Air)
					{
						//�ٴ��� ��Ÿ�Ͽ� ���� ������ �ǰ�-�ȵǰ� ���ؾ��Ѵ�.
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
						//������ �ε�����-�ε����ٰ� ���� �ʱ�ȭ �Ǹ� �ȵ�
						else if (mObjectList[i]->GetRect().right > mRect.right)
						{
							mX = mObjectList[i]->GetRect().left - mSizeX / 2;
						}
						//�������� �ε�����- �ε����ٰ� ���� �ʱ�ȭ �ϸ� �ȵ�
						else if (mObjectList[i]->GetRect().left < mRect.left)
						{
							mX = mObjectList[i]->GetRect().right + mSizeX / 2;
						}
					}
					else
					{
						//������ �ε�����-���� ��������
						if (mObjectList[i]->GetRect().right > mRect.right)
						{
							mX = mObjectList[i]->GetRect().left - mSizeX / 2;
						}
						//�������� �ε�����
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

	if (mPositionState == PositionState::OnGround)//���鿡 ���� �Ҷ�
	{
		if (mObjectList[mFootNum]->GetRect().left > mRect.right || mObjectList[mFootNum]->GetRect().right < mRect.left)
		{
			mPositionState = PositionState::Air;
			mJumpingPawer = 0;
		}
		if (mState == State::JumpDown || mState == State::JumpUp || 
			//�������ݽÿ��� �������, �����ʱ�ȭ ì���ֱ�
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