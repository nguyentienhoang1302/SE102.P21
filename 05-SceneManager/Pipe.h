#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define PIPE_WIDTH 16
#define PIPE_BBOX_WIDTH 16
#define PIPE_BBOX_HEIGHT 16

class CPipe : public CGameObject {
protected:
	int aniId;
	int renderPriority = 2; // Default render priority
public:
	CPipe(float x, float y, int aniId) : CGameObject(x, y) {
		this->aniId = aniId;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int RenderPriority() { return renderPriority; }
	void setRenderPriority(int priority) {
		this->renderPriority = priority;
	}
};