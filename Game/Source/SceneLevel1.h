#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"


struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	
	SceneLevel1(bool startEnabled);

	~SceneLevel1();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp() override;

public:
	bool isIni = false;
	
	SDL_Texture* UItexture = nullptr;
	SDL_Texture* UItextureIn = nullptr;
	
	SDL_Rect UIrect = { 1, 230, 60, 36 };
	SDL_Rect rectlose = { 124, 268, 120, 64 };
	SDL_Rect rectwin = { 2, 268, 120, 64 };
	SDL_Rect rectNextRepeat = { 1, 156, 98, 34 };
	SDL_Rect rectplayer;
	SDL_Rect UIrectIn = { 61, 230, 61, 36 };
	SDL_Rect rectPause = { 164, 1, 106, 58 };
	
	int lvl1_map = -1;
	int zoom=1;
	int lvl = 0;
	char stepText[5] = { "\0" };
	char stageText[3] = { "\0" };
	char limitText[5] = { "\0" };
	int scoreFont = -1;
	int zoomUI=3;
	int zoomWL=3;

	bool contactUI = false;
	
	iPoint positionUI;

	Collider* colliderUI = nullptr;

	bool nextlvl = true;

	bool pause = false;
	bool noUI = false;

	int pauseIndex = 0;

	unsigned int currentTime;

	unsigned int lastTime_W = 0;
	unsigned int lastTime_S = 0;

	bool firstInput_W = false;
	bool firstInput_S = false;

	int delay_W = 500;
	int delay_S = 500;

	int w=0, h=0;

	int delayPunt = 400;
	int lastTimePunt;

	//Mix_Music* lvlmusic = nullptr;

};

#endif