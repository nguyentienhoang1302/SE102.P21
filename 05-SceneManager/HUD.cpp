#include "HUD.h"
#include "PlayScene.h"
#include "HUDManager.h"
#include "HUDNumber.h"

void CHUD::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteID)->Draw(x, y);
	//// P flashing effect when max speed
	//CPlayScene* p = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	//CMario* mario = dynamic_cast<CMario*>(p->GetPlayer());
	//float vx = mario->Getvx();
	//float absVx = abs(vx);
	//int barCount = (int)((absVx / MARIO_RUNNING_SPEED) * 6);
	//if (barCount >= 6)
	//{
	//	// Flash: only render on even frames (adjust as needed)
	//	if ((GetTickCount64() / 100) % 2 == 0)
	//	{
	//		pMeter->Render();
	//	}
	//}
	//RenderBoundingBox();
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
	}
	
	CPlayScene* p = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = dynamic_cast<CMario*>(p->GetPlayer());

	float vx = mario->Getvx();
	float absVx = abs(vx);

	int barCount = (int)((absVx / MARIO_RUNNING_SPEED) * 6);
	barCount = min(barCount, 6);

	for (int i = 0; i < 6; i++)
	{
		if (i < barCount)
			dynamic_cast<CHUDNumber*>(speedbars[i])->SetIdSprite(500200);
		else
			dynamic_cast<CHUDNumber*>(speedbars[i])->SetIdSprite(500202);
	}

	if (barCount >= 6 && (GetTickCount64() / 100) % 2 == 0)
	{
		dynamic_cast<CHUDNumber*>(pMeter)->SetIdSprite(500201);
	}
	else
	{
		dynamic_cast<CHUDNumber*>(pMeter)->SetIdSprite(500204);
	}

	this->SetPosition(x, y);
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
}