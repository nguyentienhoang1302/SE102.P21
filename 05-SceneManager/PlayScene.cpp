#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Tree.h"
#include "Cloud.h"
#include "ColorBlock.h"
#include "Pipe.h"
#include "MysteryBlock.h"
#include "DarkZone.h"
#include "PiranhaPlant.h"
#include "Fireball.h"
#include "Koopa.h"
#include "Leaf.h"
#include "Shadow.h"
#include "HUD.h"
#include "Point.h"
#include "PSwitch.h"
#include "GiftBox.h"
#include "GiftSelect.h"

#include "SampleKeyEventHandler.h"
#include "HUDManager.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		// Get Mario level in case of switching from another scene, default level is small
		int savedLevel = CGame::GetInstance()->GetSavedMarioLevel();
		obj = new CMario(x, y);
		((CMario*)obj)->SetLevel(savedLevel);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA:
	{
		int type = (int)atoi(tokens[3].c_str());
		obj = new CGoomba(x, y, type);
		break;
	}
	case OBJECT_TYPE_BRICK:
	{
		int aniId = (int)atoi(tokens[3].c_str());
		obj = new CBrick(x, y, aniId);
		break;
	}
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y, 0); break;

	case OBJECT_TYPE_TREE:
	{
		int aniId = (int)atoi(tokens[3].c_str());
		obj = new CTree(x, y, aniId);
		break;
	}

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_CLOUD:
	{
		int aniId = (int)atoi(tokens[3].c_str());
		obj = new CCloud(x, y, aniId);
		break;
	}

	case OBJECT_TYPE_COLORBLOCK:
	{
		int aniId = (int)atoi(tokens[3].c_str());
		obj = new CColorBlock(x, y, aniId);
		break;
	}

	case OBJECT_TYPE_PIPE:
	{
		int aniId = (int)atoi(tokens[3].c_str());
		obj = new CPipe(x, y, aniId);
		break;
	}

	case OBJECT_TYPE_MBLOCK:
	{
		int content = (int)atoi(tokens[4].c_str());
		int aniId = (int)atoi(tokens[3].c_str());
		obj = new CMBlock(x, y, aniId, content);
		break;
	}

	case OBJECT_TYPE_DARKZONE:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int sprite_begin = atoi(tokens[7].c_str());
		int sprite_middle = atoi(tokens[8].c_str());
		int sprite_end = atoi(tokens[9].c_str());

		obj = new CDarkZone(
			x, y,
			cell_width, cell_height, length, height,
			sprite_begin, sprite_middle, sprite_end
		);
		break;
	}

	case OBJECT_TYPE_PIRANHAPLANT:
	{
		int type = (int)atoi(tokens[3].c_str());
		obj = new CPPlant(x, y, type);
		break;
	}

	case OBJECT_TYPE_FIREBALL:
	{
		int direction = (int)atoi(tokens[3].c_str());
		obj = new CFireball(x, y, direction);
		break;
	}

	case OBJECT_TYPE_KOOPA:
	{
		int type = (int)atoi(tokens[3].c_str());
		obj = new CKoopa(x, y, type);
		break;
	}

	case OBJECT_TYPE_LEAF: obj = new CLeaf(x, y); break;

	case OBJECT_TYPE_SHADOW:
	{
		int aniId = (int)atoi(tokens[3].c_str());
		obj = new CShadow(x, y, aniId);
		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;

	case OBJECT_TYPE_PSWITCH:
	{
		obj = new CPSwitch(x, y);
		break;
	}

	case OBJECT_TYPE_HUD:
	{
		int spriteId = (int)atoi(tokens[3].c_str());
		obj = new CHUD(x, y, spriteId);
		HUD = (CHUD*)obj;
		break;
	}

	case OBJECT_TYPE_POINT:
	{
		int point = atoi(tokens[3].c_str());
		obj = new CPoint(x, y, point);
		objects.push_back(obj);
		break;
	}

	case OBJECT_TYPE_GIFTBOX:
	{
		int aniId = (int)atoi(tokens[3].c_str());
		obj = new CGiftBox(x, y, aniId);
		break;
	}

	case OBJECT_TYPE_GIFTSELECT: obj = new CGiftSelect(x, y); break;

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}


	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	//pause game update when game over, ask if player wants to restart
	if (isGameOver)
	{
		int result = MessageBox(
			NULL,
			L"Game Over!\nDo you want to restart?",
			L"Game Over",
			MB_YESNO | MB_ICONQUESTION
		);

		if (result == IDYES) {
			CHUDManager::GetInstance()->lifes = 4;
			CHUDManager::GetInstance()->coins = 0;
			CHUDManager::GetInstance()->point = 0;
			CHUDManager::GetInstance()->timer = 300;
			isGameOver = false;
			CGame::GetInstance()->RequestReload();
		}
		else if (result == IDNO) {
			exit(0);
		}
		return;
	}

	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	//for (size_t i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->Update(dt, &coObjects);
	//}
	size_t i = 0;
	while (i < objects.size())
	{
		objects[i]->Update(dt, &coObjects);
		if (objects[i]->CreateSubObject) {
			CGameObject* obj = NULL;
			obj = objects[i]->subObject;
			objects.push_back(obj);
			Render();
			objects[i]->CreateSubObject = false;
		}
		i++;
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	
	// Limit camera movement in each stage
	if (CGame::GetInstance()->GetCurrentScene()->GetStageId() == 5)
	{
		if (cx < 0) cx = 0;
		if (cx > 2560) cx = 2560;
		if (cy > 0) cy = 0;
		if (cy < -208) cy = -208;
	}
	else if (CGame::GetInstance()->GetCurrentScene()->GetStageId() == 6)
	{
		if (cx < 0) cx = 0;
		if (cx > 504) cx = 504;
		cy = 0;
	}

	// Set HUD position after camera position
	if (HUD != NULL)
	{
		HUD->SetPosition(cx+120, cy + 227);
		HUD->Update(dt);
	}

	// Update HUD
	CHUDManager::GetInstance()->Update(dt, &objects);

	CGame::GetInstance()->SetCamPos(cx - 8, cy);

	PurgeDeletedObjects();

	// Check if reload is requested
	CGame::GetInstance()->ProcessReload();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		if (objects[i] != player)
			objects[i]->Render();
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->RenderPriority() == 1)
			objects[i]->Render();
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->RenderPriority() == 2)
			objects[i]->Render();
	if (player)
		player->Render();
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->RenderPriority() == 3)
			objects[i]->Render();
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->RenderPriority() == 4)
			objects[i]->Render();
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->RenderPriority() == 5)
			objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

void CPlayScene::AddEffect(LPGAMEOBJECT obj)
{
	objects.push_back(obj);
}