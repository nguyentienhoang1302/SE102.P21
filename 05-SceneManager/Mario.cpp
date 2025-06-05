#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "MysteryBlock.h"
#include "Mushroom.h"
#include "PiranhaPlant.h"
#include "Fireball.h"
#include "Brick.h"
#include "Koopa.h"
#include "TailHitbox.h"
#include "Point.h"

#include "Collision.h"
#include "SampleKeyEventHandler.h"
#include "PlayScene.h"
#include "HUD.h"
#include "HUDManager.h"
#include "PSwitch.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGame::GetInstance()->GetCurrentScene()->xMario = x;
	CGame::GetInstance()->GetCurrentScene()->yMario = y;
	CGame::GetInstance()->GetCurrentScene()->MLevel = level;

	//limit mario movement in playscene and set mario die if he falls out of the screen
	if (this->x < 0)
	{
		this->x = 0;
	}
	if (this->x > 2800)
	{
		this->x = 2800;
	}
	if (this->y > 194)
	{
		SetState(MARIO_STATE_DIE);
	}
	if (this->y < -230)
	{
		this->y = -230;
	}

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// Update the position of the held Koopa shell
	if (heldKoopa != nullptr)
	{
		float marioX, marioY;
		GetPosition(marioX, marioY);
		// Offset based on Mario's direction and level
		if (this->level == MARIO_LEVEL_RACCOON)
		{
			heldKoopa->SetPosition(marioX + (nx > 0 ? 16 : -16), marioY);
		}
		else if (this->level == MARIO_LEVEL_BIG)
		{
			heldKoopa->SetPosition(marioX + (nx > 0 ? 12 : -12), marioY);
		}
		else if (this->level == MARIO_LEVEL_SMALL)
		{
			heldKoopa->SetPosition(marioX + (nx > 0 ? 12 : -12), marioY - 2);
		}		
	}

	if (heldKoopa != nullptr && GetTickCount64() - heldKoopa_start > KOOPA_SHELL_TIMEOUT)
	{
		if (heldKoopa->GetState() == KOOPA_STATE_RED_HELD)
		{
			if (nx < 0)
				heldKoopa->SetState(KOOPA_STATE_RED_WALK);
			else
				heldKoopa->SetState(KOOPA_STATE_RED_WALK2);
		}
		else
		{
			if (nx < 0)
				heldKoopa->SetState(KOOPA_STATE_WALK);
			else
				heldKoopa->SetState(KOOPA_STATE_WALK2);
		}
		heldKoopa = nullptr;
	}

	//Delete used hitbox immediately and unused hitbox after timeout
	CTailHitbox* tail = dynamic_cast<CTailHitbox*>(subObject);
	if (subObject != nullptr && tail->IsUsed() == 0 && GetTickCount64() - tailAttack_start > MARIO_TAIL_ATTACK_TIME)
	{
		subObject->Delete();
		subObject = NULL;
	}
	else if (subObject != nullptr && tail->IsUsed() == 1)
	{
		subObject->Delete();
		subObject = NULL;
	}

	if (state == MARIO_STATE_DIE && GetTickCount64() - die_start > 1500)
	{
		if (CHUDManager::GetInstance()->lifes <= 0)
		{
			// Set game over flag in the current scene
			CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			if (scene) scene->isGameOver = true;
			DebugOut(L"[INFO] GAME OVER");
			return;
		}
		else
		{
			CGame::GetInstance()->RequestReload();
		}
	}
	//Entering pipe and switch scene
	if (isEnteringPipe)
	{
		if (GetTickCount64() - pipe_timer > MARIO_PIPE_TIME)
		{
			isEnteringPipe = false;
			CGame::GetInstance()->InitiateSwitchScene(pipe_scene_id);
		}
		if(CGame::GetInstance()->GetCurrentScene()->GetStageId() == 5 && CGame::GetInstance()->GetIsFromSecretLevel() == false)
			vy = 0.03f;
		else if (CGame::GetInstance()->GetCurrentScene()->GetStageId() == 5 && CGame::GetInstance()->GetIsFromSecretLevel() == true)
			vy = -0.03f;
		else if (CGame::GetInstance()->GetCurrentScene()->GetStageId() == 6)
			vy = -0.03f;
		y += vy * dt;
		return;
	}

	//Exiting pipe
	if (isExitingPipe)
	{
		if (GetTickCount64() - pipe_timer > MARIO_PIPE_TIME)
		{
			isExitingPipe = false;
		}
		vy = -0.03f;
		y += vy * dt;
		return;
	}

	//Set Mario position after he come back from secret stage
	if (CGame::GetInstance()->GetCurrentScene()->GetStageId() == 6)
	{
		CGame::GetInstance()->SetIsFromSecretLevel(true);
	}

	if (CGame::GetInstance()->GetIsFromSecretLevel() && CGame::GetInstance()->GetCurrentScene()->GetStageId() == 5)
	{
		SetState(MARIO_STATE_PIPE_EXIT);
		this->SetPosition(2324, 170);
		CGame::GetInstance()->SetIsFromSecretLevel(false);
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMBlock*>(e->obj))
		OnCollisionWithMBlock(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CPPlant*>(e->obj))
		OnCollisionWithPPlant(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireball(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CPSwitch*>(e->obj))
		OnCollisionWithPSwitch(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	float gx, gy;
	goomba->GetPosition(gx, gy);
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0 && goomba->GetState() == PARAGOOMBA_STATE_WALK || (e->ny < 0 && goomba->GetState() == PARAGOOMBA_STATE_JUMP) || (e->ny < 0 && goomba->GetState() == PARAGOOMBA_STATE_LOWJUMP))
	{
		{
			LPGAMEOBJECT effectPoint = new CPoint(gx, gy - 16, 100);
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddEffect(effectPoint);
			goomba->ParagoombaGetHit();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (e->ny < 0 && goomba->GetState() == GOOMBA_STATE_WALKING)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			LPGAMEOBJECT effectPoint = new CPoint(gx, gy - 16, 100);
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddEffect(effectPoint);
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if(goomba->GetState() != GOOMBA_STATE_DIE_FROM_ATTACK && goomba->GetState() != PARAGOOMBA_STATE_DIE_FROM_ATTACK) // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_RACCOON)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CHUDManager::GetInstance()->coins++;
	CHUDManager::GetInstance()->point = CHUDManager::GetInstance()->point + 50;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	if (CGame::GetInstance()->IsKeyDown(DIK_DOWN) || e->ny > 0)
	{
		SetState(MARIO_STATE_PIPE_ENTER);
		isEnteringPipe = true;
		pipe_timer = GetTickCount64();
		pipe_scene_id = p->GetSceneId();
		CGame::GetInstance()->SetSavedMarioLevel(this->GetLevel());
	}
}

void CMario::OnCollisionWithMBlock(LPCOLLISIONEVENT e)
{
	CMBlock* mysteryblock = (CMBlock*)(e->obj);
	if (e->ny > 0 && mysteryblock->GetState() == MBLOCK_STATE_DEFAULT) {
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

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	int point = 0;
	CMushroom* mushroom = (CMushroom*)(e->obj);
	if (mushroom->GetType() == 1)
	{
		if (level == MARIO_LEVEL_SMALL)
		{
			y -= 8;
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		point = 1000;
	}
	else if (mushroom->GetType() == 2)
	{
		CHUDManager::GetInstance()->lifes++;
		point = 10; //1 up
	}
	e->obj->Delete();

	float gx, gy;
	e->obj->GetPosition(gx, gy);
	LPGAMEOBJECT effectPoint = new CPoint(gx, gy - 16, point);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->AddEffect(effectPoint);
}

void CMario::OnCollisionWithPPlant(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_RACCOON)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithFireball(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_RACCOON)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = (CBrick*)(e->obj);
	if (brick->IsBreakable() == 1 && level != MARIO_LEVEL_SMALL && e->ny > 0)
	{
		brick->Break();
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	float x0, y0;
	koopa->GetPosition(x0, y0);
	if ((e->ny < 0 && koopa->GetState() == PARAKOOPA_STATE_WALK) || (e->ny < 0 && koopa->GetState() == PARAKOOPA_STATE_JUMP))
	{
		koopa->SetState(KOOPA_STATE_WALK);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		LPGAMEOBJECT effectPoint = new CPoint(x0, y0 - 16, 100);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddEffect(effectPoint);
	}
	else if (e->ny < 0 && koopa->GetState() == KOOPA_STATE_WALK)
	{
		koopa->SetState(KOOPA_STATE_SHELL);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		LPGAMEOBJECT effectPoint = new CPoint(x0, y0 - 16, 100);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddEffect(effectPoint);
	}
	else if (e->ny < 0 && koopa->GetState() == KOOPA_STATE_RED_WALK)
	{
		koopa->SetState(KOOPA_STATE_RED_SHELL);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		LPGAMEOBJECT effectPoint = new CPoint(x0, y0 - 16, 100);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddEffect(effectPoint);
	}
	else if (e->ny < 0 && koopa->GetState() == KOOPA_STATE_RED_WALK2)
	{
		koopa->SetState(KOOPA_STATE_RED_SHELL);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		LPGAMEOBJECT effectPoint = new CPoint(x0, y0 - 16, 100);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddEffect(effectPoint);
	}
	else if (e->ny < 0 && koopa->GetState() == KOOPA_STATE_SPIN)
	{
		koopa->SetState(KOOPA_STATE_SHELL);
		koopa->SetPosition(x0, y0 - 8);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else if (e->ny < 0 && koopa->GetState() == KOOPA_STATE_RED_SPIN)
	{
		koopa->SetState(KOOPA_STATE_RED_SHELL);
		koopa->SetPosition(x0, y0 - 8);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}

	else if (koopa->GetState() == KOOPA_STATE_SHELL)
	{
		if (e->ny < 0)
		{
			koopa->SetState(KOOPA_STATE_SPIN);

			float x0, y0;
			koopa->GetPosition(x0, y0);
			if (x < x0) // if mario is to the right of the shell, shell spins left
			{
				koopa->SpinLeft();
			}
			else if (x >= x0) // if mario is to the left of the shell, shell spins right
			{
				koopa->SpinRight();
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (e->nx < 0)
		{
			if (CGame::GetInstance()->IsKeyDown(DIK_A) && heldKoopa == nullptr)
			{
				// Pick up the shell
				heldKoopa = koopa;
				heldKoopa->SetState(KOOPA_STATE_HELD);
				SetState(MARIO_STATE_HOLD_SHELL);
			}
			else
			{
				koopa->SetState(KOOPA_STATE_SPIN);
				koopa->SpinLeft();
			}
		}
		else
		{
			if (CGame::GetInstance()->IsKeyDown(DIK_A) && heldKoopa == nullptr)
			{
				// Pick up the shell
				heldKoopa = koopa;
				heldKoopa->SetState(KOOPA_STATE_HELD);
				SetState(MARIO_STATE_HOLD_SHELL);
			}
			else
			{
				koopa->SetState(KOOPA_STATE_SPIN);
				koopa->SpinRight();
			}
		}
	}
	else if (koopa->GetState() == KOOPA_STATE_RED_SHELL)
	{
		if (e->ny < 0)
		{
			koopa->SetState(KOOPA_STATE_RED_SPIN);

			float x0, y0;
			koopa->GetPosition(x0, y0);
			if (x < x0) // if mario is to the right of the shell, shell spins left
			{
				koopa->SpinLeft();
			}
			else if (x >= x0) // if mario is to the left of the shell, shell spins right
			{
				koopa->SpinRight();
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (e->nx < 0)
		{
			if (CGame::GetInstance()->IsKeyDown(DIK_A) && heldKoopa == nullptr)
			{
				// Pick up the shell
				heldKoopa = koopa;
				heldKoopa->SetState(KOOPA_STATE_RED_HELD);
				SetState(MARIO_STATE_HOLD_SHELL);
			}
			else
			{
				koopa->SetState(KOOPA_STATE_RED_SPIN);
				koopa->SpinLeft();
			}
		}
		else
		{
			if (CGame::GetInstance()->IsKeyDown(DIK_A) && heldKoopa == nullptr)
			{
				// Pick up the shell
				heldKoopa = koopa;
				heldKoopa->SetState(KOOPA_STATE_RED_HELD);
				SetState(MARIO_STATE_HOLD_SHELL);
			}
			else
			{
				koopa->SetState(KOOPA_STATE_RED_SPIN);
				koopa->SpinRight();
			}
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL)
			{
				if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_RACCOON)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (level == MARIO_LEVEL_SMALL || level == MARIO_LEVEL_BIG)
	{
		y -= 8;
		level = MARIO_LEVEL_RACCOON;
		StartUntouchable();
	}
	float gx, gy;
	e->obj->GetPosition(gx, gy);
	LPGAMEOBJECT effectPoint = new CPoint(gx, gy - 16, 1000);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->AddEffect(effectPoint);
}

void CMario::OnCollisionWithPSwitch(LPCOLLISIONEVENT e)
{
	CPSwitch* b = dynamic_cast<CPSwitch*>(e->obj);
	if (e->ny < 0)
	{
		b->HandleClick();
	}
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (heldKoopa == nullptr)
	{
		if (isEnteringPipe || isExitingPipe)
		{
			aniId = ID_ANI_MARIO_SMALL_PIPE;
		}
		else if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (vx == MARIO_RUNNING_SPEED)
					{
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					}
					else
					{
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (vx == -MARIO_RUNNING_SPEED)
					{
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					}
					else
					{
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
					}
				}

		if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
	}
	else
	{
		if (vx == 0 && nx > 0)
		{
			aniId = ID_ANI_MARIO_SMALL_HOLD_SHELL_RIGHT_IDLE;
		}
		else if (vx == 0 && nx < 0)
		{
			aniId = ID_ANI_MARIO_SMALL_HOLD_SHELL_LEFT_IDLE;
		}
		else if (nx > 0)
		{
			aniId = ID_ANI_MARIO_SMALL_HOLD_SHELL_RIGHT;
		}
		else
		{
			aniId = ID_ANI_MARIO_SMALL_HOLD_SHELL_LEFT;
		}
	}

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (heldKoopa == nullptr)
	{
		if (isEnteringPipe || isExitingPipe)
		{
			aniId = ID_ANI_MARIO_PIPE;
		}
		else if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (vx == MARIO_RUNNING_SPEED)
					{
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					}
					else
					{
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (vx == -MARIO_RUNNING_SPEED)
					{
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					}
					else
					{
						aniId = ID_ANI_MARIO_WALKING_LEFT;
					}
				}

		if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;
	}
	else
	{
		if (vx == 0 && nx > 0)
		{
			aniId = ID_ANI_MARIO_HOLD_SHELL_RIGHT_IDLE;
		}
		else if (vx == 0 && nx < 0)
		{
			aniId = ID_ANI_MARIO_HOLD_SHELL_LEFT_IDLE;
		}
		else if (nx > 0)
		{
			aniId = ID_ANI_MARIO_HOLD_SHELL_RIGHT;
		}
		else
		{
			aniId = ID_ANI_MARIO_HOLD_SHELL_LEFT;
		}
	}

	return aniId;
}

//
// Get animation ID for Raccoon Mario
//
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (heldKoopa == nullptr)
	{
		if (isEnteringPipe || isExitingPipe)
		{
			aniId = ID_ANI_MARIO_RACCOON_PIPE;
		}
		else if (!isOnPlatform)
		{
			if (isFlying)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_RACCOON_FLY_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_FLY_LEFT;
			}
			else
			{
				if (isHovering)
				{
					if (nx > 0)
						aniId = ID_ANI_MARIO_RACCOON_HOVER_RIGHT;
					else
						aniId = ID_ANI_MARIO_RACCOON_HOVER_LEFT;
				}
				else if (vy != 0)
				{
					if (nx > 0)
						aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
				}
				if (vy == 0)
				{
					CSampleKeyHandler* keyHandler = (CSampleKeyHandler*)CGame::GetInstance()->GetKeyHandler();
					keyHandler->OnKeyUp(DIK_S); // Simulate releasing the 'S' key when done hovering
				}
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
			}
			else
			{
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
					else if (vx == MARIO_RUNNING_SPEED)
					{
						aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
					}
					else
					{
						aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
					else if (vx == -MARIO_RUNNING_SPEED)
					{
						aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
					}
					else
					{
						aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
					}
				}
			}

		if (state == MARIO_STATE_TAIL_ATTACK)
		{
			aniId = ID_ANI_MARIO_RACCOON_TAIL_ATTACK;
		}

		if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
	}
	else
	{
		if (vx == 0 && nx > 0)
		{
			aniId = ID_ANI_MARIO_RACCOON_HOLD_SHELL_RIGHT_IDLE;
		}
		else if (vx == 0 && nx < 0)
		{
			aniId = ID_ANI_MARIO_RACCOON_HOLD_SHELL_LEFT_IDLE;
		}
		else if (nx > 0)
		{
			aniId = ID_ANI_MARIO_RACCOON_HOLD_SHELL_RIGHT;
		}
		else
		{
			aniId = ID_ANI_MARIO_RACCOON_HOLD_SHELL_LEFT;
		}
	}

	return aniId;
}

void CMario::Render()
{
	// Flashing effect when untouchable
	if (untouchable)
	{
		// Flash: only render on even frames (adjust as needed)
		if ((GetTickCount64() / 100) % 2 == 0)
		{
			CAnimations* animations = CAnimations::GetInstance();
			int aniId = -1;

			if (state == MARIO_STATE_DIE)
				aniId = ID_ANI_MARIO_DIE;
			else if (level == MARIO_LEVEL_BIG)
				aniId = GetAniIdBig();
			else if (level == MARIO_LEVEL_SMALL)
				aniId = GetAniIdSmall();
			else if (level == MARIO_LEVEL_RACCOON)
				aniId = GetAniIdRaccoon();

			animations->Get(aniId)->Render(x, y);
		}
	}
	else
	{
		// Normal render
		CAnimations* animations = CAnimations::GetInstance();
		int aniId = -1;

		if (state == MARIO_STATE_DIE)
			aniId = ID_ANI_MARIO_DIE;
		else if (level == MARIO_LEVEL_BIG)
			aniId = GetAniIdBig();
		else if (level == MARIO_LEVEL_SMALL)
			aniId = GetAniIdSmall();
		else if (level == MARIO_LEVEL_RACCOON)
			aniId = GetAniIdRaccoon();

		animations->Get(aniId)->Render(x, y);
	}

	//RenderBoundingBox();
	
	DebugOutTitle(L"Super Mario Bros 3");
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	// Prevent state changes during the tail attack
	if (this->state == MARIO_STATE_TAIL_ATTACK && GetTickCount64() - tailAttack_start < MARIO_TAIL_ATTACK_TIME) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_RELEASE_JUMP:
		ay = MARIO_GRAVITY;
		isFlying = false;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;
	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL && heldKoopa == nullptr)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		if (isOnPlatform)
		{
			isHovering = false;
		}
		isFlying = false;
		break;
	case MARIO_STATE_DIE:
		CHUDManager::GetInstance()->lifes--;
		die_start = GetTickCount64();
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_FLY:
		if (isSitting) break;
		isHovering = false;
		isFlying = true;
		vy = -MARIO_FLY_SPEED;
		ay = 0;
		break;
	case MARIO_STATE_HOVER:
		if (isSitting) break;
		isFlying = false;
		isHovering = true;
		vy = MARIO_HOVER_SPEED;
		ay = 0;
		break;
	case MARIO_STATE_HOLD_SHELL:
		heldKoopa_start = GetTickCount64();
		if (heldKoopa != nullptr)
		{
			// Update the Koopa shell's position to follow Mario
			float marioX, marioY;
			GetPosition(marioX, marioY);
			// Offset based on Mario's direction and level
			if (this->level == MARIO_LEVEL_RACCOON)
			{
				heldKoopa->SetPosition(marioX + (nx > 0 ? 16 : -16), marioY);
			}
			else if (this->level == MARIO_LEVEL_BIG)
			{
				heldKoopa->SetPosition(marioX + (nx > 0 ? 12 : -12), marioY);
			}
			else if (this->level == MARIO_LEVEL_SMALL)
			{
				heldKoopa->SetPosition(marioX + (nx > 0 ? 12 : -12), marioY - 2);
			}
		}
		break;
	case MARIO_STATE_RELEASE_SHELL:
		if (heldKoopa != nullptr)
		{
			// Throw the shell in Mario's facing direction
			if (heldKoopa->GetState() == KOOPA_STATE_RED_HELD)
			{
				heldKoopa->SetState(KOOPA_STATE_RED_SPIN);
			}
			else
			{
				heldKoopa->SetState(KOOPA_STATE_SPIN);
			}
			if (nx > 0)
			{
				heldKoopa->SpinLeft();
			}
			else
			{
				heldKoopa->SpinRight();
			}
			heldKoopa = nullptr; // Mario is no longer holding the shell
		}
		break;
	case MARIO_STATE_TAIL_ATTACK:
		ax = 0.0f;
		if (level == MARIO_LEVEL_RACCOON)
		{
			// If there is an old hitbox, delete it first
			if (subObject != nullptr && !subObject->IsDeleted())
			{
				subObject->Delete();
				subObject = nullptr;
			}
			tailAttack_start = GetTickCount64();
			float marioX, marioY;
			GetPosition(marioX, marioY);
			subObject = new CTailHitbox(marioX, marioY);
			if (nx > 0)
			{
				subObject->SetPosition(marioX - 6, marioY + 6);
				subObject->SetSpeed(0.12f, 0);
			}
			else
			{
				subObject->SetPosition(marioX + 6, marioY + 6);
				subObject->SetSpeed(-0.12f, 0);
			}
			CreateSubObject = true;
		}
		break;
	case MARIO_STATE_PIPE_ENTER:
		pipe_timer = GetTickCount64();
		isEnteringPipe = true;
		break;
	case MARIO_STATE_PIPE_EXIT:
		pipe_timer = GetTickCount64();
		isExitingPipe = true;
		break;
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == MARIO_STATE_TAIL_ATTACK)
	{
		left = x - MARIO_TAIL_ATTACK_BBOX_WIDTH / 2;
		top = y - MARIO_TAIL_ATTACK_BBOX_HEIGHT / 2;
		right = left + MARIO_TAIL_ATTACK_BBOX_WIDTH;
		bottom = top + MARIO_TAIL_ATTACK_BBOX_HEIGHT;
	}
	else
	{
		if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACCOON)
		{
			if (isSitting)
			{
				left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
				top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
				right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
				bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
			}
			else
			{
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
				top = y - MARIO_BIG_BBOX_HEIGHT / 2;
				right = left + MARIO_BIG_BBOX_WIDTH;
				bottom = top + MARIO_BIG_BBOX_HEIGHT;
			}
		}
		else
		{
			left = x - MARIO_SMALL_BBOX_WIDTH / 2;
			top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
			right = left + MARIO_SMALL_BBOX_WIDTH;
			bottom = top + MARIO_SMALL_BBOX_HEIGHT;
		}
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

