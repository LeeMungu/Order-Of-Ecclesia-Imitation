#pragma once
#include "Unit.h"
#include "Weapon.h"
class Image;
class Object;
class Weapon;
class Effect;
enum class State
{
	Stand,
	Stop,
	Run,
	Down,
	JumpUp,
	JumpDown,
	JumpDrop,
	Up, 
	Atteck,
	LeftTurnRight,
	RightTurnLeft,
	Evasion,//ȸ��
	StandAttackLeft,
	StandAttackRight,
	JumpAttackLeft,
	JumpAttackRight,
	DownAttackLeft,
	DownAttackRight,
	Damege,
	SpAttack
};

enum class PositionState
{
	Jumping,
	OnGround,
	Down,
	Air,
	Up
};

enum class DoorType
{
	Front,
	Back
};

class Player : public Unit
{
private:
	Image* mGageImage;
	Image* mHpImage;
	Image* mMpImage;
	Image* mNumImage;
	vector<Effect*> mEffect;
	vector<Object*> mObjectList;
	int mMotionRL;//��������0������1����
	//������������
	float mJumpingPawer;
	int mJumpingCount;
	float mGravity;
	State mState;//������ ����
	PositionState mPositionState;//��������
	//���� ����
	int mFootNum;
	bool mAttackRight;//right���ÿ���
	bool mAttackLeft;//left���ÿ���
	float mCameraX;
	float mCameraY;
	bool mCameraBool;
	float mBeforeX, mBeforeY;//ī�޶� ���ú���
	//��������
	bool mInvincibility;
	int mInviCount;//�����ð�
	//mp
	int mMp;
	int mMpMax;
	//sp
	int mSp;
	int mSpMax;
	//����
	Weapon* mWeapon;
	WeaponType mWeaponType;
	//�������� �Ѿ��
	int mStageNum;
	bool mStageSet;
	float mStageStartX;
	float mStageStartY;
	float mStageCameraX;
	float mStageCameraY;
	DoorType mDoorType;
public:
	void Init(wstring key, float x, float y, float speed, float angle);

	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Control();
	void Move(float moveX, float moveY);
	void UpdateFrame();
	void UpdateState();
	void UpdateFootBord();
	void UpdateCamera();
	void Jump();
	void WeaponGeneration();

	void SetObjectList(vector<Object*> objectList) { mObjectList = objectList; }
	
	float GetCameraX() { return mCameraX; }
	float GetCameraY() { return mCameraY; }
	int GetMotionRL() { return mMotionRL; }
	State GetState() const { return mState; }
	int GetSp()const { return mSp; }
	bool GetInvin()const { return mInvincibility; }
	int GetStageNum()const { return mStageNum; }
	bool GetStageSet()const { return mStageSet; }
	DoorType GetDoorType()const { return mDoorType; }
	float GetStageStartX()const { return mStageStartX; }
	float GetStageStartY()const { return mStageStartY; }

	Weapon* GetWeapon()const
	{
		if (mWeapon != NULL) return mWeapon;
		else return NULL;
	}

	void SetInvin(bool invin) { mInvincibility = invin; }
	void SetSp(int sp) { mSp = sp; }
	void SetState(State state) { mState = state; }
	void SetIndexX(int indexX) { mIndexX = indexX; }
	void SetMotionRL(int motion) { mMotionRL = motion; }
	void SetStageSet(bool stageSet) { mStageSet = stageSet; }
	void SetX(float x) { mX = x; }
	void SetY(float y) { mY = y; }
	void SetWeaponType(WeaponType weaponType) { mWeaponType = weaponType; }
};

