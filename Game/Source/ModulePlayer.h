#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;
	void walkx();
	void walky();
	void spawn(int lvl);

	void isStopped (char dir);
	void Push (char dir);

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleDown, idleUp, idleRight, idleLeft;
	Animation walkDown, walkUp, walkRight, walkLeft;
	Animation pushDown, pushUp, pushRight, pushLeft;

	// The player's collider
	Collider* collider = nullptr;

	Collider* colliderR = nullptr;
	Collider* colliderL = nullptr;
	Collider* colliderU = nullptr;
	Collider* colliderD = nullptr;
	bool resetTouch = true;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// Font score index
	int score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	///frames
	const int FPS = 60;
	const int frameDelay = 500 / FPS;

	Uint32 frameStart;
	int frameTime;
	
	signed int countx = 0;
	signed int county = 0;
	signed int movx;
	signed int movy;

	bool posInix = true;
	bool posIniy = true;

	bool isTouchingR = false;
	bool isTouchingL = false;
	bool isTouchingU = false;
	bool isTouchingD = false;

	bool isPushingR = false;
	bool isPushingL = false;
	bool isPushingU = false;
	bool isPushingD = false;

	bool isBlockedR = false;
	bool isBlockedL = false;
	bool isBlockedU = false;
	bool isBlockedD = false;

	int zoom;

	int lvl;
};

#endif //!__MODULE_PLAYER_H__