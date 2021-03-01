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
	//�� ����
	Image* mImageOpen;
	RECT mRectOpen;
	bool mIsPlayerNear;
	int mFrameCount;
	float mOpenSizeX;
	//int mOpen

	int mIndexX, mIndexY;
	int mType;//���� �ٸ����⿡�� �浹���� ���� 0==���׸�����, 1==ū��ֹ�, 2==�չ�, 3==�޹�
	bool mMulty;
	wstring mKey;
public:
	//type:���� �ٸ����⿡�� �浹���� ���� 0==���׸�����, 1==ū��ֹ�, 2==�չ�, 3==�޹�
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

