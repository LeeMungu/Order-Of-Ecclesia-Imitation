#pragma once
#include "GameObject.h"
#include "Player.h"

enum class EffectType
{
	WeaponEffect, //���� ������ ����Ʈ
	MonsterEffect1,
	MonsterEffect2,
	PointEffect,//������ ȿ��
	DestroyEffect, // ���Ľ� ����Ʈ
	HitEffect,//�ǰ� ȿ��
	NumberEffect, //�ǰ� ����� ǥ��
	MapEffect // ���� ȿ��
};


class Effect : public GameObject
{
private:
	Player* mPlayer;
	Image* mImage;
	EffectType mType;
	bool mExtence;//���翩�� true�� ����
	int mCount; //Ư���ð��� ���� ex true
	int mIndexX;
	int mIndexY;
	int mNum;//������ ��½�
	float mStartX, mStartY;//�� ����
	float mAngle;
public:
	void Init(EffectType type, float x, float y, int num);
	void Release() override;
	void Update() override;
	void Render(HDC hdc, float cameraX, float cameraY);
	
	bool GetEx()const { return mExtence; }
	void SetPlayer(Player* player) { mPlayer = player; }
};

