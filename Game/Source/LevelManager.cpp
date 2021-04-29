#include "Application.h"
#include "LevelManager.h"
#include "ModulePlayer.h"
#include "ModuleBoxes.h"
#include "Boxes.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

LevelManager::LevelManager(bool isEnabled) : Module(isEnabled)
{

}

LevelManager::~LevelManager()
{

}

void LevelManager::lvlChange(int change, char op)
{
	switch (op) {
	case '=':
		lvl = change;
		break;
	case '+':
		lvl += change;
		break;
	case '-':
		lvl -= change;
		break;
	default:
		break;
	}
	
}



void LevelManager::Lose()
{
	win = 2;
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		App->lvlManage->lvlChange(1, '-');
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
		
		boxes_lvl = 0;
		win = 0;
	}

}

void LevelManager::LevelComplete()
{
	switch (lvl) {
	case 1:

		

		if (boxes_lvl == 2*3) {
			win = 1;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
				lvlChange(1, '+');
				boxes_lvl = 0;
				win = 0;
				}
			
		}


		break;
	case 2:
		if (boxes_lvl == 2 * 11) {
			win = 1;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
				lvlChange(1, '+');
				boxes_lvl = 0;
				win = 0;
			}
		}
		break;

	case 3:
		if (boxes_lvl == 2 * 12) {
			win = 1;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
				lvlChange(1, '+');
				boxes_lvl = 0;
				win = 0;
			}
		}
		break;
	}
	


}

int LevelManager::Getlvl() {
	return lvl;
}

