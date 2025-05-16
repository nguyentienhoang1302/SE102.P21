#pragma once

#include "GameObject.h"

#define TAILHITBOX_BBOX_WIDTH 9
#define TAILHITBOX_BBOX_HEIGHT 9

class CTailHitbox : public CGameObject {
protected:
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CTailHitbox(float x, float y);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMBlock(LPCOLLISIONEVENT e);

	int RenderPriority() { return 2; }
};