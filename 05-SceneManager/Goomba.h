#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_VY_JUMP 0.40f
#define GOOMBA_VY_LOWJUMP 0.15f

#define VX_DIE_FROM_ATTACK 0.05f
#define VY_DIE_FROM_ATTACK 0.26f
#define GRAVITY_DIE_FROM_ATTACK 0.001f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 14
#define PARAGOOMBA_BBOX_WIDTH 20
#define PARAGOOMBA_BBOX_HEIGHT 19

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_DIE_FROM_ATTACK_TIMEOUT 2000

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define PARAGOOMBA_STATE_WALK 300
#define PARAGOOMBA_STATE_JUMP 400
#define PARAGOOMBA_STATE_LOWJUMP 500
#define GOOMBA_STATE_WAITING 000
#define GOOMBA_STATE_DIE_FROM_ATTACK 600
#define PARAGOOMBA_STATE_DIE_FROM_ATTACK 700

#define ID_ANI_GOOMBA_WAITING 20000
#define ID_ANI_GOOMBA_WALKING 21000
#define ID_ANI_GOOMBA_DIE 22000
#define ID_ANI_PARAGOOMBA 23000
#define ID_ANI_PARAGOOMBA_WINGLESS_WALK 24000
#define ID_ANI_PARAGOOMBA_WINGLESS_DIE 25000
#define ID_ANI_GOOMBA_DIE_FROM_ATTACK 26000
#define ID_ANI_PARAGOOMBA_DIE_FROM_ATTACK 27000

class CGoomba : public CGameObject
{
protected:
	float start_x;
	float start_y;
	float ax;				
	float ay;
	int type;
	int lowjumpcount;
	bool wingless = false;
	bool isActivated = false;
	bool isOutOfRange = false;

	ULONGLONG die_start;
	ULONGLONG walk_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int type); //1 - Goomba, 2 - Paragoomba
	virtual void SetState(int state);
	int RenderPriority() { return 2; }
	void ParagoombaGetHit(); //Set Goomba direction after Paragoomba turn into Goomba
	void DieFromAttack(int Direction);
};