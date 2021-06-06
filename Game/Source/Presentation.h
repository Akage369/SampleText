#ifndef __PRESENTATION_H__
#define __PRESENTATION_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class Presentation : public Module
{
public:
	
	Presentation(bool startEnabled);

	~Presentation();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;
	bool CleanUp() override;

public:

	SDL_Texture* bgTexture = nullptr;

	int scoreFont = -1;

	int w, h;
};

#endif

