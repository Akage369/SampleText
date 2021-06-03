#include "SceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "LevelManager.h"
#include "Presentation.h"

Presentation::Presentation(bool startEnabled) : Module(startEnabled)
{

}

Presentation::~Presentation()
{

}

// Load assets
bool Presentation::Start()
{

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Textures/presentacion.png");
	//bgTexto = App->textures->Load("Assets/Textures/spritesheet_intro_texto.png");
	//App->audio->PlayMusic("Assets/Audio/Music/MusicAnimation.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status Presentation::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{


		App->fade->FadeToBlack(this, (Module*)App->packInVideo, 20);
		//lvl++;
		//App->player->spawn(lvl);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status Presentation::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexto, 15, 50, NULL);

	return Update_Status::UPDATE_CONTINUE;
}