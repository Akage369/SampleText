#ifndef __INTRO_ANIMATION_H__
#define __INTRO_ANIMATION_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class IntroAnimation : public Module
{
public:
	//Constructor
	IntroAnimation(bool startEnabled);

	//Destructor
	~IntroAnimation();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* introTexture = nullptr;
	SDL_Texture* carTexture = nullptr;
	int zoom = 1;
	SDL_Rect closeUp = { 1,1,256,223 };
	SDL_Rect closeUpOposite = { 259,1,256,223 };
	SDL_Rect back = { 1,227,192,223 };
	SDL_Rect backOposite = { 259,227,192,223 };
	SDL_Rect fullBody = { 1,453,73,220 };
	SDL_Rect fullBodyOposite = { 259,453,73,220 };
	SDL_Rect fullBodyBack = { 1,679,45,163 };
	SDL_Rect fullBodyBackOposite = { 259,679,53,163 };
	SDL_Rect yellowCar = { 1,905,256,223 };
	SDL_Rect blueCar = { 259,905,256,223 };
	SDL_Rect yellowCarSmall = { 1,1131,98,140 };
	SDL_Rect blueCarSmall = { 259,1131,100,122 };
	SDL_Rect sadProtagonist = { 1,1357,75,158 };
	SDL_Rect leavingWoman = { 259,1357,53,168 };
	SDL_Rect clouds = { 1,1583,230,80 };
	SDL_Rect ground = { 259,1583,256,41 };
	SDL_Rect imagination = { 1,1809,136,88 };
	SDL_Rect smoke = { 259,1809,175,146 };
	SDL_Rect coffee = { 1,2035,32,39 };
	SDL_Rect coffeeOposite = { 259,2035,32,39 };
	SDL_Rect disaproval = { 1 ,2261, 27, 38 };
	SDL_Rect disapoint = { 259,2261,35,39 };
	SDL_Rect sky = { 1,2485,256,224 };
	SDL_Rect black = { 259,2485,256,224 };

	Animation ImCarAnim;
	Animation* currentAnimationCar = nullptr;
	SDL_Rect ImCar_rect;

	Animation intro;

	int menuFont = -1;



	bool nextScene;

	iPoint yellow;
	iPoint yellowSmall;
	iPoint blue;
	iPoint blueSmall;
	iPoint smokeM;
	iPoint coffeeLeft;
	iPoint yellowThink;
	iPoint coffeeRight;
	iPoint blackThink;
	iPoint fullBodyThinking;
	iPoint fullBodyLeaving;
	iPoint fullBodyWoman;
	iPoint sadMan;
	iPoint imaginCar;

	

	int screen_w = 0, screen_h=0;

	int titleY;

	unsigned int currentTime;

	unsigned int lastTime = 0;

	int delay = 400;

	int animIndex = 0;

	int loop = 0;

	bool oposite = false;
};

#endif
