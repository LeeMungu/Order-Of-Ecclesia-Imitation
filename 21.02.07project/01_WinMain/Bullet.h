#pragma once

/*
1. 화면밖에 총알나가면 삭제
2. 적이랑 충돌하면 적 + 총알 삭제
3. 적도 총알을 쏴야한다(플레이어한테 날라가게)
4. 적도 여러마리 존재
*/

class Bullet
{
	float mX;
	float mY;
	float mSpeed;
	float mAngle;
	RECT mRect;
	class Image* mImage;
public:
	void Fire(class Image* image, float x, float y, float speed, float angle);
	void Update();
	void Render(HDC hdc);

	RECT GetRect()const { return mRect; }
};

