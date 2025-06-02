#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "HUDNumber.h"

class CHUD : public CGameObject {
	int spriteID;
	vector<LPGAMEOBJECT> timer;
	vector<LPGAMEOBJECT> coins;
	vector<LPGAMEOBJECT> point;
	vector<LPGAMEOBJECT> lifes;
	vector<LPGAMEOBJECT> speedbars;
	LPGAMEOBJECT pMeter;
	bool isInitUI;
public:
	CHUD(float x, float y, int spriteID) {
		this->spriteID = spriteID;
		isInitUI = false;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void InitUI();

	void UpdateElements(vector<LPGAMEOBJECT>& elements, DWORD value);

	void SetPosition(float x, float y);

	int RenderPriority() { return 4; }
};

