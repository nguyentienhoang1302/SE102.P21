#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "Koopa.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		if (mario->isOnPlatform == true)
		{
			mario->SetState(MARIO_STATE_JUMP);
		}
		if (mario->GetLevel() == MARIO_LEVEL_RACCOON && CGame::GetInstance()->IsKeyDown(DIK_A) && (abs(mario->Getvx()) == MARIO_RUNNING_SPEED))
		{
			mario->SetState(MARIO_STATE_FLY);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_RACCOON && !mario->isOnPlatform)
		{
			mario->SetState(MARIO_STATE_HOVER);
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		CGame::GetInstance()->RequestReload();
		break;
	case DIK_A:
		if (mario->GetLevel() == MARIO_LEVEL_RACCOON && mario->GetState() != MARIO_STATE_TAIL_ATTACK && mario->heldKoopa == nullptr && mario->isSitting == false)
		{
			mario->SetState(MARIO_STATE_TAIL_ATTACK);
			break;
		}
		if (mario->heldKoopa == nullptr)
		{
			mario->ShellPickUp();
			break;
		}
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		if (mario->heldKoopa != nullptr)
		{
			mario->SetState(MARIO_STATE_RELEASE_SHELL);
		}
		break;
	}

}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A) && mario->heldKoopa == nullptr)
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A) && mario->heldKoopa == nullptr)
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}