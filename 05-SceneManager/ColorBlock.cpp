#include "ColorBlock.h"

void CColorBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CColorBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COLORBLOCK_BBOX_WIDTH / 2;
	t = y - COLORBLOCK_BBOX_HEIGHT / 2;
	r = l + COLORBLOCK_BBOX_WIDTH;
	b = t + COLORBLOCK_BBOX_HEIGHT;
}

int CColorBlock::IsDirectionColliable(float nx, float ny)
{
	if(this->aniID == 81001 || this->aniID == 81002 || this->aniID == 81003 || this->aniID == 82001 || this->aniID == 82002 || this->aniID == 82003 || this->aniID == 83001 || this->aniID == 83002 || this->aniID == 83003 || this->aniID == 84001 || this->aniID == 84002 || this->aniID == 84003)
		if (nx == 0 && ny == -1) return 1;
	else return 0;
}
