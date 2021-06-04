#ifndef __TILES_H__
#define __TILES_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_TILESETS 2
#define MAX_TILES_BLOCKS 8

struct SDL_Texture;

struct Tile
{
	
	int tilesTable[MAX_TILES_BLOCKS];

	
	SDL_Texture* texture = nullptr;

	
	uint totalLength;
	uint rows, columns;
	uint tile_w, tile_h;
};

class Tiles : public Module
{
public:

	
	Tiles(bool isEnabled);


	~Tiles();

	int Load(const char* texturePath, const char* tile, uint rows = 1);

	
	void UnLoad(int tileIndex);

	
	void BlitScene(int x, int y, int tileIndex,const char* map, int zoom) const;
	void genObjects(int x, int y, int tileIndex, const char* map, int zoom) const;
	Update_Status Update();


private:
	
	Tile tiles[MAX_TILESETS];
	
};



#endif // __Tiles_H__

