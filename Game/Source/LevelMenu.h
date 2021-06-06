#ifndef __LEVEL_MENU_H__
#define __LEVEL_MENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class LevelMenu : public Module
{
public:

	LevelMenu(bool startEnabled);

	~LevelMenu();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp();

public:
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgTexto = nullptr;

	SDL_Rect rectbg = { 259, 631, 256, 440 };
	SDL_Rect rectlvls = { 1, 1, 161, 81 };
	SDL_Rect rectTop = { 1, 84, 118, 70 };
	SDL_Rect rectDown = { 507, 84, 102, 22 };
	SDL_Rect rectD = { 387, 84, 118, 22 };
	SDL_Rect text = { 273, 84, 112, 47 };
	SDL_Rect title = { 1,499,215,130 };

	int FontText = -1;
	int titleY;

};

#endif

