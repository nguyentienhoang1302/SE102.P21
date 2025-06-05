#pragma once

#include "GameObject.h"

#define GBOX_WIDTH 16
#define GBOX_BBOX_WIDTH 16
#define GBOX_BBOX_HEIGHT 16


class CGiftBox : public CGameObject {
	int aniID;
public:
	CGiftBox(float x, float y, int aniID) {
		this->aniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};