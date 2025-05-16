#include "Shadow.h"

void CShadow::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CShadow::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}