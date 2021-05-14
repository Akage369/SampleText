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
	loseTexture = App->textures->Load("Assets/Textures/spritesheet_menus.png");
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

	App->lvlManage->boxes_lvl = 0;
	
	if (App->lvlManage->Getlvl() == 1) {
		App->lvlManage->max_steps = 90;
	}

	App->lvlManage->win = 0;

	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.x += 3;
	switch (App->lvlManage->Getlvl()) {
	case 1:
		App->tiles->BlitScene(-1, -1, lvl1_map, "ooooooooooo,ooWwwwwwWoo,ooWbbBBBWoo,ooWbbbwwwWo,oWwwbbbbbWo,oWbbbWbwbWo,oWbbbWbbbWo,oWbbbWwwwwo,owwwwwooooo,ooooooooooo");
		//App->lvlManage->boxes_lvl = 3;

		//App->lvlManage->max_steps = 750;
		//App->lvlManage->max_steps = 700;
		break;
	default:
		break;
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	



	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN) {
		App->lvlManage->max_steps = 0;
		App->lvlManage->Lose();
		
	}

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN) {
		
		App->lvlManage->lvlChange(1, '+');
		App->lvlManage->LevelComplete();

	}
	if (!App->player->destroyed)
	{
		SDL_Rect rect = App->player->currentAnimation->GetCurrentFrame();
		App->render->Blit(App->player->texture, App->player->position.x, App->player->position.y, &rect);

	}
	


	if (App->lvlManage->win == 2) {
		SDL_Rect rectlose = {124, 268, 120, 64};
		App->render->Blit(App->sceneLevel_1->loseTexture, (SCREEN_WIDTH - 120) / 2, (SCREEN_HEIGHT - 64)/2,&rectlose, 0.0f, false);
		//App->render->Blit(App->sceneLevel_1->loseTexture,0,0,&rectlose, 0.0f, false);
	
	}
	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);
	
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