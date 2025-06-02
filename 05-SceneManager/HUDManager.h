#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Brick.h"
#include "PlayScene.h"
#include "debug.h"


class CHUDManager : public CGameObject {
protected:
	static CHUDManager* __instance;
public:
	int point;
	int timer;
	int lifes;
	int coins;
	float elapsedTime;
	static CHUDManager* GetInstance();
	CHUDManager(float x = 0, float y = 0) : CGameObject(x, y)
	{
		point = coins = 0;
		timer = 300;
		elapsedTime = 0;
		lifes = 4;
	}
	void Render() {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};
