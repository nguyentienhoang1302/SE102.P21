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
			//mario->SetState(MARIO_STATE_FLY);
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
		//Reload();
		break;
	case DIK_A:
		if (mario->GetLevel() == MARIO_LEVEL_RACCOON && mario->GetState() != MARIO_STATE_TAIL_ATTACK && mario->heldKoopa == nullptr)
		{
			mario->SetState(MARIO_STATE_TAIL_ATTACK);
			break;
		}
		if (mario->heldKoopa == nullptr)
		{
			// Check for nearby Koopa shells to pick up
			vector<LPGAMEOBJECT>* objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetObjects();
			for (size_t i = 0; i < objects->size(); i++)
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(objects->at(i));
				if (koopa != nullptr && (koopa->GetState() == KOOPA_STATE_SHELL || koopa->GetState() == KOOPA_STATE_RED_SHELL))
				{
					float marioX, marioY, koopaX, koopaY;
					mario->GetPosition(marioX, marioY);
					koopa->GetPosition(koopaX, koopaY);

					// Check if Koopa shell is close enough to Mario
					if (abs(marioX - koopaX) < 16 && abs(marioY - koopaY) < 16)
					{
						mario->heldKoopa = koopa; // Mario picks up the shell
						mario->SetState(MARIO_STATE_HOLD_SHELL);
						break;
					}
				}
			}
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
		//if (mario->GetLevel() == MARIO_LEVEL_RACCOON && mario->GetState() != MARIO_STATE_TAIL_ATTACK && mario->heldKoopa == nullptr)
		//{
		//	mario->SetState(MARIO_STATE_TAIL_ATTACK);
		//	break;
		//}
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