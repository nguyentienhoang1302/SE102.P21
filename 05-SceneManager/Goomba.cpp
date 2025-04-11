#include "Goomba.h"
#include "Game.h"

CGoomba::CGoomba(float x, float y, int type):CGameObject(x, y)
{
	this->type = type;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	walk_start = -1;
	SetState(GOOMBA_STATE_WAITING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == GOOMBA_STATE_WALKING)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
	else
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}
	if (state == GOOMBA_STATE_WAITING && CGame::GetInstance()->GetCurrentScene()->xMario + 180 >= this->x)
	{
		lowjumpcount = 0;
		if (type == 1)
		{
			SetState(GOOMBA_STATE_WALKING);
		}
		else if (type == 2)
		{
			SetState(PARAGOOMBA_STATE_WALK);
		}
	}
	if ((GetTickCount64() - walk_start > 500) && state == PARAGOOMBA_STATE_WALK)
	{
		SetState(PARAGOOMBA_STATE_LOWJUMP);
	}
	if (state == PARAGOOMBA_STATE_LOWJUMP)
	{
		lowjumpcount++;
		SetState(PARAGOOMBA_STATE_WALK);
	}
	if (lowjumpcount == 3 && state == PARAGOOMBA_STATE_WALK)
	{
		SetState(PARAGOOMBA_STATE_JUMP);
		lowjumpcount = 0;
	}
	if (state == PARAGOOMBA_STATE_JUMP)
	{
		SetState(PARAGOOMBA_STATE_WALK);
	}
	if (this->GetState() == PARAGOOMBA_STATE_WALK || this->GetState() == PARAGOOMBA_STATE_LOWJUMP || this->GetState() == PARAGOOMBA_STATE_JUMP)
	{
		float x1 = CGame::GetInstance()->GetCurrentScene()->xMario;
		if (x1 < x && vx > 0) {
			vx = -vx;
		}
		else if (x1 > x && vx < 0) {
			vx = -vx;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = -1;
	if (state == PARAGOOMBA_STATE_WALK)
	{
		//aniId = ID_ANI_PARAGOOMBA_WALK;
		aniId = ID_ANI_PARAGOOMBA;
	}
	else if (state == GOOMBA_STATE_WALKING)
	{
		aniId = ID_ANI_GOOMBA_WALKING;
	}
	else if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == PARAGOOMBA_STATE_JUMP)
	{
		//aniId = ID_ANI_PARAGOOMBA_JUMP;
		aniId = ID_ANI_PARAGOOMBA;
	}
	else if (state == PARAGOOMBA_STATE_LOWJUMP)
	{
		//aniId = ID_ANI_PARAGOOMBA_JUMP;
		aniId = ID_ANI_PARAGOOMBA;
	}
	else if (state == GOOMBA_STATE_WAITING)
	{
		aniId = ID_ANI_GOOMBA_WAITING;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING:
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case PARAGOOMBA_STATE_WALK:
			walk_start = GetTickCount64();
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case PARAGOOMBA_STATE_JUMP:
			vy = -GOOMBA_VY_JUMP;
			break;
		case PARAGOOMBA_STATE_LOWJUMP:
			vy = -GOOMBA_VY_LOWJUMP;
			break;
		case GOOMBA_STATE_WAITING:
			vx = 0;
			break;
	}
}
