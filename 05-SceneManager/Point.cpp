#include "Point.h"
#include "HUDManager.h"

void CPoint::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* ani = CAnimations::GetInstance();

	switch (point)
	{
	case 100:
		sprites->Get(ID_ANI_POINT_100)->Draw(x, y);
		if (added == false)
		{
			CHUDManager::GetInstance()->point = CHUDManager::GetInstance()->point + 100;
			added = true;
		}
		break;
	case 1000:
		sprites->Get(ID_ANI_POINT_1000)->Draw(x, y);
		if (added == false)
		{
			CHUDManager::GetInstance()->point = CHUDManager::GetInstance()->point + 1000;
			added = true;
		}
		break;
	case 10:
		sprites->Get(ID_ANI_1UP)->Draw(x, y);
		break;
	}
	//RenderBoundingBox();
}

void CPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - POINT_BBOX_WIDTH / 2;
	t = y - POINT_BBOX_HEIGHT / 2;
	r = l + POINT_BBOX_WIDTH - 1;
	b = t + POINT_BBOX_HEIGHT;
}

void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	y += vy * dt;
	if (vy > 0) {
		this->Delete();
	}
	CGameObject::Update(dt, coObjects);
}