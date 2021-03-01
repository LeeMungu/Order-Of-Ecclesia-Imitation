#include "pch.h"
#include "BackGroundManager.h"
#include "Image.h"


void BackGroundManager::Init(int stage)
{
	if (stage == 0)
	{
		BackGround* BackGround2 = new BackGround();
		BackGround2->Init(L"BackGround2", BackGroundType::BackGroundBack);

		BackGround* BackGround1=new BackGround();
		BackGround1->Init(L"BackGround1", BackGroundType::BackGround);
		
		BackGround* Wall = new BackGround();
		Wall->Init(L"Wall", BackGroundType::Wall);

		mBackGroundList.push_back(BackGround2);
		mBackGroundList.push_back(BackGround1);
		mBackGroundList.push_back(Wall);
	}
	else if (stage == 1)
	{
		BackGround* BackGroundType3_1 = new BackGround();
		BackGroundType3_1 -> Init(L"BackGroundType3-1", BackGroundType::BackGroundBack1);
		
		BackGround* BackGroundType3_2 = new BackGround();
		BackGroundType3_2->Init(L"BackGroundType3-2", BackGroundType::BackGroundBack2);
		
		BackGround* BackGroundType3_3 = new BackGround();
		BackGroundType3_3->Init(L"BackGroundType3-3", BackGroundType::BackGroundBack3);
		
		BackGround* BackGroundType3 = new BackGround();
		BackGroundType3->Init(L"BackGroundType3", BackGroundType::Wall);

		mBackGroundList.push_back(BackGroundType3_3);
		mBackGroundList.push_back(BackGroundType3_2);
		mBackGroundList.push_back(BackGroundType3_1);
		mBackGroundList.push_back(BackGroundType3);
	}
	else if (stage == 2)
	{
		BackGround* BackGroundType2 = new BackGround();
		BackGroundType2->Init(L"BackGroundType2", BackGroundType::BackGround);

		BackGround* BackGroundType2_2 = new BackGround();
		BackGroundType2_2->Init(L"BackGroundType2-2", BackGroundType::BackGroundBack);

		BackGround* WallType2 = new BackGround();
		WallType2->Init(L"WallType2", BackGroundType::Wall);

		mBackGroundList.push_back(BackGroundType2_2);
		mBackGroundList.push_back(BackGroundType2);
		mBackGroundList.push_back(WallType2);
	}
	else if (stage == 3)
	{
		BackGround* BackGroundType4 = new BackGround();
		BackGroundType4->Init(L"BackGroundType4", BackGroundType::BackGround);

		BackGround* BackGroundType4_2 = new BackGround();
		BackGroundType4_2->Init(L"BackGroundType4-2", BackGroundType::BackGroundBack);

		BackGround* WallType4 = new BackGround();
		WallType4->Init(L"WallType4", BackGroundType::Wall);

		mBackGroundList.push_back(BackGroundType4_2);
		mBackGroundList.push_back(BackGroundType4);
		mBackGroundList.push_back(WallType4);
	}
}

void BackGroundManager::Release()
{
	if (mBackGroundList.size() != NULL)
	{
		for (int i = 0; i < mBackGroundList.size(); ++i)
		{
			mBackGroundList[i]->Release();
			SafeDelete(mBackGroundList[i]);
		}
	}
}

void BackGroundManager::Update()
{
}

void BackGroundManager::Render(HDC hdc, float cameraX, float cameraY)
{
	if (mBackGroundList.size() != NULL)
	{
		for (int i = 0; i < mBackGroundList.size(); ++i)
		{
			mBackGroundList[i]->Render(hdc, cameraX, cameraY);
		}
	}
}
