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
#include "LevelManager.h"

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
	
	walkDown.PushBack({ 1, 105, 24, 24 });
	walkDown.PushBack({ 27, 105, 24, 24 });
	walkDown.PushBack({ 53, 105, 24, 24 });
	walkDown.PushBack({ 79, 105, 24, 24 });
	walkDown.PushBack({ 105, 105, 24, 24 });
	walkDown.PushBack({ 131, 105, 24, 24 });
	walkDown.PushBack({ 157, 105, 24, 24 });
	walkDown.PushBack({ 183, 105, 24, 24 });
	

	walkDown.loop = true;
	walkDown.speed = 0.3f;

	// move upwards

	walkUp.PushBack({ 1, 131, 24, 24 });
	walkUp.PushBack({ 27, 131, 24, 24 });
	walkUp.PushBack({ 53, 131, 24, 24 });
	walkUp.PushBack({ 79, 131, 24, 24 });
	walkUp.PushBack({ 105, 131, 24, 24 });
	walkUp.PushBack({ 131, 131, 24, 24 });
	walkUp.PushBack({ 157, 131, 24, 24 });
	walkUp.PushBack({ 183, 131, 24, 24 });


	walkUp.loop = true;
	walkUp.speed = 0.3f;

	// move right
	
	walkRight.PushBack({ 1, 157, 24, 24 });
	walkRight.PushBack({ 27, 157, 24, 24 });
	walkRight.PushBack({ 53, 157, 24, 24 });
	walkRight.PushBack({ 79, 157, 24, 24 });
	walkRight.PushBack({ 105, 157, 24, 24 });
	walkRight.PushBack({ 131, 157, 24, 24 });
	walkRight.PushBack({ 157, 157, 24, 24 });
	walkRight.PushBack({ 183, 157, 24, 24 });
	

	walkRight.loop = true;
	walkRight.speed = 0.3f;

	// move left

	walkLeft.PushBack({ 1, 183, 24, 24 });
	walkLeft.PushBack({ 27, 183, 24, 24 });
	walkLeft.PushBack({ 53, 183, 24, 24 });
	walkLeft.PushBack({ 79, 183, 24, 24 });
	walkLeft.PushBack({ 105, 183, 24, 24 });
	walkLeft.PushBack({ 131, 183, 24, 24 });
	walkLeft.PushBack({ 157, 183, 24, 24 });
	walkLeft.PushBack({ 183, 183, 24, 24 });
	
	walkLeft.loop = true;
	walkLeft.speed = 0.3f;

	// push down

	pushDown.PushBack({ 1, 209, 24, 24 });
	pushDown.PushBack({ 27, 209, 24, 24 });
	pushDown.PushBack({ 53, 209, 24, 24 });
	pushDown.PushBack({ 79, 209, 24, 24 });
	pushDown.PushBack({ 105, 209, 24, 24 });
	pushDown.PushBack({ 131, 209, 24, 24 });
	pushDown.PushBack({ 157, 209, 24, 24 });
	pushDown.PushBack({ 183, 209, 24, 24 });

	pushDown.loop = true;
	pushDown.speed = 0.3f;

	// push up

	pushUp.PushBack({ 1, 235, 24, 24 });
	pushUp.PushBack({ 27, 235, 24, 24 });
	pushUp.PushBack({ 53, 235, 24, 24 });
	pushUp.PushBack({ 79, 235, 24, 24 });
	pushUp.PushBack({ 105, 235, 24, 24 });
	pushUp.PushBack({ 131, 235, 24, 24 });
	pushUp.PushBack({ 157, 235, 24, 24 });
	pushUp.PushBack({ 183, 235, 24, 24 });

	pushUp.loop = true;
	pushUp.speed = 0.3f;

	// push right

	pushRight.PushBack({ 1, 261, 24, 24 });
	pushRight.PushBack({ 27, 261, 24, 24 });
	pushRight.PushBack({ 53, 261, 24, 24 });
	pushRight.PushBack({ 79, 261, 24, 24 });
	pushRight.PushBack({ 105, 261, 24, 24 });
	pushRight.PushBack({ 131, 261, 24, 24 });
	pushRight.PushBack({ 157, 261, 24, 24 });
	pushRight.PushBack({ 183, 261, 24, 24 });

	pushRight.loop = true;
	pushRight.speed = 0.3f;

	// push left

	pushLeft.PushBack({ 1, 287, 24, 24 });
	pushLeft.PushBack({ 27, 287, 24, 24 });
	pushLeft.PushBack({ 53, 287, 24, 24 });
	pushLeft.PushBack({ 79, 287, 24, 24 });
	pushLeft.PushBack({ 105, 287, 24, 24 });
	pushLeft.PushBack({ 131, 287, 24, 24 });
	pushLeft.PushBack({ 157, 287, 24, 24 });
	pushLeft.PushBack({ 183, 287, 24, 24 });

	pushLeft.loop = true;
	pushLeft.speed = 0.3f;

	
	
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
	
	posInix = true;
	posIniy = true;
 
	lvl = App->lvlManage->Getlvl();
	spawn(lvl);
	 

	//if (destroyed == true) {
	//	App->collisions->RemoveCollider(collider);
	//}
	
	
	
	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 24, 24 }, Collider::Type::PLAYER, this);

	colliderR = App->collisions->AddCollider({ position.x+24, position.y, 24, 24 }, Collider::Type::TOUCH, this); 
	colliderL = App->collisions->AddCollider({ position.x-24, position.y, 24, 24 }, Collider::Type::TOUCH, this);
	colliderU = App->collisions->AddCollider({ position.x, position.y-24, 24, 24 }, Collider::Type::TOUCH, this);
	colliderD = App->collisions->AddCollider({ position.x, position.y+24, 24, 24 }, Collider::Type::TOUCH, this);

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
void ModulePlayer::spawn(int lvl) {
	
	switch (lvl) {
	case 0:
		position.x = 0;
		position.y = 0;
		break;
	case 1:
		position.x = 216;
		position.y = 144;
		break;
	case 2:
		position.x = 72;
		position.y = 48;
		break;
	case 3:
		position.x = 384;
		position.y = 240;
		break;
	default:
		position.x = 384;
		position.y = 240;
		break;

	}
}

