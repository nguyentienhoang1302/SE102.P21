#include "Cloud.h"

void CCloud::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CCloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}