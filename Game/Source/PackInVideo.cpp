#include "SceneIntro.h"
#include "PackInVideo.h"
#include "Presentation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "LevelManager.h"
#include "ModuleWindow.h"
#include "WindowSize.h"
#include "ModuleFonts.h"

PackInVideo::PackInVideo(bool startEnabled) : Module(startEnabled)
{

}

PackInVideo::~PackInVideo()
{

}

bool PackInVideo::Start()
{
	LOG("Loading background assets");
	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	scoreFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);
	bool ret = true;

	bgTexture = App->textures->Load("Assets/Textures/spritesheet_menus.png");



	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->lvlManage->changeScene = true;
	zoom = 4;

	return ret;
}

Update_Status PackInVideo::Update()
{
	if (App->lvlManage->godmode == true) {
		if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
			App->fade->FadeToBlack(this, (Module*)App->presentation, 20);
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{


		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 20);

	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status PackInVideo::PostUpdate()
{
	App->render->Blit(bgTexture, (App->winSize->w - rect.w *zoom)/2, (App->winSize->h- rect.h *zoom)/2,&rect, 1.0f, true, zoom);
	if (App->lvlManage->godmode == true) {
		App->fonts->BlitText(App->winSize->w / 2 - 4 * 9 * 3, App->winSize->h - 50 * 3, scoreFont, "GOD MODE", 3, 158, 75, 250, (App->winSize->w - 98 * 3) / 2 + 98 * 3 - 5 * 3);
	}

	return Update_Status::UPDATE_CONTINUE; 
}

bool PackInVideo::CleanUp()
{
	App->packInVideo->Disable();
	App->fonts->UnLoad(0);

	return true;
}