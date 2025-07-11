﻿#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "Koopa.h"

#define MARIO_WALKING_SPEED         0.1f
#define MARIO_RUNNING_SPEED         0.22f

#define MARIO_ACCEL_WALK_X          0.00025f
#define MARIO_ACCEL_RUN_X           0.0004f

#define MARIO_JUMP_SPEED_Y          0.3f
#define MARIO_JUMP_RUN_SPEED_Y      0.35f

#define MARIO_JUMP_DEFLECT_SPEED    0.25f

#define MARIO_GRAVITY               0.0006f

#define MARIO_FLY_SPEED             0.24f
#define MARIO_HOVER_SPEED           0.04f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_FLY			700
#define MARIO_STATE_HOVER		701

#define MARIO_STATE_HOLD_SHELL 800
#define MARIO_STATE_RELEASE_SHELL 801

#define MARIO_STATE_TAIL_ATTACK 900

#define MARIO_STATE_PIPE_ENTER 1000
#define MARIO_STATE_PIPE_EXIT 1001

#pragma region ANIMATION_ID
//BIG MARIO

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_HOLD_SHELL_RIGHT 1021
#define ID_ANI_MARIO_HOLD_SHELL_LEFT 1022
#define ID_ANI_MARIO_HOLD_SHELL_RIGHT_IDLE 1011
#define ID_ANI_MARIO_HOLD_SHELL_LEFT_IDLE 1012

#define ID_ANI_MARIO_PIPE 1030

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLD_SHELL_RIGHT 1801
#define ID_ANI_MARIO_SMALL_HOLD_SHELL_LEFT 1802
#define ID_ANI_MARIO_SMALL_HOLD_SHELL_RIGHT_IDLE 1701
#define ID_ANI_MARIO_SMALL_HOLD_SHELL_LEFT_IDLE 1702

#define ID_ANI_MARIO_SMALL_PIPE 1031

// RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 2001
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 2002

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 2101
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 2102

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 2201
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 2202

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2301
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2302

#define ID_ANI_MARIO_RACCOON_FLY_RIGHT 2401
#define ID_ANI_MARIO_RACCOON_FLY_LEFT 2402

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2501
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2502

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2601
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2602

#define ID_ANI_MARIO_RACCOON_HOVER_RIGHT 2701
#define ID_ANI_MARIO_RACCOON_HOVER_LEFT 2702

#define ID_ANI_MARIO_RACCOON_HOLD_SHELL_RIGHT 2901
#define ID_ANI_MARIO_RACCOON_HOLD_SHELL_LEFT 2902
#define ID_ANI_MARIO_RACCOON_HOLD_SHELL_RIGHT_IDLE 2801
#define ID_ANI_MARIO_RACCOON_HOLD_SHELL_LEFT_IDLE 2802

#define ID_ANI_MARIO_RACCOON_TAIL_ATTACK 3000

#define ID_ANI_MARIO_RACCOON_PIPE 1032

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON		3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_TAIL_ATTACK_BBOX_WIDTH  24
#define MARIO_TAIL_ATTACK_BBOX_HEIGHT 24


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_TAIL_ATTACK_TIME 200
#define MARIO_PIPE_TIME 1000

class CMario : public CGameObject
{
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG tailAttack_start = -1;
	ULONGLONG heldKoopa_start = -1;
	ULONGLONG die_start = -1;
	ULONGLONG pipe_timer = -1;
	int pipe_scene_id = -1;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithMBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithPPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPSwitch(LPCOLLISIONEVENT e);
	void OnCollisionWithGiftSelect(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	BOOLEAN isSitting;
	BOOLEAN isOnPlatform;
	BOOLEAN isFlying = false;
	BOOLEAN isHovering = false;
	BOOLEAN isEnteringPipe = false;
	BOOLEAN isExitingPipe = false;
	CKoopa* heldKoopa = nullptr;
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int GetLevel() { return level; };
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	float Getvy() { return vy; }
	float Getvx() { return vx; }

	void ShellPickUp();
};