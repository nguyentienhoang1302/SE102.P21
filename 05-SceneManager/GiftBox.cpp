#include "GiftBox.h"

void CGiftBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CGiftBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}