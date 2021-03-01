#pragma once
#include "GameObject.h" 
enum class BackGroundType
{
	BackGround,
	BackGroundBack,
	Wall,
	BackGroundBack1,
	BackGroundBack2,
	BackGroundBack3
};

class BackGround :public GameObject
{
	Image* mImage;
	BackGroundType mType;
	int mCorrection;//-타입마다 다른 이동속도 보정값
public:
	void Init(wstring key, BackGroundType type);
	void Release();
	void Update();
	void Render(HDC hdc, float cameraX, float cameraY);

	BackGroundType GetType()const { return mType; }

};

