#include "SceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_scancode.h"

SceneIntro::SceneIntro(bool startEnabled) :Module(startEnabled)
{
	//Logo before animation
	intro.PushBack({ 1, 1, 256, 224 });
	intro.PushBack({ 260, 2713, 256, 224 });
	intro.PushBack({ 260, 2713, 256, 224 });
	intro.PushBack({ 1, 1, 256, 224 });

	//animation
	intro.PushBack({ 1, 1, 256, 224 });
	intro.PushBack({ 1, 227, 256, 224 });
	intro.PushBack({ 1, 227, 256, 224 });
	intro.PushBack({ 1, 1, 256, 224 });
	intro.PushBack({ 2065, 227, 256, 224 });
	intro.PushBack({ 2323, 227, 256, 224 });
	intro.PushBack({ 2581, 227, 256, 224 });
	intro.PushBack({ 2839, 227, 256, 224 });
	intro.PushBack({ 3097, 227, 256, 224 });
	intro.PushBack({ 3355, 227, 256, 224 });
	intro.PushBack({ 2065, 453, 256, 224 });
	intro.PushBack({ 775, 905, 256, 224 });
	intro.PushBack({ 1033, 905, 256, 224 });
	intro.PushBack({ 1291, 905, 256, 224 });
	intro.PushBack({ 1807, 905, 256, 224 });
	intro.PushBack({ 2581,1357, 256, 224 });
	intro.PushBack({ 2839,1357, 256, 224 });
	intro.PushBack({ 3097,1357, 256, 224 });
	intro.PushBack({ 3355,1357, 256, 224 });
	intro.PushBack({ 3613,1357, 256, 224 });
	intro.PushBack({ 1,1583, 256, 224 });
	intro.PushBack({ 2323,1809, 256, 224 });
	intro.PushBack({ 2581,1809, 256, 224 });
	intro.PushBack({ 2839,1809, 256, 224 });
	intro.PushBack({ 1,2713, 256, 224 });

	intro.loop = false;
	intro.speed = 0.015f;
}

SceneIntro::~SceneIntro() {

}