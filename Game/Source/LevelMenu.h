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

	bool CleanUp() override;

public:
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgTexto = nullptr;

	SDL_Rect rectbg = { 259, 631, 256, 440 };
	SDL_Rect rectlvls = { 1, 1, 161, 81 };

	int scoreFont = -1;
};

#endif

