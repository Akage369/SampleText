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
	

	App->boxes->AddBox(Box_Type::BOX, 96, 96); 
	//App->boxes->AddBox(Box_Type::BOX, 144, 48);
	App->boxes->AddBox(Box_Type::BOX, 144, 120);
	App->boxes->AddBox(Box_Type::BOX, 72, 144);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->lvlManage->lvlChange(1, '+'); 

	App->player->Enable();
	App->boxes->Enable();
	//App->enemies->Enable();
	App->collisions->Enable();
	//App->tiles->Enable();
	

	char tilesetTable[] = { "WwobCcB" };
	lvl1_map = App->tiles->Load("Assets/Textures/spritesheet_tiles.png", tilesetTable, 1);

	
	

	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.x += 3;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	switch (App->lvlManage->Getlvl() == 1) {
	case 1:
		App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooo,oooooooWwwwwwWooooooo,oooooooWbbBBBWooooooo,ooooooWbbbwwwWooooooo,ooooooWwwbbbbbWoooooo,ooooooWbbbWbwbWoooooo,ooooooWbbbWbbbWooooooo,ooooooWbbbWwwwwoooooo,oooooowwwwwoooooooooo,ooooooooooooooooooooooo");
		break;
	case 2:
		App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooo,oooooooWwwwwwWooooooo,oooooooWbbBBBWooooooo,ooooooWbbbwwwWooooooo,ooooooWwwbbbbbWoooooo,ooooooWbbbWbwbWoooooo,ooooooWbbbWbbbWooooooo,ooooooWbbbWwwwwoooooo,oooooowwwwwoooooooooo,ooooooooooooooooooooooo");
		break;
	case 3:
		App->tiles->BlitScene(-1, -1, lvl1_map, "oooooooooooooooooooo,oooooooWwwwwwWooooooo,oooooooWbbBBBWooooooo,ooooooWbbbwwwWooooooo,ooooooWwwbbbbbWoooooo,ooooooWbbbWbwbWoooooo,ooooooWbbbWbbbWooooooo,ooooooWbbbWwwwwoooooo,oooooowwwwwoooooooooo,ooooooooooooooooooooooo");
		break;
	default:
		break;
	}
	


	
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	
	///Tiles
	
	
	///Cajas
	
	
	//App->tiles->BlitScene(96, 96, lvl1_map, "C");
	//App->tiles->BlitScene(144, 120, lvl1_map, "C");
	//App->tiles->BlitScene(72, 144, lvl1_map, "C");
	
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	//App->enemies->Disable();
	App->collisions->Disable();
	App->tiles->UnLoad(0);
	//App->tiles->Disable();
	App->boxes->Disable();
	return true;
}