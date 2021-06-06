#ifndef __POINTER_H__
#define __POINTER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class Pointer : public Module
{
public:
	
	Pointer(bool startEnabled);

	
	~Pointer();

	
	bool Start() override;

	
	Update_Status Update() override;

	
	Update_Status PostUpdate() override;

	bool CleanUp() override;


public:
	
	iPoint position;

	
	int speed = 1;

	
	SDL_Texture* texture = nullptr;

	SDL_Rect pointRect = { 16, 361, 9, 9 };

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

	int index=1;

	int zoom = 3;
	int delayPunt = 350;
	int lastTimePunt;

	bool StopPad_S = false;
	bool StopPad_W = false;
	bool StopPad_A = false;
	bool StopPad_D = false;
	unsigned int DelayPad = 500;
	unsigned int LastTPad;
};

#endif //!__MODULE_PLAYER_H__
