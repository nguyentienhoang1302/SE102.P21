#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_POINT_100 501000
#define ID_ANI_POINT_1000 501001
#define ID_ANI_1UP 501002

#define POINT_BBOX_WIDTH 12
#define POINT_BBOX_HEIGHT 8

#define POINT_VY_START -0.06f
#define POINT_GRAVITY_START 0.00005f

class CPoint : public CGameObject {
private:
	int point;
	float ay;
	bool added = false;
public:
	CPoint(float x, float y, int point) : CGameObject(x, y) {
		this->point = point;
		this->vy = POINT_VY_START;
		this->ay = POINT_GRAVITY_START;
		if (point < 10)
			this->vy = POINT_VY_START - 0.03f;
	};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int IsBlocking() { return 0; }

	int RenderPriority() { return 3; }
};