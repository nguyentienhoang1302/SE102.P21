#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define TREE_WIDTH 16
#define TREE_BBOX_WIDTH 16
#define TREE_BBOX_HEIGHT 16


class CTree : public CGameObject {
	int aniID;
public:
	CTree(float x, float y, int aniID) {
		this->aniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};