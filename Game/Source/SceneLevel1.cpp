#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Tiles.h"

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
	
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 600, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 625, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 640, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 665, 80);

	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 735, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 750, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 775, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 790, 120);

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 830, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 890, 100);

	App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->tiles->Enable();
	App->player->Enable();
	App->enemies->Enable();
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
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	
	///Tiles
	App->tiles->BlitScene(0, 0, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwbbbbbWo,oWbbbWbwbWo,oWbbbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo");

	///Cajas
	App->tiles->BlitScene(96, 96, lvl1_map, "C");
	App->tiles->BlitScene(144, 120, lvl1_map, "C");
	App->tiles->BlitScene(72, 144, lvl1_map, "C");
	///App->tiles->BlitScene(0, 120, lvl1_map, "oooooooooooooWwwwwwWooooWbbBBBWooooWbbbwwwWooWwwCbbbbWooWbbbWCwbWooWbCbWbbbWooWbbbWwwwwoowwwwwoooooooooooooooo");
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	return true;
}