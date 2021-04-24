#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
///Tiles
#include "Tiles.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 66, 1, 32, 14 });

	// move upwards
	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Textures/ship.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Audio/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Audio/Fx/explosion.wav");

	position.x = 150;
	position.y = 120;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	char tilesetTable[] = { "WwobCcB" };
	scoreFont = App->fonts->Load("Assets/Textures/rtype_font3.png", lookupTable, 2);
	lvl1_map = App->tiles->Load("Assets/Textures/spritesheet_tiles.png", tilesetTable, 1);
	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	App->player->position.x += 1;

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		newParticle->collider->AddListener(this);
		App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);


	///Tiles ///Imprime todas las texturas seguidas
	/// 
	//App->tiles->BlitScene(0, 120,lvl1_map, "WwobCcBwwWBBC");
	///
 
	///Nivel 1
	/// Paredes
	App->tiles->BlitScene(312, 24, lvl1_map, "W");
	App->tiles->BlitScene(312, 48, lvl1_map, "W");
	App->tiles->BlitScene(312, 72, lvl1_map, "W");
	App->tiles->BlitScene(312, 96, lvl1_map, "w");
	App->tiles->BlitScene(336, 96, lvl1_map, "w");
	App->tiles->BlitScene(288, 96, lvl1_map, "W");
	App->tiles->BlitScene(288, 120, lvl1_map, "W");
	App->tiles->BlitScene(288, 144, lvl1_map, "W");
	App->tiles->BlitScene(288, 168, lvl1_map, "W");
	App->tiles->BlitScene(288, 192, lvl1_map, "w");
	App->tiles->BlitScene(312, 192, lvl1_map, "w");
	App->tiles->BlitScene(336, 192, lvl1_map, "w");
	App->tiles->BlitScene(360, 192, lvl1_map, "w");
	App->tiles->BlitScene(384, 192, lvl1_map, "w");
	App->tiles->BlitScene(384, 168, lvl1_map, "W");
	App->tiles->BlitScene(384, 144, lvl1_map, "W");
	App->tiles->BlitScene(384, 120, lvl1_map, "W");
	App->tiles->BlitScene(408, 168, lvl1_map, "w");
	App->tiles->BlitScene(432, 168, lvl1_map, "w");
	App->tiles->BlitScene(456, 168, lvl1_map, "w");
	App->tiles->BlitScene(480, 168, lvl1_map, "w");
	App->tiles->BlitScene(480, 144, lvl1_map, "W");
	App->tiles->BlitScene(480, 120, lvl1_map, "W");
	App->tiles->BlitScene(480, 96, lvl1_map, "W");
	App->tiles->BlitScene(480, 72, lvl1_map, "W");
	App->tiles->BlitScene(456, 72, lvl1_map, "w");
	App->tiles->BlitScene(432, 72, lvl1_map, "w");
	App->tiles->BlitScene(408, 72, lvl1_map, "w");
	App->tiles->BlitScene(336, 24, lvl1_map, "w");
	App->tiles->BlitScene(360, 24, lvl1_map, "w");
	App->tiles->BlitScene(384, 24, lvl1_map, "w");
	App->tiles->BlitScene(408, 24, lvl1_map, "w");
	App->tiles->BlitScene(432, 24, lvl1_map, "w");
	App->tiles->BlitScene(456, 24, lvl1_map, "W");
	App->tiles->BlitScene(456, 48, lvl1_map, "W");
	App->tiles->BlitScene(432, 120, lvl1_map, "w");
	///Suelo
	App->tiles->BlitScene(336, 48, lvl1_map, "b");
	App->tiles->BlitScene(360, 48, lvl1_map, "b");
	App->tiles->BlitScene(384, 48, lvl1_map, "b");
	App->tiles->BlitScene(408, 48, lvl1_map, "b");
	App->tiles->BlitScene(432, 48, lvl1_map, "b");

	App->tiles->BlitScene(336, 72, lvl1_map, "b");
	App->tiles->BlitScene(360, 72, lvl1_map, "b");
	App->tiles->BlitScene(384, 72, lvl1_map, "b");

	App->tiles->BlitScene(360, 96, lvl1_map, "b");
	App->tiles->BlitScene(384, 96, lvl1_map, "b");
	App->tiles->BlitScene(408, 96, lvl1_map, "b");
	App->tiles->BlitScene(432, 96, lvl1_map, "b");
	App->tiles->BlitScene(456, 96, lvl1_map, "b");

	App->tiles->BlitScene(312, 120, lvl1_map, "b");
	App->tiles->BlitScene(336, 120, lvl1_map, "b");
	App->tiles->BlitScene(360, 120, lvl1_map, "b");
	App->tiles->BlitScene(408, 120, lvl1_map, "b");
	App->tiles->BlitScene(456, 120, lvl1_map, "b");

	App->tiles->BlitScene(312, 144, lvl1_map, "b");
	App->tiles->BlitScene(336, 144, lvl1_map, "b");
	App->tiles->BlitScene(360, 144, lvl1_map, "b");
	App->tiles->BlitScene(408, 144, lvl1_map, "b");
	App->tiles->BlitScene(432, 144, lvl1_map, "b");
	App->tiles->BlitScene(456, 144, lvl1_map, "b");

	App->tiles->BlitScene(312, 168, lvl1_map, "b");
	App->tiles->BlitScene(336, 168, lvl1_map, "b");
	App->tiles->BlitScene(360, 168, lvl1_map, "b");
	

	
	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(58, 248, scoreFont, scoreText);

	App->fonts->BlitText(150, 248, scoreFont, "this is just a font test");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}