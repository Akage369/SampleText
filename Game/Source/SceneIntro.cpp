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
#include "ModuleFonts.h"
#include "WindowSize.h"

#include "SDL/include/SDL.h"


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
	//if (App->audio->IsEnabled() == false) {
		//App->audio->Enable();
	//}

	introMenu = App->textures->Load("Assets/Textures/spritesheet_menus.png");
	App->audio->PlayMusic("Assets/Audio/Music/introTitle.ogg", 1.0f);

	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	optFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	scrollerY =0;
	scroller2Y =scrollers.h*3;
	scroller3Y = -scrollers.h*3;

	p_pos.x = p_x;
	p_pos.y = p_y;


	App->lvlManage->changeScene = true;

	zoom = 4;
	tope = 50;
	optIndex = 0;
	nextScene = false;
	titleY = (App->winSize->h - title.h * 3) / 2;
	lastTime = SDL_GetTicks();

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->lvlManage->godmode == true) {
		if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
			App->fade->FadeToBlack(this, (Module*)App->introAnim, 20);
		}
	}
	currentTime = SDL_GetTicks();
	if (currentTime > lastTime + delay) {
		if (titleY > tope * zoom) {
			titleY -= 1;
		}

		scrollerY += 1;
		scroller2Y += 1;
		scroller3Y += 1;

		if (scrollerY == scrollers.h * 3) {
			scrollerY = 0;
		}
		if (scroller2Y == scrollers.h * 2 * 3) {
			scroller2Y = scrollers.h * 3;
		}
		if (scroller3Y == 0) {
			scroller3Y = -scrollers.h * 3;
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		if (titleY > tope * zoom) {
			titleY = tope * zoom;
		}
		else {
			switch (optIndex) {
			case 0:
				App->fade->FadeToBlack(this, (Module*)App->levelMenu, 20);
				break;
			case 1:
				App->fade->FadeToBlack(this, (Module*)App->introAnim, 20);
				break;
			case 2:
				return Update_Status::UPDATE_STOP;
				break;
			}
		}
	}
	if (titleY == tope * zoom) {

		if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN))
		{
			firstInput_W = true;
		}

		if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT))
		{
			if (firstInput_W == true) {
				if (optIndex > 0) {
					optIndex -= 1;
				}
				else {
					optIndex = 2;
				}
				lastTime_W = SDL_GetTicks();
				delay_W = 500;
				firstInput_W = false;
			}
			else if (currentTime > lastTime_W + delay_W) {
				if (optIndex > 0) {
					optIndex -= 1;
				}
				else {
					optIndex = 2;
				}
				lastTime_W = SDL_GetTicks();
				delay_W = 150;
				lastTime_W = currentTime;

			}
		}

		if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			firstInput_S = true;
		}
		if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_S == true) {

				if (optIndex < 2) {
					optIndex += 1;
				}
				else {
					optIndex = 0;
				}

				lastTime_S = SDL_GetTicks();
				delay_S = 500;
				firstInput_S = false;
			}
			else if (currentTime > lastTime_S + delay_S) {
				if (optIndex < 2) {
					optIndex += 1;
				}
				else {
					optIndex = 0;
				}
				lastTime_S = SDL_GetTicks();
				delay_S = 150;
				lastTime_S = currentTime;

			}
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneIntro::PostUpdate()
{
	App->render->Blit(introMenu, 0, -scrollerY, &scrollers, 1.0f, true, 3);
	App->render->Blit(introMenu, 0, -(scrollerY-scrollers.h*3), &scrollers, 1.0f, true, 3);
	App->render->Blit(introMenu, scrollers.w*3, -scrollerY, &scrollers, 1.0f, true, 3);
	App->render->Blit(introMenu, scrollers.w*3, -(scrollerY - scrollers.h * 3), &scrollers, 1.0f, true, 3);
	App->render->Blit(introMenu, scrollers.w*2*3, -scrollerY, &scrollers, 1.0f, true, 3);
	App->render->Blit(introMenu, scrollers.w*2*3, -(scrollerY - scrollers.h * 3), &scrollers, 1.0f, true, 3);

	App->render->Blit(introMenu, (App->winSize->w-title.w*zoom-33*zoom)/2, titleY, &title, 1.0f, true, zoom);

	App->render->Blit(introMenu, (App->winSize->w - copyright.w * zoom) / 2, titleY+ title.h*zoom +60*zoom, &copyright, 1.0f, true, zoom);
	if (titleY<= tope *zoom) {
		App->render->Blit(introMenu, (App->winSize->w -options.w* zoomText)/2 - 5 * zoomText, titleY + title.h * zoomText + 6 * zoomText , &options, 1.0f, true, zoomText);
		switch (optIndex) {
		case 0:
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText , titleY + title.h * zoomText  + 13 * zoomText , optFont, "PLAY", zoomText, 214, 0, 0, App->winSize->w, zoomText);
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText , titleY + title.h * zoomText + 13 * zoomText, optFont, "|REPEAT INTRO", zoomText, 16, 16, 24, App->winSize->w, zoomText);
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText , titleY + title.h * zoomText  + 13 * zoomText, optFont, "||QUIT", zoomText, 16, 16, 24, App->winSize->w, zoomText);
			App->render->Blit(introMenu, (App->winSize->w - options.w * zoomText) / 2 + 1 * zoomText, titleY + title.h * zoomText +12 * zoomText, &pointRect, 0.0f, true, zoomText);
			break;
		case 1:
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText , titleY + title.h * zoomText + 13 * zoomText, optFont, "PLAY", zoomText, 16, 16, 24, App->winSize->w, zoomText);
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText , titleY + title.h * zoomText + 13 * zoomText , optFont, "|REPEAT INTRO", zoomText, 214, 0, 0, App->winSize->w, zoomText);
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText , titleY + title.h * zoomText + 13 * zoomText, optFont, "||QUIT", zoomText, 16, 16, 24, App->winSize->w, zoomText);
			App->render->Blit(introMenu, (App->winSize->w - options.w * zoomText) / 2 + 1 * zoomText, titleY + title.h * zoomText + 24 * zoomText, &pointRect, 0.0f, true, zoomText);
			break;
		case 2:
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText , titleY + title.h * zoomText + 13 * zoomText, optFont, "PLAY", zoomText, 16, 16, 24, App->winSize->w, zoomText);
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText , titleY + title.h * zoomText + 13  * zoomText, optFont, "|REPEAT INTRO", zoomText, 16, 16, 24, App->winSize->w, zoomText);
			App->fonts->BlitText((App->winSize->w - options.w * zoomText) / 2 + 10 * zoomText, titleY + title.h * zoomText + 13 * zoomText, optFont, "||QUIT", zoomText, 214, 0, 0, App->winSize->w, zoomText);
			App->render->Blit(introMenu, (App->winSize->w - options.w * zoomText) / 2 + 1 * zoomText , titleY + title.h * zoomText + 36 * zoomText, &pointRect, 0.0f, true, zoomText);
			break;
		}
	}

	if (App->lvlManage->godmode == true) {
		App->fonts->BlitText(App->winSize->w / 2 - 4 * 9 * 3, App->winSize->h - 50 * 3, scoreFont, "GOD MODE", 3, 158, 75, 250, (App->winSize->w - 98 * 3) / 2 + 98 * 3 - 5 * 3);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->textures->Unload(introMenu);
	//App->audio->Disable();
	App->sceneIntro->Disable();
	App->fonts->UnLoad(optFont);
	
	return true;
}