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

public:
	
	SDL_Texture* bgTexture = nullptr;

	SDL_Texture* bgTexto = nullptr;

	SDL_Rect rect = { 2, 372, 164, 107 };
	int zoom=3;
	
};

#endif 


