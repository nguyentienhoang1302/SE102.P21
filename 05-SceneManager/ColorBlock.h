#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define COLORBLOCK_WIDTH 16
#define COLORBLOCK_BBOX_WIDTH 16
#define COLORBLOCK_BBOX_HEIGHT 16


class CColorBlock : public CGameObject {
	int aniID;
public:
	CColorBlock(float x, float y, int aniID) {
		this->aniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
};