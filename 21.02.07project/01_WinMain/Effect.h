#pragma once
#include "GameObject.h"
#include "Player.h"

enum class EffectType
{
	WeaponEffect, //무기 데미지 이펙트
	MonsterEffect1,
	MonsterEffect2,
	PointEffect,//아이템 효과
	DestroyEffect, // 완파시 이팩트
	HitEffect,//피격 효과
	NumberEffect, //피격 대미지 표시
	MapEffect // 지도 효과
};


class Effect : public GameObject
{
private:
	Player* mPlayer;
	Image* mImage;
	EffectType mType;
	bool mExtence;//존재여부 true면 제거
	int mCount; //특정시간이 나면 ex true
	int mIndexX;
	int mIndexY;
	int mNum;//데미지 출력시
	float mStartX, mStartY;//맵 전용
	float mAngle;
public:
	void Init(EffectType type, float x, float y, int num);
	void Release() override;
	void Update() override;
	void Render(HDC hdc, float cameraX, float cameraY);
	
	bool GetEx()const { return mExtence; }
	void SetPlayer(Player* player) { mPlayer = player; }
};

