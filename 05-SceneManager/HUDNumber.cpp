#include "HUDNumber.h"

void CHUDNumber::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteID)->Draw(x, y);
	//RenderBoundingBox();
}

void CHUDNumber::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}

void CHUDNumber::SetIdSprite(int spriteId)
{
	this->spriteID = spriteId;
}
