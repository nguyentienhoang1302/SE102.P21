#include "Mushroom.h"

CMushroom::CMushroom(float x, float y, int type) : CGameObject(x, y) {
	this->type = type;
	if (type == 1)
		aniID = ID_ANI_MUSHROOM_RED;
	else if (type == 2)
		aniID = ID_ANI_MUSHROOM_GREEN;
	vx = 0;
	vy = -0.016f;
	ay = 0;
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
	if (!setAppear) {
		timer = GetTickCount64();
		setAppear = true;
	}
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (GetTickCount64() - timer > 500) {
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CMushroom*>(e->obj)) return;

		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
	else return;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type == 1)
	{
		vy += ay * dt;
		vx += ax * dt;

		if (GetTickCount64() - timer > 500) {
			ay = MUSHROOM_GRAVITY;
			vx = -MUSHROOM_WALKING_SPEED;
		}
		else y += vy * dt;
	}
	else if (type == 2)
	{
		vy += ay * dt;
		vx += ax * dt;

		if (GetTickCount64() - timer > 100) {
			ay = MUSHROOM_GRAVITY;
		}
		else y += vy * dt;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}