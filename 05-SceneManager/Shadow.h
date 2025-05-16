#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define SHADOW_WIDTH 16
#define SHADOW_BBOX_WIDTH 16
#define SHADOW_BBOX_HEIGHT 16


class CShadow : public CGameObject {
	int aniID;
public:
	CShadow(float x, float y, int aniID) {
		this->aniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};