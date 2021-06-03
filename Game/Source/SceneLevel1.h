#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"


struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	bool isIni = false;
	// The scene sprite sheet loaded into an SDL_Texture
	//SDL_Texture* bgTexture = nullptr;
	SDL_Texture* UItexture = nullptr;
	SDL_Texture* UItextureIn = nullptr;
	//SDL_Texture* UItextureIn = nullptr;
	SDL_Rect UIrect = { 1, 230, 60, 36 };
	SDL_Rect rectlose = { 124, 268, 120, 64 };
	SDL_Rect rectwin = { 2, 268, 120, 64 };
	SDL_Rect rectNextRepeat = { 1, 156, 98, 34 };
	SDL_Rect rectplayer;
	SDL_Rect UIrectIn = { 61, 230, 61, 36 };
	//SDL_Texture* scoreBoxIn = nullptr;
	///tiles
	//SDL_Texture* bgTiles = nullptr;

	///Level1_Tiles
	int lvl1_map = -1;
	int zoom=1;
	int lvl = 0;
	char stepText[5] = { "\0" };
	char stageText[3] = { "\0" };
	char limitText[5] = { "\0" };
	int scoreFont = -1;

	bool contactUI = false;
	
	iPoint positionUI;

	Collider* colliderUI = nullptr;

	bool nextlvl = true;

};

#endif