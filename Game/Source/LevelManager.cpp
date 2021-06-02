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
		//App->lvlManage->max_steps = 0;
		win = 2;

	}

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN) {

		win = 1;
		

	}
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
		//App->lvlManage->max_steps = 0;
		
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
		
		lvlChange(1, '-');
		boxes_lvl = 0;
		//win = 0;
		//steps = 0;
		
	}


	/*if (App->fade->frameCount == App->fade->maxFadeFrames / 2) {
		switch (win) {
		case 0:
			break;
		case 1:
			
				
				lvlChange(1, '+');
				boxes_lvl = 0;
				//win = 0;
				steps = 0;
			
			break;
		case 2:
			
				//App->lvlManage->lvlChange(1, '-');

				

				boxes_lvl = 0;
				//win = 0;
				//steps = 0;
			
			break;
		}
	}
	*/

	switch (win) {
	case 0:
		break;
	case 1:
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
			lvlChange(1, '+');
			//boxes_lvl = 0;
			//win = 0;
			//steps = 0;
		}
		break;
	case 2:
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			//App->lvlManage->lvlChange(1, '-');

			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);

			boxes_lvl = 0;
			//win = 0;
			//steps = 0;
		}
		break;
	}
	return Update_Status::UPDATE_CONTINUE;
}


Update_Status LevelManager::PostUpdate() {
	/*if (win == 2) {
		SDL_Rect rectlose = { 124, 268, 120, 64 };
		App->render->Blit(App->sceneLevel_1->loseTexture, (SCREEN_WIDTH - 120) / 2, (SCREEN_HEIGHT - 64) / 2, &rectlose, 0.0f, true);
		//App->render->Blit(App->sceneLevel_1->loseTexture,0,0,&rectlose, 0.0f, false);

	}
	*/
	return Update_Status::UPDATE_CONTINUE;
}

void LevelManager::Lose()
{/*
	win = 2;	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		App->lvlManage->lvlChange(1, '-');

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
		
		boxes_lvl = 0;
		win = 0;
		steps = 0;
	}
	*/
	win = 2;
	
}

void LevelManager::LevelComplete()
{
	switch (lvl) {
	case 1:

		

		if (boxes_lvl == 3) {
			win = 1;
			//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			//	App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
			//	lvlChange(1, '+');
			//	boxes_lvl = 0;
			//	win = 0;
			//	steps = 0;
			//	}
			
		}


		break;
	case 2:
		if (boxes_lvl == 11) {
			win = 1;
			//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			//	App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
			//	lvlChange(1, '+');
			//	boxes_lvl = 0;
			//	win = 0;
			//	steps = 0;
			//}
		}
		break;

	case 3:
		if (boxes_lvl == 12) {
			win = 1;
			//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			//	App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
			//	lvlChange(1, '+');
			//	boxes_lvl = 0;
			//	win = 0;
			//	steps = 0;
			//}
		}
		break;
	}
	


}

int LevelManager::Getlvl() {
	return lvl;
}

