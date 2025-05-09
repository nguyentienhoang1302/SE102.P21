#pragma once
#include "GameObject.h"

#define LEAF_BBOX_WIDTH  20
#define LEAF_BBOX_HEIGHT 20

#define LEAF_FALL_SPEED_X	0.04f 
#define LEAF_FALL_SPEED_Y	0.02f
#define LEAF_RISE_SPEED 0.02f
#define LEAF_RISE_HEIGHT 50

#define LEAF_STATE_RISE	100
#define LEAF_STATE_FALLLEFT	200
#define LEAF_STATE_FALLRIGHT	300

#define ID_ANI_LEAF_FALLLEFT	151000
#define ID_ANI_LEAF_FALLRIGHT	152000

class CLeaf : public CGameObject
{
protected:
	float x0, y0;

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual int RenderPriority() { return 1; };

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
};

