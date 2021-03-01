#pragma once
#include "Unit.h"
#include "Player.h"

class Player;

enum class MonsterState
{
	Generation,//생성
	Generation2,
	Stand,//상시상태
	Move,//이동
	Attack1,//공쏘기
	Attack2,//구르기
	Attack3,//빔
	Extinction//제거 - 모션끝에 Extinction bool값을 true로 갖는다
};


class Monster : public Unit
{
protected:
	Image* mImageMotion;
	int mMotionLR;//좌우
	float mAngle;
	bool mIsFallow;
	wstring mKey;
	Player* mPlayer;
	MonsterState mState;
	bool mAttackBool;//공격여부
	int mAttack;//공격데미지
	int mAttackCount;//공격텀
	bool mDamegeBool;//공격 당했을때
	int mDamegeCount;//공격당 했을때 텀
	bool mExtence;
	int mExtenceCount;
	int mFallowCount;// 유도 텀
	float mFallowX, mFallowY;
	int mMotionCount;//모션전환 텀
	float mStartX;//보스 제자리 셋팅용 - 박쥐도 씀
	float mStartY;
	int mBeamCount;
public:
	virtual void Init(wstring key, float x, float y, float speed, float angle);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, float cameraX, float cameraY);
	virtual void UpdateCrash();
	
	virtual void InitDate() {};
	virtual void Move() {};
	virtual void UpdateFrame() {};
	virtual void UpdateState() {};
	
	wstring GetKey()const { return mKey; }
	MonsterState GetState()const { return mState; }
	bool GetExtence()const { return mExtence; }
	bool GetAttackBool()const { return mAttackBool; }
	int GetAttack()const { return mAttack; }
	bool GetDamegeBool()const { return mDamegeBool; }

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetExtence(bool ex) { mExtence = ex; }
	void SetAttackBool(bool attack) { mAttackBool = attack; }
	void SetDamegeBool(bool damegeBool) { mDamegeBool = damegeBool; }
};

