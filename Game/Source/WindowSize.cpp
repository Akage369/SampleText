#include "Application.h"

#include "ModuleWindow.h"

#include "SDL/include/SDL.h"

#include "WindowSize.h"

#include<string.h>

WinSize::WinSize(bool isEnabled) : Module(isEnabled)
{

}

WinSize::~WinSize()
{

}

bool WinSize::Start() {
	w = App->window->screenSurface->w;
	h = App->window->screenSurface->h;
	return true;
}

Update_Status WinSize::Update() {
	w = App->window->screenSurface->w;
	h = App->window->screenSurface->h;
	

	return Update_Status::UPDATE_CONTINUE;
}


