#include "Coin.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->isFromBox == 0)
	{
		animations->Get(ID_ANI_COIN)->Render(x, y);
	}
	else if (this->isFromBox == 1)
	{
		animations->Get(ID_ANI_COIN)->Render(x, y - 16);
		if (!setAppear) {
			timer = GetTickCount64();
			setAppear = true;
		}
	}
	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isFromBox == 1)
	{
		if (!isDeleted) {
			vy = -0.3f; y += vy * dt;
			if ((GetTickCount64() - timer) > 150)
			{
				y = 0;
				isDeleted = true;
				return;
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}