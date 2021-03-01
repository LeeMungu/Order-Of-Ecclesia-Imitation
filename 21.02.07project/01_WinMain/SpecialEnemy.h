#pragma once
#include "Enemy.h"
class SpecialEnemy : public Enemy
{
public:
	void Update()override;
	void Render(HDC hdc)override;
};

