#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "LevelManager.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Textures/spritesheet_intro_fondo.png");
	bgTexto = App->textures->Load("Assets/Textures/spritesheet_intro_texto.png");
	App->audio->PlayMusic("Assets/Audio/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		
		
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		//lvl++;
		//App->player->spawn(lvl);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexture, 256, 0, NULL);
	App->render->Blit(bgTexture, 512, 0, NULL);
	App->render->Blit(bgTexto, 250, 125, NULL);

	return Update_Status::UPDATE_CONTINUE;
}