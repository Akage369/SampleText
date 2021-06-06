#include "Application.h"
#include "LevelManager.h"
#include "ModulePlayer.h"
#include "ModuleBoxes.h"
#include "Boxes.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "WindowSize.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "MusicManager.h"
#include "SDL/include/SDL.h"

LevelManager::LevelManager(bool isEnabled) : Module(isEnabled)
{

}

LevelManager::~LevelManager()
{

}

void LevelManager::lvlChange(int change, char op)
{
	if(changeScene == true)
	switch (op) {
	case '=':
		lvl = change;
		break;
	case '+':
		lvl += change;
		break;
	case '-':
		lvl -= change;
		break;
	default:
		break;
	}
	changeScene = false;
	
}

bool LevelManager::Start(){
	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	scoreFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);
	//loseFX = App->audio->LoadFx("Assets/Audio/Music/lose.ogg");
	//lvlmusic = Mix_LoadMUS("Assets/Audio/Music/lose.ogg");

	//Mix_Music* musiclvl;
	//musiclvl = Mix_LoadMUS("Assets/Audio/Music/lose.ogg");
	//lvlmusic = App->audio->Mix_LoadMUS("Assets/Audio/Music/lose.ogg");
	//App->audio->loseMusic = App->audio->Mix_LoadMUS("Assets/Audio/Music/lose.ogg");

	indexEffects[0] = App->audio->LoadFx("Assets/Audio/Fx/car_fx.wav");
	indexEffects[1] = App->audio->LoadFx("Assets/Audio/Fx/enter_fx.wav");
	indexEffects[2] = App->audio->LoadFx("Assets/Audio/Fx/options_fx.wav");
	indexEffects[3] = App->audio->LoadFx("Assets/Audio/Fx/pointer_fx.wav");

	return true;

}

Update_Status LevelManager::Update() {
	GamePad& pad = App->input->pads[0];
	currentTime = SDL_GetTicks();
	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN) {
		if (lvl > 0 && lvl <= 6) {
			if (App->sceneLevel_1->pause == false) {
				if (godmode == false) {
					godmode = true;
					}
				else {
					godmode = false;
				}
			}
		}
		else {
			if (godmode == false) {
				godmode = true;
			}
			else {
				godmode = false;
			}
		}
	}
	
	if (godmode == true) {
		if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN) {
			if (lvl > 0 && lvl <= 6) {
				if (App->sceneLevel_1->pause == false) {
					win = 2;
				}
			}

		}

		if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN) {
			if (lvl > 0 && lvl <= 6) {
				if (App->sceneLevel_1->pause == false) {
					win = 1;
				}
			}
		}
if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {

	if ((App->sceneLevel_1->lvl > 1 && App->sceneLevel_1->lvl <= 6)) {

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
		lvlChange(1, '-');

		boxes_lvl = 0;
	}
	else if (App->sceneLevel_1->lvl <= 1) {

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->levelMenu, 30);
		lvlChange(0, '=');
	}


}
if (App->input->keys[SDL_SCANCODE_0] == KEY_DOWN) {

	steps = 0;



}
	}





	switch (win) {
	case 0:
		break;
	case 1:

		if (lvl > 0 && lvl <= 6) {
			if (firstCaption == true) {
				App->audio->PlayMusic("Assets/Audio/Music/win.ogg",0);
				firstCaption = false;
			}
			
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || (pad.a == KEY_DOWN)) {
				//App->audio->Disable();
				App->audio->PlayFx(App->lvlManage->indexEffects[1], 0);
				if (App->sceneLevel_1->nextlvl == true) {
					if (lvl == 6) {
						App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->levelMenu, 30);
						lvlChange(0, '=');
					}
					else {
						App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
						lvlChange(1, '+');
					}
				}
				else {
					App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
					boxes_lvl = 0;
				}
			}
			if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || ((pad.left == KEY_DOWN) || (pad.left_x < 0.0f))) {
				if (App->sceneLevel_1->nextlvl == false) {
					App->sceneLevel_1->nextlvl = true;
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);

				}
				
			}
			if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || ((pad.right == KEY_DOWN) || (pad.left_x > 0.0f))) {
				if (App->sceneLevel_1->nextlvl == true) {
					App->sceneLevel_1->nextlvl = false;
					App->audio->PlayFx(App->lvlManage->indexEffects[3], 0);
				}
				
			}
		}
		break;
	case 2:
		if (lvl > 0 && lvl <= 6) {
			if (playEffect == true) {
				//playMusicLose();
				//App->audio->Mix_PlayMusic(App->audio->music, 1);
			}
			else {
				//disableMusic(7200);
	
			}
			if (firstCaption == true) {
				App->audio->PlayMusic("Assets/Audio/Music/lose.ogg", 0);
				lastTime = SDL_GetTicks();
				firstCaption = false;
			}
			else {
				disableMusic(7200);
			}
			//App->audio->PlayMusic("Assets/Audio/Music/lose.ogg");
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || (pad.a == KEY_DOWN)) {

				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 30);
				boxes_lvl = 0;

			}
		}
		break;
	}
	return Update_Status::UPDATE_CONTINUE;
}

void LevelManager::playMusicLose() {
	//App->audio->music = nullptr;

	//App->musicManage->playMusic("Assets/Audio/Music/lose.ogg");
	lastTime = SDL_GetTicks();

	//Mix_PlayMusic(App->audio->music, 1);
	//App->audio->PlayMusic("Assets/Audio/Music/lose.ogg", 0);
	//App->audio->PlayFx(loseFX, 1);
	playEffect = false;


}

void LevelManager::disableMusic(int delay) {
	if (firstCaption == true){
		
		firstCaption = false;
		
	}
	
	
	if (currentTime >= lastTime + delay) {
		App->audio->PlayMusic("Assets/Audio/Music/nada.ogg",0);
		//if(App->audio->isEnabled()== true){}
		//App->audio->Disable();
		//App->audio->music = nullptr;
		//firstCaption = true;
	}


	
}

Update_Status LevelManager::PostUpdate() {

	if (godmode == true) {
		App->fonts->BlitText(App->winSize->w / 2 - 4 * 9 * 3, App->winSize->h - 50 * 3, scoreFont, "GOD MODE", 3, 158, 75, 250, (App->winSize->w - 98 * 3) / 2 + 98* 3 - 5 * 3);
	}

	return Update_Status::UPDATE_CONTINUE;
}

void LevelManager::Lose()
{
	win = 2;
}

void LevelManager::LevelComplete()
{
	switch (lvl) {
	case 1:
		if (boxes_lvl == 3) {
			win = 1;
		}
		break;
	case 2:
		if (boxes_lvl == 6) {
			win = 1;
		}
		break;

	case 3:
		if (boxes_lvl == 11) {
			win = 1;
		}
		break;
	case 4:
		if (boxes_lvl == 12) {
			win = 1;
		}
		break;
	case 5:
		if (boxes_lvl == 14) {
			win = 1;
		}
		break;
	case 6:
		if (boxes_lvl == 13) {
			win = 1;
		}
		break;
	}
	


}

int LevelManager::Getlvl() {
	return lvl;
}

bool LevelManager::CleanUp()
{
	
	App->fonts->UnLoad(0);

	return true;
}

