#ifndef __MODULE_FONTS_H__
#define __MODULE_FONTS_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font
{
	char table[MAX_FONT_CHARS];

	SDL_Texture* texture = nullptr;

	uint totalLength;
	uint rows, columns;
	uint char_w, char_h;
};

class ModuleFonts : public Module
{
public:

	ModuleFonts(bool isEnabled);

	~ModuleFonts();

	int Load(const char* texturePath, const char* characters, uint rows = 1);

	void UnLoad(int fontIndex);

	void BlitText(int x, int y, int fontIndex, const char* text, int zoom=1, int r=255, int g = 255, int b = 255, int max= 1920, int down=1) const;

private:

	Font fonts[MAX_FONTS];
	
};


#endif // __ModuleFonts_H__
