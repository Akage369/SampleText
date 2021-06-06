#ifndef __PACK_IN_VIDEO_H__
#define __PACK_IN_VIDEO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class PackInVideo : public Module
{
public:
	
	PackInVideo(bool startEnabled);

	~PackInVideo();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

public:
	
	Animation* currentAnimationPack = nullptr;
	SDL_Texture* bgTexture = nullptr;


	Animation packAnim;
	SDL_Rect pack_rect;
	SDL_Rect rect = { 2, 372, 164, 107 };
	int zoom=3;
	bool canInput = false;

	int scoreFont = -1;

	unsigned int currentTime;

	unsigned int lastTime = 0;

	int delay = 7000;
	bool canWait = true;
};

#endif 


