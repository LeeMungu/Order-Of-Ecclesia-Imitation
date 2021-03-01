#pragma once
//���ӿ��� ���Ǵ� ������Ʈ���� �̳༮�� ��ӹ޴´�
//UI, �Ѿ�, ����, ������ ����
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

