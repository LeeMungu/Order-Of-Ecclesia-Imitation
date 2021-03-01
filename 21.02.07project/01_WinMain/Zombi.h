#pragma once
#include "Monster.h"

class Monster;

class Zombi : public Monster
{
public:
	void InitDate() override;
	void Move() override;                    
	void UpdateFrame() override;
	void UpdateState() override;
};

