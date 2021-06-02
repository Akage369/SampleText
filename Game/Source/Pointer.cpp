#include "ModulePlayer.h"
#include "Pointer.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneLevel1.h"
///Tiles
#include "Tiles.h"
#include "LevelManager.h"

#include "SDL/include/SDL.h"

#include <stdio.h>


Pointer::Pointer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite

	//pointAnim.PushBack({ 16, 361, 9, 9 });
}



bool Pointer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	///Lookup table
	//char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };

	//scoreFont = App->fonts->Load("Assets/Textures/rtype_font3.png", lookupTable, 2);


	texture = App->textures->Load("Assets/Textures/spritesheet_menus.png");
	//currentAnimation = &pointAnim;
	pointRect = { 16, 361, 9, 9 };
	position.x = 42;
	position.y = 111;
	//laserFx = App->audio->LoadFx("Assets/Audio/Fx/laser.wav");
	//explosionFx = App->audio->LoadFx("Assets/Audio/Fx/explosion.wav");




	return ret;
}



Update_Status Pointer::Update()
{


	currentTime = SDL_GetTicks();
	//KEY_REPEAT
	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		firstInput_A = true;
	}
	if (position.x >= 42) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			//firstInput = true;
			/*frameStart = SDL_GetTicks();
			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);

		}*/
			if (firstInput_A == true) {

				if (position.x == 42) {
					position.x = 186;
					position.y -= 16;
				}
				else {
					position.x -= 16;
				}
				lastTime_A = SDL_GetTicks();
				delay_A = 500;
				firstInput_A = false;
			}
			else if (currentTime > lastTime_A + delay_A) {
				delay_A = 50;
				//if (firstInput == false) {
				if (position.x == 42) {
					position.x = 186;
					position.y -= 16;
				}
				else {
					position.x -= 16;
				}
				//}
				//currentTime = SDL_GetTicks();
				lastTime_A = currentTime;
				//frameStart = SDL_GetTicks();



			}

		}


	}
	if ((App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		firstInput_D = true;
	}
	if (position.x <= 186) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_D == true) {
				if (position.x == 186) {
					position.x = 42;
					position.y += 16;
				}
				else {
					position.x += 16;
				}
				lastTime_D = SDL_GetTicks();
				delay_D = 500;
				firstInput_D = false;
			}
			else if (currentTime > lastTime_D + delay_D) {
				delay_D = 50;
				//if (firstInput == false) {
				if (position.x == 186) {
					position.x = 42;
					position.y += 16;
				}
				else {
					position.x += 16;
				}
				//}
				//currentTime = SDL_GetTicks();
				lastTime_D = currentTime;
				//frameStart = SDL_GetTicks();



			}

		}
	}


	if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		firstInput_S = true;
	}
	if (position.y <= 159) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_S == true) {
				position.y += 16;
				lastTime_S = SDL_GetTicks();
				delay_S = 500;
				firstInput_S = false;
			}
			else if (currentTime > lastTime_S + delay_S) {
				delay_S = 50;
				//if (firstInput == false) {
				position.y += 16;
				//}
				//currentTime = SDL_GetTicks();
				lastTime_S = currentTime;
				//frameStart = SDL_GetTicks();



			}

		}
	}

	if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE))
	{
		firstInput_W = true;
	}
	if (position.y >= 127) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT))
		{
			if (firstInput_W == true) {
				position.y -= 16;
				lastTime_W = SDL_GetTicks();
				delay_W = 500;
				firstInput_W = false;
			}
			else if (currentTime > lastTime_W + delay_W) {
				delay_W = 50;
				//if (firstInput == false) {
				position.y -= 16;
				//}
				//currentTime = SDL_GetTicks();
				lastTime_W = currentTime;
				//frameStart = SDL_GetTicks();



			}

		}
	}

	return Update_Status::UPDATE_CONTINUE;
}



Update_Status Pointer::PostUpdate()
{

	

	// Draw UI (score) --------------------------------------
	//sprintf_s(scoreText, 10, "%7d", App->lvlManage->steps);





	// TODO 3: Blit the text of the score in at the bottom of the screen
	//App->fonts->BlitText(58, 248, scoreFont, scoreText);

	/*if (App->lvlManage->win == 0) {
		App->fonts->BlitText(150, 248, scoreFont, " ");
	}
	else if (App->lvlManage->win == 1) {

		App->fonts->BlitText(150, 248, scoreFont, "you win!");
	}
	else if (App->lvlManage->win == 2) {
		App->fonts->BlitText(150, 248, scoreFont, "you lose!");
	}



	*/
	App->render->Blit(texture, position.x, position.y, &pointRect, 0.0f, true);
	return Update_Status::UPDATE_CONTINUE;
}



