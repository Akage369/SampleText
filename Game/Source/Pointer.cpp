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
#include "WindowSize.h"
#include "LevelMenu.h"

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
	zoom = 4;
	
	position.x = (App->winSize->w - App->levelMenu->rectlvls.w*zoom)/2 - 6* zoom;

	position.y = 112 * zoom;
	index = 1;

	

	return ret;
}



Update_Status Pointer::Update()
{
	GamePad& pad = App->input->pads[0];

	currentTime = SDL_GetTicks();
	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE) || ((pad.left == KEY_DOWN) || (pad.left_x < 0.0f)))
	{
		firstInput_A = true;
		
	}
	if (position.x >= (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE) || ((pad.left == KEY_REPEAT) || (pad.left_x < 0.0f)))
		{
			if (firstInput_A == true) {

				if (position.y >= 112 * zoom) {
					if (position.x == (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom) {
						if (position.y > 112 * zoom) {
							position.x = (App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom;
							position.y -= 16 * zoom;
							index--;
							
								App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
								lastTimePunt = currentTime;
							
						}
					}
					else {
						position.x -= 16 * zoom;
						index--;
						
							App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
							lastTimePunt = currentTime;
						
					}
					lastTime_A = SDL_GetTicks();
					delay_A = 500;
					firstInput_A = false;
				}
			}
			else if (currentTime > lastTime_A + delay_A) {
				delay_A = 50;
				
				if (position.y >= 112 * zoom) {
					if (position.x == (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom) {
						if (position.y > 112 * zoom) {
							position.x = (App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom;
							position.y -= 16 * zoom;
							index--;
							if (currentTime >= lastTimePunt + delayPunt) {
								App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
								lastTimePunt = currentTime;
							}
						}
					}
					else {
						position.x -= 16 * zoom;
						index--;
						if (currentTime >= lastTimePunt + delayPunt) {
							App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
							lastTimePunt = currentTime;
						}
					}
				
					lastTime_A = currentTime;
					
				}
			}
		}
	}

	if ((pad.left == 0) && (pad.left_x == 0.0f))
	{
		StopPad_A = false;

	}
	if (position.x >= (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom) {
		if ((pad.left == KEY_DOWN) || (pad.left_x < 0.0f))
		{
			if (firstInput_A == true) {

				if (position.y >= 112 * zoom) {
					if (position.x == (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom) {
						if (position.y > 112 * zoom) {
							position.x = (App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom;
							position.y -= 16 * zoom;
							index--;

							App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
							lastTimePunt = currentTime;

						}
					}
					else {
						position.x -= 16 * zoom;
						index--;

						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;

					}
					lastTime_A = currentTime + 500;
					delay_A = 500;
					StopPad_A = true;
				}
			}
			else if (currentTime > lastTime_A + 50) {
				delay_A = 50;

				if (position.y >= 112 * zoom) {
					if (position.x == (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom) {
						if (position.y > 112 * zoom) {
							position.x = (App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom;
							position.y -= 16 * zoom;
							index--;
							if (currentTime >= lastTimePunt + delayPunt) {
								App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
								lastTimePunt = currentTime;
							}
						}
					}
					else {
						position.x -= 16 * zoom;
						index--;
						if (currentTime >= lastTimePunt + delayPunt) {
							App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
							lastTimePunt = currentTime;
						}
					}

					lastTime_A = SDL_GetTicks();
					delay_A = 150;
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
	if (position.x <= ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom)) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_D == true) {
				if (position.x ==( (App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom )&& position.y <= 160 * zoom) {
					position.x = (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom;
					position.y += 16 * zoom;
					index++;
					
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					
				}
				else if (position.y > 160 * zoom && position.x > ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * 2 * zoom)) {

				}
				else {
					position.x += 16 * zoom;
					index++;
					
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					
				}
				lastTime_D = SDL_GetTicks();
				delay_D = 500;
				firstInput_D = false;
			}
			else if (currentTime > lastTime_D + delay_D) {
				delay_D = 50;
			
				if (position.x == ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom) && position.y <= 160 * zoom) {
					position.x = (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom;
					position.y += 16 * zoom;
					index++;
					if (currentTime >= lastTimePunt + delayPunt) {
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					}
					
				}
				else if (position.y > 160 * zoom && position.x > ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * 2*zoom)) {

				}
				else {
					position.x += 16 * zoom;
					index++;
					if (currentTime >= lastTimePunt + delayPunt) {
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					}
					//App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				}
			
				lastTime_D = currentTime;

			}

		}
	}

	if ((pad.right == 0) && (pad.left_x == 0.0f))
	{
		StopPad_D = false;

	}
	if (position.x <= ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom)) {
		if ((pad.right == KEY_DOWN) || (pad.left_x > 0.0f))
		{
			if (StopPad_D == false) {
				if (position.x == ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom) && position.y <= 160 * zoom) {
					position.x = (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom;
					position.y += 16 * zoom;
					index++;

					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;

				}
				else if (position.y > 160 * zoom && position.x > ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * 2 * zoom)) {

				}
				else {
					position.x += 16 * zoom;
					index++;

					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;

				}
				lastTime_D = currentTime + 500;
				delay_D = 500;
				StopPad_D = true;
			}
			else if (currentTime > lastTime_D + 50) {
				delay_D = 50;

				if (position.x == ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * zoom) && position.y <= 160 * zoom) {
					position.x = (App->winSize->w - App->levelMenu->rectlvls.w * zoom) / 2 - 6 * zoom;
					position.y += 16 * zoom;
					index++;
					if (currentTime >= lastTimePunt + delayPunt) {
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					}

				}
				else if (position.y > 160 * zoom && position.x > ((App->winSize->w + App->levelMenu->rectlvls.w * zoom) / 2 - 7 * zoom - 16 * 2 * zoom)) {

				}
				else {
					position.x += 16 * zoom;
					index++;
					if (currentTime >= lastTimePunt + delayPunt) {
						App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
						lastTimePunt = currentTime;
					}
					//App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				}

				lastTime_D = SDL_GetTicks();
				delay_D = 150;
				lastTime_D = currentTime;

			}

		}
	}


	if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		firstInput_S = true;
		
	}
	if (position.y <= 160 * zoom) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
		{
			if (firstInput_S == true) {
				position.y += 16 * zoom;
				index+=10;
				
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;
				
				lastTime_S = SDL_GetTicks();
				delay_S = 500;
				firstInput_S = false;
			}
			else if (currentTime > lastTime_S + delay_S) {
				delay_S = 50;
	
				position.y += 16 * zoom;
				index += 10;
				if (currentTime >= lastTimePunt + delayPunt) {
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;
				}
				lastTime_S = currentTime;
			}

		}
	}

	if ((pad.down == 0) && (pad.left_y == 0.0f))
	{
		StopPad_S = false;

	}
	if (position.y <= 160 * zoom) {
		if ((pad.down == KEY_DOWN) || (pad.left_y > 0.0f))
		{
			if (StopPad_S == false) {
				position.y += 16 * zoom;
				index += 10;

				App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				lastTimePunt = currentTime;

				lastTime_S = currentTime + 500;
				delay_S = 500;

				StopPad_S = true;
			}
			else if (currentTime > lastTime_S + 50) {
				delay_S = 50;

				position.y += 16 * zoom;
				index += 10;
				if (currentTime >= lastTimePunt + delayPunt) {
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;
				}
				lastTime_S = SDL_GetTicks();
				delay_S = 150;
				lastTime_S = currentTime;

			}

		}
	}

	if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE))
	{
		firstInput_W = true;
		
	}
	if (position.y >= 128 * zoom) {
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT))
		{
			if (firstInput_W == true) {
				position.y -= 16 * zoom;
				index -= 10;
				
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;
				
				lastTime_W = SDL_GetTicks();
				delay_W = 500;
				firstInput_W = false;
			}
			else if (currentTime > lastTime_W + delay_W) {
				delay_W = 50;
		
				position.y -= 16 * zoom;
				index -= 10;
				if (currentTime >= lastTimePunt + delayPunt) {
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;
				}
		
				lastTime_W = currentTime;
			}

		}
	}

	if ((pad.up == 0) && (pad.left_y == 0.0f))
	{
		StopPad_W = false;

	}
	if (position.y >= 128 * zoom) {
		if ((pad.up == KEY_DOWN) || (pad.left_y < 0.0f))
		{
			if (StopPad_W == false) {
				position.y -= 16 * zoom;
				index -= 10;

				App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				lastTimePunt = currentTime;

				lastTime_W = currentTime + 500;
				delay_W = 500;
				
				StopPad_W = true;
			}
			else if (currentTime > lastTime_W + 50) {
				delay_W = 50;

				position.y -= 16 * zoom;
				index -= 10;
				if (currentTime >= lastTimePunt + delayPunt) {
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
					lastTimePunt = currentTime;
				}

				lastTime_W = SDL_GetTicks();
				delay_W = 150;
				lastTime_W = currentTime;
				
			}

		}
	}

	return Update_Status::UPDATE_CONTINUE;
}



Update_Status Pointer::PostUpdate()
{

	App->render->Blit(texture, position.x, position.y, &pointRect, 0.0f, true, zoom);
	return Update_Status::UPDATE_CONTINUE;
}

bool Pointer::CleanUp()
{
	App->textures->Unload(texture);
	
	return true;
}

