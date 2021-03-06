#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Tiles.h"
#include "LevelManager.h"
#include "ModuleBoxes.h"
#include "ModuleInput.h"
#include "Boxes.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWindow.h"
#include "WindowSize.h"
#include "MusicManager.h"

#include "SDL/include/SDL.h"

#include <stdio.h>


SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

bool SceneLevel1::Start()
{
	w = App->window->screenSurface->w;

	LOG("Loading background assets");
	bool ret = true;
	UItexture = App->textures->Load("Assets/Textures/spritesheet_menus.png");
	UItextureIn = UItexture;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->boxes->Enable();
	App->collisions->Enable();
	//App->audio->Enable();
	
	App->lvlManage->changeScene = true;
	

	char tilesetTable[] = { "WwobCcB" };
	lvl1_map = App->tiles->Load("Assets/Textures/spritesheet_tiles.png", tilesetTable, 1);

	
	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	scoreFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);

	zoomUI = 5;
	zoomWL = 5;

	lvl = App->lvlManage->Getlvl();
	App->lvlManage->boxes_lvl = 0;
	App->lvlManage->steps = 0;
	App->lvlManage->playEffect = true;
	App->lvlManage->firstCaption = true;

	pause = false;
	noUI = false;
	StopPad_Y = false;
	lastTime_Y = currentTime;
	lastTime_Start = currentTime;
	StopPad_Start = false;
	StopPad_W = false;
	lastTime_W = SDL_GetTicks();
	switch (lvl) {
	case 1:
		zoom = 5;
		break;
	case 2:
		zoom = 4;
		break;
	case 3:
		zoom = 3;
		break;
	case 4:
		zoom = 3;
		break;
	case 5:
		zoom = 3;
		break;
	case 6:
		zoom = 3;
		break;
	default:
		zoom = 1;
		break;
	}
	
	//UItexture = { 1, 230, 60, 36 };

	colliderUI = App->collisions->AddCollider({ (App->winSize->w - UIrectIn.w * zoomUI - 30 * zoomUI + 1 * zoomUI) , 22 * zoomUI,UIrect.w * zoomUI, UIrect.h* zoomUI }, Collider::Type::UI, this);
	positionUI = { (App->winSize->w - UIrect.w * zoomUI - 30 * zoomUI),22 * zoomUI };

	switch (lvl) {

		case 1:
			App->tiles->genObjects(-zoom + (App->winSize->w - 21 * 24 * zoom) / 2, -zoom + (App->winSize->h - 12 * 24 * zoom) / 2, lvl1_map, "ooooooooooooooooooooo,ooooooooooooooooooooo,oooooooWwwwwwWooooooo,oooooooWbbBBBWooooooo,oooooooWbbbwwwWoooooo,ooooooWwwCbbbbWoooooo,ooooooWbbbWCwbWoooooo,ooooooWbCbWbbbWoooooo,ooooooWbbbWwwwwoooooo,oooooowwwwwoooooooooo,ooooooooooooooooooooo,ooooooooooooooooooooo", zoom);
			
			//lvlmusic = ("Assets / Audio / Music / stage1.ogg");
			//App->musicManage->playMusic("Assets/Audio/Music/stage1.ogg",0);
			App->audio->PlayMusic("Assets/Audio/Music/stage1.ogg",0);
			App->lvlManage->max_steps = 90;
			sprintf_s(stageText, 3, "%02d", 1);
			break;
		case 2:
			App->tiles->genObjects(-zoom + (App->winSize->w - 21 * 24 * zoom) / 2, -zoom + (App->winSize->h - 13 * 24 * zoom) / 2, lvl1_map, "ooooooooooooooooooooo,ooooooooooooooooooooo,ooooooWwwwwwwWooooooo,ooooooWbbbbbbWooooooo,ooooooWbwCCbbWooooooo,ooooooWbBBBwbWooooooo,oooooowWBBBCbwWoooooo,oooooooWbwwbCbWoooooo,oooooooWCbbCbbWoooooo,oooooooWbbWbbbWoooooo,ooooooowwwwwwwwoooooo,ooooooooooooooooooooo,ooooooooooooooooooooo,ooooooooooooooooooooo", zoom);
			App->audio->PlayMusic("Assets/Audio/Music/stage2.ogg", 0);
			App->lvlManage->max_steps = 120;
			sprintf_s(stageText, 3, "%02d", 10);
			break;
		case 3:
			//App->tiles->genObjects(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,ooooooooooooWwwwwwWooooooooooooo,ooooooooooooWbbBBBWooooooooooooo,ooooooooooooWbbbwwwWoooooooooooo,oooooooooooWwwCbbbbWoooooooooooo,oooooooooooWbbbWCwbWoooooooooooo,oooooooooooWbCbWbbbWoooooooooooo,oooooooooooWbbbWwwwwoooooooooooo,ooooooooooowwwwwoooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
			App->tiles->genObjects(-zoom + (App->winSize->w - 34 * 24 * zoom) / 2, -zoom + (App->winSize->h - 18 * 24 * zoom) / 2, lvl1_map, "oooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooooo,oooooooooooWwWwwWoWwwwWooooooooooo,ooooooooooWwbwbbwwWbbbwWoooooooooo,ooooooooooWbbbbCbbwbCbbWoooooooooo,ooooooooooWbbCbbWbbbbCbWoooooooooo,ooooooooooWWWbWWwwWWbbbWoooooooooo,ooooooooooWwwbwWbbWwCwWwoooooooooo,ooooooooooWbCbbwwwwbBBWooooooooooo,ooooooooooWbCbCbCbbBBBWooooooooooo,ooooooooooWbbbbWwwWBBBWooooooooooo,ooooooooooWbCCbWooWBBBWooooooooooo,ooooooooooWbbWwwoowwwwwooooooooooo,oooooooooowwwwoooooooooooooooooooo,oooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooooo", zoom);
			App->audio->PlayMusic("Assets/Audio/Music/stage2.ogg", 0);
			App->lvlManage->max_steps = 750;
			sprintf_s(stageText, 3, "%02d", 22);
			break;
		case 4:
			App->tiles->genObjects(-zoom + (App->winSize->w - 33 * 24 * zoom) / 2, -zoom + (App->winSize->h - 25 * 24 * zoom) / 2, lvl1_map, "ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooWwwwWooooooooooooo,oooooooooooooooWbbbWWwwWooooooooo,oooooooooooooooWbwCwwbbWooooooooo,oooooooooooooooWbbbbCbbWooooooooo,oooooooWwwwwwwWWbwwwbbbWooooooooo,oooooooWBBBBbbwwbCbbCWWwooooooooo,oooooooWBBBBbbbbCbCCbwWoooooooooo,oooooooWBBBBbbWWCbbCbbWoooooooooo,ooooooowwwwwwwwWbbCbbwWoooooooooo,oooooooooooooooWbCbCbbWoooooooooo,ooooooooooooooowwWbwwbWoooooooooo,oooooooooooooooooWbbbbWoooooooooo,ooooooooooooooooowwwwwwoooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo", zoom);
			App->audio->PlayMusic("Assets/Audio/Music/stage1.ogg", 0);
			App->lvlManage->max_steps = 700;
			sprintf_s(stageText, 3, "%02d", 23);
			break;
		case 5:
			App->tiles->genObjects(-zoom + (App->winSize->w - 32 * 24 * zoom) / 2, -zoom + (App->winSize->h - 21 * 24 * zoom) / 2, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooWwwWwwwWooooooooooo,ooooooooooWwwWbbwBBBWooooooooooo,ooooooooooWbbwCbbBBBwwwwWooooooo,oooooooWwwwbCbbbWWBBBBbbWooooooo,oooooooWbbbCCwCbWWBBBBbbWooooooo,oooooooWbCbbbbbWWWWwwwbWwooooooo,oooooooWbwWwbCWwWwwbbCbWoooooooo,oooooooWbbWbCbwbwbbbCbbWoooooooo,ooooooowWbwbbbbCbbCCbWwwoooooooo,ooooooooWbbbwbCbwbbWwwoooooooooo,oooooooowwWbbwwbbWwwoooooooooooo,oooooooooowWbbbbbWoooooooooooooo,ooooooooooowwwwwwwoooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
			App->audio->PlayMusic("Assets/Audio/Music/stage2.ogg", 0);
			App->lvlManage->max_steps = 1400;
			sprintf_s(stageText, 3, "%02d", 44);
			break;
		case 6:
			//App->tiles->genObjects(-2, -2, lvl1_map, "oooooooooooooooo,oWwwwWWwwwwwwwWoo,oWbbbWWbBBBBBBWo,oWbbWwwbBBWBwbWo,oWbCWbbBBWwBbBWo,oWwbwbCwbwbbbbWo,oWbCbbCbbbbWbwWo,oWbCWbWbCwwWCbWo,oWbbWbWbCbbWbbWo,oWbCwbwWCwbwCbWo,oWbCbbbWbbbbbbWo,owwWbbbWbwwCbWwo,ooowwwwWbbbbbWoo,ooooooowwwwwwwoo,oooooooooooooooo", zoom);
			App->tiles->genObjects(-zoom + (App->winSize->w - 32 * 24 * zoom) / 2, -zoom + (App->winSize->h - 21 * 24 * zoom) / 2, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooWwwwWWwwwwwwwWooooooooo,oooooooooWbbbWWbBBBBBBWooooooooo,oooooooooWbbWwwbBBWBwbWooooooooo,oooooooooWbCWbbBBWwBbBWooooooooo,oooooooooWwbwbCwbwbbbbWooooooooo,oooooooooWbCbbCbbbbWbwWooooooooo,oooooooooWbCWbWbCwwWCbWooooooooo,oooooooooWbbWbWbCbbWbbWooooooooo,oooooooooWbCwbwWCwbwCbWooooooooo,oooooooooWbCbbbWbbbbbbWooooooooo,ooooooooowwWbbbWbwwCbWwooooooooo,ooooooooooowwwwWbbbbbWoooooooooo,ooooooooooooooowwwwwwwoooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
			App->audio->PlayMusic("Assets/Audio/Music/stage1.ogg", 0);
			App->lvlManage->max_steps = 600;
			sprintf_s(stageText, 3, "%02d", 50);
			break;
		
		default:
			break;
		}

	
	sprintf_s(limitText, 5, "%04d", App->lvlManage->max_steps);

	nextlvl = true;

	App->lvlManage->win = 0;
	
	return ret;
}

Update_Status SceneLevel1::Update()
{
	GamePad& pad = App->input->pads[0];
	//POR CADA ELEMENTO, +1 EN W
	//POR CADA STRING, +1 EN H
	switch (lvl) {
	case 1:
		//App->tiles->BlitScene(-3 - 12, -3 - 24, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwCbbbbWo,oWbbbWCwbWo,oWbCbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo", zoom);
		App->tiles->BlitScene(-zoom +( App->winSize->w - 21*24*zoom)/2, -zoom + (App->winSize->h - 12 * 24 * zoom) / 2, lvl1_map, "ooooooooooooooooooooo,ooooooooooooooooooooo,oooooooWwwwwwWooooooo,oooooooWbbBBBWooooooo,oooooooWbbbwwwWoooooo,ooooooWwwCbbbbWoooooo,ooooooWbbbWCwbWoooooo,ooooooWbCbWbbbWoooooo,ooooooWbbbWwwwwoooooo,oooooowwwwwoooooooooo,ooooooooooooooooooooo,ooooooooooooooooooooo", zoom);
		//App->lvlManage->max_steps = 750;
		//App->lvlManage->max_steps = 700;
		break;
	case 2:
		App->tiles->BlitScene(-zoom + (App->winSize->w - 21 * 24 * zoom) / 2, -zoom + (App->winSize->h - 13 * 24 * zoom) / 2, lvl1_map, "ooooooooooooooooooooo,ooooooooooooooooooooo,ooooooWwwwwwwWooooooo,ooooooWbbbbbbWooooooo,ooooooWbwCCbbWooooooo,ooooooWbBBBwbWooooooo,oooooowWBBBCbwWoooooo,oooooooWbwwbCbWoooooo,oooooooWCbbCbbWoooooo,oooooooWbbWbbbWoooooo,ooooooowwwwwwwwoooooo,ooooooooooooooooooooo,ooooooooooooooooooooo,ooooooooooooooooooooo", zoom);
		break;
	case 3:
		//App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,ooooooooooooWwwwwwWooooooooooooo,ooooooooooooWbbBBBWooooooooooooo,ooooooooooooWbbbwwwWoooooooooooo,oooooooooooWwwCbbbbWoooooooooooo,oooooooooooWbbbWCwbWoooooooooooo,oooooooooooWbCbWbbbWoooooooooooo,oooooooooooWbbbWwwwwoooooooooooo,ooooooooooowwwwwoooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		App->tiles->BlitScene(-zoom + (App->winSize->w - 34 * 24 * zoom) / 2, -zoom + (App->winSize->h - 18 * 24 * zoom) / 2, lvl1_map, "oooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooooo,oooooooooooWwWwwWoWwwwWooooooooooo,ooooooooooWwbwbbwwWbbbwWoooooooooo,ooooooooooWbbbbCbbwbCbbWoooooooooo,ooooooooooWbbCbbWbbbbCbWoooooooooo,ooooooooooWWWbWWwwWWbbbWoooooooooo,ooooooooooWwwbwWbbWwCwWwoooooooooo,ooooooooooWbCbbwwwwbBBWooooooooooo,ooooooooooWbCbCbCbbBBBWooooooooooo,ooooooooooWbbbbWwwWBBBWooooooooooo,ooooooooooWbCCbWooWBBBWooooooooooo,ooooooooooWbbWwwoowwwwwooooooooooo,oooooooooowwwwoooooooooooooooooooo,oooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooooo", zoom);
		break;
	case 4:
		App->tiles->BlitScene(-zoom + (App->winSize->w - 33 * 24 * zoom) / 2, -zoom + (App->winSize->h - 21 * 24 * zoom) / 2, lvl1_map, "ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooWwwwWooooooooooooo,oooooooooooooooWbbbWWwwWooooooooo,oooooooooooooooWbwCwwbbWooooooooo,oooooooooooooooWbbbbCbbWooooooooo,oooooooWwwwwwwWWbwwwbbbWooooooooo,oooooooWBBBBbbwwbCbbCWWwooooooooo,oooooooWBBBBbbbbCbCCbwWoooooooooo,oooooooWBBBBbbWWCbbCbbWoooooooooo,ooooooowwwwwwwwWbbCbbwWoooooooooo,oooooooooooooooWbCbCbbWoooooooooo,ooooooooooooooowwWbwwbWoooooooooo,oooooooooooooooooWbbbbWoooooooooo,ooooooooooooooooowwwwwwoooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo", zoom);
		break;
	case 5:
		App->tiles->BlitScene(-zoom + (App->winSize->w - 32 * 24 * zoom) / 2, -zoom + (App->winSize->h - 21 * 24 * zoom) / 2, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooWwwWwwwWooooooooooo,ooooooooooWwwWbbwBBBWooooooooooo,ooooooooooWbbwCbbBBBwwwwWooooooo,oooooooWwwwbCbbbWWBBBBbbWooooooo,oooooooWbbbCCwCbWWBBBBbbWooooooo,oooooooWbCbbbbbWWWWwwwbWwooooooo,oooooooWbwWwbCWwWwwbbCbWoooooooo,oooooooWbbWbCbwbwbbbCbbWoooooooo,ooooooowWbwbbbbCbbCCbWwwoooooooo,ooooooooWbbbwbCbwbbWwwoooooooooo,oooooooowwWbbwwbbWwwoooooooooooo,oooooooooowWbbbbbWoooooooooooooo,ooooooooooowwwwwwwoooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		break;
	case 6:
		//App->tiles->BlitScene(-2, -2, lvl1_map, "oooooooooooooooo,oWwwwWWwwwwwwwWoo,oWbbbWWbBBBBBBWo,oWbbWwwbBBWBwbWo,oWbCWbbBBWwBbBWo,oWwbwbCwbwbbbbWo,oWbCbbCbbbbWbwWo,oWbCWbWbCwwWCbWo,oWbbWbWbCbbWbbWo,oWbCwbwWCwbwCbWo,oWbCbbbWbbbbbbWo,owwWbbbWbwwCbWwo,ooowwwwWbbbbbWoo,ooooooowwwwwwwoo,oooooooooooooooo", zoom);
		App->tiles->BlitScene(-zoom + (App->winSize->w - 32 * 24 * zoom) / 2, -zoom + (App->winSize->h - 21 * 24 * zoom) / 2, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooWwwwWWwwwwwwwWooooooooo,oooooooooWbbbWWbBBBBBBWooooooooo,oooooooooWbbWwwbBBWBwbWooooooooo,oooooooooWbCWbbBBWwBbBWooooooooo,oooooooooWwbwbCwbwbbbbWooooooooo,oooooooooWbCbbCbbbbWbwWooooooooo,oooooooooWbCWbWbCwwWCbWooooooooo,oooooooooWbbWbWbCbbWbbWooooooooo,oooooooooWbCwbwWCwbwCbWooooooooo,oooooooooWbCbbbWbbbbbbWooooooooo,ooooooooowwWbbbWbwwCbWwooooooooo,ooooooooooowwwwWbbbbbWoooooooooo,ooooooooooooooowwwwwwwoooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		break;
	
	default:
		break;

}

	w = App->window->screenSurface->w;

	if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN || (pad.y == KEY_DOWN)) {
		
			if (currentTime >= lastTime_Y + 200) {
				if (App->lvlManage->win == 0) {



					lastTime_Y = currentTime;
					

					if (pause == false) {
						if (noUI == false) {
							noUI = true;
						}
						else {
							noUI = false;
						}
					}
					StopPad_Y = true;
				}
			}
		
	}

	if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN || (pad.start == KEY_DOWN)) {
		App->audio->PlayFx(App->lvlManage->indexEffects[2],0);
		if (currentTime >= lastTime_Start + 200) {
			if (App->lvlManage->win == 0) {
				if (pause == false) {
					pause = true;
					pauseIndex = 0;

					
				}
				else {
					pause = false;
				}
				lastTime_Start = currentTime;
				StopPad_Start = true;
			}
		}
	}
	currentTime = SDL_GetTicks();
	if (pause == true) {
		
	if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN))
	{
		if (pause == true) {
			firstInput_W = true;
		}
		
	}

	if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT))
	{
		if (firstInput_W == true) {
			if (pauseIndex > 0) {
				App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				pauseIndex -= 1;
			}
			else {
				App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				pauseIndex = 2;
			}
			lastTime_W = SDL_GetTicks();
			delay_W = 500;
			firstInput_W = false;
		}
		else if (currentTime > lastTime_W + delay_W) {
			if (pauseIndex > 0) {
				if (currentTime >= lastTimePunt + delayPunt) {
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;
				}
				pauseIndex -= 1;
			}
			else {
				if (currentTime >= lastTimePunt + delayPunt) {
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;
				}
				pauseIndex = 2;
			}
			lastTime_W = SDL_GetTicks();
			delay_W = 150;
			lastTime_W = currentTime;




		}

	}

	if ((pad.up == KEY_DOWN) && (pad.left_y < 0.0f))
	{
		if (pause == true) {
			if (PauseTest == false) {
				StopPad_W = false;
				PauseTest = true;
			}
		}

	}
	if ((pad.up == 0) && (pad.left_y == 0.0f)) {
		PauseTest = false;
		StopPad_W = false;
	}
	if (PauseTest == false) {
		if ((pad.up == KEY_DOWN) || (pad.left_y < 0.0f))
		{
			if (StopPad_W == false) {
				if (pauseIndex > 0) {
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					pauseIndex -= 1;
				}
				else {
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					pauseIndex = 2;
				}
				lastTime_W = currentTime + 500;
				delay_W = 50;
				StopPad_W = true;
			}
			else if (currentTime > lastTime_W + delay_W) {
				delay_W = 50;
				if (pauseIndex > 0) {
					if (currentTime >= lastTimePunt + delayPunt) {
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					}
					pauseIndex -= 1;
				}
				else {
					if (currentTime >= lastTimePunt + delayPunt) {
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					}
					pauseIndex = 2;
				}
				lastTime_W = SDL_GetTicks();
				delay_W = 150;
				lastTime_W = currentTime;




			}

		}
	}
	
		if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			firstInput_S = true;
		}
		if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_S == true) {

				if (pauseIndex < 2) {
					pauseIndex += 1;
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				}
				else {
					pauseIndex = 0;
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				}

				lastTime_S = SDL_GetTicks();
				delay_S = 500;
				firstInput_S = false;
			}
			else if (currentTime > lastTime_S + delay_S) {
				if (pauseIndex < 2) {
					pauseIndex += 1;
					if (currentTime >= lastTimePunt + delayPunt) {
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					}
				}
				else {
					pauseIndex = 0;
					if (currentTime >= lastTimePunt + delayPunt) {
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					}
				}
				lastTime_S = SDL_GetTicks();
				delay_S = 150;
				lastTime_S = currentTime;

			}

		}

		if ((pad.down == KEY_DOWN) && (pad.left_y > 0.0f))
		{
			if (pause == true) {
				if (PauseTest2 == false) {
					StopPad_S = false;
					PauseTest2 = true;
				}
			}
		}

		if ((pad.down == 0) && (pad.left_y == 0.0f)) {
			PauseTest2 = false;
			StopPad_S = false;
		}
		if (PauseTest2 == false) {
			if ((pad.down == KEY_DOWN) || (pad.left_y > 0.0f))
			{
				if (StopPad_S == false) {

					if (pauseIndex < 2) {
						pauseIndex += 1;
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					}
					else {
						pauseIndex = 0;
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					}

					lastTime_S = currentTime + 500;
					delay_S = 50;
					StopPad_S = true;
				}
				else if (currentTime > lastTime_S + delay_S) {
					delay_S = 50;
					if (pauseIndex < 2) {
						pauseIndex += 1;
						if (currentTime >= lastTimePunt + delayPunt) {
							App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
							lastTimePunt = currentTime;
						}
					}
					else {
						pauseIndex = 0;
						if (currentTime >= lastTimePunt + delayPunt) {
							App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
							lastTimePunt = currentTime;
						}
					}
					lastTime_S = SDL_GetTicks();
					delay_S = 150;
					lastTime_S = currentTime;

				}

			}
		}
	}

	colliderUI->SetPos(positionUI.x, positionUI.y);
	
	

	if (pause == true) {

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || (pad.a == KEY_DOWN)) {
			switch (pauseIndex) {
			case 0:
				App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
				pause = false;
				break;
			case 1:
				App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
				App->fade->FadeToBlack(this, (Module*)App->levelMenu, 30);
				App->lvlManage->lvlChange(0, '=');
				
				break;
			case 2:
				App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
				App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 30);
				
				break;
			}
		
		}
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::PostUpdate()
{
	
	if (noUI == false && pause == false) {

		SDL_SetTextureAlphaMod(UItexture, 125);
		App->render->Blit(UItextureIn, positionUI.x, positionUI.y, &UIrectIn, 0.0f, true, zoomUI);
		SDL_SetTextureAlphaMod(UItextureIn, 255);
		App->render->Blit(UItexture, positionUI.x, positionUI.y, &UIrect, 0.0f, true, zoomUI);


		App->fonts->BlitText(positionUI.x + 28 * zoomUI + 7 * 2 * zoomUI, positionUI.y + 3 * zoomUI, scoreFont, stageText, zoomUI, 222, 218, 222);

		sprintf_s(stepText, 5, "%04d", App->lvlManage->steps);
		App->fonts->BlitText(positionUI.x + 28 * zoomUI, positionUI.y + 15 * zoomUI, scoreFont, stepText, zoomUI, 222, 218, 222);

		App->fonts->BlitText(positionUI.x + 28 * zoomUI, positionUI.y + 24 * zoomUI, scoreFont, limitText, zoomUI, 222, 218, 222);

	}

	if (!App->player->destroyed)
	{
		rectplayer = App->player->currentAnimation->GetCurrentFrame();
		App->render->Blit(App->player->texture, App->player->position.x, App->player->position.y, &rectplayer, NULL, 1.0f, zoom);

	}

	if (App->lvlManage->win == 2) {
		
		App->render->Blit(UItexture, (App->winSize->w - rectlose.w*zoomWL) / 2, (App->winSize->h - rectlose.h * zoomWL)/2,&rectlose, 0.0f, true, zoomWL);
		App->fonts->BlitText((App->winSize->w - rectlose.w * zoomWL) / 2 + 6 * zoomWL, (App->winSize->h - rectlose.h * zoomWL) / 2 +17* zoomWL, scoreFont, "YOU LOSE!SPACE TO TRY AGAIN", zoomWL, 0, 32, 33, (App->winSize->w - rectlose.w * zoomWL) / 2 + rectlose.w * zoomWL - 45 * zoomWL, 3);
	
	}

	if (App->lvlManage->win == 1) {
		
		App->render->Blit(UItexture, (App->winSize->w - rectwin.w * zoomWL) / 2, (App->winSize->h - rectwin.h * zoomWL) / 2, &rectwin, 0.0f, true, zoomWL);
		App->fonts->BlitText((App->winSize->w - rectlose.w * zoomWL) / 2 + 10 * zoomWL, (App->winSize->h - rectlose.h * zoomWL) / 2 + 17 * zoomWL, scoreFont, " YOU WIN!SPACE TO  CONFIRM", zoomWL, 0, 32, 33, (App->winSize->w - rectlose.w * zoomWL) / 2 + rectlose.w * zoomWL - 45 * zoomWL, 3);
		App->render->Blit(UItexture, (App->winSize->w - rectNextRepeat.w * zoomWL) / 2, (App->winSize->h) / 2 + 44 * zoomWL, &rectNextRepeat, 0.0f, true, zoomWL);
		App->fonts->BlitText((App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + 4 * zoomWL, (App->winSize->h) / 2 + 44 * zoomWL + 5 * zoomWL, scoreFont, " GO TO NEXT LEVEL?", 3, 0, 0, 0, (App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + rectNextRepeat.w * zoomWL - 5 * zoomWL);
		if (nextlvl==true) {
			App->fonts->BlitText((App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + 15 * zoomWL, (App->winSize->h) / 2 + 44 * zoomWL + 15 * zoomWL, scoreFont, "YES", zoomWL,214, 0, 0, (App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + rectNextRepeat.w * 3 - 5 * zoomWL);
			App->fonts->BlitText((App->winSize->w + 3 * zoomWL) / 2 + 10 * zoomWL, (App->winSize->h) / 2 + 44 * zoomWL + 15 * zoomWL, scoreFont, "NO", zoomWL, 16, 16, 24, (App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + rectNextRepeat.w * zoomWL - 5 * zoomWL);
		}
		else {
			App->fonts->BlitText((App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + 15 * zoomWL, (App->winSize->h) / 2 + 44 * zoomWL + 15 * zoomWL, scoreFont, "YES", zoomWL, 16, 16, 24, (App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + rectNextRepeat.w * zoomWL - 5 * zoomWL);
			App->fonts->BlitText((App->winSize->w + 3 * zoomWL) / 2 + 10 * zoomWL, (App->winSize->h) / 2 + 44 * zoomWL + 15 * zoomWL, scoreFont, "NO", zoomWL, 214, 0, 0, (App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + rectNextRepeat.w * zoomWL - 5 * zoomWL);
		}
		
		App->fonts->BlitText((App->winSize->w - 4* zoomWL) /2, (App->winSize->h) / 2 + 44 * zoomWL + 15 * zoomWL, scoreFont, "/", zoomWL, 16, 16, 24, (App->winSize->w - rectNextRepeat.w * zoomWL) / 2 + rectNextRepeat.w * zoomWL - 5 * zoomWL);

		
	}

	if (pause == true) {
		App->render->Blit(UItexture, (App->winSize->w - rectPause.w * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2, &rectPause, 0.0f, true, zoomUI);
		App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 7 * zoomUI) / 2 + 60* zoomUI, (App->winSize->h - rectPause.h * zoomUI) / 2 + 5* zoomUI, scoreFont, stageText, zoomUI, 33, 0, 255);

		switch (pauseIndex) {
		case 0:
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI)/2 + 21 * zoomUI, scoreFont, "RESUME", zoomUI, 214, 0, 0, App->winSize->w, 3);
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2 + 21 * zoomUI, scoreFont, "|GO TO MENU", zoomUI, 16, 16, 24, App->winSize->w, 3);
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2 + 21 * zoomUI, scoreFont, "||GO TO TITLE", zoomUI, 16, 16, 24, App->winSize->w, 3);
			break;
		case 1:
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2 + 21 * zoomUI, scoreFont, "RESUME", zoomUI, 16, 16, 24, App->winSize->w, 3);
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2 + 21 * zoomUI, scoreFont, "|GO TO MENU", zoomUI, 214, 0, 0, App->winSize->w, 3);
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2 + 21 * zoomUI, scoreFont, "||GO TO TITLE", zoomUI, 16, 16, 24, App->winSize->w, 3);
			break;
		case 2:
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2 + 21 * zoomUI, scoreFont, "RESUME", zoomUI, 16, 16, 24, App->winSize->w, 3);
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2 + 21 * zoomUI, scoreFont, "|GO TO MENU", zoomUI, 16, 16, 24, App->winSize->w, 3);
			App->fonts->BlitText((App->winSize->w - rectPause.w * zoomUI + 10 * zoomUI) / 2, (App->winSize->h - rectPause.h * zoomUI) / 2 + 21 * zoomUI, scoreFont, "||GO TO TITLE", zoomUI, 214, 0, 0, App->winSize->w, 3);
			break;
		}
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

void SceneLevel1::OnCollision(Collider* c1, Collider* c2)
{

	if (c1->type == Collider::Type::UI && c2->type == Collider::Type::PLAYER) {
		if (positionUI.x == 22 * zoomUI && positionUI.y == 22 * zoomUI) {
			positionUI = { (App->winSize->w - UIrect.w * zoomUI - 30 * zoomUI), 22 * zoomUI };
		}
		else {
			positionUI = { 22 * zoomUI, 22 * zoomUI };
		}
	}
}

bool SceneLevel1::CleanUp()
{
	pause = false;
	App->collisions->RemoveCollider(colliderUI);
	App->player->Disable();
	App->collisions->Disable();
	App->tiles->UnLoad(0);
	App->fonts->UnLoad(0);
	App->boxes->Disable();
	App->textures->Unload(UItexture);
	App->textures->Unload(UItextureIn);
	return true;
}

