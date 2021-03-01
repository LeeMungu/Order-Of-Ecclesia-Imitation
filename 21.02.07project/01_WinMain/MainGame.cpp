#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "BackGroundManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "MonsterManager.h"
#include "ItemManager.h"
#include "Map.h"
/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*/
void MainGame::Init()
{
	SetTimer(_hWnd, 1, 10, NULL);

	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	/*ImageManager::GetInstance()->
		LoadFromFile(L"Background",Resources(L"background.bmp"), 600, 800, false);
	ImageManager::GetInstance()
		->LoadFromFile(L"Enemy",Resources(L"ufo.bmp"), 530, 32, 10, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Bullet", Resources(L"missile.bmp"), 416, 64, 13, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"CircleBullet", Resources(L"bullet.bmp"), 21, 21, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Explosion", Resources(L"explosion.bmp"), 832, 62, 26, 1, true);
	mExplosion = ImageManager::GetInstance()->FindImage(L"Explosion");
	mBackground = ImageManager::GetInstance()->FindImage(L"Background");*/

	AllImageLoad();
	
	mPlayer = new Player();
	mPlayer->Init(L"Player", WINSIZEX / 8, WINSIZEY / 6 * 4, 5.f, 0.f);
	
	mStageNum = mPlayer->GetStageNum();
	mStageSet = false;

	mBackGroundManager = new BackGroundManager();
	mBackGroundManager->Init(mStageNum);

	mObjectManager = new ObjectManager();
	mObjectManager->Init(mStageNum);
	
	//발판정보를 플레이어에 넣어줌
	mPlayer->SetObjectList(mObjectManager->GetObjectList());

	mMonsterManager = new MonsterManager();
	mMonsterManager->Init(mStageNum);

	mItemManager = new ItemManager();
	mItemManager->Init(mStageNum);

	mMap = new Map();
	mMap->Init();
}

/*
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	KillTimer(_hWnd, 1);//타이머 꺼주자

	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	SafeDelete(mBackBuffer);

	mBackGroundManager->Release();
	SafeDelete(mBackGroundManager);

	mPlayer->Release();
	SafeDelete(mPlayer);

	mObjectManager->Release();
	SafeDelete(mObjectManager);

	mMonsterManager->Release();
	SafeDelete(mMonsterManager);

	mItemManager->Release();
	SafeDelete(mItemManager);

	mMap->Release();
	SafeDelete(mMap);
}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
*/
void MainGame::Update()
{
	mPlayer->Update();
	mMap->SetPlayer(mPlayer);
	mMap->Update();
	//스테이지 번호
	mStageNum = mPlayer->GetStageNum();
	//스테이지 이동 여부
	mStageSet = mPlayer->GetStageSet();
	if (mStageSet == false)
	{
		mObjectManager->SetPlayerPtr(mPlayer);
		mObjectManager->Update();

		mMonsterManager->SetPlayerPtr(mPlayer);
		mMonsterManager->Update(mStageNum);

		mItemManager->SetPlayerPtr(mPlayer);
		mItemManager->Update();
	}
	else if(mStageSet == true)
	{
		//배경리셋
		mBackGroundManager->Release();
		SafeDelete(mBackGroundManager);
		mBackGroundManager = new BackGroundManager();
		mBackGroundManager->Init(mStageNum);

		//오브젝트 리셋
		mObjectManager->Release();
		SafeDelete(mObjectManager);
		mObjectManager = new ObjectManager();
		mObjectManager->Init(mStageNum);
		//발판정보를 플레이어에 넣어줌
		mPlayer->SetObjectList(mObjectManager->GetObjectList());

		//몬스터 리셋
		mMonsterManager->Release();
		SafeDelete(mMonsterManager);
		mMonsterManager = new MonsterManager();
		mMonsterManager->Init(mStageNum);

		//아이템 리셋
		mItemManager->Release();
		SafeDelete(mItemManager);
		mItemManager = new ItemManager();
		mItemManager->Init(mStageNum);


		//플레이어 위치 리셋
		if (mPlayer->GetDoorType() == DoorType::Front)
		{
			mPlayer->SetX(WINSIZEX / 8);
			mPlayer->SetY(WINSIZEY / 6 * 4);
		}
		else if (mPlayer->GetDoorType() == DoorType::Back)
		{
			mPlayer->SetX(mPlayer->GetStageStartX());
			mPlayer->SetY(mPlayer->GetStageStartY());
		}

		
		//스테이지셋 리셋
		mStageSet = false;
		mPlayer->SetStageSet(mStageSet);
	}
}

