#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_DEBRIS 501003

#define DEBRIS_BBOX_WIDTH 8
#define DEBRIS_BBOX_HEIGHT 8

#define DEBRIS_SPEED_X 0.1f
#define DEBRIS_SPEED_Y 0.2f
#define DEBRIS_TIMEOUT 3000
#define DEBRIS_GRAVITY 0.001f

class CDebris : public CGameObject {
private:
    float vx, vy, ay;
    ULONGLONG startTime;
public:
    CDebris(float x, float y, float vx, float vy) {
        this->x = x;
        this->y = y;
        this->vx = vx;
        this->vy = vy;
        this->ay = DEBRIS_GRAVITY;
        startTime = GetTickCount64();
    }

    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int RenderPriority() { return 2; }
};

