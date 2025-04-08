#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define CLOUD_WIDTH 16
#define CLOUD_BBOX_WIDTH 16
#define CLOUD_BBOX_HEIGHT 16


class CCloud : public CGameObject {
	int aniID;
public:
	CCloud(float x, float y, int aniID) {
		this->aniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};