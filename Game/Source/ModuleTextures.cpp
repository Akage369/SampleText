#include "ModuleTextures.h"

#include "Application.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_TEXTURES; ++i)
		textures[i] = nullptr;
}

ModuleTextures::~ModuleTextures()
{}

bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (uint i = 0; i < MAX_TEXTURES; ++i)
	{
		if (textures[i] != nullptr)
		{
			SDL_DestroyTexture(textures[i]);
			textures[i] = nullptr;
		}
	}

	IMG_Quit();
	return true;
}

SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

		if (texture == NULL)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			for (uint i = 0; i < MAX_TEXTURES; ++i)
			{
				if (textures[i] == nullptr)
				{
					textures[i] = texture;
					break;
				}
			}
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

bool ModuleTextures::Unload(SDL_Texture* texture)
{
	bool ret = false;

	if (texture != nullptr)
	{
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (textures[i] == texture)
			{
				textures[i] = nullptr;
				ret = true;
				break;
			}
		}
		SDL_DestroyTexture(texture);
	}

	return ret;
}

void ModuleTextures::GetTextureSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*)&width, (int*)&height);
}