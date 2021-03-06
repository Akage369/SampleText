#include "SceneIntro.h"
#include "PackInVideo.h"
#include "menuSoukoban.h"
#include "Presentacion.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "LevelManager.h"

menuSoukoban::menuSoukoban(bool startEnabled) : Module(startEnabled)
{

}

menuSoukoban::~menuSoukoban()
{

}

// Load assets
bool menuSoukoban::Start()
{

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Textures/menuSoukoban.png");
	//bgTexto = App->textures->Load("Assets/Textures/spritesheet_intro_texto.png");
	//App->audio->PlayMusic("Assets/Audio/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status menuSoukoban::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{


		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
		//lvl++;
		//App->player->spawn(lvl);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status menuSoukoban::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0,0, NULL);
	App->render->Blit(bgTexto, 15, 50, NULL);

	return Update_Status::UPDATE_CONTINUE;
}