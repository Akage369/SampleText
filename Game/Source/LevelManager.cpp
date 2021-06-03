#include "Application.h"
#include "LevelManager.h"
#include "ModulePlayer.h"
#include "ModuleBoxes.h"
#include "Boxes.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"

LevelManager::LevelManager(bool isEnabled) : Module(isEnabled)
{

}

LevelManager::~LevelManager()
{

}

void LevelManager::lvlChange(int change, char op)
{
	if(changeScene == true)
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
	changeScene = false;
	
}

Update_Status LevelManager::Update() {

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN) {
		
		win = 2;

	}

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN) {

		win = 1;
		
	}
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
		
		if (lvl==-1) {
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);

			lvlChange(6, '=');
			boxes_lvl = 0;
		}
		else {
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);

			lvlChange(1, '-');
			boxes_lvl = 0;
		}
		
	}

	switch (win) {
	case 0:
		break;
	case 1:
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			if (App->sceneLevel_1->nextlvl == true) {
				if (lvl == 6) {
					App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
					lvlChange(0, '=');
				}
				else {
					App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
					lvlChange(1, '+');
				}
			}
			else {
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
				boxes_lvl = 0;
			}
		}
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) {
			App->sceneLevel_1->nextlvl = true;
		}
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) {
			App->sceneLevel_1->nextlvl = false;
		}
		break;
	case 2:
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
				boxes_lvl = 0;

		}
		break;
	}
	return Update_Status::UPDATE_CONTINUE;
}


Update_Status LevelManager::PostUpdate() {

	return Update_Status::UPDATE_CONTINUE;
}

void LevelManager::Lose()
{
	win = 2;
}

void LevelManager::LevelComplete()
{
	switch (lvl) {
	case 1:
		if (boxes_lvl == 3) {
			win = 1;
		}
		break;
	case 2:
		if (boxes_lvl == 11) {
			win = 1;
		}
		break;

	case 3:
		if (boxes_lvl == 12) {
			win = 1;
		}
		break;
	case 4:
		if (boxes_lvl == 12) {
			win = 1;
		}
		break;
	case 5:
		if (boxes_lvl == 12) {
			win = 1;
		}
		break;
	case 6:
		if (boxes_lvl == 12) {
			win = 1;
		}
		break;
	}
	


}

int LevelManager::Getlvl() {
	return lvl;
}

