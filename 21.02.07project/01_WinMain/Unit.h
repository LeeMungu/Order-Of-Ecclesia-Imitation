#pragma once
#include "GameObject.h"
/*
�θ�Ŭ���� 
*/

//public : �������⼭ �� ���ٰ���
//private : �ش� Ŭ���� ���� �����ϰ� ���� ���� �Ұ�
//protected : ��Ӱ��迡�� ���� ����, �ڽ��� ��ȣ�ϴ� �θ��� ���� ������(aka �̱���) 

//���߻�� : �������� �θ�Ŭ������ ��ӹ޴� ��, ���������� ���ؼ� �� �Ⱦ�

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

