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

	ModulePlayer(bool startEnabled);

	~ModulePlayer();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

	void OnCollision(Collider* c1, Collider* c2) override;
	void walkx();
	void walky();
	void spawn(int lvl);

	void isStopped (char dir);
	void Push (char dir);

public:

	iPoint position;

	int speed = 1;

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;

	Animation idleDown, idleUp, idleRight, idleLeft;
	Animation walkDown, walkUp, walkRight, walkLeft;
	Animation pushDown, pushUp, pushRight, pushLeft;

	Collider* collider = nullptr;

	Collider* colliderR = nullptr;
	Collider* colliderL = nullptr;
	Collider* colliderU = nullptr;
	Collider* colliderD = nullptr;
	bool resetTouch = true;

	bool destroyed = false;

	uint laserFx = 0;
	uint explosionFx = 0;

	int score = 000;

	const int FPS = 60;
	const int frameDelay = 100 / FPS;

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

	bool inContactR = false;
	bool inContactL = false;
	bool inContactU = false;
	bool inContactD = false;



	bool canStart = false;

	int zoom;

	int lvl;

	unsigned int currentTime;

	unsigned int lastTime = 0;

	int delay = 300;
};

#endif //!__MODULE_PLAYER_H__