#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Tiles.h"

#include<string.h>

Tiles::Tiles(bool isEnabled) : Module(isEnabled)
{

}

Tiles::~Tiles()
{

}

// Load new texture from file path
int Tiles::Load(const char* texture_path, const char* tile, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || tile == nullptr || rows == 0)
	{
		LOG("Could not load tileset");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr  || strlen(tile) >= MAX_TILES_BLOCKS)//|| tile[MAX_TILES_BLOCKS] >= MAX_TILES_BLOCKS)
	{
		LOG("Could not load tileset at %s with tiles '%s'", texture_path, tile);
		return id;
	}

	id = 0;
	for (; id < MAX_TILESETS; ++id)
		if (tiles[id].texture == nullptr)
			break;

	if (id == MAX_TILESETS)
	{
		LOG("Cannot load tileset %s. Array is full (max %d).", texture_path, MAX_TILESETS);
		return id;
	}

	Tile* tilesptr = &tiles[id];
	tilesptr->texture = tex;
	tilesptr->rows = rows;



	// TODO 1: Finish storing font data

	// totalLength ---	length of the lookup table
	// table ---------  All characters displayed in the same order as the texture
	// columns -------  Amount of chars per row of the texture
	// char_w --------	Width of each character
	// char_h --------	Height of each character



	for (int i = 0; i < MAX_TILES_BLOCKS;i++) {
		tiles[id].tilesTable[i] = tile[i];
	}
	///Donde el 6 va el total de numeros de la matriz
	tilesptr->totalLength = strlen(tile);
	tilesptr->columns = tiles[id].totalLength / rows; 

	uint tex_w, tex_h;
	App->textures->GetTextureSize(tex, tex_w, tex_h);
	tilesptr->tile_w = tex_w / tilesptr->columns; 
	tilesptr->tile_h = tex_h / tilesptr->rows; 

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void Tiles::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_TILESETS && tiles[font_id].texture != nullptr)
	{
		App->textures->Unload(tiles[font_id].texture);
		tiles[font_id].texture = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

void Tiles::BlitScene(int x, int y, int tile_id, const char* map) const
{
	if (map == nullptr || tile_id < 0 || tile_id >= MAX_TILESETS || tiles[tile_id].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", tile_id);
		return;
	}

	const Tile* tilesptr = &tiles[tile_id];
	SDL_Rect spriteRect;
	uint len = strlen(map);

	spriteRect.w = tilesptr->tile_w;
	spriteRect.h = tilesptr->tile_h;

	for (uint i = 0; i < len; ++i)
	{
		// TODO 2: Find the character in the table and its position in the texture, then Blit
		uint charIndex = 0;

		// Find the location of the current character in the lookup table
		for (uint j = 0; j < tilesptr->totalLength; ++j)
		{
			if (tilesptr->tilesTable[j] == map[i])
			{
				charIndex = j;
				break;
			}
		}

		if (map[i] == ',') {
			x = 0;
			y += tilesptr->tile_h - 2;
		}

		else {
			// Retrieve the position of the current character in the sprite
			spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
			spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);

			App->render->Blit(tilesptr->texture, x, y, &spriteRect, 0.0f, false);

			// Advance the position where we blit the next character
			x += spriteRect.w - 2;
		}

		
		
	}
}
