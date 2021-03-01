#pragma once
#include "GameObject.h"
enum class Position
{
	Center,
	Edge
};

class Image;

class Object : public GameObject
{
private:
	Image* mImage;
	//문 전용
	Image* mImageOpen;
	RECT mRectOpen;
	bool mIsPlayerNear;
	int mFrameCount;
	float mOpenSizeX;
	//int mOpen

	int mIndexX, mIndexY;
	int mType;//발판 다른방향에서 충돌가능 여부 0==조그만발판, 1==큰장애물, 2==앞문, 3==뒷문
	bool mMulty;
	wstring mKey;
public:
	//type:발판 다른방향에서 충돌가능 여부 0==조그만발판, 1==큰장애물, 2==앞문, 3==뒷문
	void Init(wstring key, float x, float y, int type, int indexX, int indexY, Position position);
	void Init(wstring key, float x, float y, int type);
	void Release()override;
	void Update()override;
	void Render(HDC hdc,float cameraX,float cameraY);
	int GetType()const { return mType; }
	wstring GetKey()const { return mKey; }
	bool GetIsPlayerNear()const { return mIsPlayerNear; }
	void SetIsPlayerNear(bool isPlayerNear) { mIsPlayerNear = isPlayerNear; }
};

