#include "Leaf.h"

CLeaf::CLeaf(float x, float y) : CGameObject(x, y) {
	SetState(LEAF_STATE_RISE);
	x0 = x;
	y0 = y;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (state == LEAF_STATE_RISE && y0 - y >= LEAF_RISE_HEIGHT)
	{
		SetState(LEAF_STATE_FALLLEFT);
	}

	if (state == LEAF_STATE_FALLLEFT && x0 - x >= LEAF_BBOX_WIDTH * 2)
	{
		SetState(LEAF_STATE_FALLRIGHT);
	}

	if (state == LEAF_STATE_FALLRIGHT && x - x0 >= LEAF_BBOX_WIDTH * 2)
	{
		SetState(LEAF_STATE_FALLLEFT);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::Render()
{
	int aniId = 1;
	if (state == LEAF_STATE_RISE)
	{
		aniId = ID_ANI_LEAF_FALLLEFT;
	}
	else if (state == LEAF_STATE_FALLLEFT)
	{
		aniId = ID_ANI_LEAF_FALLLEFT;
	}
	else if (state == LEAF_STATE_FALLRIGHT)
	{
		aniId = ID_ANI_LEAF_FALLRIGHT;
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CLeaf::SetState(int state)
{
	switch (state)
	{
	case LEAF_STATE_RISE:
		vx = 0;
		vy = -LEAF_RISE_SPEED;
		break;
	case LEAF_STATE_FALLLEFT:
		vx = -LEAF_FALL_SPEED_X;
		vy = LEAF_FALL_SPEED_Y;
		break;
	case LEAF_STATE_FALLRIGHT:
		vx = LEAF_FALL_SPEED_X;
		vy = LEAF_FALL_SPEED_Y;
		break;
	}
	CGameObject::SetState(state);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
}