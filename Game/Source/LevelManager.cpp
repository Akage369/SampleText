#include "Application.h"
#include "LevelManager.h"
#include "ModulePlayer.h"
#include "ModuleBoxes.h"
#include "Boxes.h"
#include "ModuleFadeToBlack.h"

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

void LevelManager::BoxesDone()
{
	

}

void LevelManager::LevelComplete()
{
	switch (lvl) {
	case 1:

		App->player->score = boxes_lvl;

		if (boxes_lvl == 2*3) {
			
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 90);
			lvlChange(1, '+');
			
		}
		break;

	}

}

int LevelManager::Getlvl() {
	return lvl;
}

