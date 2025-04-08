#include "ColorBlock.h"

void CColorBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CColorBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}
