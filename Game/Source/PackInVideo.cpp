#include "SceneIntro.h"
#include "PackInVideo.h"
#include "Presentation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "LevelManager.h"
#include "ModuleWindow.h"
#include "WindowSize.h"
#include "ModuleFonts.h"

PackInVideo::PackInVideo(bool startEnabled) : Module(startEnabled)
{
	packAnim.PushBack({ 1, 1, 256, 224 });
	packAnim.PushBack({ 258, 1, 256, 224 });
	packAnim.PushBack({ 515, 1, 256, 224 });
	packAnim.PushBack({ 772, 1, 256, 224 });
	packAnim.PushBack({ 1029, 1, 256, 224 });
	packAnim.PushBack({ 1286, 1, 256, 224 });
	packAnim.PushBack({ 1543, 1, 256, 224 });

	packAnim.PushBack({ 1, 226, 256, 224 });
	packAnim.PushBack({ 258, 226, 256, 224 });
	packAnim.PushBack({ 515, 226, 256, 224 });
	packAnim.PushBack({ 772, 226, 256, 224 });
	packAnim.PushBack({ 1029, 226, 256, 224 });
	packAnim.PushBack({ 1286, 226, 256, 224 });
	packAnim.PushBack({ 1543, 226, 256, 224 });

	packAnim.PushBack({ 1, 451, 256, 224 });
	packAnim.PushBack({ 258, 451, 256, 224 });
	packAnim.PushBack({ 515, 451, 256, 224 });
	packAnim.PushBack({ 772, 451, 256, 224 });
	packAnim.PushBack({ 1029, 451, 256, 224 });
	packAnim.PushBack({ 1286, 451, 256, 224 });
	packAnim.PushBack({ 1543, 451, 256, 224 });

	packAnim.PushBack({ 1, 676, 256, 224 });
	packAnim.PushBack({ 258, 676, 256, 224 });
	packAnim.PushBack({ 515, 676, 256, 224 });
	packAnim.PushBack({ 772, 676, 256, 224 });
	packAnim.PushBack({ 1029, 676, 256, 224 });
	packAnim.PushBack({ 1286, 676, 256, 224 });

	

	packAnim.pingpong = false;
	packAnim.loop = false;
	packAnim.speed = 1;
}

PackInVideo::~PackInVideo()
{

}

bool PackInVideo::Start()
{
	LOG("Loading background assets");
	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	scoreFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);
	bool ret = true;

	//bgTexture = App->textures->Load("Assets/Textures/spritesheet_menus.png");
	bgTexture = App->textures->Load("Assets/Textures/pack_in_video.png");

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->lvlManage->changeScene = true;
	zoom = 4;
	canInput = false;
	currentAnimationPack = &packAnim;
	return ret;
}

Update_Status PackInVideo::Update()
{
	GamePad& pad = App->input->pads[0];

	currentAnimationPack = &packAnim;
	if (App->lvlManage->godmode == true) {
		if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
			App->fade->FadeToBlack(this, (Module*)App->presentation, 20);
		}
	}

	if (currentAnimationPack->GetCurrentFrame().x == 1 && currentAnimationPack->GetCurrentFrame().y == 1 && canInput == true) {
		currentAnimationPack->speed = 0;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && canInput == true)
	{
		
			currentAnimationPack->pingpong = true;
		
		


		App->fade->FadeToBlack(this, (Module*)App->introAnim, 60);



	}
	
	if (currentAnimationPack->HasFinished()) 
	{
		canInput = true;
		
	}
	currentAnimationPack->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status PackInVideo::PostUpdate()
{
	pack_rect = currentAnimationPack->GetCurrentFrame();
	App->render->Blit(bgTexture, (App->winSize->w - pack_rect.w * zoom) / 2, (App->winSize->h - pack_rect.h * zoom) / 2, &pack_rect, 1.0f, true, zoom);
	//App->render->Blit(bgTexture, (App->winSize->w - rect.w *zoom)/2, (App->winSize->h- rect.h *zoom)/2,&rect, 1.0f, true, zoom);
	if (App->lvlManage->godmode == true) {
		App->fonts->BlitText(App->winSize->w / 2 - 4 * 9 * 3, App->winSize->h - 50 * 3, scoreFont, "GOD MODE", 3, 158, 75, 250, (App->winSize->w - 98 * 3) / 2 + 98 * 3 - 5 * 3);
	}

	return Update_Status::UPDATE_CONTINUE; 
}

bool PackInVideo::CleanUp()
{
	currentAnimationPack = nullptr;
	delete currentAnimationPack;
	App->fonts->UnLoad(scoreFont);
	App->textures->Unload(bgTexture);
	App->packInVideo->Disable();
	return true;
}