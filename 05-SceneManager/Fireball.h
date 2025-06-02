#pragma once

#include "GameObject.h"

#define ID_ANI_FIREBALL 140000

#define	FIREBALL_WIDTH 9
#define FIREBALL_BBOX_WIDTH 9
#define FIREBALL_BBOX_HEIGHT 9

class CFireball : public CGameObject {
protected:
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }

public:
	CFireball(float x, float y, int direction); //direction: 1 - topleft, 2 - botleft, 3 - topright, 4 - botright
	int RenderPriority() { return 3; }
};