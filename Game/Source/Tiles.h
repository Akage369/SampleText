#ifndef __TILES_H__
#define __TILES_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_TILESETS 2
#define MAX_TILES_BLOCKS 8

struct SDL_Texture;

struct Tile
{
	// Lookup table. All characters displayed in the same order as the texture
	int tilesTable[MAX_TILES_BLOCKS];

	// The font texture
	SDL_Texture* texture = nullptr;

	// Font setup data
	uint totalLength;
	uint rows, columns;
	uint tile_w, tile_h;
};

class Tiles : public Module
{
public:

	// Constructor
	Tiles(bool isEnabled);

	// Destructor
	~Tiles();

	// Loads a font file from a texture
	// Returns a font index from the fonts array
	// Param texturePath	- The path to the texture file
	// Param characters		- The lookup table. All characters displayed in the same order as the texture
	// Param rows			- The amount of character rows in the texture
	int Load(const char* texturePath, const char* tile, uint rows = 1);

	// Removes a font by its index
	// Unloads the texture and removes it from the fonts array
	void UnLoad(int tileIndex);

	// Create a surface from text
	void BlitScene(int x, int y, int tileIndex,const char* map) const;

private:
	// An array to keep track and store all loaded fonts
	Tile tiles[MAX_TILESETS];
};



#endif // __Tiles_H__

