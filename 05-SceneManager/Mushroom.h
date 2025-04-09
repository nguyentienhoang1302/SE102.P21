#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_WALKING_SPEED 0.06f

#define	MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14

class CMushroom : public CGameObject {
protected:
	float ax;
	float ay;
	bool setAppear = false;
	int aniID;
	int type;

	ULONGLONG timer;

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y, int type); //1 - Red, 2 - Green
	int GetType() { return type; }
};