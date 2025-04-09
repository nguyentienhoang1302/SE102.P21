#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Coin.h"
#include "Mushroom.h"

#define ID_SPRITE_MBLOCK 100000
#define ID_ANI_MBLOCK 101000
#define ID_ANI_MBLOCK_EMPTY 102000

#define MBLOCK_WIDTH 16
#define MBLOCK_BBOX_WIDTH 16
#define MBLOCK_BBOX_HEIGHT 16

#define MBLOCK_STATE_DEFAULT 101
#define MBLOCK_STATE_EMPTY 102

class CMBlock : public CGameObject {
protected:
	int aniId;
	int content;

	float ax = 0;
	float ay = 0;

	float y0;

	ULONGLONG empty_start;

	virtual int RenderPriority() { return 1; };

public:
	CMBlock(float x, float y, int aniID, int content);
	//content: 1-coin, 2-mushroom, 3-leaf, 4-greenmushroom

	virtual void SetState(int state);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int getContent();
};