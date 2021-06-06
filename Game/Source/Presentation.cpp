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
#include "ModuleFonts.h"
#include "WindowSize.h"
#include "SDL/include/SDL.h"

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
	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	scoreFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	
	SDL_QueryTexture(bgTexture, NULL, NULL, &w, &h);

	App->lvlManage->changeScene = true;

	return ret;
}

Update_Status Presentation::Update()
{
	if (App->lvlManage->godmode == true) {
		if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			App->lvlManage->lvlChange(6, '=');
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{


		App->fade->FadeToBlack(this, (Module*)App->packInVideo, 20);
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Presentation::PostUpdate()
{
	App->render->Blit(bgTexture,( App->winSize->w-w*2)/2, (App->winSize->h - h * 2) / 2, NULL, 1.0F,true,2);

	if (App->lvlManage->godmode == true) {
		App->fonts->BlitText(App->winSize->w / 2 - 4 * 9 * 3, App->winSize->h - 50 * 3, scoreFont, "GOD MODE", 3, 158, 75, 250, (App->winSize->w - 98 * 3) / 2 + 98 * 3 - 5 * 3);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool Presentation::CleanUp()
{
	App->textures->Unload(bgTexture);
	
	App->fonts->UnLoad(scoreFont);
	App->presentation->Disable();

	return true;
}