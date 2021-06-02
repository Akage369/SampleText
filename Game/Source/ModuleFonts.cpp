#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

#include<string.h>

ModuleFonts::ModuleFonts(bool isEnabled) : Module(isEnabled)
{

}

ModuleFonts::~ModuleFonts()
{

}

// Load new texture from file path
int ModuleFonts::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].texture == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	Font& font = fonts[id];

	font.texture = tex;
	font.rows = rows;

	

	// TODO 1: Finish storing font data

	// totalLength ---	length of the lookup table
	// table ---------  All characters displayed in the same order as the texture
	// columns -------  Amount of chars per row of the texture
	// char_w --------	Width of each character
	// char_h --------	Height of each character

	strcpy_s(fonts[id].table, MAX_FONT_CHARS, characters);
	font.totalLength = strlen(characters);
	font.columns = fonts[id].totalLength / rows;

	uint tex_w, tex_h;
	App->textures->GetTextureSize(tex, tex_w, tex_h);
	font.char_w = tex_w / font.columns;
	font.char_h = tex_h / font.rows;

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleFonts::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].texture != nullptr)
	{
		App->textures->Unload(fonts[font_id].texture);
		fonts[font_id].texture = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

void ModuleFonts::BlitText(int x, int y, int font_id, const char* text, int zoom, int r, int g, int b, int max, int down) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}
	int x0 = x;
	int y0 = y;

	const Font* font = &fonts[font_id];
	SDL_Rect spriteRect;
	//SDL_Rect fontRect{ 79, 1, 24, 24 };
	uint len = strlen(text);

	spriteRect.w = 9;//*zoom;//font->char_w;
	spriteRect.h = 8;// *zoom;// font->char_h;

	for (uint i = 0; i < len; ++i)
	{
		// TODO 2: Find the character in the table and its position in the texture, then Blit
		uint charIndex = 0;

		// Find the location of the current character in the lookup table
		for (uint j = 0; j < font->totalLength; ++j)
		{
			if (font->table[j] == text[i])
			{
				charIndex = j;
				break;
			}
		}

		// Retrieve the position of the current character in the sprite
		spriteRect.x = spriteRect.w * (charIndex % font->columns);
		spriteRect.y = 348;//spriteRect.h * (charIndex / font->columns);

		if( text[i] == '|') {
			x = x0;
			y += spriteRect.h * zoom + zoom * down;
		}else if (text[i] == 'I') {
			App->render->Blit(font->texture, x -2*zoom+zoom, y + zoom, &spriteRect, 0.0f, false, zoom,  r,  g,  b);
			x += spriteRect.w * zoom - zoom-5*zoom;
		}
		else if(text[i]=='T'){
			App->render->Blit(font->texture, x + zoom, y + zoom, &spriteRect, 0.0f, false, zoom,  r,  g,  b);
			x += spriteRect.w * zoom - 2*zoom;
		}
		//else if (text[i] == ('0'||'1'||'2' || '3' || '4' || '5' || '6' || '7' || '8' || '9' )) {
		else if (text[i] == '0'|| text[i] == '1' || text[i] == '2' || text[i] == '3' || text[i] == '4' || text[i] == '5' || text[i] == '6' || text[i] == '7' || text[i] == '8' || text[i] == '9' ) {
			App->render->Blit(font->texture, x + zoom, y + zoom, &spriteRect, 0.0f, false, zoom,  r,  g,  b);
			x += spriteRect.w * zoom - 2*zoom;
		}
		else {
			App->render->Blit(font->texture, x + zoom, y + zoom, &spriteRect, 0.0f, false, zoom,  r,  g,  b);
			x += spriteRect.w * zoom - zoom;
		}

		if (x > max) {
			x = x0;
			y += spriteRect.h * zoom + zoom*down;
		}

		
		// Advance the position where we blit the next character
		
	}
}
