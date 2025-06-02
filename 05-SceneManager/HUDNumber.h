#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define NUMBER_0 500100
#define NUMBER_1 500101
#define NUMBER_2 500102
#define NUMBER_3 500103
#define NUMBER_4 500104
#define NUMBER_5 500105
#define NUMBER_6 500106
#define NUMBER_7 500107
#define NUMBER_8 500108
#define NUMBER_9 500109


class CHUDNumber : public CGameObject {
	int spriteID;
public:
	CHUDNumber(float x, float y) {
		spriteID = NUMBER_0;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetIdSprite(int spriteId);

	int RenderPriority() { return 5; }
};

