#include "SceneIntro.h"
#include "Presentacion.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "LevelManager.h"


SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	
	LOG("Loading background assets");
	
	bool ret = true;

	scroller1 = App->textures->Load("Assets/Textures/spritesheet_intro_fondo.png");
	bgTexto = App->textures->Load("Assets/Textures/spritesheet_intro_texto.png");
	puntero = App->textures->Load("Assets/Textures/puntero");
	scroller2 = App->textures->Load("Assets/Textures/spritesheet_intro_fondo.png");
	BoxMenu = App->textures->Load("Assets/Textures/menu_caja");
	App->audio->PlayMusic("Assets/Audio/Music/introTitle.ogg", 1.0f);


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	p_pos.x = p_x;
	p_pos.y = p_y;

	MenuMusic = App->audio->PlayMusic("Assets/Music/", 1.0f); //Falta por determinar sonido
	selectFx = App->audio->LoadFx("Assets"); //Falta por determinar sonido
	nextFx = App->audio->LoadFx("Assets"); //Falta por determinar sonido
	backFx = App->audio->LoadFx("Assets"); //Falta por determinar sonido

	return ret;
}

Update_Status SceneIntro::Update()
{
	scrollerY -= -1;
	scroller2Y -= -1;

	if (scrollerY < -1036) {
		scrollerY = 1034;
	}
	if (scroller2Y < -1036) {
		scroller2Y = 1034;
	}

	//input teclas
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->audio->PlayFx(selectFx);
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 20);
		//lvl++;
		//App->player->spawn(lvl);
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) {
		if (M_index < 2) {
			M_index++;
			p_y -= 13;
			App->audio->PlayFx(selectFx);
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) {
		if (M_index > 0) {
			M_index--;
			p_y += 13;
			App->audio->PlayFx(selectFx);
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(scroller1, 0, scrollerY, NULL);
	App->render->Blit(scroller2, 0, scroller2Y, NULL);
	App->render->Blit(BoxMenu, 150, 140, NULL);
	App->render->Blit(bgTexto, 140, 125, NULL);

	App->render->Blit(bgTexture, SCREEN_WIDTH / 2 - 115, SCREEN_HEIGHT / 2 - 120, NULL);
	App->render->Blit(puntero, p_x, p_y, NULL);

	//App->fonts->BlitText(SCREEN_WIDTH / 2 -20, 150)

	return Update_Status::UPDATE_CONTINUE;
}