/*
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	//백버퍼의 HDC 가져온다
	HDC backDC = mBackBuffer->GetHDC();
	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		float cameraX = mPlayer->GetCameraX();
		float cameraY = mPlayer->GetCameraY();
		mBackGroundManager->Render(backDC, cameraX, cameraY);
		
		mObjectManager->Render(backDC, cameraX, cameraY);
		
		mPlayer->Render(backDC);
		
		mMonsterManager->Render(backDC, cameraX, cameraY);

		mItemManager->Render(backDC, cameraX, cameraY);

		mMap->Render(backDC);
	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사
	mBackBuffer->Render(hdc, 0, 0);
}

void MainGame::AllImageLoad()
{
	//배경
	//stage0
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGround1", Resources(L"background1.bmp"), 2320, 730, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Wall", Resources(L"wall.bmp"), 2565, 885, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGround2", Resources(L"background2.bmp"), 2240, 810, true);
	//stage1
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGroundType3", Resources(L"backgroundtype3.bmp"), 768, 1680, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGroundType3-1", Resources(L"backgroundtype3-1.bmp"), 672, 1644, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGroundType3-2", Resources(L"backgroundtype3-2.bmp"), 672, 1644, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGroundType3-3", Resources(L"backgroundtype3-3.bmp"), 672, 1644, true);
	//stage2
	ImageManager::GetInstance()
		->LoadFromFile(L"WallType2", Resources(L"walltype2.bmp"), 5000, 680, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGroundType2", Resources(L"backgroundtype2.bmp"), 6545, 640, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGroundType2-2", Resources(L"backgroundtype2-2.bmp"), 6545, 498, true);
	//stage3
	ImageManager::GetInstance()
		->LoadFromFile(L"WallType4", Resources(L"walltype4.bmp"), 1800, 680, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGroundType4", Resources(L"backgroundtype4.bmp"), 2356, 640, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BackGroundType4-2", Resources(L"backgroundtype4-1.bmp"), 2353, 498, true);



	//번호
	ImageManager::GetInstance()
		->LoadFromFile(L"Number", Resources(L"number.bmp"), 150, 24, 10, 1, true);

	//구조물
	//stage 0
	ImageManager::GetInstance()
		->LoadFromFile(L"Buttom", Resources(L"Buttom.bmp"), 2600, 80, 1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Wall2", Resources(L"wall2.bmp"), 320, 640, 2, 2, true);
	//stage 1
	ImageManager::GetInstance()
		->LoadFromFile(L"Buttom3", Resources(L"Buttom3.bmp"), 768, 48, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"WallType3-2", Resources(L"walltype3-2.bmp"), 128, 1342, 2, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"WallType3-3", Resources(L"walltype3-3.bmp"), 288, 92, 1, 2, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"WallType3-4", Resources(L"walltype3-4.bmp"), 192, 48, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"WallType3-5", Resources(L"walltype3-5.bmp"), 156, 144, 2, 1, true);
	//stage 2
	ImageManager::GetInstance()
		->LoadFromFile(L"Buttom2", Resources(L"Buttom2.bmp"), 5000, 48, 1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"WallType2-2", Resources(L"walltype2-2.bmp"), 204, 386, 2, 2, true);
	//stage 3
	ImageManager::GetInstance()
		->LoadFromFile(L"Buttom4", Resources(L"buttom4.bmp"), 1800, 48, 1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"WallType4-2", Resources(L"walltype4-2.bmp"), 95, 528, 1, 1, true);


	//발판
	ImageManager::GetInstance()
		->LoadFromFile(L"FootBord", Resources(L"FootBord.bmp"), 96, 30, 1, 1, true);

	//문
	ImageManager::GetInstance()
		->LoadFromFile(L"Door1", Resources(L"door1.bmp"), 80, 320, 1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Door2", Resources(L"door2.bmp"), 40, 320, 1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Door2Open", Resources(L"door2Open.bmp"), 200, 320, 1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"DoorType3", Resources(L"doortype3.bmp"), 24,192, 1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"DoorType3Open", Resources(L"doortype3open.bmp"), 120, 192, 1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"DoorType4", Resources(L"doortype4.bmp"), 24, 192, 1, 1, true);

	//플레이어
	ImageManager::GetInstance()
		->LoadFromFile(L"Player", Resources(L"shanoa1.bmp"), 5625, 11250, 25, 50, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Gage", Resources(L"gage.bmp"), 285, 66, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Hp", Resources(L"Hp.bmp"), 285, 66, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Mp", Resources(L"mp.bmp"), 285, 66, true);
	//무기
	ImageManager::GetInstance()
		->LoadFromFile(L"Weapon", Resources(L"weapon.bmp"), 1800, 900, 6, 4, true);
	
	//필드 아이템
	ImageManager::GetInstance()
		->LoadFromFile(L"FieldWeapon", Resources(L"FieldWeapon.bmp"), 180, 180, 2, 2, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"FieldWeaponBack", Resources(L"FieldWeaponBack.bmp"), 1551, 180, 8, 1, true);
	
	//이팩트
	ImageManager::GetInstance()
		->LoadFromFile(L"PointEffect", Resources(L"PointEffect.bmp"), 960, 120, 8, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"WeaponEffect", Resources(L"weaponEffect.bmp"),2000,250, 5, 2, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"HitEffect", Resources(L"hiteffect.bmp"), 500, 100, 10, 2, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Explosion", Resources(L"explosion.bmp"), 832, 62, 26, 1, true);

	//몬스터
	ImageManager::GetInstance()
		->LoadFromFile(L"Bat", Resources(L"bat.bmp"), 975, 600, 13, 4, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Zombi", Resources(L"zombi.bmp"), 5400, 1800, 24, 8, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Boss", Resources(L"boss1.bmp"), 1350, 27575, 2, 41, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BossAttack2", Resources(L"bossAttack2.bmp"), 1350, 5400, 2, 8, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"BossAttack3", Resources(L"bossAttack3.bmp"), 3600, 3200, 3, 4, true);

	//맵
	ImageManager::GetInstance()
		->LoadFromFile(L"MapBack", Resources(L"MapBack.bmp"), 256,192,1, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Map", Resources(L"Map.bmp"), 170, 65, 1, 1, true);
}