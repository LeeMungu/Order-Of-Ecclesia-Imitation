#pragma once

/*
ObjectManager
*/

class Image;
class Player;
class ObjectManager;
class MonsterManager;
class BackGroundManager;
class ItemManager;
class Map;
class MainGame
{
	Image* mBackBuffer;	//후면버퍼(건들지마라)
private:
	Image* mBackground1;
	Image* mBackground2;
	Image* mWall;
	Image* mExplosion;
	MonsterManager* mMonsterManager;
	ObjectManager* mObjectManager;
	BackGroundManager* mBackGroundManager;
	ItemManager* mItemManager;
	Player* mPlayer;
	Map* mMap;
	float mCameraX;
	float mCameraY;
	int mStageNum;
	bool mStageSet;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AllImageLoad();
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

