#include "PiranhaPlant.h"
#include "Game.h"
#include "Fireball.h"
#include "PlayScene.h"

CPPlant::CPPlant(float x, float y, int type) :CEnemy()
{
	this->type = type;
	this->x = x; 
	this->y = y;
	SetStartPosition(x, y);
	if (type == 1)
	{
		SetBoundingBoxSize(FIREPIRANHAPLANT_BBOX_WIDTH, FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN);
		SetState(FIREPIRANHAPLANT_STATE_WAIT);
		y0 = y + 6;
		timer = 0;
	}
	else if (type == 2)
	{
		SetBoundingBoxSize(FIREPIRANHAPLANT_BBOX_WIDTH, FIREPIRANHAPLANT_BBOX_HEIGHT_RED);
		SetState(FIREPIRANHAPLANT_STATE_WAIT);
		y0 = y + 10;
		timer = 0;
	}
	else if (type == 3)
	{
		y0 = y + 6;
		timer = 0;
	}
}

void CPPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (type == 1)
	{
		left = x - FIREPIRANHAPLANT_BBOX_WIDTH / 2;
		top = y - FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN / 2;
		right = left + FIREPIRANHAPLANT_BBOX_WIDTH;
		bottom = top + FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN;
	}
	else if (type == 2)
	{
		left = x - FIREPIRANHAPLANT_BBOX_WIDTH / 2;
		top = y - FIREPIRANHAPLANT_BBOX_HEIGHT_RED / 2;
		right = left + FIREPIRANHAPLANT_BBOX_WIDTH;
		bottom = top + FIREPIRANHAPLANT_BBOX_HEIGHT_RED;
	}
	else if (type == 3)
	{
		left = x - PIRANHAPLANT_BBOX_WIDTH / 2;
		top = y - PIRANHAPLANT_BBOX_HEIGHT / 2;
		right = left + PIRANHAPLANT_BBOX_WIDTH;
		bottom = top + PIRANHAPLANT_BBOX_HEIGHT;
	}
}

void CPPlant::OnActivated() {
	SetState(FIREPIRANHAPLANT_STATE_TL);
	timer = 0;
	isStart = true;
}

void CPPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->type == 3)
	{
		x += vx * dt;
		y += vy * dt;

		timer += dt;
		if (timer < 4000) {
			Rise();
		}
		else if (timer < 8000) {
			Fall();
		}
		else timer = 0;

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	else
	{
		float cam_x, cam_y;
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);
		UpdateActivation(cam_x, cam_y, 270, 287);
		if (!IsVisible()) return;

		if (isStart == true)
		{
			x += vx * dt;
			y += vy * dt;
			timer += dt;
			if (timer < 2000) {
				Rise();
			}
			else if (timer < 5000) {
				Shoot();
			}
			else if (timer < 8000) {
				isShooting = false;
				Fall();
			}
			else timer = 0;

			float x1 = CGame::GetInstance()->GetCurrentScene()->xMario;
			float y1 = CGame::GetInstance()->GetCurrentScene()->yMario;
			if (x1 < x && y1 < y) {
				SetState(FIREPIRANHAPLANT_STATE_TL);
			}
			else if (x1 < x && y1 > y) {
				SetState(FIREPIRANHAPLANT_STATE_BL);
			}
			else if (x1 > x && y1 < y) {
				SetState(FIREPIRANHAPLANT_STATE_TR);
			}
			else if (x1 > x && y1 > y) {
				SetState(FIREPIRANHAPLANT_STATE_BR);
			}
			CGameObject::Update(dt, coObjects);
			CCollision::GetInstance()->Process(this, dt, coObjects);
		}
	}
}

