#include "Application.h"
#include "LevelManager.h"
#include "ModulePlayer.h"
#include "ModuleBoxes.h"
#include "Boxes.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "WindowSize.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "MusicManager.h"


MusicManager::MusicManager(bool isEnabled) : Module(isEnabled)
{

}

MusicManager::~MusicManager()
{

}


bool MusicManager::Start() {
	
	//loseFX = App->audio->LoadFx("Assets/Audio/Music/lose.ogg");
	return true;

}

Update_Status MusicManager::Update() {


	
	return Update_Status::UPDATE_CONTINUE;
}

void MusicManager::playMusic(const char*path) {
	//App->audio->music = nullptr;
	//"Assets/Audio/Music/lose.ogg"
	//if (playEffect == true) {

	//	App->audio->PlayMusic(path);
		
	//}
	//App->audio->PlayFx(loseFX, 1);
	playEffect = false;


}


Update_Status MusicManager::PostUpdate() {

	

	return Update_Status::UPDATE_CONTINUE;
}


bool MusicManager::CleanUp()
{

	App->fonts->UnLoad(0);

	return true;
}


