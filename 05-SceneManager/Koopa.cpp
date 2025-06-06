#include "Koopa.h"
#include "Brick.h"
#include "Goomba.h"
#include "MysteryBlock.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Point.h"
#include "HUDManager.h"

CKoopa::CKoopa(float x, float y, int type) :CEnemy()
{
	this->type = type;
	this->x = x; 
	this->y = y;
	SetStartPosition(x, y);
	SetBoundingBoxSize(KOOPA_BBOX_WIDTH, KOOPA_BBOX_HEIGHT);
	SetState(KOOPA_STATE_WAIT);
	ay = KOOPA_GRAVITY;
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_RED_SHELL || state == KOOPA_STATE_SPIN || state == KOOPA_STATE_RED_SPIN)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else if (state == KOOPA_STATE_WALK || state == KOOPA_STATE_RED_WALK)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - PARAKOOPA_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_BBOX_HEIGHT / 2;
		right = left + PARAKOOPA_BBOX_WIDTH;
		bottom = top + PARAKOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

bool CKoopa::IsOnPlatform(vector<LPGAMEOBJECT>* coObjects)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	float x0;
	if (vx > 0)
	{
		x0 = r; // Right edge of Koopa
	}
	else
	{
		x0 = l; // Left edge of Koopa
	}
	float y0 = b + 1; // Slightly below the bottom edge of Koopa

	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (obj->IsBlocking())
		{
			float objL, objT, objR, objB;
			obj->GetBoundingBox(objL, objT, objR, objB);
			if (x0 >= objL - 8 && x0 <= objR + 8 && y0 >= objT && y0 <= objB)
			{
				return true;
			}
		}
	}
	return false;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SPIN || state == KOOPA_STATE_RED_SPIN)
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

	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		if (state == KOOPA_STATE_RED_WALK)
		{
			SetState(KOOPA_STATE_RED_WALK2);
		}
		else if (state == KOOPA_STATE_RED_WALK2)
		{
			SetState(KOOPA_STATE_RED_WALK);
		}
		else if (state == KOOPA_STATE_WALK)
		{
			SetState(KOOPA_STATE_WALK2);
		}
		else if (state == KOOPA_STATE_WALK2)
		{
			SetState(KOOPA_STATE_WALK);
		}
	}
}

