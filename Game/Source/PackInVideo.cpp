#include "SceneIntro.h"
#include "PackInVideo.h"
#include "Presentacion.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "LevelManager.h"
#include "Presentacion.h"

PackInVideo::PackInVideo(bool startEnabled) : Module(startEnabled)
{

}

PackInVideo::~PackInVideo()
{

}

// Load assets
bool PackInVideo::Start()
{

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Textures/PackInVideo.png");
	//bgTexto = App->textures->Load("Assets/Textures/spritesheet_intro_texto.png");
	//App->audio->PlayMusic("Assets/Audio/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status PackInVideo::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{


		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 20);
		//lvl++;
		//App->player->spawn(lvl);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status PackInVideo::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, (SCREEN_WIDTH - 164)/2, (SCREEN_HEIGHT-107)/2, NULL);
	App->render->Blit(bgTexto, 15, 50, NULL);

	return Update_Status::UPDATE_CONTINUE;
}