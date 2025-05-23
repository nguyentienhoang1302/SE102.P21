#include "Debris.h"

void CDebris::Render()
{
    CSprites* s = CSprites::GetInstance();
    s->Get(ID_ANI_DEBRIS)->Draw(x, y);
}

void CDebris::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;
    x += vx * dt;
    y += vy * dt;

    if (GetTickCount64() - startTime > DEBRIS_TIMEOUT)
        this->Delete();
}

void CDebris::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - DEBRIS_BBOX_WIDTH / 2;
    t = y - DEBRIS_BBOX_HEIGHT / 2;
    r = l + DEBRIS_BBOX_WIDTH - 1;
    b = t + DEBRIS_BBOX_HEIGHT;
}
