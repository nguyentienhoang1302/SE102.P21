#include "MysteryBlock.h"
#include "PlayScene.h"


CMBlock::CMBlock(float x, float y, int aniID, int content) : CGameObject(x, y) {
	this->aniId = aniID;
	this->content = content;

	SetState(MBLOCK_STATE_DEFAULT);
	y0 = y;
}

void CMBlock::Render()
{
	int aniID = ID_ANI_MBLOCK;
	if (state == MBLOCK_STATE_EMPTY)
	{
		aniID = ID_ANI_MBLOCK_EMPTY;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MBLOCK_BBOX_WIDTH / 2;
	t = y - MBLOCK_BBOX_HEIGHT / 2;
	r = l + MBLOCK_BBOX_WIDTH;
	b = t + MBLOCK_BBOX_HEIGHT;
}

int CMBlock::getContent()
{
	return this->content;
}

void CMBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MBLOCK_STATE_DEFAULT:
		break;
	case MBLOCK_STATE_EMPTY:
		empty_start = GetTickCount64();
		CreateSubObject = true;
		break;
	}
}

void CMBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (content == 1) {
		subObject = new CCoin(x, y, 1);
		subObject->SetPosition(x, y - 16);
	}
	else if (content == 2) {
		subObject = new CMushroom(x, y, 1);
	}
	else if (content == 3) {
		if (CGame::GetInstance()->GetCurrentScene()->MLevel == MARIO_LEVEL_SMALL)
		{
			subObject = new CMushroom(x, y, 1);
		}
		else if (CGame::GetInstance()->GetCurrentScene()->MLevel == MARIO_LEVEL_BIG)
		{
			subObject = new CLeaf(x, y);
			subObject->SetPosition(x, y - 16);
		}
		else if (CGame::GetInstance()->GetCurrentScene()->MLevel == MARIO_LEVEL_RACCOON)
		{
			subObject = new CLeaf(x, y);
			subObject->SetPosition(x, y - 16);
		}
	}
	else if (content == 4) {
		subObject = new CMushroom(x, y, 2);
		subObject->SetPosition(x, y - 16);
	}
	else if (content == 5)
	{
		subObject = new CPSwitch(x, y);
		//subObject = new CMushroom(x, y, 2);
		subObject->SetPosition(x, y - 16);
	}

	if (state == MBLOCK_STATE_EMPTY) {
		y += vy * dt;
		if (GetTickCount64() - empty_start < 70) {
			vy = -0.1f;
		}
		else if (y < y0) {
			vy = 0.1f;
		}
		else {
			y = y0;
			vy = 0;
			aniId = ID_ANI_MBLOCK_EMPTY;
		}
	}
}