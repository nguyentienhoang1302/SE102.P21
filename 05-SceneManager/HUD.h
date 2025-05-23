#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CHUD : public CGameObject {
	int spriteID;
public:
	CHUD(float x, float y, int spriteID) {
		this->spriteID = spriteID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int RenderPriority() { return 3; }
};

