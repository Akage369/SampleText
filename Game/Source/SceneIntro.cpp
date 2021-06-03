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

	
	scroller1 = App->textures->Load("Assets/Textures/spritesheet_intro_fondo.png");
	bgTexto = App->textures->Load("Assets/Textures/spritesheet_intro_texto.png");
	puntero = App->textures->Load("Assets/Textures/puntero");
	scroller2 = App->textures->Load("Assets/Textures/spritesheet_intro_fondo.png");
	introMenu = App->textures->Load("Assets/Textures/spritesheet_menus.png");
	BoxMenu = App->textures->Load("Assets/Textures/menu_caja");
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

	MenuMusic = App->audio->PlayMusic("Assets/Music/MenuMusic", 1.0f); //Falta por determinar sonido
	selectFx = App->audio->LoadFx("Assets"); //Falta por determinar sonido
	nextFx = App->audio->LoadFx("Assets"); //Falta por determinar sonido
	backFx = App->audio->LoadFx("Assets"); //Falta por determinar sonido

	App->lvlManage->changeScene = true;

	optIndex = 0;
	nextScene = false;
	titleY = (SCREEN_HEIGHT - title.h * 3) / 2;
	lastTime = SDL_GetTicks();

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->packInVideo, 20);
	}

	currentTime = SDL_GetTicks();
	if (currentTime > lastTime + delay) {
		if (titleY > 4 * 3) {
			titleY -= 1;
		}

		scrollerY += 1;
		scroller2Y += 1;
		scroller3Y += 1;
		//Condición scroll
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
	//input teclas
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		if (titleY > 4 * 3) {
			titleY = 4 * 3;
		}
		else {
			//App->audio->PlayFx(selectFx);
			switch (optIndex) {
			case 0:
				App->fade->FadeToBlack(this, (Module*)App->levelMenu, 20);
				break;
			case 1:
				break;
			case 2:
				return Update_Status::UPDATE_STOP;
				break;
			}
			
			//lvl++;
			//App->player->spawn(lvl);

			////CAMBIO PARA AVANZAR AL MENU DE NIVELES

			//if (nextScene == false) {
			//	nextScene = true;
			//	App->lvlManage->lvlChange(1, '+');

			//}
		}
		
	}
	if (titleY == 4 * 3) {
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
	/*
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN)
	{
		if (titleY == 4 * 3) {
			lastTime_W = SDL_GetTicks();

			if (optIndex > 0) {
				optIndex -= 1;
			}
			else {
				optIndex = 2;
			}
		}
	}
	*/
	/*
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{
		lastTime_S = SDL_GetTicks();
		if (titleY == 4 * 3) {
			if (optIndex < 2) {
				optIndex += 1;
			}
			else {
				optIndex = 0;
			}
		}
	}
	*/
	

	//if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) {
	//	if (M_index < 2) {
	//		M_index++;
	//		p_y -= 13;
	//		App->audio->PlayFx(selectFx);
	//	}
	//}
	//if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) {
	//	if (M_index > 0) {
	//		M_index--;
	//		p_y += 13;
	//		App->audio->PlayFx(selectFx);
	//	}
	//}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	///App->render->Blit(introMenu, 0, scroller3Y*3, &scrollers, 1.0f, true, 3);
	////App->render->Blit(introMenu, 0, scroller2Y * 3, &scrollers, 1.0f, true, 3);
	//App->render->Blit(introMenu, scrollers.w*3, scroller3Y*3, &scrollers, 1.0f, true, 3);
	///App->render->Blit(introMenu, scrollers.w*2, scroller3Y, &scrollers, 1.0f, true, 3);
	//App->render->Blit(introMenu, scrollers.w, scroller3Y, &scrollers, 1.0f, true, 1);
	//App->render->Blit(introMenu, scrollers.w * 2, scroller3Y, &scrollers, 1.0f, true, 1);
	///App->render->Blit(introMenu, 0, scrollerY, &scrollers, 1.0f, true, 1);
	///App->render->Blit(introMenu, scrollers.w, scrollerY, &scrollers, 1.0f, true, 1);
	///App->render->Blit(introMenu, scrollers.w*2, scrollerY, &scrollers, 1.0f, true, 1);
	//App->render->Blit(introMenu, scrollers.w, scrollerY, &scrollers,  1.0f, true, 1);
	//App->render->Blit(introMenu, scrollers.w*2, scrollerY, &scrollers, 1.0f, true, 1);
	///App->render->Blit(introMenu, scrollers.w*2, scroller2Y, &scrollers, 1.0f, true, 1);
	//App->render->Blit(introMenu, scrollers.w,scroller2Y, &scrollers, 1.0f, true, 1);
	//App->render->Blit(introMenu, scrollers.w*2, scroller2Y, &scrollers, 1.0f, true, 1);

	App->render->Blit(introMenu, 0, -scrollerY, &scrollers, 1.0f, true, 3);
	App->render->Blit(introMenu, 0, -(scrollerY-scrollers.h*3), &scrollers, 1.0f, true, 3);

	//App->render->Blit(introMenu, 255, scrollerY, &scrollers);
	//App->render->Blit(introMenu, 255, scroller2Y, &scrollers);
	//App->render->Blit(introMenu, (SCREEN_WIDTH-title.w*3)/2, titleY, &title, 1.0f, true, 3);
	//App->render->Blit(introMenu, 9*3, titleY, &title, 1.0f, true, 3);
	App->render->Blit(introMenu, 9*3, titleY, &title, 1.0f, true, 3);
	//App->render->Blit(bgTexto, 140, 125, NULL);
	
	//App->fonts->BlitText(0,titleY + 61*3, scoreFont, "YOU LOSE!SPACE TO TRY AGAIN", 3, 0, 0, 0, (SCREEN_WIDTH - rectlose.w * 3) / 2 + rectlose.w * 3 - 45 * 3, 3);
	App->render->Blit(introMenu, (SCREEN_WIDTH - copyright.w * 3) / 2, titleY+ title.h*3 + 62*3, &copyright, 1.0f, true, 3);
	if (titleY<=4*3) {
		App->render->Blit(introMenu, (SCREEN_WIDTH-options.w*3)/2, titleY + title.h * 3 + 6 * 3, &options, 1.0f, true, 3);
		switch (optIndex) {
		case 0:
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "PLAY", 3, 214, 0, 0, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "|REPEAT INTRO", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "||QUIT", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->render->Blit(introMenu, (SCREEN_WIDTH - options.w * 3) / 2 + 5 * 3, titleY + title.h * 3 + 6 * 3 + 7 * 3, &pointRect, 0.0f, true, 3);
			break;
		case 1:
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "PLAY", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "|REPEAT INTRO", 3, 214, 0, 0, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "||QUIT", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->render->Blit(introMenu, (SCREEN_WIDTH - options.w * 3) / 2 + 5 * 3, titleY + title.h * 3 + 6 * 3 + 18 * 3, &pointRect, 0.0f, true, 3);
			break;
		case 2:
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "PLAY", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "|REPEAT INTRO", 3, 16, 16, 24, SCREEN_WIDTH, 3);
			App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2 + 14 * 3, titleY + title.h * 3 + 6 * 3 + 8 * 3, optFont, "||QUIT", 3, 214, 0, 0, SCREEN_WIDTH, 3);
			App->render->Blit(introMenu, (SCREEN_WIDTH - options.w * 3) / 2 + 5 * 3, titleY + title.h * 3 + 6 * 3 + 29 * 3, &pointRect, 0.0f, true, 3);
			break;
		}
	
	}
	//App->fonts->BlitText((SCREEN_WIDTH - options.w * 3) / 2+14*3, titleY + title.h * 3 + 6 * 3 + 9*3, optFont, "PLAY REPEAT INTRO QUIT", 3, 255, 255, 255);
	
	//App->render->Blit(bgTexture, SCREEN_WIDTH / 2 - 115, SCREEN_HEIGHT / 2 - 120, NULL);
	App->render->Blit(puntero, p_x, p_y, NULL);

	//App->fonts->BlitText(SCREEN_WIDTH / 2 -20, 150)

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->sceneIntro->Disable();
	App->fonts->UnLoad(0);
	
	return true;
}