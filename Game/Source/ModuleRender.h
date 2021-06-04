#ifndef __MODULE_RENDER_H__
#define __MODULE_RENDER_H__

#include "Module.h"
#include "SDL/include/SDL_Rect.h"

struct SDL_Texture;
struct SDL_Renderer;

class ModuleRender : public Module
{
public:
	
	ModuleRender(bool startEnabled);

	~ModuleRender();

	bool Init() override;

	bool Start() override;

	Update_Status PreUpdate() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = nullptr, float speed = 1.0f, bool useCamera = true, int mult = 1, int r=255, int g = 255, int b = 255);

	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed = 1.0f, bool useCamera = true);

public:

	SDL_Renderer* renderer = nullptr;

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	int cameraSpeed = 3;

};

#endif //__MODULE_RENDER_H__
