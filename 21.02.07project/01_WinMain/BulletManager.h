#pragma once

class Bullet;
class BulletManager
{
	vector<Bullet*> mBullets;
public:
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(wstring key, float x, float y, float speed, float angle);
};

