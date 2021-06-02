#ifndef __POINTER_H__
#define __POINTER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class Pointer : public Module
{
public:
	// Constructor
	Pointer(bool startEnabled);

	// Destructor
	~Pointer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;


public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	SDL_Rect pointRect;
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation pointAnim;


	///frames
	unsigned int currentTime;

	unsigned int lastTime_A = 0;
	unsigned int lastTime_W = 0;
	unsigned int lastTime_S = 0;
	unsigned int lastTime_D = 0;

	bool firstInput_A = false;
	bool firstInput_W = false;
	bool firstInput_S = false;
	bool firstInput_D = false;

	int delay_A = 500;
	int delay_W = 500;
	int delay_S = 500;
	int delay_D = 500;

	const int FPS = 60;
	const int frameDelay = 5000 / FPS;

	Uint32 frameStart;
	int frameTime;

};

#endif //!__MODULE_PLAYER_H__
