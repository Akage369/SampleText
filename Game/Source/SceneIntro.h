#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	//Constructor
	SceneIntro(bool startEnabled);

	//Destructor
	~SceneIntro();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgTexto = nullptr;
	SDL_Texture* puntero = nullptr;
	SDL_Texture* scroller1 = nullptr;
	SDL_Texture* scroller2 = nullptr;
	SDL_Texture* introMenu = nullptr;
	int scrollerY;
	int scroller2Y;
	int scroller3Y;
	SDL_Texture* BoxMenu = nullptr;

	int p_x = 155;
	int p_y = 145;

	SDL_Rect p_pos;
	SDL_Rect scrollers = { 1,631,256,520 };
	SDL_Rect title = { 1,499,215,130 };
	SDL_Rect copyright = { 259, 1083, 245, 16 };
	SDL_Rect options = { 273, 84, 112, 47 };
	
	Animation intro;

	int menuFont = -1;

	const int B_play = 2;
	const int B_Coop = 1;
	const int B_Edit = 0;

	int M_index = 2;

	uint MenuMusic = 0;
	uint selectFx = 0;
	uint nextFx = 0;
	uint backFx = 0;

	bool nextScene;

	int titleY;

	unsigned int currentTime;

	unsigned int lastTime = 0;

	int delay = 1000;

	int optFont = -1;
};

#endif
