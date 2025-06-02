#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define PSWITCH_STATE_IDLE 100
#define PSWITCH_STATE_CLICKED 200

#define	PSWITCH_WIDTH 16
#define PSWITCH_BBOX_WIDTH 16
#define PSWITCH_BBOX_HEIGHT 16

#define PSWITCH_ANI_IDLE 170001
#define PSWITCH_ANI_CLICKED 170002

class CPSwitch : public CGameObject {
protected:
	bool canClick;
public:
	CPSwitch(float x, float y) : CGameObject(x, y) {
		SetState(PSWITCH_STATE_IDLE);
		this->canClick = true;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	void HandleClick();

	int RenderPriority() { return 2; }
};