#include "Brick.h"
#include "Debris.h"
#include "Scene.h"
#include "Game.h"
#include "PlayScene.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

int CBrick::IsBreakable()
{
	if (this->aniID == 12000)
		return 1;
	else
		return 0;
}

void CBrick::Break()
{
	if (this->IsBreakable())
	{
		this->Delete();
		//Create 4 debris
		for (int i = 0; i < 4; i++) {
			float frag_vx = (i < 2 ? -1 : 1) * DEBRIS_SPEED_X;
			float frag_vy = (i % 2 == 0 ? -1 : 1) * DEBRIS_SPEED_Y;

			CDebris* frag = new CDebris(x, y, frag_vx, frag_vy);
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddEffect(frag);
		}
	}
}
