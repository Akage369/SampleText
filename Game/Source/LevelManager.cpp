#include "Application.h"
#include "LevelManager.h"

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

int LevelManager::Getlvl() {
	return lvl;
}