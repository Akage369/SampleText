#include "SceneIntro.h"
#include "Presentation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "LevelManager.h"
#include "LevelMenu.h"
#include "Pointer.h"

LevelMenu::LevelMenu(bool startEnabled) : Module(startEnabled)
{

}

LevelMenu::~LevelMenu()
{

}

// Load assets
bool LevelMenu::Start()
{

	LOG("Loading background assets");

	bool ret = true;
	App->pointer->Enable();
	bgTexture = App->textures->Load("Assets/Textures/menuSoukoban.png");

	//App->audio->PlayMusic("Assets/Audio/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->lvlManage->changeScene = true;

	return ret;
}

Update_Status LevelMenu::Update()
{
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 20);
}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->lvlManage->lvlChange(1, '=');
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
	
		
		//lvl++;
		//App->player->spawn(lvl);
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status LevelMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL, 1.0f, true, 3);
	/*App->render->Blit(bgTexture, 256, 0, NULL);
	App->render->Blit(bgTexture, 512, 0, NULL);
	App->render->Blit(bgTexto, 140, 125, NULL);*/

	return Update_Status::UPDATE_CONTINUE;
}

bool LevelMenu::CleanUp()
{

	App->pointer->Disable();
	return true;
}