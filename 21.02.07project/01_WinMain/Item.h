#pragma once
#include "GameObject.h"
#include "Image.h"

enum class WeaponType
{
	Confodere,//레이피어
	Secare//검
};

enum class Kinds
{
	FieldWeapon,
	EquipmentWeapon,
	Food
};

class Item : public GameObject
{
protected:
	Image* mImage;
	int mIndexX;
	int mIndexY;
	int mFrameCount;

public:
	virtual void Init(float x, float y, WeaponType type);
	virtual void Release();
	virtual void Update() ;
	virtual void Render(HDC hdc, float cameraX, float cameraY);
	
};

