#include "HUD.h"

void CHUD::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteID)->Draw(x, y);
	//RenderBoundingBox();
}

void CHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}