Update_Status ModulePlayer::Update()
{
	

	
	if (countx < movx) {
		countx+=1;
		
		if (isPushingR==true) {
			currentAnimation = &pushRight;
		}
		else {
			currentAnimation = &walkRight;
		}
	}
	else if (countx == movx) {
		if (currentAnimation == &walkRight) {
			walkRight.Reset();
		}
	}


	if (countx > movx) {
		countx-=1;
		
		if (isPushingL == true) {
			currentAnimation = &pushLeft;
		}
		else {
			currentAnimation = &walkLeft;
		}
	}
	else if (countx == movx) {
		if (currentAnimation == &walkLeft) {
			walkLeft.Reset();
		}
	}

	if (county < movy) {
		county += 1 ;
		
		if (isPushingD == true) {
			currentAnimation = &pushDown;
		}
		else {
			currentAnimation = &walkDown;
		}
	}
	else if (county == movy) {
		if (currentAnimation == &walkDown) {
			walkDown.Reset();
		}
	}

	if (county > movy) {
		county -= 1;
		if (isPushingU == true) {
			currentAnimation = &pushUp;
		}
		else {

			currentAnimation = &walkUp;
		}
		
	}
	else if (county == movy) {
		if (currentAnimation == &walkUp) {
			walkUp.Reset();
		}
	}

	if (!posInix) {
		position.x = countx;
		
	}
	if (!posIniy) {
		position.y = county;

	}

	//if (App->input->keys[SDL_SCANCODE_R] == Key_State::KEY_DOWN) {
	//	App->lvlManage->lvlChange(1,'+');
	//}

	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;
	
	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
	// Moving the player with the camera scroll
	//App->player->position.x += 1;
	
	//position.x = count;
	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)&& (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		if (isTouchingL == false && isBlockedL ==false) {

		
			if (movy == county) {
				if (movx == countx) {
					movx = position.x - 24;

				}
				else {
					if (countx - movx ==0) {
						movx -= 24;
					}

				}

				walkx();

			}
			
		}
	}

	
	
	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		if (isTouchingR == false && isBlockedR == false) {
			if (movy == county) {
				if (movx == countx) {
					movx = position.x + 24;


				}
				else {
					if (movx - countx ==0) {
						movx += 24;
					}

				}
				walkx();
			}
		}
	}

	
	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE))
	{
		if (isTouchingD == false && isBlockedD == false) {
			if (movx == countx) {
				if (movy == county) {
					movy = position.y + 24;

				}
				else {
					if (movy - county ==0) {
						movy += 24;
					}

				}
				walky();
				
			}
		}
	}


	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT))
	{
		if (isTouchingU == false && isBlockedU == false) {
			if (movx == countx) {
				if (movy == county) {
					movy = position.y - 24;

				}
				else {
					if (county - movy ==0) {
						movy -= 24;
					}

				}

				walky();



			}

			
			

		}
		
	}


	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		//Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		//newParticle->collider->AddListener(this);
		//App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	///if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		///&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)
	///	currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	colliderR->SetPos(position.x+24, position.y);
	colliderL->SetPos(position.x-24, position.y);
	colliderU->SetPos(position.x, position.y-24);
	colliderD->SetPos(position.x, position.y+24);
	

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;

	//if (destroyed == true) {
	//	lvl++;
	//	spawn(lvl);
	//}
}

Update_Status ModulePlayer::PostUpdate()
{
	
	isBlockedR = false;
	isBlockedL = false;
	isBlockedU = false;
	isBlockedD = false;

	isTouchingL = false;
	isTouchingR = false;
	isTouchingU = false;
	isTouchingD = false;

	isPushingL = false;
	isPushingR = false;
	isPushingU = false;
	isPushingD = false;

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

void ModulePlayer::isStopped(char dir) {
	switch (dir) {
	case'L':
		isTouchingL = true;
		break;
	case'R':
		isTouchingR = true;
		break;
	case'U':
		isTouchingU = true;
		break;
	case'D':
		isTouchingD = true;
		break;
	}
}
void ModulePlayer::Push(char d) {
	switch (d) {
	case'L':
		isPushingL = true;
		break;
	case'R':
		isPushingR = true;
		break;
	case'U':
		isPushingU = true;
		break;
	case'D':
		isPushingD = true;
		break;
	case'N':
		isPushingL = false;
		isPushingR = false;
		isPushingU = false;
		isPushingD = false;
		break;
	}
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	//if (c1->type == Collider::Type::TOUCH && c2->type == Collider::Type::WALL) {


		/*if (c1 == collider && destroyed == false)
		{


			App->audio->PlayFx(explosionFx);
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
			//App->collisions->RemoveCollider(collider);
			destroyed = true;
		}
		*/
		
		//if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
		//{
		//	score += 23;
		//}
	//}
}

