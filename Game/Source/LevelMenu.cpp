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
#include "WindowSize.h"

LevelMenu::LevelMenu(bool startEnabled) : Module(startEnabled)
{

}

LevelMenu::~LevelMenu()
{

}

bool LevelMenu::Start()
{

	LOG("Loading background assets");

	bool ret = true;
	App->pointer->Enable();
	bgTexture = App->textures->Load("Assets/Textures/spritesheet_menus.png");

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
		switch (App->pointer->index) {
		case 1:
			App->lvlManage->lvlChange(1, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 10:
			App->lvlManage->lvlChange(2, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 22:
			App->lvlManage->lvlChange(3, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 23:
			App->lvlManage->lvlChange(4, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 44:
			App->lvlManage->lvlChange(5, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 50:
			App->lvlManage->lvlChange(6, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status LevelMenu::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, &rectbg, 1.0f, true, 3);
	App->render->Blit(bgTexture, rectbg.w*3, 0, &rectbg, 1.0f, true, 3);
	App->render->Blit(bgTexture, rectbg.w*3*2, 0, &rectbg, 1.0f, true, 3);
	App->render->Blit(bgTexture, (App->winSize->w-(rectlvls.w*4))/2 , 111*4, &rectlvls, 1.0f, true, 4);
	return Update_Status::UPDATE_CONTINUE;
}

bool LevelMenu::CleanUp()
{
	App->pointer->Disable();
	return true;
}