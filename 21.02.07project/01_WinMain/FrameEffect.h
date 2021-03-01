#pragma once
class FrameEffect
{
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	RECT mRect;

	int mFrameCount;
	int mFrameUpdateCount;
	int mFrameIndexX;

	class Image* mImage;

	bool mIsEnd;	//³¡³µ³Ä????
public:
	void Init(wstring imageKey, float x, float y,int frameUpdateCount);
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsEnd()const { return mIsEnd; }
};

