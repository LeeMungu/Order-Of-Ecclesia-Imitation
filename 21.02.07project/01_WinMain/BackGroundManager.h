#pragma once
#include "BackGround.h"

class BackGround;
class BackGroundManager
{
	vector<BackGround*> mBackGroundList;
public:
	void Init(int stage);
	void Release();
	void Update();
	void Render(HDC hdc, float cameraX, float cameraY);
};

