#include "pch.h"
#include "MonsterManager.h"
#include "Monster.h"
#include "Bat.h"
#include "Zombi.h"
#include "Player.h"
#include "Boss.h"
#include "Weapon.h"

void MonsterManager::Init(int stage)
{
	if (stage == 0)
	{
		
	}
	else if (stage == 1)
	{
		Monster* bat = new Bat;
		bat->Init(L"Bat", 130, WINSIZEY - 527, 2, 0);
		mMonsterList.push_back(bat);
		Monster* bat1 = new Bat;
		bat1->Init(L"Bat", 130, WINSIZEY - 1205, 2, 0);
		mMonsterList.push_back(bat1);
		Monster* bat2 = new Bat;
		bat2->Init(L"Bat", 300, 0, 2, 0);
		mMonsterList.push_back(bat2);
		Monster* bat3 = new Bat;
		bat3->Init(L"Bat", 130, WINSIZEY - 900, 2, 0);
		mMonsterList.push_back(bat3);



	}
	else if (stage == 3)
	{
		Monster* boss = new Boss;
		boss->Init(L"Boss", WINSIZEX / 4*3, 300, 3, 0);
		mMonsterList.push_back(boss);
	}
}

void MonsterManager::Release()
{
	if (mMonsterList.size() != NULL)
	{
		for (int i = 0; i < mMonsterList.size(); ++i)
		{
			mMonsterList[i]->Release();
			SafeDelete(mMonsterList[i]);
		}
	}
	if (mEffectList.size() != NULL)
	{
		for (int i = 0; i < mEffectList.size(); ++i)
		{
			mEffectList[i]->Release();
			SafeDelete(mEffectList[i]);
		}
	}
}

void MonsterManager::Update(int stage)
{
	if (stage == 0)
	{
		////좀비 생성
		//mFrameCount++;
		//if (mFrameCount > 200 && Random::GetInstance()->RandomInt(5) > 2 && mMonsterList.size() < 10)
		//{
		//	mFrameCount = 0;
		//	Monster* zombi = new Zombi;
		//	zombi->Init(L"Zombi", Random::GetInstance()->RandomInt(WINSIZEY / 2, WINSIZEY / 2 * 3), WINSIZEY - 48 - 90, 1, 0);
		//	mMonsterList.push_back(zombi);
		//}
	}
	else if (stage == 1)
	{
		
	}
	else if (stage == 2)
	{
		//좀비 생성
		mFrameCount++;
		if (mFrameCount > 100 && Random::GetInstance()->RandomInt(5) > 1 && mMonsterList.size() < 20)
		{
			mFrameCount = 0;
			Monster* zombi = new Zombi;
			zombi->Init(L"Zombi", Random::GetInstance()->RandomInt(WINSIZEY / 3*2, 4000), WINSIZEY - 24-90, 1, 0);
			mMonsterList.push_back(zombi);
		}
	}

	//몬스터들 업데이트
	if (mMonsterList.size() != NULL)
	{
		for (int i = 0; i < mMonsterList.size(); i++)
		{
			mMonsterList[i]->SetPlayerPtr(mPlayer);
			mMonsterList[i]->Update();
		}
	}

	UpdatePlayerMonsterCrash();
	UpdateWeaponMonsterCrash();
	UpdateEffect();

	//몬스터 제거
	if (mMonsterList.size() != NULL)
	{
		for (int i = 0; i < mMonsterList.size(); i++)
		{
			if (mMonsterList[i]->GetExtence() == true)
			{
				//보스일경우 폭발
				if (mMonsterList[i]->GetKey() == L"Boss")
				{
					Effect* explotion = new Effect;
					explotion->Init(EffectType::DestroyEffect, mMonsterList[i]->GetRect().left-50, mMonsterList[i]->GetRect().top+50,0);
					mEffectList.push_back(explotion);
				}
				mMonsterList[i]->Release();
				SafeDelete(mMonsterList[i]);
				mMonsterList.erase(mMonsterList.begin() + i);
				i--;
			}
		}
	}
	
}

void MonsterManager::Render(HDC hdc, float cameraX, float cameraY)
{
	if (mMonsterList.size() != NULL)
	{
		for (int i = 0; i < mMonsterList.size(); i++)
		{
			mMonsterList[i]->Render(hdc, cameraX, cameraY);
		}
	}
	if (mEffectList.size() != NULL)
	{
		for (int i = 0; i < mEffectList.size(); i++)
		{
			mEffectList[i]->Render(hdc, cameraX, cameraY);
		}
	}
}

