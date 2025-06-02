#include "PSwitch.h"
#include "Brick.h"
#include "PlayScene.h"
#include "Coin.h"

void CPSwitch::Render()
{
	if (state == PSWITCH_STATE_IDLE)
	{
		CSprites* spirtes = CSprites::GetInstance();
		spirtes->Get(PSWITCH_ANI_IDLE)->Draw(x, y);
	}
	else
	{
		CSprites* spirtes = CSprites::GetInstance();
		spirtes->Get(PSWITCH_ANI_CLICKED)->Draw(x, y);
	}
	//RenderBoundingBox();
}

void CPSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PSWITCH_BBOX_WIDTH / 2;
	t = y - PSWITCH_BBOX_HEIGHT / 2;
	r = l + PSWITCH_BBOX_WIDTH;
	b = t + PSWITCH_BBOX_HEIGHT;
}

void CPSwitch::HandleClick()
{
    SetState(PSWITCH_STATE_CLICKED);
    canClick = false;

    vector<LPGAMEOBJECT>* objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetObjects();

    for (size_t i = 0; i < objects->size(); i++)
    {
        CBrick* brick = dynamic_cast<CBrick*>(objects->at(i));
        if (brick && brick->IsBreakable())
        {
            float x, y;
            brick->GetPosition(x, y);

            CCoin* coin = new CCoin(x, y, 0);
			coin->SetPosition(x, y);

            objects->at(i) = coin;

			brick->Delete();
        }
    }
}