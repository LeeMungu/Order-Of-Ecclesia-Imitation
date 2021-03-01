#pragma once
#include "Monster.h"

class Monster;

class Bat : public Monster
{
public:
	void Move() override;
	void UpdateFrame() override;
	void UpdateState() override;
};

