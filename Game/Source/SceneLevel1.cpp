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
	/*
	bgTexture = App->textures->Load("Assets/Textures/background.png");
	
	App->audio->PlayMusic("Assets/Audio/Music/stage1.ogg", 1.0f);

	///tiles
	bgTiles = App->textures->Load("Assets/Textures/spritesheet_tiles.png");

	//Bottomside collider
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	//First two columns colliders
	App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);
	*/
	// Enemies ---
	

	//App->boxes->AddBox(Box_Type::BOX, 96, 96); 
	//App->boxes->AddBox(Box_Type::BOX, 144, 48);
	//App->boxes->AddBox(Box_Type::BOX, 144, 120);
	//App->boxes->AddBox(Box_Type::BOX, 72, 144);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	//App->lvlManage->lvlChange(1, '+'); 

	App->player->Enable();
	App->boxes->Enable();
	//App->enemies->Enable();
	App->collisions->Enable();
	//App->tiles->Enable();
	
	App->lvlManage->changeScene = true;

	char tilesetTable[] = { "WwobCcB" };
	lvl1_map = App->tiles->Load("Assets/Textures/spritesheet_tiles.png", tilesetTable, 1);

	
	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@ " };
	scoreFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);

	lvl = App->lvlManage->Getlvl();
	App->lvlManage->boxes_lvl = 0;
	App->lvlManage->steps = 0;

	switch (lvl) {
	case 1:
		zoom = 3;
		break;
	case 2:
		zoom = 2;
		break;
	case 3: 
		zoom = 1;
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
	default:
		break;
	}
	/*
	switch(App->lvlManage->Getlvl()){
		
	case 1:
		App->tiles->genObjects(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,ooooooooooooWwwwwwWooooooooooooo,ooooooooooooWbbBBBWooooooooooooo,ooooooooooooWbbbwwwWoooooooooooo,oooooooooooWwwCbbbbWoooooooooooo,oooooooooooWbbbWCwbWoooooooooooo,oooooooooooWbCbWbbbWoooooooooooo,oooooooooooWbbbWwwwwoooooooooooo,ooooooooooowwwwwoooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo");
		App->lvlManage->max_steps = 90;
		break;
	case 2:
		App->tiles->genObjects(-1, -1, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwCbbbbWo,oWbbbWCwbWo,oWbCbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo");
		App->lvlManage->max_steps = 90;
		break;
	}
	*/
	
	//UItexture = { 1, 230, 60, 36 };

	colliderUI = App->collisions->AddCollider({ (SCREEN_WIDTH - UIrectIn.w * 3 - 30 * 3 + 1 * 3) , 22 * 3,UIrect.w *3, UIrect.h*3}, Collider::Type::UI, this);
	positionUI = { (SCREEN_WIDTH - UIrect.w * 3 - 30 * 3),22 * 3 };

	switch (lvl) {

	case 1:
		App->tiles->genObjects(-3 - 12, -3 - 24, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwCbbbbWo,oWbbbWCwbWo,oWbCbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo", zoom);
		App->lvlManage->max_steps = 90;
		break;
	case 2:
		//App->tiles->genObjects(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,ooooooooooooWwwwwwWooooooooooooo,ooooooooooooWbbBBBWooooooooooooo,ooooooooooooWbbbwwwWoooooooooooo,oooooooooooWwwCbbbbWoooooooooooo,oooooooooooWbbbWCwbWoooooooooooo,oooooooooooWbCbWbbbWoooooooooooo,oooooooooooWbbbWwwwwoooooooooooo,ooooooooooowwwwwoooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		App->tiles->genObjects(-2, -2, lvl1_map, "oooooooooooooooo,ooWwWwwWoWwwwWoo,oWwbwbbwwWbbbwWo,oWbbbbCbbwbCbbWo,oWbbCbbWbbbbCbWo,oWWWbWWwwWWbbbWo,oWwwbwWbbWwCwWwo,oWbCbbwwwwbBBWoo,oWbCbCbCbbBBBWoo,oWbbbbWwwWBBBWoo,oWbCCbWooWBBBWoo,oWbbWwwoowwwwwoo,owwwwooooooooooo,oooooooooooooooo", zoom);
		App->lvlManage->max_steps = 750;
		break;
	case 3:
		App->tiles->genObjects(-1, -1, lvl1_map, "ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooWwwwWooooooooooooo,oooooooooooooooWbbbWWwwWooooooooo,oooooooooooooooWbwCwwbbWooooooooo,oooooooooooooooWbbbbCbbWooooooooo,oooooooWwwwwwwWWbwwwbbbWooooooooo,oooooooWBBBBbbwwbCbbCWWwooooooooo,oooooooWBBBBbbbbCbCCbwWoooooooooo,oooooooWBBBBbbWWCbbCbbWoooooooooo,ooooooowwwwwwwwWbbCbbwWoooooooooo,oooooooooooooooWbCbCbbWoooooooooo,ooooooooooooooowwWbwwbWoooooooooo,oooooooooooooooooWbbbbWoooooooooo,ooooooooooooooooowwwwwwoooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		App->lvlManage->max_steps = 700;
		break;
	case 4:
		App->tiles->genObjects(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooWwwWwwwWooooooooooo,ooooooooooWwwWbbwBBBWooooooooooo,ooooooooooWbbwCbbBBBwwwwWooooooo,oooooooWwwwbCbbbWWBBBBbbWooooooo,oooooooWbbbCCwCbWWBBBBbbWooooooo,oooooooWbCbbbbbWWWWwwwbWwooooooo,oooooooWbwWwbCWwWwwbbCbWoooooooo,oooooooWbbWbCbwbwbbbCbbWoooooooo,ooooooowWbwbbbbCbbCCbWwwoooooooo,ooooooooWbbbwbCbwbbWwwoooooooooo,oooooooowwWbbwwbbWwwoooooooooooo,oooooooooowWbbbbbWoooooooooooooo,ooooooooooowwwwwwwoooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		App->lvlManage->max_steps = 1400;
		break;
	case 5:
		//App->tiles->genObjects(-2, -2, lvl1_map, "oooooooooooooooo,oWwwwWWwwwwwwwWoo,oWbbbWWbBBBBBBWo,oWbbWwwbBBWBwbWo,oWbCWbbBBWwBbBWo,oWwbwbCwbwbbbbWo,oWbCbbCbbbbWbwWo,oWbCWbWbCwwWCbWo,oWbbWbWbCbbWbbWo,oWbCwbwWCwbwCbWo,oWbCbbbWbbbbbbWo,owwWbbbWbwwCbWwo,ooowwwwWbbbbbWoo,ooooooowwwwwwwoo,oooooooooooooooo", zoom);
		App->tiles->genObjects(-1, -1, lvl1_map, "oooooooooooooooo,oWwwwWWwwwwwwwWo,oWbbbWWbBBBBBBWo,oWbbWwwbBBWBwbWo,oWbbWbCBBWwBbBWo,oWwbwbbwbwbbbbWo,oWbbbbbbbbbWbwWo,oWbbWbWbbwwWbbWo,oWbbWbWbbbbWbbWo,oWbbwbwWbwbwbbWo,oWbCbbbWbbbbbbWo,owwWbbbWbwwbbWwo,ooowwwwWbbbbbWoo,ooooooowwwwwwwoo,oooooooooooooooo", zoom);
		App->lvlManage->max_steps = 600;
		break;
	case 6:
		break;
	default:
		break;
	}

	sprintf_s(stageText, 3, "%02d", lvl);
	sprintf_s(limitText, 5, "%04d", App->lvlManage->max_steps);

	//App->lvlManage->max_steps = 90;
	App->lvlManage->win = 0;
	
	return ret;
}

Update_Status SceneLevel1::Update()
{
	/*
	//App->render->camera.x += 3;
	switch (App->lvlManage->Getlvl()) {
	case 1:
		App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,ooooooooooooWwwwwwWooooooooooooo,ooooooooooooWbbBBBWooooooooooooo,ooooooooooooWbbbwwwWoooooooooooo,oooooooooooWwwCbbbbWoooooooooooo,oooooooooooWbbbWCwbWoooooooooooo,oooooooooooWbCbWbbbWoooooooooooo,oooooooooooWbbbWwwwwoooooooooooo,ooooooooooowwwwwoooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo");

		//App->lvlManage->max_steps = 750;
		//App->lvlManage->max_steps = 700;
		break;
	case 2:
		App->tiles->BlitScene(-1, -1, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwCbbbbWo,oWbbbWCwbWo,oWbCbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo");
		break;
	default:
		break;
	}
	*/

	//App->render->camera.x += 3;
	switch (lvl) {
	case 1:
		App->tiles->BlitScene(-3 - 12, -3 - 24, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwCbbbbWo,oWbbbWCwbWo,oWbCbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo", zoom);
		//App->lvlManage->max_steps = 750;
		//App->lvlManage->max_steps = 700;
		break;
	case 2:
		//App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,ooooooooooooWwwwwwWooooooooooooo,ooooooooooooWbbBBBWooooooooooooo,ooooooooooooWbbbwwwWoooooooooooo,oooooooooooWwwCbbbbWoooooooooooo,oooooooooooWbbbWCwbWoooooooooooo,oooooooooooWbCbWbbbWoooooooooooo,oooooooooooWbbbWwwwwoooooooooooo,ooooooooooowwwwwoooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		App->tiles->BlitScene(-2, -2, lvl1_map, "oooooooooooooooo,ooWwWwwWoWwwwWoo,oWwbwbbwwWbbbwWo,oWbbbbCbbwbCbbWo,oWbbCbbWbbbbCbWo,oWWWbWWwwWWbbbWo,oWwwbwWbbWwCwWwo,oWbCbbwwwwbBBWoo,oWbCbCbCbbBBBWoo,oWbbbbWwwWBBBWoo,oWbCCbWooWBBBWoo,oWbbWwwoowwwwwoo,owwwwooooooooooo,oooooooooooooooo", zoom);
		
		break;
	case 3:
		App->tiles->BlitScene(-1, -1, lvl1_map, "ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooWwwwWooooooooooooo,oooooooooooooooWbbbWWwwWooooooooo,oooooooooooooooWbwCwwbbWooooooooo,oooooooooooooooWbbbbCbbWooooooooo,oooooooWwwwwwwWWbwwwbbbWooooooooo,oooooooWBBBBbbwwbCbbCWWwooooooooo,oooooooWBBBBbbbbCbCCbwWoooooooooo,oooooooWBBBBbbWWCbbCbbWoooooooooo,ooooooowwwwwwwwWbbCbbwWoooooooooo,oooooooooooooooWbCbCbbWoooooooooo,ooooooooooooooowwWbwwbWoooooooooo,oooooooooooooooooWbbbbWoooooooooo,ooooooooooooooooowwwwwwoooooooooo,ooooooooooooooooooooooooooooooooo,ooooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		break;
	case 4:
		App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooWwwWwwwWooooooooooo,ooooooooooWwwWbbwBBBWooooooooooo,ooooooooooWbbwCbbBBBwwwwWooooooo,oooooooWwwwbCbbbWWBBBBbbWooooooo,oooooooWbbbCCwCbWWBBBBbbWooooooo,oooooooWbCbbbbbWWWWwwwbWwooooooo,oooooooWbwWwbCWwWwwbbCbWoooooooo,oooooooWbbWbCbwbwbbbCbbWoooooooo,ooooooowWbwbbbbCbbCCbWwwoooooooo,ooooooooWbbbwbCbwbbWwwoooooooooo,oooooooowwWbbwwbbWwwoooooooooooo,oooooooooowWbbbbbWoooooooooooooo,ooooooooooowwwwwwwoooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo,oooooooooooooooooooooooooooooooo", zoom);
		break;
	case 5:
		//App->tiles->BlitScene(-2, -2, lvl1_map, "oooooooooooooooo,oWwwwWWwwwwwwwWoo,oWbbbWWbBBBBBBWo,oWbbWwwbBBWBwbWo,oWbCWbbBBWwBbBWo,oWwbwbCwbwbbbbWo,oWbCbbCbbbbWbwWo,oWbCWbWbCwwWCbWo,oWbbWbWbCbbWbbWo,oWbCwbwWCwbwCbWo,oWbCbbbWbbbbbbWo,owwWbbbWbwwCbWwo,ooowwwwWbbbbbWoo,ooooooowwwwwwwoo,oooooooooooooooo", zoom);
		App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooo,oWwwwWWwwwwwwwWo,oWbbbWWbBBBBBBWo,oWbbWwwbBBWBwbWo,oWbCWbbBBWwBbBWo,oWwbwbbwbwbbbbWo,oWbbbbbbbbbWbwWo,oWbbWbWbbwwWbbWo,oWbbWbWbbbbWbbWo,oWbbwbwWbwbwbbWo,oWbCbbbWbbbbbbWo,owwWbbbWbwwbbWwo,ooowwwwWbbbbbWoo,ooooooowwwwwwwoo,oooooooooooooooo", zoom);
		break;
	case 6:
		break;
	default:
		break;
	
	}
	
	colliderUI->SetPos(positionUI.x, positionUI.y);
	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	
	//UItexture = { 1, 230, 60, 36 };

	//if (contactUI == false) {

		/*SDL_SetTextureAlphaMod(UItexture, 125);
		App->render->Blit(UItextureIn, (SCREEN_WIDTH - UIrectIn.w * 3 - 30 * 3 + 1 * 3), 22 * 3, &UIrectIn, 0.0f, true, 3);
		SDL_SetTextureAlphaMod(UItextureIn, 255);
		App->render->Blit(UItexture, (SCREEN_WIDTH - UIrect.w * 3 - 30 * 3), 22 * 3, &UIrect, 0.0f, true, 3);


		App->fonts->BlitText((SCREEN_WIDTH - UIrectIn.w * 3 - 1 * 3 + 7 * 2 * 3), (22 + 15 - 12) * 3, scoreFont, stageText, 3, 222, 218, 222);

		sprintf_s(stepText, 5, "%04d", App->lvlManage->steps);
		App->fonts->BlitText((SCREEN_WIDTH - UIrectIn.w * 3 - 1 * 3), (22 + 15) * 3, scoreFont, stepText, 3, 222, 218, 222);

		App->fonts->BlitText((SCREEN_WIDTH - UIrectIn.w * 3 - 1 * 3), (22 + 15 + 9) * 3, scoreFont, limitText, 3, 222, 218, 222);
*/

		SDL_SetTextureAlphaMod(UItexture, 125);
		App->render->Blit(UItextureIn, positionUI.x, positionUI.y, &UIrectIn, 0.0f, true, 3);
		SDL_SetTextureAlphaMod(UItextureIn, 255);
		App->render->Blit(UItexture, positionUI.x, positionUI.y, &UIrect, 0.0f, true, 3);


		App->fonts->BlitText(positionUI.x + 28 * 3 + 7 * 2 * 3,positionUI.y+3*3, scoreFont, stageText, 3, 222, 218, 222);

		sprintf_s(stepText, 5, "%04d", App->lvlManage->steps);
		App->fonts->BlitText(positionUI.x + 28 * 3, positionUI.y + 15 * 3, scoreFont, stepText, 3, 222, 218, 222);

		App->fonts->BlitText(positionUI.x + 28 * 3, positionUI.y + 24 * 3, scoreFont, limitText, 3, 222, 218, 222);
	//}
	//else {
		/*
		SDL_SetTextureAlphaMod(UItexture, 125);
		App->render->Blit(UItextureIn, (22 * 3 ), 22 * 3, &UIrectIn, 0.0f, true, 3);
		SDL_SetTextureAlphaMod(UItextureIn, 255);
		App->render->Blit(UItexture, (22 * 3), 22 * 3, &UIrect, 0.0f, true, 3);


		App->fonts->BlitText((52 * 3 + 7 * 2 * 3-2*3), (22 + 15 - 12) * 3, scoreFont, stageText, 3, 222, 218, 222);

		sprintf_s(stepText, 5, "%04d", App->lvlManage->steps);
		App->fonts->BlitText((52 * 3-2 * 3), (22 + 15) * 3, scoreFont, stepText, 3, 222, 218, 222);

		App->fonts->BlitText((52 * 3- 2 * 3), (22 + 15 + 9) * 3, scoreFont, limitText, 3, 222, 218, 222);
		*/
	//}
	
	if (!App->player->destroyed)
	{
		rectplayer = App->player->currentAnimation->GetCurrentFrame();
		App->render->Blit(App->player->texture, App->player->position.x, App->player->position.y, &rectplayer, NULL, 1.0f, zoom);

	}
	

	if (App->lvlManage->win == 2) {
		
		App->render->Blit(UItexture, (SCREEN_WIDTH - rectlose.w*3) / 2, (SCREEN_HEIGHT - rectlose.h *3)/2,&rectlose, 0.0f, true, 3);
		//App->render->Blit(App->sceneLevel_1->loseTexture,0,0,&rectlose, 0.0f, false);
		App->fonts->BlitText((SCREEN_WIDTH - rectlose.w * 3) / 2 + 6 * 3, (SCREEN_HEIGHT - rectlose.h * 3) / 2 +17*3, scoreFont, "YOU LOSE!SPACE TO TRY AGAIN", 3, 0, 0, 0, (SCREEN_WIDTH - rectlose.w * 3) / 2 + rectlose.w * 3 - 45 * 3, 3);
	
	}

	if (App->lvlManage->win == 1) {
		
		App->render->Blit(UItexture, (SCREEN_WIDTH - rectwin.w * 3) / 2, (SCREEN_HEIGHT - rectwin.h * 3) / 2, &rectwin, 0.0f, true, 3);
		App->fonts->BlitText((SCREEN_WIDTH - rectlose.w * 3) / 2 + 10 * 3, (SCREEN_HEIGHT - rectlose.h * 3) / 2 + 17 * 3, scoreFont, " YOU WIN!SPACE TO  CONFIRM", 3, 0, 0, 0, (SCREEN_WIDTH - rectlose.w * 3) / 2 + rectlose.w * 3 - 45 * 3, 3);
		App->render->Blit(UItexture, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2, (SCREEN_HEIGHT) / 2 + 44 * 3, &rectNextRepeat, 0.0f, true, 3);
		App->fonts->BlitText((SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + 4 * 3, (SCREEN_HEIGHT) / 2 + 44 * 3 + 5 * 3, scoreFont, "GO TO NEXT LEVEL?", 2, 0, 0, 0, (SCREEN_WIDTH - rectNextRepeat.w * 3) / 2 + rectNextRepeat.w * 3 - 5 * 3);

	}
	
	//SDL_Rect rectlose = { 2, 268, 120, 64 };
	//App->render->Blit(App->sceneLevel_1->loseTexture, (SCREEN_WIDTH - 120 * 3) / 2, (SCREEN_HEIGHT - 64 * 3) / 2, &rectlose, 0.0f, true, 3);

	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);
	
	///Tiles
	
	
	///Cajas
	
	
	//App->tiles->BlitScene(96, 96, lvl1_map, "C");
	//App->tiles->BlitScene(144, 120, lvl1_map, "C");
	//App->tiles->BlitScene(72, 144, lvl1_map, "C");
	
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
		
		//contactUI = true;
	}
	


		/*if (c1 == collider && destroyed == false)
		{


			App->audio->PlayFx(explosionFx);
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
			//App->collisions->RemoveCollider(collider);
			destroyed = true;
		}
		*/

		//if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
		//{
		//	score += 23;
		//}
	//}

}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	//App->enemies->Disable();
	App->collisions->Disable();
	App->tiles->UnLoad(0);
	App->fonts->UnLoad(0);
	//App->tiles->Disable();
	App->boxes->Disable();
	return true;
}

