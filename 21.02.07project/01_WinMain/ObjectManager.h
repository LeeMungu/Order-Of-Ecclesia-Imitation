#pragma once
#include "Player.h"
#include "Object.h"

class Player;
class Object;

class ObjectManager
{
private:
	vector<Object*> mObjectList;
	Player* mPlayer;
public:
	void Init(int stage);
	void Release();
	void Update();
	void Render(HDC hdc,float cameraX,float cameraY);

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	vector<Object*> GetObjectList() const { return mObjectList; }
};

