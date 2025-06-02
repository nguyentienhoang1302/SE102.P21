#include "HUDManager.h"

CHUDManager* CHUDManager::__instance = NULL;

CHUDManager* CHUDManager::GetInstance()
{
	if (__instance == NULL) __instance = new CHUDManager(0, 0);
	return __instance;
}

void CHUDManager::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	elapsedTime += dt;
	if (elapsedTime >= 1000 && timer >= 0)
	{
		timer--;
		elapsedTime -= 1000;
	}
}
