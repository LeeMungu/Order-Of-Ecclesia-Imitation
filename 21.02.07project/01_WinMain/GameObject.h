#pragma once
//게임에서 사용되는 오브젝트들은 이녀석을 상속받는다
//UI, 총알, 몬스터, 아이템 등등등
class GameObject
{
protected:
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	RECT mRect;
	
public:
	virtual void Init() {}
	virtual void Release() {}
	virtual void Update() {}
	virtual void Render(HDC hdc) {}

	RECT GetRect()const { return mRect; }
	float GetX()const { return mX; }
	float GetY()const { return mY; }
};

