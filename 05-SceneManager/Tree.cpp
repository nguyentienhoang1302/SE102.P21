#include "Tree.h"

void CTree::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}