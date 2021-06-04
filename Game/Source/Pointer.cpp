#include "ModulePlayer.h"
#include "Pointer.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneLevel1.h"

#include "Tiles.h"
#include "LevelManager.h"

#include "SDL/include/SDL.h"

#include <stdio.h>


Pointer::Pointer(bool startEnabled) : Module(startEnabled)
{

}



bool Pointer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	texture = App->textures->Load("Assets/Textures/spritesheet_menus.png");
	pointRect = { 16, 361, 9, 9 };
	position.x = 42 * 3;
	position.y = 111 * 3;
	index = 1;

	return ret;
}



Update_Status Pointer::Update()
{


	currentTime = SDL_GetTicks();
	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		firstInput_A = true;
	}
	if (position.x >= 42 * 3) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_A == true) {

				if (position.y >= 111 * 3) {
					if (position.x == 42 * 3) {
						if (position.y > 111 * 3) {
							position.x = 186 * 3;
							position.y -= 16 * 3;
							index--;
						}
					}
					else {
						position.x -= 16 * 3;
						index--;
					}
					lastTime_A = SDL_GetTicks();
					delay_A = 500;
					firstInput_A = false;
				}
			}
			else if (currentTime > lastTime_A + delay_A) {
				delay_A = 50;
				
				if (position.y >= 111 * 3) {
					if (position.x == 42 * 3) {
						if (position.y > 111 * 3) {
							position.x = 186 * 3;
							position.y -= 16 * 3;
							index--;
						}
					}
					else {
						position.x -= 16 * 3;
						index--;
					}
				
					lastTime_A = currentTime;
					
				}
			}
		}
	}

	if ((App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		firstInput_D = true;
	}
	if (position.x <= 186 * 3) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_D == true) {
				if (position.x == 186 * 3 && position.y <= 159 * 3) {
					position.x = 42 * 3;
					position.y += 16 * 3;
					index++;
				}
				else if (position.y > 159 * 3 && position.x > 170 * 3) {

				}
				else {
					position.x += 16 * 3;
					index++;
				}
				lastTime_D = SDL_GetTicks();
				delay_D = 500;
				firstInput_D = false;
			}
			else if (currentTime > lastTime_D + delay_D) {
				delay_D = 50;
			
				if (position.x == 186 * 3 && position.y <= 159 * 3) {
					position.x = 42 * 3;
					position.y += 16 * 3;
					index++;
				}
				else if (position.y > 159 * 3 && position.x > 170 * 3) {

				}
				else {
					position.x += 16 * 3;
					index++;
				}
			
				lastTime_D = currentTime;

			}

		}
	}


	if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		firstInput_S = true;
	}
	if (position.y <= 159 * 3) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_S == true) {
				position.y += 16 * 3;
				index+=10;
				lastTime_S = SDL_GetTicks();
				delay_S = 500;
				firstInput_S = false;
			}
			else if (currentTime > lastTime_S + delay_S) {
				delay_S = 50;
	
				position.y += 16 * 3;
				index += 10;
				lastTime_S = currentTime;
			}

		}
	}

	if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE))
	{
		firstInput_W = true;
	}
	if (position.y >= 127 * 3) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT))
		{
			if (firstInput_W == true) {
				position.y -= 16 * 3;
				index -= 10;
				lastTime_W = SDL_GetTicks();
				delay_W = 500;
				firstInput_W = false;
			}
			else if (currentTime > lastTime_W + delay_W) {
				delay_W = 50;
		
				position.y -= 16 * 3;
				index -= 10;
		
				lastTime_W = currentTime;
	



			}

		}
	}

	if (position.x == 42 * 3 && position.y == 127 * 3) {
	//	index = 1;
	}

	if (position.x == 90 * 3 && position.y == 127 * 3) {
	//	index = 2;
	}

	if (position.x == 58 * 3 && position.y == 127 * 3) {
		//index = 3;
	}

	if (position.x == 42 * 3 && position.y == 127 * 3) {
	//	index = 4;
	}

	if (position.x == 42 * 3 && position.y == 127 * 3) {
		//index = 5;
	}

	if (position.x == 42 * 3 && position.y == 127 * 3) {
		//index = 6;
	}

	return Update_Status::UPDATE_CONTINUE;
}



Update_Status Pointer::PostUpdate()
{

	App->render->Blit(texture, position.x, position.y, &pointRect, 0.0f, true, 3);
	return Update_Status::UPDATE_CONTINUE;
}



