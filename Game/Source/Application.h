#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 21

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneIntro;
class SceneLevel1;
class ModuleCollisions;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender; 
class Tiles;
class LevelManager;
class ModuleBoxes;
class Presentation;
class PackInVideo;
class LevelMenu;
class Pointer;
class WinSize;
class IntroAnimation;
class MusicManager;

class Application
{

public:

	Application();

	~Application();

	bool Init();

	Update_Status Update();

	bool CleanUp();

public:

	Module* modules[NUM_MODULES];

	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;


	Presentation* presentation = nullptr;
	PackInVideo* packInVideo = nullptr;
	IntroAnimation* introAnim = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;

	LevelMenu* levelMenu = nullptr;
	Pointer* pointer = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	Tiles* tiles = nullptr;
	LevelManager* lvlManage = nullptr;
	ModuleBoxes* boxes = nullptr;
	WinSize* winSize = nullptr;
	MusicManager* musicManage = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__