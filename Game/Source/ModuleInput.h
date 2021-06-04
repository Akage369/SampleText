#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"

#define MAX_KEYS 256

enum Key_State
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput(bool startEnabled);

	~ModuleInput();

	bool Init() override;

	Update_Status PreUpdate() override;

	bool CleanUp() override;

public:
	
	Key_State keys[MAX_KEYS] = { KEY_IDLE };
};

#endif // __ModuleInput_H__