void CKoopa::OnActivated() {
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	walk_start = -1;
	shell_start = -1;
	if (type == 1)
	{
		SetState(KOOPA_STATE_WALK);
	}
	else if (type == 2)
	{
		SetState(PARAKOOPA_STATE_WALK);
	}
	else if (type == 3)
	{
		SetState(KOOPA_STATE_RED_WALK);
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == KOOPA_STATE_DIE_FROM_ATTACK || state == KOOPA_STATE_RED_DIE_FROM_ATTACK)
	{
		y += vy * dt;
		x += vx * dt;
		if (GetTickCount64() - die_start > KOOPA_DIE_FROM_ATTACK_TIMEOUT)
		{
			isDeleted = true;
		}
		return;
	}

	if (state == KOOPA_STATE_RED_WALK) {
		if (!IsOnPlatform(coObjects))
		{
			SetState(KOOPA_STATE_RED_WALK2);
		}
	}

	if (state == KOOPA_STATE_RED_WALK2) {
		if (!IsOnPlatform(coObjects))
		{
			SetState(KOOPA_STATE_RED_WALK);
		}
	}

	if (state == PARAKOOPA_STATE_JUMP)
	{
		SetState(PARAKOOPA_STATE_WALK);
	}
	if ((GetTickCount64() - walk_start > 600) && state == PARAKOOPA_STATE_WALK)
	{
		SetState(PARAKOOPA_STATE_JUMP);
	}

	if (state == KOOPA_STATE_SHELL && GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT)
	{
		SetState(KOOPA_STATE_WALK);
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
	}

	if (state == KOOPA_STATE_RED_SHELL && GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT)
	{
		SetState(KOOPA_STATE_RED_WALK);
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
	}

	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	UpdateActivation(cam_x, cam_y, 270, 287);
	//if (!IsVisible()) return;

	vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	if (!IsVisible()) return;
	int aniId = -1;
	if (state == PARAKOOPA_STATE_WALK)
	{
		aniId = ID_ANI_PARAKOOPA_WALK;
	}
	else if (state == KOOPA_STATE_WALK)
	{
		aniId = ID_ANI_KOOPA_WALK;
	}
	else if (state == KOOPA_STATE_WALK2)
	{
		aniId = ID_ANI_KOOPA_WALK2;
	}
	else if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_HELD)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SPIN)
	{
		aniId = ID_ANI_KOOPA_SPIN;
	}
	else if (state == PARAKOOPA_STATE_JUMP)
	{
		aniId = ID_ANI_PARAKOOPA_JUMP;
	}
	else if (state == KOOPA_STATE_RED_WALK)
	{
		aniId = ID_ANI_KOOPA_RED_WALK;
	}
	else if (state == KOOPA_STATE_RED_SPIN)
	{
		aniId = ID_ANI_KOOPA_RED_SPIN;
	}
	else if (state == KOOPA_STATE_RED_SHELL || state == KOOPA_STATE_RED_HELD)
	{
		aniId = ID_ANI_KOOPA_RED_SHELL;
	}
	else if (state == KOOPA_STATE_WAIT)
	{
		aniId = ID_ANI_KOOPA_WAIT;
	}
	else if (state == KOOPA_STATE_RED_WALK2)
	{
		aniId = ID_ANI_KOOPA_RED_WALK2;
	}
	else if (state == KOOPA_STATE_DIE_FROM_ATTACK)
	{
		aniId = ID_ANI_KOOPA_DIE_FROM_ATTACK;
	}
	else if (state == KOOPA_STATE_RED_DIE_FROM_ATTACK)
	{
		aniId = ID_ANI_KOOPA_RED_DIE_FROM_ATTACK;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		shell_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_WALK:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case PARAKOOPA_STATE_WALK:
		walk_start = GetTickCount64();
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_WALK2:
		vx = KOOPA_WALKING_SPEED;
		break;
	case PARAKOOPA_STATE_JUMP:
		vy = -KOOPA_VY_JUMP;
		break;
	case KOOPA_STATE_RED_SHELL:
		shell_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_RED_WALK:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_RED_WALK2:
		vx = KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SPIN:
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_RED_SPIN:
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_WAIT:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_HELD:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_RED_HELD:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_DIE_FROM_ATTACK:
		die_start = GetTickCount64();
		break;
	case KOOPA_STATE_RED_DIE_FROM_ATTACK:
		die_start = GetTickCount64();
		break;
	}

	if (this->state == KOOPA_STATE_DIE_FROM_ATTACK || this->state == KOOPA_STATE_RED_DIE_FROM_ATTACK) return;

	CGameObject::SetState(state);
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	float x1 = CGame::GetInstance()->GetCurrentScene()->xMario;
	if (x1 > x)
		goomba->DieFromAttack(-1);
	else
		goomba->DieFromAttack(1);
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	float x1 = CGame::GetInstance()->GetCurrentScene()->xMario;
	if (x1 > x)
		koopa->DieFromAttack(-1);
	else
		koopa->DieFromAttack(1);
}

void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = (CBrick*)(e->obj);
	if (brick->IsBreakable() == 1)
	{
		if (e->nx != 0)
			brick->Break();
	}
}

void CKoopa::OnCollisionWithMBlock(LPCOLLISIONEVENT e)
{
	CMBlock* mysteryblock = (CMBlock*)(e->obj);
	if (e->nx != 0 && mysteryblock->GetState() == MBLOCK_STATE_DEFAULT) {
		mysteryblock->SetState(MBLOCK_STATE_EMPTY);
		if (mysteryblock->getContent() == 1) {
			CHUDManager::GetInstance()->coins++;
			float gx, gy;
			mysteryblock->GetPosition(gx, gy);
			LPGAMEOBJECT effectPoint = new CPoint(gx, gy - 16, 100);
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddEffect(effectPoint);
		}
	}
}

void CKoopa::SpinLeft() {
	vx = KOOPA_SPINNING_SPEED;
}

void CKoopa::SpinRight() {
	vx = -KOOPA_SPINNING_SPEED;
}

void CKoopa::DieFromAttack(int Direction)
{
	vx = KOOPA_VX_DIE_FROM_ATTACK * Direction;
	vy = KOOPA_VY_DIE_FROM_ATTACK;
	ay = KOOPA_GRAVITY;
	if (state == KOOPA_STATE_RED_WALK || state == KOOPA_STATE_RED_WALK2 || state == KOOPA_STATE_RED_SPIN || state == KOOPA_STATE_RED_SHELL)
	{
		SetState(KOOPA_STATE_RED_DIE_FROM_ATTACK);
	}
	else
	{
		SetState(KOOPA_STATE_DIE_FROM_ATTACK);
	}

	LPGAMEOBJECT effectPoint = new CPoint(x, y - 16, 100);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->AddEffect(effectPoint);
}
