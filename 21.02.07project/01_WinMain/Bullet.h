#pragma once

/*
1. ȭ��ۿ� �Ѿ˳����� ����
2. ���̶� �浹�ϸ� �� + �Ѿ� ����
3. ���� �Ѿ��� �����Ѵ�(�÷��̾����� ���󰡰�)
4. ���� �������� ����
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

