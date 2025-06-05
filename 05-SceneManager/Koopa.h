#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_VY_JUMP 0.40f
#define KOOPA_SPINNING_SPEED 0.25f
#define KOOPA_VY_DIE_FROM_ATTACK -0.3f
#define KOOPA_VX_DIE_FROM_ATTACK 0.1f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_SHELL 14
#define PARAKOOPA_BBOX_WIDTH 20
#define PARAKOOPA_BBOX_HEIGHT 24

#define KOOPA_SHELL_TIMEOUT 5000
#define KOOPA_DIE_FROM_ATTACK_TIMEOUT 2000

#define KOOPA_STATE_WAIT 000
#define KOOPA_STATE_WALK 100
#define KOOPA_STATE_WALK2 110
#define KOOPA_STATE_SHELL 200
#define KOOPA_STATE_SPIN 300
#define PARAKOOPA_STATE_WALK 400
#define PARAKOOPA_STATE_JUMP 500
#define KOOPA_STATE_RED_WALK 600
#define KOOPA_STATE_RED_SHELL 700
#define KOOPA_STATE_RED_SPIN 800
#define KOOPA_STATE_RED_WALK2 900
#define KOOPA_STATE_HELD 1000
#define KOOPA_STATE_RED_HELD 1100
#define KOOPA_STATE_DIE_FROM_ATTACK 1200
#define KOOPA_STATE_RED_DIE_FROM_ATTACK 1300

#define ID_ANI_KOOPA_WAIT 31000
#define ID_ANI_KOOPA_WALK 31000
#define ID_ANI_KOOPA_WALK2 31010
#define ID_ANI_KOOPA_SHELL 32000
#define ID_ANI_KOOPA_SPIN 33000
#define ID_ANI_PARAKOOPA_WALK 34000
#define ID_ANI_PARAKOOPA_JUMP 35000
#define ID_ANI_KOOPA_RED_WALK 36000
#define ID_ANI_KOOPA_RED_SHELL 37000
#define ID_ANI_KOOPA_RED_SPIN 38000
#define ID_ANI_KOOPA_RED_WALK2 39000
#define ID_ANI_KOOPA_DIE_FROM_ATTACK 39991
#define ID_ANI_KOOPA_RED_DIE_FROM_ATTACK 39992

class CKoopa : public CGameObject
{
protected:
	float start_x;
	float start_y;
	float ax;
	float ay;
	int type;
	bool isActivated = false;
	bool isOutOfRange = false;

	ULONGLONG shell_start;
	ULONGLONG walk_start;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	bool IsOnPlatform(vector<LPGAMEOBJECT>* coObjects);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y, int type); //1 - Koopa, 2 - ParaKoopa, 3 - Red Koopa
	virtual void SetState(int state);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMBlock(LPCOLLISIONEVENT e);

	virtual void SpinLeft();
	virtual void SpinRight();
	int RenderPriority() { return 2; }
	void DieFromAttack(int Direction);
};