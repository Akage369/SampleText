#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Tiles.h"
#include "LevelManager.h"
#include "ModuleBoxes.h"
#include "ModuleInput.h"
#include "Boxes.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"

#include <stdio.h>


SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	UItexture = App->textures->Load("Assets/Textures/spritesheet_menus.png");
	UItextureIn = UItexture;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->boxes->Enable();
	App->collisions->Enable();
	
	App->lvlManage->changeScene = true;

	char tilesetTable[] = { "WwobCcB" };
	lvl1_map = App->tiles->Load("Assets/Textures/spritesheet_tiles.png", tilesetTable, 1);

	
	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	scoreFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);

	lvl = App->lvlManage->Getlvl();
	App->lvlManage->boxes_lvl = 0;
	App->lvlManage->steps = 0;

	//if (lvl == 0) {
	//	App->fade->FadeToBlack(this, (Module*)App->levelMenu, 30);
	//}

	switch (lvl) {
	case 1:
		zoom = 3;
		break;
	case 3:
		zoom = 2;
		break;
	case 4:
		zoom = 1;
		break;
	case 5:
		zoom = 1;
		break;
	case 6:
		zoom = 1;
		break;
	case 2:
		zoom = 2;
		break;
	default:
		zoom = 1;
		break;
	}
	
	//UItexture = { 1, 230, 60, 36 };

	colliderUI = App->collisions->AddCollider({ (SCREEN_WIDTH - UIrectIn.w * 3 - 30 * 3 + 1 * 3) , 22 * 3,UIrect.w *3, UIrect.h*3}, Collider::Type::UI, this);
	positionUI = { (SCREEN_WIDTH - UIrect.w * 3 - 30 * 3),22 * 3 };

	switch (lvl) {

		case 1:
			App->tiles->genObjects(-3 - 12, -3 - 24, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwCbbbbWo,oWbbbWCwbWo,oWbCbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo", zoom);
			App->lvlManage->max_steps = 90;
			break;
		case 3:
			//App->tiles->genObjects(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,ooooooooooooWwwwwwWooooooooooooo,ooooooooooooWbbBBBWooooooooooooo,ooooooooooooWbbbwwwWoooooooooooo,oooooooooooWwwCbbbbWoooooooooooo,oooooooooooWbbbWCwbWoooooooooooo,oooooooooooWbCbWbbbWoooooooooooo,oooooooooooWbbbWwwwwoooooooooooo,ooooooooooowwwwwoooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
			App->tiles->genObjects(-2, -2, lvl1_map, "oooooooooooooooo,ooWwWwwWoWwwwWoo,oWwbwbbwwWbbbwWo,oWbbbbCbbwbCbbWo,oWbbCbbWbbbbCbWo,oWWWbWWwwWWbbbWo,oWwwbwWbbWwCwWwo,oWbCbbwwwwbBBWoo,oWbCbCbCbbBBBWoo,oWbbbbWwwWBBBWoo,oWbCCbWooWBBBWoo,oWbbWwwoowwwwwoo,owwwwooooooooooo,oooooooooooooooo", zoom);
			App->lvlManage->max_steps = 750;
			break;
		case 4:
			App->tiles->genObjects(-1, -1, lvl1_map, "ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooWwwwWooooooooooooo,oooooooooooooooWbbbWWwwWooooooooo,oooooooooooooooWbwCwwbbWooooooooo,oooooooooooooooWbbbbCbbWooooooooo,oooooooWwwwwwwWWbwwwbbbWooooooooo,oooooooWBBBBbbwwbCbbCWWwooooooooo,oooooooWBBBBbbbbCbCCbwWoooooooooo,oooooooWBBBBbbWWCbbCbbWoooooooooo,ooooooowwwwwwwwWbbCbbwWoooooooooo,oooooooooooooooWbCbCbbWoooooooooo,ooooooooooooooowwWbwwbWoooooooooo,oooooooooooooooooWbbbbWoooooooooo,ooooooooooooooooowwwwwwoooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
			App->lvlManage->max_steps = 700;
			break;
		case 5:
			App->tiles->genObjects(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooWwwWwwwWooooooooooo,ooooooooooWwwWbbwBBBWooooooooooo,ooooooooooWbbwCbbBBBwwwwWooooooo,oooooooWwwwbCbbbWWBBBBbbWooooooo,oooooooWbbbCCwCbWWBBBBbbWooooooo,oooooooWbCbbbbbWWWWwwwbWwooooooo,oooooooWbwWwbCWwWwwbbCbWoooooooo,oooooooWbbWbCbwbwbbbCbbWoooooooo,ooooooowWbwbbbbCbbCCbWwwoooooooo,ooooooooWbbbwbCbwbbWwwoooooooooo,oooooooowwWbbwwbbWwwoooooooooooo,oooooooooowWbbbbbWoooooooooooooo,ooooooooooowwwwwwwoooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
			App->lvlManage->max_steps = 1400;
			break;
		case 6:
			//App->tiles->genObjects(-2, -2, lvl1_map, "oooooooooooooooo,oWwwwWWwwwwwwwWoo,oWbbbWWbBBBBBBWo,oWbbWwwbBBWBwbWo,oWbCWbbBBWwBbBWo,oWwbwbCwbwbbbbWo,oWbCbbCbbbbWbwWo,oWbCWbWbCwwWCbWo,oWbbWbWbCbbWbbWo,oWbCwbwWCwbwCbWo,oWbCbbbWbbbbbbWo,owwWbbbWbwwCbWwo,ooowwwwWbbbbbWoo,ooooooowwwwwwwoo,oooooooooooooooo", zoom);
			App->tiles->genObjects(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooWwwwWWwwwwwwwWooooooooo,oooooooooWbbbWWbBBBBBBWooooooooo,oooooooooWbbWwwbBBWBwbWooooooooo,oooooooooWbCWbbBBWwBbBWooooooooo,oooooooooWwbwbCwbwbbbbWooooooooo,oooooooooWbCbbCbbbbWbwWooooooooo,oooooooooWbCWbWbCwwWCbWooooooooo,oooooooooWbbWbWbCbbWbbWooooooooo,oooooooooWbCwbwWCwbwCbWooooooooo,oooooooooWbCbbbWbbbbbbWooooooooo,ooooooooowwWbbbWbwwCbWwooooooooo,ooooooooooowwwwWbbbbbWoooooooooo,ooooooooooooooowwwwwwwoooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
			App->lvlManage->max_steps = 600;
			break;
		case 2:
			App->tiles->genObjects(-2, -2, lvl1_map, "oooooooooooooooo,oooooooooooooooo,ooooWwwwwwwWoooo,ooooWbbbbbbWoooo,ooooWbwCCbbWoooo,ooooWbBBBwbWoooo,oooowWBBBCbwWooo,oooooWbwwbCbWooo,oooooWCbbCbbWooo,oooooWbbWbbbWooo,ooooowwwwwwwwooo,oooooooooooooooo,oooooooooooooooo,oooooooooooooooo", zoom);
			App->lvlManage->max_steps = 120;
			break;
		default:
			break;
		}

	sprintf_s(stageText, 3, "%02d", lvl);
	sprintf_s(limitText, 5, "%04d", App->lvlManage->max_steps);

	nextlvl = true;

	App->lvlManage->win = 0;
	
	return ret;
}

Update_Status SceneLevel1::Update()
{
	
	switch (lvl) {
	case 1:
		App->tiles->BlitScene(-3 - 12, -3 - 24, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwCbbbbWo,oWbbbWCwbWo,oWbCbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo", zoom);
		//App->lvlManage->max_steps = 750;
		//App->lvlManage->max_steps = 700;
		break;
	case 3:
		//App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,ooooooooooooWwwwwwWooooooooooooo,ooooooooooooWbbBBBWooooooooooooo,ooooooooooooWbbbwwwWoooooooooooo,oooooooooooWwwCbbbbWoooooooooooo,oooooooooooWbbbWCwbWoooooooooooo,oooooooooooWbCbWbbbWoooooooooooo,oooooooooooWbbbWwwwwoooooooooooo,ooooooooooowwwwwoooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		App->tiles->BlitScene(-2, -2, lvl1_map, "oooooooooooooooo,ooWwWwwWoWwwwWoo,oWwbwbbwwWbbbwWo,oWbbbbCbbwbCbbWo,oWbbCbbWbbbbCbWo,oWWWbWWwwWWbbbWo,oWwwbwWbbWwCwWwo,oWbCbbwwwwbBBWoo,oWbCbCbCbbBBBWoo,oWbbbbWwwWBBBWoo,oWbCCbWooWBBBWoo,oWbbWwwoowwwwwoo,owwwwooooooooooo,oooooooooooooooo", zoom);

		break;
	case 4:
		App->tiles->BlitScene(-1, -1, lvl1_map, "ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooWwwwWooooooooooooo,oooooooooooooooWbbbWWwwWooooooooo,oooooooooooooooWbwCwwbbWooooooooo,oooooooooooooooWbbbbCbbWooooooooo,oooooooWwwwwwwWWbwwwbbbWooooooooo,oooooooWBBBBbbwwbCbbCWWwooooooooo,oooooooWBBBBbbbbCbCCbwWoooooooooo,oooooooWBBBBbbWWCbbCbbWoooooooooo,ooooooowwwwwwwwWbbCbbwWoooooooooo,oooooooooooooooWbCbCbbWoooooooooo,ooooooooooooooowwWbwwbWoooooooooo,oooooooooooooooooWbbbbWoooooooooo,ooooooooooooooooowwwwwwoooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		break;
	case 5:
		App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooWwwWwwwWooooooooooo,ooooooooooWwwWbbwBBBWooooooooooo,ooooooooooWbbwCbbBBBwwwwWooooooo,oooooooWwwwbCbbbWWBBBBbbWooooooo,oooooooWbbbCCwCbWWBBBBbbWooooooo,oooooooWbCbbbbbWWWWwwwbWwooooooo,oooooooWbwWwbCWwWwwbbCbWoooooooo,oooooooWbbWbCbwbwbbbCbbWoooooooo,ooooooowWbwbbbbCbbCCbWwwoooooooo,ooooooooWbbbwbCbwbbWwwoooooooooo,oooooooowwWbbwwbbWwwoooooooooooo,oooooooooowWbbbbbWoooooooooooooo,ooooooooooowwwwwwwoooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		break;
	case 6:
		//App->tiles->BlitScene(-2, -2, lvl1_map, "oooooooooooooooo,oWwwwWWwwwwwwwWoo,oWbbbWWbBBBBBBWo,oWbbWwwbBBWBwbWo,oWbCWbbBBWwBbBWo,oWwbwbCwbwbbbbWo,oWbCbbCbbbbWbwWo,oWbCWbWbCwwWCbWo,oWbbWbWbCbbWbbWo,oWbCwbwWCwbwCbWo,oWbCbbbWbbbbbbWo,owwWbbbWbwwCbWwo,ooowwwwWbbbbbWoo,ooooooowwwwwwwoo,oooooooooooooooo", zoom);
		App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooWwwwWWwwwwwwwWooooooooo,oooooooooWbbbWWbBBBBBBWooooooooo,oooooooooWbbWwwbBBWBwbWooooooooo,oooooooooWbCWbbBBWwBbBWooooooooo,oooooooooWwbwbCwbwbbbbWooooooooo,oooooooooWbCbbCbbbbWbwWooooooooo,oooooooooWbCWbWbCwwWCbWooooooooo,oooooooooWbbWbWbCbbWbbWooooooooo,oooooooooWbCwbwWCwbwCbWooooooooo,oooooooooWbCbbbWbbbbbbWooooooooo,ooooooooowwWbbbWbwwCbWwooooooooo,ooooooooooowwwwWbbbbbWoooooooooo,ooooooooooooooowwwwwwwoooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		break;
	case 2:
		App->tiles->BlitScene(-2, -2, lvl1_map, "oooooooooooooooo,oooooooooooooooo,ooooWwwwwwwWoooo,ooooWbbbbbbWoooo,ooooWbwCCbbWoooo,ooooWbBBBwbWoooo,oooowWBBBCbwWooo,oooooWbwwbCbWooo,oooooWCbbCbbWooo,oooooWbbWbbbWooo,ooooowwwwwwwwooo,oooooooooooooooo,oooooooooooooooo,oooooooooooooooo", zoom);
		break;
	default:
		break;

}

	if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {
		if (App->lvlManage->win == 0) {


			if (pause == false) {
				if (noUI == false) {
					noUI = true;
				}
				else {
					noUI = false;
				}
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN) {
		if (App->lvlManage->win == 0) {
			if (pause == false) {
				pause = true;
				pauseIndex = 0;
			}
			else {
				pause = false;
			}
		}
	}
	if (pause == true) {
		currentTime = SDL_GetTicks();
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
				pauseIndex -= 1;
			}
			else {
				pauseIndex = 2;
			}
			lastTime_W = SDL_GetTicks();
			delay_W = 500;
			firstInput_W = false;
		}
		else if (currentTime > lastTime_W + delay_W) {
			if (pauseIndex > 0) {
				pauseIndex -= 1;
			}
			else {
				pauseIndex = 2;
			}
			lastTime_W = SDL_GetTicks();
			delay_W = 150;
			lastTime_W = currentTime;




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
				}
				else {
					pauseIndex = 0;
				}

				lastTime_S = SDL_GetTicks();
				delay_S = 500;
				firstInput_S = false;
			}
			else if (currentTime > lastTime_S + delay_S) {
				if (pauseIndex < 2) {
					pauseIndex += 1;
				}
				else {
					pauseIndex = 0;
				}
				lastTime_S = SDL_GetTicks();
				delay_S = 150;
				lastTime_S = currentTime;




			}

		}
	}

	colliderUI->SetPos(positionUI.x, positionUI.y);
	
	
	if (pause == true) {

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			switch (pauseIndex) {
			case 0:
				pause = false;
				break;
			case 1:
				
				break;
			case 2:
				
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
		App->render->Blit(UItextureIn, positionUI.x, positionUI.y, &UIrectIn, 0.0f, true, 3);
		SDL_SetTextureAlphaMod(UItextureIn, 255);
		App->render->Blit(UItexture, positionUI.x, positionUI.y, &UIrect, 0.0f, true, 3);


		App->fonts->BlitText(positionUI.x + 28 * 3 + 7 * 2 * 3, positionUI.y + 3 * 3, scoreFont, stageText, 3, 222, 218, 222);

		sprintf_s(stepText, 5, "%04d", App->lvlManage->steps);
		App->fonts->BlitText(positionUI.x + 28 * 3, positionUI.y + 15 * 3, scoreFont, stepText, 3, 222, 218, 222);

		App->fonts->BlitText(positionUI.x + 28 * 3, positionUI.y + 24 * 3, scoreFont, limitText, 3, 222, 218, 222);

	}

	if (!App->player->destroyed)
	{
		rectplayer = App->player->currentAnimation->GetCurrentFrame();
		App->render->Blit(App->player->texture, App->player->position.x, App->player->position.y, &rectplayer, NULL, 1.0f, zoom);

	}
	

	if (App->lvlManage->win == 2) {
		
		App->render->Blit(UItexture, (SCREEN_WIDTH - rectlose.w*3) / 2, (SCREEN_HEIGHT - rectlose.h *3)/2,&rectlose, 0.0f, true, 3);
		App->fonts->BlitText((SCREEN_WIDTH - rectlose.w * 3) / 2 + 6 * 3, (SCREEN_HEIGHT - rectlose.h * 3) / 2 +17*3, scoreFont, "YOU LOSE!SPACE TO TRY AGAIN", 3, 0, 32, 33, (SCREEN_WIDTH - rectlose.w * 3) / 2 + rectlose.w * 3 - 45 * 3, 3);
	
	}

	if (App->lvlManage->win == 1) {
		
		App->render->Blit(UItexture, (SCREEN_WIDTH - rectwin.w * 3) / 2, (SCREEN_HEIGHT - rectwin.h * 3) / 2, &rectwin, 0.0f, true, 3);
		App->fonts->BlitText((SCREEN_WIDTH - rectlose.w * 3) / 2 + 10 * 3, (SCREEN_HEIGHT - rectlose.h * 3) / 2 + 17 * 3, scoreFont, " YOU WIN!SPACE TO  CONFIRM", 3, 0, 32, 33, (SCREEN_WIDTH - rectlose.w * 3) / 2 + rectlose.w * 3 - 45 * 3, 3);
		App->render->Blit(UItexture, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2, (SCREEN_HEIGHT) / 2 + 44 * 3, &rectNextRepeat, 0.0f, true, 3);
		App->fonts->BlitText((SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + 4 * 3, (SCREEN_HEIGHT) / 2 + 44 * 3 + 5 * 3, scoreFont, "GO TO NEXT LEVEL?", 2, 0, 0, 0, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + rectNextRepeat.w * 3 - 5 * 3);
		if (nextlvl==true) {
			App->fonts->BlitText((SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + 15 * 3, (SCREEN_HEIGHT) / 2 + 44 * 3 + 15 * 3, scoreFont, "YES", 3,214, 0, 0, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + rectNextRepeat.w * 3 - 5 * 3);
			App->fonts->BlitText((SCREEN_WIDTH + 3 * 3) / 2 + 10 * 3, (SCREEN_HEIGHT) / 2 + 44 * 3 + 15 * 3, scoreFont, "NO", 3, 16, 16, 24, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + rectNextRepeat.w * 3 - 5 * 3);
		}
		else {
			App->fonts->BlitText((SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + 15 * 3, (SCREEN_HEIGHT) / 2 + 44 * 3 + 15 * 3, scoreFont, "YES", 3, 16, 16, 24, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + rectNextRepeat.w * 3 - 5 * 3);
			App->fonts->BlitText((SCREEN_WIDTH + 3 * 3) / 2 + 10 * 3, (SCREEN_HEIGHT) / 2 + 44 * 3 + 15 * 3, scoreFont, "NO", 3, 214, 0, 0, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + rectNextRepeat.w * 3 - 5 * 3);
		}
		
		App->fonts->BlitText((SCREEN_WIDTH - 4*3) /2, (SCREEN_HEIGHT) / 2 + 44 * 3 + 15 * 3, scoreFont, "/", 3, 16, 16, 24, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + rectNextRepeat.w * 3 - 5 * 3);

		
	}

	if (pause == true) {
		App->render->Blit(UItexture, (SCREEN_WIDTH - rectPause.w * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3) / 2, &rectPause, 0.0f, true, 3);
		App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2 + 60*3 , (SCREEN_HEIGHT - rectPause.h * 3) / 2 + 5*3, scoreFont, stageText, 3, 33, 0, 255);

		switch (pauseIndex) {
		case 0:
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3 )/2 + 22 * 3, scoreFont, "RESUME", 3, 214, 0, 0, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3 ) / 2 + 22 * 3, scoreFont, "|GO TO MENU", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3 ) / 2 + 22 * 3, scoreFont, "||GO TO INTRO", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			break;
		case 1:
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3) / 2 + 22 * 3, scoreFont, "RESUME", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3) / 2 + 22 * 3, scoreFont, "|GO TO MENU", 3, 214, 0, 0, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3) / 2 + 22 * 3, scoreFont, "||GO TO INTRO", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			break;
		case 2:
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3) / 2 + 22 * 3, scoreFont, "RESUME", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3) / 2 + 22 * 3, scoreFont, "|GO TO MENU", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - rectPause.w * 3 + 7 * 3) / 2, (SCREEN_HEIGHT - rectPause.h * 3) / 2 + 22 * 3, scoreFont, "||GO TO INTRO", 3, 214, 0, 0, SCREEN_WIDTH, 3);
			break;
		}
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

void SceneLevel1::OnCollision(Collider* c1, Collider* c2)
{

	if (c1->type == Collider::Type::UI && c2->type == Collider::Type::PLAYER) {
		if (positionUI.x == 22 * 3&& positionUI.y == 22 * 3) {
			positionUI = { (SCREEN_WIDTH - UIrect.w * 3 - 30 * 3), 22 * 3 };
		}
		else {
			positionUI = { 22 * 3, 22 * 3 };
		}
	}
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->collisions->Disable();
	App->tiles->UnLoad(0);
	App->fonts->UnLoad(0);
	App->boxes->Disable();
	return true;
}

