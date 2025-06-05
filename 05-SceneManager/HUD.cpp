#include "HUD.h"
#include "PlayScene.h"
#include "HUDManager.h"
#include "HUDNumber.h"

void CHUD::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteID)->Draw(x, y);
}

void CHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isInitUI)
	{
		this->InitUI();
	}
	else {
		UpdateElements(timer, CHUDManager::GetInstance()->timer);
		UpdateElements(coins, CHUDManager::GetInstance()->coins);
		UpdateElements(point, CHUDManager::GetInstance()->point);
		UpdateElements(lifes, CHUDManager::GetInstance()->lifes);

		//speed bar
		CPlayScene* p = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(p->GetPlayer());

		float vx = mario->Getvx();
		float absVx = abs(vx);

		int barCount = 0;
		if (absVx > MARIO_WALKING_SPEED)
		{
			barCount = static_cast<int>(((absVx - MARIO_WALKING_SPEED) / (MARIO_RUNNING_SPEED - MARIO_WALKING_SPEED)) * 6 + 1);
			barCount = min(barCount, 6);
		}
		else
		{
			barCount = 0;
		}

		for (int i = 0; i < 6; i++)
		{
			if (i < barCount)
				dynamic_cast<CHUDNumber*>(speedbars[i])->SetIdSprite(500200);
			else
				dynamic_cast<CHUDNumber*>(speedbars[i])->SetIdSprite(500202);
		}
		if (barCount >= 6 && (GetTickCount64() / 100) % 2 == 0)
		{
			dynamic_cast<CHUDNumber*>(pMeter)->SetIdSprite(500201); //P flashing effect
		}
		else
		{
			dynamic_cast<CHUDNumber*>(pMeter)->SetIdSprite(500204);
		}

		//display gift
		int collectedGift = CHUDManager::GetInstance()->collectedGift;
		if (collectedGift == 1)
		{
			dynamic_cast<CHUDNumber*>(gift)->SetIdSprite(500302);
		}
		else if (collectedGift == 2)
		{
			dynamic_cast<CHUDNumber*>(gift)->SetIdSprite(500303);
		}
		else if (collectedGift == 3)
		{
			dynamic_cast<CHUDNumber*>(gift)->SetIdSprite(500301);
		}

		this->SetPosition(x, y);
	}
	CGameObject::Update(dt, coObjects);
}

void CHUD::InitUI()
{
	isInitUI = true;
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* p = dynamic_cast<CPlayScene*>(s);
	for (int i = 0; i < 3; i++)
	{
		LPGAMEOBJECT num = new CHUDNumber(x, y);
		p->AddEffect(num);
		timer.push_back(num);
	}
	for (int i = 0; i < 2; i++)
	{
		LPGAMEOBJECT num = new CHUDNumber(x, y);
		p->AddEffect(num);
		coins.push_back(num);
	}
	for (int i = 0; i < 7; i++)
	{
		LPGAMEOBJECT num = new CHUDNumber(x, y);
		p->AddEffect(num);
		point.push_back(num);
	}
	for (int i = 0; i < 2; i++)
	{
		LPGAMEOBJECT num = new CHUDNumber(x, y);
		p->AddEffect(num);
		lifes.push_back(num);
	}
	for (int i = 0; i < 6; i++)
	{
		LPGAMEOBJECT bar = new CHUDNumber(x, y);
		p->AddEffect(bar);
		speedbars.push_back(bar);
	}

	pMeter = new CHUDNumber(x, y);
	dynamic_cast<CHUDNumber*>(pMeter)->SetIdSprite(500204);
	p->AddEffect(pMeter);

	gift = new CHUDNumber(x, y);
	dynamic_cast<CHUDNumber*>(gift)->SetIdSprite(500300);
	p->AddEffect(gift);
}

void CHUD::UpdateElements(vector<LPGAMEOBJECT>& elements, DWORD value)
{
	std::string valueStr = std::to_string(value);
	while (valueStr.length() < elements.size())
	{
		valueStr = "0" + valueStr;
	}

	int index = elements.size() - 1;
	for (int i = valueStr.length() - 1; i >= 0 && index >= 0; --i, --index)
	{
		int digit = valueStr[i] - '0';
		dynamic_cast<CHUDNumber*>(elements[index])->SetIdSprite(500100 + digit);
	}
}

void CHUD::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	if (timer.size() > 0)
	{
		for (int i = 0; i < timer.size(); i++)
		{
			timer[i]->SetPosition(x + i * 8 + 12, y - 4);
		}
	}
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->SetPosition(x + i * 8 + 20, y - 12);
	}
	for (int i = 0; i < point.size(); i++)
	{
		point[i]->SetPosition(x + i * 8 - 60, y - 4);
	}
	for (int i = 0; i < lifes.size(); i++)
	{
		lifes[i]->SetPosition(x + i * 8 - 84, y - 4);
	}
	for (int i = 0; i < speedbars.size(); i++)
	{
		speedbars[i]->SetPosition(x + i * 8 - 60, y - 12);
	}
	if (pMeter != nullptr)
	{
		pMeter->SetPosition(x + 6 * 8 - 60 + 4, y - 12);
	}
	if (gift != nullptr)
	{
		gift->SetPosition(x + 56, y - 8);
	}
}