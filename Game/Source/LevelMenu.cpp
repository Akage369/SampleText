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
#include "ModuleFonts.h"


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

	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	FontText = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);
	App->audio->PlayMusic("Assets/Audio/Music/levelsMusic.ogg");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->lvlManage->changeScene = true;

	return ret;
}

Update_Status LevelMenu::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 20);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || (pad.a == KEY_DOWN))
	{
		switch (App->pointer->index) {
		case 1:
			App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
			App->lvlManage->lvlChange(1, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 10:
			App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
			App->lvlManage->lvlChange(2, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 22:
			App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
			App->lvlManage->lvlChange(3, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 23:
			App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
			App->lvlManage->lvlChange(4, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 44:
			App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
			App->lvlManage->lvlChange(5, '=');
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
			break;
		case 50:
			App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
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
	App->render->Blit(bgTexture, rectbg.w * 3, 0, &rectbg, 1.0f, true, 3);
	App->render->Blit(bgTexture, rectbg.w * 3 * 2, 0, &rectbg, 1.0f, true, 3);
	App->render->Blit(bgTexture, (App->winSize->w - (rectlvls.w * 4)) / 2, 111 * 4, &rectlvls, 1.0f, true, 4);
	App->render->Blit(bgTexture, (App->winSize->w - (rectTop.w * 4)) / 2, 4 * 4, &rectTop, 1.0f, true, 4);
	App->render->Blit(bgTexture, (App->winSize->w - (rectDown.w * 4)) / 2, 84 * 4, &rectDown, 1.0f, true, 4);
	App->render->Blit(bgTexture, (App->winSize->w - (rectD.w * 4)) / 2, 196 * 4 + 10*4, &rectD, 1.0f, true, 4);
	App->fonts->BlitText((App->winSize->w - text.w * 3) / 2 + 14 * 3 - 5 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3 - 130 * 3, FontText, "LEVELS FROM", 3, 0, 0, 0, App->winSize->w, 3);
	App->fonts->BlitText((App->winSize->w - text.w * 3) / 2 + 14 * 3 + 10 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3 - 130 * 3, FontText, "|1 TO 50", 3, 0, 0, 0, App->winSize->w, 3);
	App->fonts->BlitText((App->winSize->w - text.w * 3) / 2 + 14 * 3 - 11 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3 - 110 * 3, FontText, "||ONLY PLAYABLE", 3, 0, 0, 0, App->winSize->w, 3);
	App->fonts->BlitText((App->winSize->w - text.w * 3) / 2 + 14 * 3 + 0 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3 - 100 * 3, FontText, "||THE LEVELS", 3, 0, 0, 0, App->winSize->w, 3);
	App->fonts->BlitText((App->winSize->w - text.w * 3) / 2 + 14 * 3 - 20 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3 - 90 * 3, FontText, "||PAINTED IN YELLOW", 3, 0, 0, 0, App->winSize->w, 3);


	App->fonts->BlitText((App->winSize->w - text.w * 3) / 2 + 14 * 3 - 15 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3 - 22 * 3, FontText, "LEVEL SELECTOR", 3, 0, 0, 0, App->winSize->w, 3);

	App->fonts->BlitText((App->winSize->w - text.w * 3) / 2 + 14 * 3 - 7 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3 + 127 * 3 + 10 * 4, FontText, "JZN22QAK8Y4J", 3, 0, 0, 0, App->winSize->w, 3);

	return Update_Status::UPDATE_CONTINUE;
}

bool LevelMenu::CleanUp()
{
	App->pointer->Disable();
	return true;
}