void CPPlant::Render()
{
	if (!IsVisible()) return;
	int aniId = -1;
	if (this->type == 3)
	{
		aniId = ID_ANI_PIRANHAPLANT;
	}
	else
	{
		if (state == FIREPIRANHAPLANT_STATE_BL && type == 1 && isShooting == true)
		{
			aniId = ID_ANI_PIRANHAPLANT_GREEN_BL_SHOOT;
		}
		else if (state == FIREPIRANHAPLANT_STATE_BL && type == 1 && isShooting == false)
		{
			aniId = ID_ANI_PIRANHAPLANT_GREEN_BL_IDLE;
		}
		else if (state == FIREPIRANHAPLANT_STATE_TL && type == 1 && isShooting == true)
		{
			aniId = ID_ANI_PIRANHAPLANT_GREEN_TL_SHOOT;
		}
		else if (state == FIREPIRANHAPLANT_STATE_TL && type == 1 && isShooting == false)
		{
			aniId = ID_ANI_PIRANHAPLANT_GREEN_TL_IDLE;
		}
		else if (state == FIREPIRANHAPLANT_STATE_TR && type == 1 && isShooting == true)
		{
			aniId = ID_ANI_PIRANHAPLANT_GREEN_TR_SHOOT;
		}
		else if (state == FIREPIRANHAPLANT_STATE_TR && type == 1 && isShooting == false)
		{
			aniId = ID_ANI_PIRANHAPLANT_GREEN_TR_IDLE;
		}
		else if (state == FIREPIRANHAPLANT_STATE_BR && type == 1 && isShooting == true)
		{
			aniId = ID_ANI_PIRANHAPLANT_GREEN_BR_SHOOT;
		}
		else if (state == FIREPIRANHAPLANT_STATE_BR && type == 1 && isShooting == false)
		{
			aniId = ID_ANI_PIRANHAPLANT_GREEN_BR_IDLE;
		}
		else if (state == FIREPIRANHAPLANT_STATE_BL && type == 2 && isShooting == true)
		{
			aniId = ID_ANI_PIRANHAPLANT_RED_BL_SHOOT;
		}
		else if (state == FIREPIRANHAPLANT_STATE_BL && type == 2 && isShooting == false)
		{
			aniId = ID_ANI_PIRANHAPLANT_RED_BL_IDLE;
		}
		else if (state == FIREPIRANHAPLANT_STATE_TL && type == 2 && isShooting == true)
		{
			aniId = ID_ANI_PIRANHAPLANT_RED_TL_SHOOT;
		}
		else if (state == FIREPIRANHAPLANT_STATE_TL && type == 2 && isShooting == false)
		{
			aniId = ID_ANI_PIRANHAPLANT_RED_TL_IDLE;
		}
		else if (state == FIREPIRANHAPLANT_STATE_TR && type == 2 && isShooting == true)
		{
			aniId = ID_ANI_PIRANHAPLANT_RED_TR_SHOOT;
		}
		else if (state == FIREPIRANHAPLANT_STATE_TR && type == 2 && isShooting == false)
		{
			aniId = ID_ANI_PIRANHAPLANT_RED_TR_IDLE;
		}
		else if (state == FIREPIRANHAPLANT_STATE_BR && type == 2 && isShooting == true)
		{
			aniId = ID_ANI_PIRANHAPLANT_RED_BR_SHOOT;
		}
		else if (state == FIREPIRANHAPLANT_STATE_BR && type == 2 && isShooting == false)
		{
			aniId = ID_ANI_PIRANHAPLANT_RED_BR_IDLE;
		}
		else if (state == FIREPIRANHAPLANT_STATE_WAIT)
		{
			aniId = ID_ANI_PIRANHAPLANT_WAIT;
		}
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPPlant::SetState(int state)
{
	CGameObject::SetState(state);
}

void CPPlant::Rise()
{
	if (type == 1)
	{
		if (y < y0 - FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN)
		{
			y = y0 - FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN;
			vy = 0;
		}
		else
			vy = -0.02f;
	}
	else if (type == 2)
	{
		if (y < y0 - FIREPIRANHAPLANT_BBOX_HEIGHT_RED)
		{
			y = y0 - FIREPIRANHAPLANT_BBOX_HEIGHT_RED;
			vy = 0;
		}
		else
			vy = -0.02f;
	}
	else if (type == 3)
	{
		if (y < y0 - PIRANHAPLANT_BBOX_HEIGHT)
		{
			y = y0 - PIRANHAPLANT_BBOX_HEIGHT;
			vy = 0;
		}
		else
			vy = -0.02f;
	}
}

void CPPlant::Fall()
{
	if (y > y0 + 5)
	{
		vy = 0;
		y = y0 + 5;
	}
	else
		vy = 0.02f;
}

void CPPlant::Shoot()
{
	if (isShooting == false)
	{
		switch (state) {
		case FIREPIRANHAPLANT_STATE_TL:
			subObject = new CFireball(x, y, 1);
			subObject->SetPosition(x, y - 9);
			break;
		case FIREPIRANHAPLANT_STATE_BL:
			subObject = new CFireball(x, y, 2);
			subObject->SetPosition(x, y - 9);
			break;
		case FIREPIRANHAPLANT_STATE_TR:
			subObject = new CFireball(x, y, 3);
			subObject->SetPosition(x, y - 9);
			break;
		case FIREPIRANHAPLANT_STATE_BR:
			subObject = new CFireball(x, y, 4);
			subObject->SetPosition(x, y - 9);
			break;
		}
		isShooting = true;
		CreateSubObject = true;
	}
	vy = 0;
}