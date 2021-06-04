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

bool Presentation::Start()
{
	
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Textures/presentacion.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->lvlManage->changeScene = true;

	return ret;
}

Update_Status Presentation::Update()
{
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
		App->lvlManage->lvlChange(6, '=');
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{


		App->fade->FadeToBlack(this, (Module*)App->packInVideo, 20);
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Presentation::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexto, 15, 50, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool Presentation::CleanUp()
{
	App->sceneIntro->Disable();

	return true;
}