void MonsterManager::UpdatePlayerMonsterCrash()
{
	//플레이어 - 몬스터 충돌처리
	if (mPlayer->GetInvin() == false)//플레이어가 무적이 아닐때
	{
		RECT tempRect;
		RECT playerRect = mPlayer->GetRect();
		RECT monsterRect;
		if (mMonsterList.size() != NULL)
		{
			for (int i = 0; i < mMonsterList.size(); i++)
			{
				monsterRect = mMonsterList[i]->GetRect();
				if (IntersectRect(&tempRect, &playerRect, &monsterRect) &&
					mMonsterList[i]->GetAttackBool() == false
					&& mMonsterList[i]->GetState() != MonsterState::Generation
					&& mMonsterList[i]->GetState() != MonsterState::Extinction)
				{
					//몬스터가 공격하는 텀줌
					mMonsterList[i]->SetAttackBool(true);
					//hp깍는 작용
					mPlayer->SetHp(mPlayer->GetHp() - mMonsterList[i]->GetAttack());
					//데미지 입은 상태
					mPlayer->SetState(State::Damege);
					//플레이어 무적
					mPlayer->SetInvin(true);
					//플레이어 프레임인데 위에 상태데미지와 검토요망
					if (mPlayer->GetX() < mMonsterList[i]->GetX())
					{
						mPlayer->SetIndexX(8);
						mPlayer->SetMotionRL(0);
					}
					else
					{
						mPlayer->SetIndexX(24 - 8);
						mPlayer->SetMotionRL(1);
					}
					//숫자표시
					Effect* damegeNum = new Effect();
					damegeNum->Init(EffectType::NumberEffect, tempRect.left, tempRect.top, mMonsterList[i]->GetAttack());
					mEffectList.push_back(damegeNum);
				}

			}
		}
	}
}

void MonsterManager::UpdateWeaponMonsterCrash()
{
	//무기-몬스터 충격
	if (mPlayer->GetWeapon() != NULL)//무기가 널이 아닐때
	{
		RECT tempRect;
		RECT weaponRect = mPlayer->GetWeapon()->GetRect();
		RECT monsterRect;
		if (mMonsterList.size() != NULL)
		{
			for (int i = 0; i < mMonsterList.size(); i++)
			{
				monsterRect = mMonsterList[i]->GetRect();
				if (IntersectRect(&tempRect, &weaponRect, &monsterRect)
					&& mMonsterList[i]->GetDamegeBool() == false //데미지 중복되는거 막아줌
					&& mMonsterList[i]->GetState() != MonsterState::Generation
					&& mMonsterList[i]->GetState() != MonsterState::Extinction
					&& mPlayer->GetWeapon()->GetAppearance()==true)
				{
					//몬스터 hp깍임
					mMonsterList[i]->SetHp((mMonsterList[i]->GetHp()) - (mPlayer->GetWeapon()->GetDamege()));
					//몬스터 데미지 텀
					mMonsterList[i]->SetDamegeBool(true);
					//숫자 표시
					Effect* damegeNum = new Effect();
					damegeNum->Init(EffectType::NumberEffect, tempRect.left, tempRect.top, mPlayer->GetWeapon()->GetDamege());
					mEffectList.push_back(damegeNum);
					//피격 표시
					int tempx;
					if (mPlayer->GetX() < mMonsterList[i]->GetX())
					{
						tempx = 0;
					}
					else
					{
						tempx = 1;
					}
					Effect* hitEffect = new Effect();
					hitEffect->Init(EffectType::HitEffect, tempRect.left, tempRect.top, tempx);
					mEffectList.push_back(hitEffect);
				}
			}
		}
	}
	//무기가 사라지면 데미지여부 초기화
	else if (mPlayer->GetWeapon() == NULL)
	{
		for (int i = 0; i < mMonsterList.size(); i++)
		{
			if (mMonsterList[i]->GetDamegeBool() == true)
			{
				mMonsterList[i]->SetDamegeBool(false);
			}
		}
	}
	
}

void MonsterManager::UpdateEffect()
{
	if (mEffectList.size() != NULL)
	{
		for (int i = 0; i < mEffectList.size(); i++)
		{
			mEffectList[i]->Update();
		}
	}
	if (mEffectList.size() != NULL)
	{
		for (int i = 0; i < mEffectList.size(); i++)
		{
			if (mEffectList[i]->GetEx() == true)
			{
				mEffectList[i]->Release();
				SafeDelete(mEffectList[i]);
				mEffectList.erase(mEffectList.begin() + i);
				i--;
			}
		}
	}
}