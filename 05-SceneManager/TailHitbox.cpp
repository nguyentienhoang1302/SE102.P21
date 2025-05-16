#include "TailHitbox.h"
#include "Koopa.h"
#include "Brick.h"
#include "Goomba.h"
#include "MysteryBlock.h"

void CTailHitbox::Render()
{
	RenderBoundingBox();
}

CTailHitbox::CTailHitbox(float x, float y)
{
}

void CTailHitbox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTailHitbox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TAILHITBOX_BBOX_WIDTH / 2;
	t = y - TAILHITBOX_BBOX_HEIGHT / 2;
	r = l + TAILHITBOX_BBOX_WIDTH;
	b = t + TAILHITBOX_BBOX_HEIGHT;
}

void CTailHitbox::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	if (dynamic_cast<CMBlock*>(e->obj))
		OnCollisionWithMBlock(e);
	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
}

void CTailHitbox::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = (CBrick*)(e->obj);
	if (brick->IsBreakable() == 1)
	{
		e->obj->Delete();
	}
}

void CTailHitbox::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	goomba->Delete();
}

void CTailHitbox::OnCollisionWithMBlock(LPCOLLISIONEVENT e)
{
	CMBlock* mysteryblock = (CMBlock*)(e->obj);
	if (e->nx != 0 && mysteryblock->GetState() == MBLOCK_STATE_DEFAULT) {
		mysteryblock->SetState(MBLOCK_STATE_EMPTY);
	}
}

void CTailHitbox::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	koopa->Delete();
}