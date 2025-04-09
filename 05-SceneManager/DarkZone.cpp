#include "DarkZone.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"


void CDarkZone::Render()
{
	if (this->length <= 0) return;
	if (this->height <= 0) return;
	float xx = x;
	float yy = y;

	CSprites* s = CSprites::GetInstance();

	for (int j = 0; j < this->height; j++)
	{
		s->Get(this->spriteIdBegin)->Draw(xx, yy);
		xx += this->cellWidth;
		for (int i = 1; i < this->length; i++)
		{
			s->Get(this->spriteIdMiddle)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		xx = x;
		yy -= this->cellHeight;
	}

	//RenderBoundingBox();
}

void CDarkZone::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}