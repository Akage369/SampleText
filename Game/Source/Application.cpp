#include "Application.h"
#include "PackInVideo.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "SceneLevel1.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "Tiles.h"
#include "LevelManager.h"
#include "ModuleBoxes.h"
#include "Presentation.h"
#include "LevelMenu.h"
#include "Pointer.h"
#include "WindowSize.h"
#include "IntroAnimation.h"
#include "MusicManager.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);
	
	modules[4] = winSize = new WinSize(true);
	modules[5] = presentation = new Presentation(true);
	modules[6] = packInVideo = new PackInVideo(false);
	modules[7] = introAnim = new IntroAnimation(false);
	modules[8] = sceneIntro = new SceneIntro(false);
	modules[9] = levelMenu = new LevelMenu(false);
	modules[10] = pointer = new Pointer(false);


	modules[11] = tiles = new Tiles(true);
	modules[12] = boxes = new ModuleBoxes(false);
	modules[13] = player = new ModulePlayer(false);	//Player starts disabled
	modules[14] = sceneLevel_1 = new SceneLevel1(false);		//Gameplay scene starts disabled

	modules[15] = collisions = new ModuleCollisions(false);
	modules[16] = fade = new ModuleFadeToBlack(true);
	modules[17] = fonts = new ModuleFonts(true);
	
	
	modules[18] = lvlManage = new LevelManager(true);
	modules[19] = musicManage = new MusicManager(true);
	

	modules[20] = render = new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
