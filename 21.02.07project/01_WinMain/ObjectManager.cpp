#include "pch.h"
#include "ObjectManager.h"
#include "Image.h"

void ObjectManager::Init(int stage)
{
	
	if (stage == 0)
	{
		//포인터라 지우면 안된다.
		Object* objectDoor1 = new Object();
		objectDoor1->Init(L"Door1", 40, WINSIZEY / 2 - 85, 1);
		mObjectList.push_back(objectDoor1);

		Object* objectDoor2 = new Object();
		objectDoor2->Init(L"Door2", WINSIZEX / 2 * 3 + 612, WINSIZEY / 2 - 85, 2);
		mObjectList.push_back(objectDoor2);

		Object* objectWall1 = new Object();
		objectWall1->Init(L"Wall2", WINSIZEX / 2 - 550, -48, 1, 0, 1, Position::Center);
		mObjectList.push_back(objectWall1);
		Object* objectWall2 = new Object();
		objectWall2->Init(L"Wall2", WINSIZEX / 2 * 3 + 550, -48, 1, 1, 1, Position::Center);
		mObjectList.push_back(objectWall2);
		Object* objectWall3 = new Object();
		objectWall3->Init(L"Wall2", WINSIZEX / 2 - 550, WINSIZEY - 128, 1, 0, 1, Position::Center);
		mObjectList.push_back(objectWall3);
		Object* objectWall4 = new Object();
		objectWall4->Init(L"Wall2", WINSIZEX / 2 * 3 + 550, WINSIZEY - 128, 1, 1, 1, Position::Center);
		mObjectList.push_back(objectWall4);

		Object* objectButtom = new Object();
		objectButtom->Init(L"Buttom", WINSIZEX - 20, WINSIZEY - 24, 1);
		mObjectList.push_back(objectButtom);

		for (int i = 0; i < 4; i++)
		{
			Object* object = new Object();
			object->Init(L"FootBord", WINSIZEX / 10 * 3 + i * WINSIZEX / 3, WINSIZEY / 9 * 5, 0);
			mObjectList.push_back(object);
		}
	}
	else if (stage == 1)
	{
		Object* buttom = new Object();
		buttom->Init(L"Buttom3", 768/2, WINSIZEY-48/2-1,1 );
		mObjectList.push_back(buttom);

		Object* wall = new Object();
		wall->Init(L"WallType3-2", buttom->GetRect().left+5,buttom->GetRect().top-1342-330-7, 1, 0, 0,Position::Edge);
		mObjectList.push_back(wall);


		Object* wall2 = new Object();
		wall2->Init(L"WallType3-2", buttom->GetRect().right-65, buttom->GetRect().top - 1295, 1, 1, 0, Position::Edge);
		mObjectList.push_back(wall2);

		Object* wall3 = new Object();
		wall3->Init(L"WallType3-3", buttom->GetRect().right -288, buttom->GetRect().top -1152,1, 0, 0, Position::Edge);
		mObjectList.push_back(wall3);

		Object* wall4 = new Object();
		wall4->Init(L"WallType3-3", buttom->GetRect().left, buttom->GetRect().top - 574, 1, 0, 1, Position::Edge);
		mObjectList.push_back(wall4);

		Object* wall8 = new Object();
		wall8->Init(L"WallType3-3", buttom->GetRect().left-90, buttom->GetRect().top-1152 ,1,0,1, Position::Edge);
		mObjectList.push_back(wall8);

		Object* wall6 = new Object();
		wall6->Init(L"WallType3-5", buttom->GetRect().left, buttom->GetRect().top - 144, 1, 0, 0, Position::Edge);
		mObjectList.push_back(wall6);

		Object* wall7 = new Object();
		wall7->Init(L"WallType3-5", buttom->GetRect().right-156, buttom->GetRect().top - 1342 - 330 - 7, 1, 0, 1, Position::Edge);
		mObjectList.push_back(wall7);


		for (int i = 0; i < 2; i++)
		{
			Object* object = new Object();
			object->Init(L"FootBord", WINSIZEX / 10 * 5+32, WINSIZEY / 9 * 6 +15- i*195, 0);
			mObjectList.push_back(object);
		}

		Object* object0 = new Object();
		object0->Init(L"FootBord", WINSIZEX / 10 * 5 -100, WINSIZEY / 9 * 6 + 15 - 2 * 195, 0);
		mObjectList.push_back(object0);

		Object* object1 = new Object();
		object1->Init(L"FootBord", WINSIZEX / 10 * 4-50, WINSIZEY / 9 * 6 + 15 - 3 * 195, 0);
		mObjectList.push_back(object1);

		Object* object2 = new Object();
		object2->Init(L"FootBord", WINSIZEX / 10 * 3, WINSIZEY / 9 * 6 + 15 - 4 * 195, 0);
		mObjectList.push_back(object2);

		Object* object3 = new Object();
		object3->Init(L"FootBord", buttom->GetRect().left+100, WINSIZEY / 9 * 6 + 70 - 3 * 195, 0);
		mObjectList.push_back(object3);

		Object* object4= new Object();
		object4->Init(L"FootBord", buttom->GetRect().left + 100, wall2->GetRect().top+16, 0);
		mObjectList.push_back(object4);

		//문
		Object* door = new Object();
		door->Init(L"DoorType3", 24, wall6->GetRect().top - 96, 3, 0, 0, Position::Center);
		mObjectList.push_back(door);
		Object* door2 = new Object();
		door2->Init(L"DoorType3", buttom->GetRect().right - 24, wall2->GetRect().top - 96, 2, 0, 0, Position::Center);
		mObjectList.push_back(door2);
	}
	else if (stage == 2)
	{
		Object* buttom = new Object();
		buttom->Init(L"Buttom2", 5000 / 2, WINSIZEY - 48 / 2, 1);
		mObjectList.push_back(buttom);

		Object* wall1 = new Object();
		wall1->Init(L"WallType2-2", buttom->GetRect().left, WINSIZEY - 576, 1, 0, 0, Position::Edge);
		mObjectList.push_back(wall1);

		Object* wall2 = new Object();
		wall2->Init(L"WallType2-2", buttom->GetRect().left, WINSIZEY - 193, 1, 0, 1, Position::Edge);
		mObjectList.push_back(wall2);

		Object* wall3 = new Object();
		wall3->Init(L"WallType2-2", buttom->GetRect().right - 102, WINSIZEY - 576, 1, 1, 0, Position::Edge);
		mObjectList.push_back(wall3);

		Object* wall4 = new Object();
		wall4->Init(L"WallType2-2", buttom->GetRect().right - 102, WINSIZEY - 193, 1, 1, 1, Position::Edge);
		mObjectList.push_back(wall4);

		//문
		Object* door = new Object();
		door->Init(L"DoorType3", 24, wall2->GetRect().top - 96, 3, 0, 0, Position::Center);
		mObjectList.push_back(door);
		Object* door2 = new Object();
		door2->Init(L"DoorType3", buttom->GetRect().right-24, wall4->GetRect().top - 96, 2, 0, 0, Position::Center);
		mObjectList.push_back(door2);
	}
	else if (stage == 3)
	{
		Object* buttom = new Object();
		buttom->Init(L"Buttom4", 1800 / 2, WINSIZEY - 48 / 2, 1);
		mObjectList.push_back(buttom);

		Object* wall1 = new Object();
		wall1->Init(L"WallType2-2", buttom->GetRect().left, WINSIZEY - 576, 1, 0, 0, Position::Edge);
		mObjectList.push_back(wall1);

		Object* wall2 = new Object();
		wall2->Init(L"WallType2-2", buttom->GetRect().left, WINSIZEY - 193, 1, 0, 1, Position::Edge);
		mObjectList.push_back(wall2);

		Object* wall3 = new Object();
		wall3->Init(L"WallType4-2", buttom->GetRect().right - 102, WINSIZEY - 576, 1, 1, 0, Position::Edge);
		mObjectList.push_back(wall3);

		//문
		Object* door = new Object();
		door->Init(L"DoorType4", 24, wall2->GetRect().top - 96, 1, 0, 0, Position::Center);
		mObjectList.push_back(door);

		//발판
		Object* object = new Object();
		object->Init(L"FootBord", 350, 400, 0);
		mObjectList.push_back(object);

		Object* object1 = new Object();
		object1->Init(L"FootBord", 1800/2, 400, 0);
		mObjectList.push_back(object1);

		Object* object2 = new Object();
		object2->Init(L"FootBord", 1800-350 / 2, 400, 0);
		mObjectList.push_back(object2);
	}

}

void ObjectManager::Release()
{
	for (int i = 0; i < mObjectList.size(); ++i)
	{
		mObjectList[i]->Release();
		SafeDelete(mObjectList[i]);
	}
}

void ObjectManager::Update()
{
	for (int i = 0; i < mObjectList.size(); ++i)
	{
		mObjectList[i]->Update();
	}
	for (int i = 0; i < mObjectList.size(); ++i)
	{
		if (mObjectList[i]->GetType()==2|| mObjectList[i]->GetType() == 3)
		{
			float distance = Math::GetDistance(mPlayer->GetX(), mPlayer->GetY(),
				mObjectList[i]->GetX(), mObjectList[i]->GetY());
			if(distance<500 && mObjectList[i]->GetIsPlayerNear()==false)
			{ 
				mObjectList[i]->SetIsPlayerNear(true);
			}
			else if (distance > 500 && mObjectList[i]->GetIsPlayerNear() == true)
			{
				mObjectList[i]->SetIsPlayerNear(false);
			}
		}
	}
}

void ObjectManager::Render(HDC hdc,float cameraX, float cameraY)
{
	for (int i = 0; i < mObjectList.size(); ++i)
	{
		mObjectList[i]->Render(hdc,cameraX,cameraY);
	}
}
