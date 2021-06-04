#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Tiles.h"
#include "ModuleCollisions.h"
#include "ModuleBoxes.h"
#include "LevelManager.h"

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

	if (tex == nullptr  || strlen(tile) >= MAX_TILES_BLOCKS)
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


	for (int i = 0; i < MAX_TILES_BLOCKS;i++) {
		tiles[id].tilesTable[i] = tile[i];
	}
	
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
Update_Status Tiles:: Update() {
	

	return Update_Status::UPDATE_CONTINUE;
}

void Tiles::BlitScene(int x, int y, int tile_id, const char* map, int zoom) const
{
	int x0 = x;
	int y0 = y;

	if (map == nullptr || tile_id < 0 || tile_id >= MAX_TILESETS || tiles[tile_id].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", tile_id);
		return;
	}

	const Tile* tilesptr = &tiles[tile_id];
	SDL_Rect spriteRect;
	SDL_Rect floorRect{79, 1, 24, 24};
	uint len = strlen(map);

	spriteRect.w = tilesptr->tile_w;
	spriteRect.h = tilesptr->tile_h;

	for (uint i = 0; i < len; ++i)
	{
	
		uint charIndex = 0;

		
		for (uint j = 0; j < tilesptr->totalLength; ++j)
		{
			if (tilesptr->tilesTable[j] == map[i])
			{
				charIndex = j;
				break;
			}
		}

		if (map[i] == ',') {
			x = x0;
			y += (tilesptr->tile_h - 2)*zoom;
		}
		else if(map[i] == 'W'|| map[i] == 'w') {
			
				spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
				spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);

				App->render->Blit(tilesptr->texture, x, y, &spriteRect, 0.0f, false,zoom);
				
				
				
				
			
				x += (spriteRect.w - 2)*zoom;
			
			
		}
		else if (map[i] == 'B') {
		
				spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
				spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);

				App->render->Blit(tilesptr->texture, x, y, &spriteRect, 0.0f, false,zoom);
				
				
				x += (spriteRect.w - 2)*zoom;
			
		}
		else if (map[i] == 'C') {
			spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
			spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);

			App->render->Blit(tilesptr->texture, x+zoom, y+zoom, &floorRect, 0.0f, false,zoom);

			
			
			x += (spriteRect.w - 2)*zoom;
		}
		else {
		
		spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
		spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);

		App->render->Blit(tilesptr->texture, x, y, &spriteRect, 0.0f, false,zoom);

		
		x += (spriteRect.w - 2)*zoom;
		
		}
		
		
	}

	
}

void Tiles::genObjects(int x, int y, int tile_id, const char* map, int zoom) const
{
	int x0 = x;
	int y0 = y;

	if (map == nullptr || tile_id < 0 || tile_id >= MAX_TILESETS || tiles[tile_id].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", tile_id);
		return;
	}

	const Tile* tilesptr = &tiles[tile_id];
	SDL_Rect spriteRect;
	SDL_Rect floorRect{ 79, 1, 24, 24 };
	uint len = strlen(map);

	spriteRect.w = tilesptr->tile_w;
	spriteRect.h = tilesptr->tile_h;

	for (uint i = 0; i < len; ++i)
	{
		
		uint charIndex = 0;

	
		for (uint j = 0; j < tilesptr->totalLength; ++j)
		{
			if (tilesptr->tilesTable[j] == map[i])
			{
				charIndex = j;
				break;
			}
		}

		if (map[i] == ',') {
			x = x0;
			y += (tilesptr->tile_h - 2)*zoom;
		}
		else if (map[i] == 'W' || map[i] == 'w') {
			
			spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
			spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);


			App->boxes->AddBox(Box_Type::WALL, x + zoom, y + zoom);

			
			x += (spriteRect.w - 2) * zoom;
			

		}
		else if (map[i] == 'B') {
			
			spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
			spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);

			App->boxes->AddBox(Box_Type::BALL, x + zoom, y + zoom);
			
			x += (spriteRect.w - 2) * zoom;
			
		}
		else if (map[i] == 'C') {
			spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
			spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);

			App->boxes->AddBox(Box_Type::BOX, x + zoom, y + zoom);

			x += (spriteRect.w - 2) * zoom;
		}
		else {
			
			spriteRect.x = spriteRect.w * (charIndex % tilesptr->columns);
			spriteRect.y = spriteRect.h * (charIndex / tilesptr->columns);

			
			x += (spriteRect.w - 2) * zoom;
		
		}


	}

	
}
