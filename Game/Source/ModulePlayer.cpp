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
#include "SDL/include/SDL.h"

#include <stdio.h>


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	
	idleDown.PushBack({ 1, 1, 24, 24 });
	idleUp.PushBack({ 1, 27, 24, 24 });
	idleRight.PushBack({ 1, 53, 24, 24 });
	idleLeft.PushBack({ 1, 79, 24, 24 });

	// Move down
	
	walkDown.PushBack({ 27, 105, 24, 24 });
	walkDown.PushBack({ 53, 105, 24, 24 });
	walkDown.PushBack({ 79, 105, 24, 24 });
	walkDown.PushBack({ 105, 105, 24, 24 });
	walkDown.PushBack({ 131, 105, 24, 24 });
	walkDown.PushBack({ 157, 105, 24, 24 });
	walkDown.PushBack({ 183, 105, 24, 24 });
	walkDown.PushBack({ 1, 105, 24, 24 });

	walkDown.loop = false;
	walkDown.speed = 0.1f;

	// move upwards

	walkUp.PushBack({ 27, 131, 24, 24 });
	walkUp.PushBack({ 53, 131, 24, 24 });
	walkUp.PushBack({ 79, 131, 24, 24 });
	walkUp.PushBack({ 105, 131, 24, 24 });
	walkUp.PushBack({ 131, 131, 24, 24 });
	walkUp.PushBack({ 157, 131, 24, 24 });
	walkUp.PushBack({ 183, 131, 24, 24 });
	walkUp.PushBack({ 1, 131, 24, 24 });

	walkUp.loop = false;
	walkUp.speed = 0.1f;

	// move right
	
	walkRight.PushBack({ 27, 157, 24, 24 });
	walkRight.PushBack({ 53, 157, 24, 24 });
	walkRight.PushBack({ 79, 157, 24, 24 });
	walkRight.PushBack({ 105, 157, 24, 24 });
	walkRight.PushBack({ 131, 157, 24, 24 });
	walkRight.PushBack({ 157, 157, 24, 24 });
	walkRight.PushBack({ 183, 157, 24, 24 });
	walkRight.PushBack({ 1, 157, 24, 24 });

	walkRight.loop = false;
	walkRight.speed = 0.1f;

	// move left

	walkLeft.PushBack({ 27, 183, 24, 24 });
	walkLeft.PushBack({ 53, 183, 24, 24 });
	walkLeft.PushBack({ 79, 183, 24, 24 });
	walkLeft.PushBack({ 105, 183, 24, 24 });
	walkLeft.PushBack({ 131, 183, 24, 24 });
	walkLeft.PushBack({ 157, 183, 24, 24 });
	walkLeft.PushBack({ 183, 183, 24, 24 });
	walkLeft.PushBack({ 1, 183, 24, 24 });

	walkLeft.loop = false;
	walkLeft.speed = 0.1f;

	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	///Lookup table
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	
	scoreFont = App->fonts->Load("Assets/Textures/rtype_font3.png", lookupTable, 2);
	

	texture = App->textures->Load("Assets/Textures/spritesheet_player.png");
	currentAnimation = &idleLeft;

	laserFx = App->audio->LoadFx("Assets/Audio/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Audio/Fx/explosion.wav");

	position.x = 96;
	position.y = 48;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 24, 24 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	
	return ret;
}
void ModulePlayer::walkx() {
	if (posInix == true) {
		posInix = false;
	}
	countx = position.x;
	
	
}
void ModulePlayer::walky() {
	if (posIniy == true) {
		posIniy = false;
	}
	county = position.y;
	

}
Update_Status ModulePlayer::Update()
{
	if (countx < movx) {
		countx+=2;
	}
	else if (countx > movx) {
		countx-=2;
	}

	if (county < movy) {
		county += 2 ;
	}
	else if (county > movy) {
		county -= 2;
	}

	if (!posInix) {
		position.x = countx;
		
	}
	if (!posIniy) {
		position.y = county;

	}


	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;
	
	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
	// Moving the player with the camera scroll
	//App->player->position.x += 1;
	
	//position.x = count;
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
	{
		
		movx = position.x - 24;
		walkx();

	

		
		
			walkLeft.Reset();
			currentAnimation = &walkLeft;
		 
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
	{
		
		movx = position.x + 24;
		walkx();

			walkRight.Reset();
			currentAnimation = &walkRight;

	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{
		
		movy = position.y + 24;
		walky();

			walkDown.Reset();
			currentAnimation = &walkDown;
		
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN)
	{
		
		movy = position.y - 24;
		walky();

		walkRight.Reset();
		currentAnimation = &walkRight;

		
		
			walkUp.Reset();
			currentAnimation = &walkUp;
		
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		newParticle->collider->AddListener(this);
		App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	///if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		///&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)
	///	currentAnimation = &idleAnim;

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