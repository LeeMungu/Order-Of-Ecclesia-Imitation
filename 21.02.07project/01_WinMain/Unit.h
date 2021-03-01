#pragma once
#include "GameObject.h"
/*
부모클래스 
*/

//public : 여기저기서 다 접근가능
//private : 해당 클래스 내부 제외하고 전부 접근 불가
//protected : 상속관계에서 접근 가능, 자식을 보호하는 부모의 마음 같군요(aka 이광섭) 

//다중상속 : 여러개의 부모클래스를 상속받는 것, 안정적이지 못해서 잘 안씀

class Unit : public GameObject
{
protected:
	Image* mImage;
	float mSpeed;
	int mIndexX;
	int mIndexY;
	int mFrameCount;
	int mLimitCount;
	int mHp;
	int mHpMax;
public:
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void SetHp(int hp) { mHp = hp; }
	int GetHp()const { return mHp; }
};

