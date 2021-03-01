#include "pch.h"
#include "ItemManager.h"
#include "FieldWeapon.h"

void ItemManager::Init(int stage)
{
	if (stage == 0)
	{
		FieldWeapon* item = new FieldWeapon;
		item->Fire(WINSIZEX,WINSIZEY/5,WeaponType::Confodere);
		item->SetPlayerPtr(mPlayer);
		mItemList.push_back(item);

		FieldWeapon* item2 = new FieldWeapon;
		item2->Fire(WINSIZEX / 3, WINSIZEY /5, WeaponType::Secare);
		item2->SetPlayerPtr(mPlayer);
		mItemList.push_back(item2);
	}
}

void ItemManager::Release()
{
	if (mItemList.size() != NULL)
	{
		for (int i = 0; i < mItemList.size(); i++)
		{
			mItemList[i]->Release();
			SafeDelete(mItemList[i]);
		}
	}
}

void ItemManager::Update()
{
	if (mItemList.size() != NULL)
	{
		for (int i = 0; i < mItemList.size(); i++)
		{
			mItemList[i]->SetPlayerPtr(mPlayer);
			mItemList[i]->Update();
		}
	}
	if (mItemList.size() != NULL)
	{
		if (mPlayer->GetState()==State::Up)
		{
			for (int i = 0; i < mItemList.size(); i++)
			{
				float distance = Math::GetDistance(mPlayer->GetX(), mPlayer->GetY(),
					mItemList[i]->GetX(), mItemList[i]->GetY());
				if (distance < 600 && mItemList[i]->GetAppear()==false)
				{
					mItemList[i]->SetAppear(true);
				}
			}
		}
	}
	//충돌후 제거
	if (mItemList.size() != NULL)
	{
		for (int i = 0; i < mItemList.size(); i++)
		{
			if (mItemList[i]->GetAppear2() == true)
			{
				//플레이어에 해당 item의 WeaponType을 넣어준다.
				mPlayer->SetWeaponType(mItemList[i]->GetWeaponType());
				mItemList[i]->Release();
				SafeDelete(mItemList[i]);
				mItemList.erase(mItemList.begin() + i);
				i--;
			}
		}
	}

	//UP안누를때 초기화
	if (mItemList.size() != NULL)
	{
		if (mPlayer->GetState() != State::Up)
		{
			for (int i = 0; i < mItemList.size(); i++)
			{
				if (mItemList[i]->GetAppear() == true)
				{
					mItemList[i]->SetAppear(false);
				}
			}
		}
	}

}

void ItemManager::Render(HDC hdc, float cameraX, float cameraY)
{
	if (mItemList.size() != NULL)
	{
		for (int i = 0; i < mItemList.size(); i++)
		{
			mItemList[i]->Render(hdc, cameraX, cameraY);
		}
	}
}
