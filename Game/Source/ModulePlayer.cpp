#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneLevel1.h"

#include "Tiles.h"
#include "LevelManager.h"

#include "SDL/include/SDL.h"

#include <stdio.h>


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	
	idleDown.PushBack({ 1, 1, 24, 24 });
	idleUp.PushBack({ 1, 27, 24, 24 });
	idleRight.PushBack({ 1, 53, 24, 24 });
	idleLeft.PushBack({ 1, 79, 24, 24 });
	
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
	
	texture = App->textures->Load("Assets/Textures/spritesheet_player.png");
	currentAnimation = &idleLeft;

	laserFx = App->audio->LoadFx("Assets/Audio/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Audio/Fx/explosion.wav");
	
	posInix = true;
	posIniy = true;
 
	lvl = App->lvlManage->Getlvl();

	switch (App->lvlManage->Getlvl()) {
	case 1:
		zoom = 3;
		break;
	case 3:
		zoom = 2;
		break;
	case 4:
		zoom = 1;
		break;
	case 5:
		zoom = 1;
		break;
	case 6:
		zoom = 1;
		break;
	case 2:
		zoom = 2;
		break;
	default:
		zoom = 1;
		break;
	}

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x*zoom, position.y*zoom, 24*zoom, 24*zoom }, Collider::Type::PLAYER, this);

	colliderR = App->collisions->AddCollider({ (position.x+24)*zoom, position.y*zoom, 24*zoom, 24*zoom }, Collider::Type::TOUCH, this); 
	colliderL = App->collisions->AddCollider({ (position.x-24)*zoom, position.y*zoom, 24*zoom, 24*zoom }, Collider::Type::TOUCH, this);
	colliderU = App->collisions->AddCollider({ position.x*zoom, (position.y-24)*zoom, 24*zoom, 24*zoom }, Collider::Type::TOUCH, this);
	colliderD = App->collisions->AddCollider({ position.x*zoom, (position.y+24)*zoom, 24*zoom, 24*zoom }, Collider::Type::TOUCH, this);

	spawn(lvl);
	
	isTouchingL = false;
	isTouchingR = false;
	isTouchingU = false;
	isTouchingD = false;

	inContactL = false;
	inContactR = false;
	inContactU = false;
	inContactD = false;

	lastTime = SDL_GetTicks();
	
	 canStart = false;

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
		position.x = -12 + 96 * zoom; 
		position.y = -24 + 48 * zoom; 
		break;
	case 2:
		position.x = 264 * zoom;
		position.y = 216 * zoom;
		break;
	case 3:
		position.x = 72 * zoom;
		position.y = 48 * zoom;
		break;
	case 4:
		position.x = 504 * zoom;
		position.y = 312 * zoom;
		break;
	case 5:
		position.x = 360 *zoom ;
		position.y = 312 * zoom;
		break;
	case 6:
		position.x = 240 * zoom;
		position.y = 336 * zoom;
		break;
	}

	collider->SetPos(0,0);
	colliderR->SetPos(0,0);
	colliderL->SetPos(0, 0);
	colliderU->SetPos(0, 0);
	colliderD->SetPos(0, 0);
	collider->SetPos(0, 0);

}

Update_Status ModulePlayer::Update()
{
	currentTime = SDL_GetTicks();
	
	score = App->lvlManage->boxes_lvl;
	if (App->lvlManage->steps >= App->lvlManage->max_steps) {
		if (App->sceneLevel_1->godmode == false) {
			App->lvlManage->Lose();
		}
	
		
	}
	
	if ((currentTime > lastTime + delay)) {

		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) || (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
			|| (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) || (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN))
		{
			canStart = true;
		}

		if (countx < movx) {
			countx += 1 * zoom;

			if (isPushingR == true) {
				currentAnimation = &pushRight;
			}
			else {
				currentAnimation = &walkRight;
			}
		}

		if (countx > movx) {
			countx -= 1 * zoom;

			if (isPushingL == true) {
				currentAnimation = &pushLeft;
			}
			else {
				currentAnimation = &walkLeft;
			}
		}

		if (county < movy) {
			county += 1 * zoom;

			if (isPushingD == true) {
				currentAnimation = &pushDown;
			}
			else {
				currentAnimation = &walkDown;
			}
		}

		if (county > movy) {
			county -= 1 * zoom;
			if (isPushingU == true) {
				currentAnimation = &pushUp;
			}
			else {

				currentAnimation = &walkUp;
			}

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
		
		if (App->lvlManage->win == 0) {
			if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
				&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE) && canStart == true)
			{
				if (isTouchingL == false && isBlockedL == false&&App->sceneLevel_1->pause==false) {

					App->sceneLevel_1->noUI = false;

					if (inContactL == true) {
						isPushingL = true;
					}

					if (movy == county) {
						if (movx == countx) {
							movx = position.x - 24 * zoom;
							App->lvlManage->steps++;
						}
						else {
							if (countx - movx == 0) {
								movx -= 24 * zoom;
								App->lvlManage->steps++;
							}
						}
						walkx();
					}
				}
			}

			if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
				&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE) && canStart == true)
			{
				if (isTouchingR == false && isBlockedR == false && App->sceneLevel_1->pause == false) {

					App->sceneLevel_1->noUI = false;

					if (inContactR == true) {
						isPushingR = true;
					}

					if (movy == county) {
						if (movx == countx) {
							movx = position.x + 24 * zoom;
							App->lvlManage->steps++;


						}
						else {
							if (movx - countx == 0) {
								movx += 24 * zoom;
								App->lvlManage->steps++;
							}
						}
						walkx();
					}
				}
			}

			if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
				&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE) && canStart == true)
			{
				if (isTouchingD == false && isBlockedD == false && App->sceneLevel_1->pause == false) {

					App->sceneLevel_1->noUI = false;

					if (inContactD == true) {
						isPushingD = true;
					}

					if (movx == countx) {
						if (movy == county) {
							movy = position.y + 24 * zoom;
							App->lvlManage->steps++;
						}
						else {
							if (movy - county == 0) {
								movy += 24 * zoom;
								App->lvlManage->steps++;
							}

						}
						walky();

					}
				}
			}

			if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
				&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)&& canStart==true)
			{
				if (isTouchingU == false && isBlockedU == false && App->sceneLevel_1->pause == false) {

					App->sceneLevel_1->noUI = false;

					if (inContactU == true) {
						isPushingU = true;
					}

					if (movx == countx) {
						if (movy == county) {
							movy = position.y - 24 * zoom;
							App->lvlManage->steps++;

						}
						else {
							if (county - movy == 0) {
								movy -= 24 * zoom;
								App->lvlManage->steps++;
							}

						}

						walky();



					}
				}
			}
		}

		if (countx == movx && county == movy)
		{
			isPushingL = false;
			isPushingR = false;
			isPushingU = false;
			isPushingD = false;

			if (currentAnimation == &walkDown || currentAnimation == &pushDown) {
				currentAnimation = &walkDown;
				walkDown.Reset();
			}
			if (currentAnimation == &walkLeft || currentAnimation == &pushLeft) {
				currentAnimation = &walkLeft;
				walkLeft.Reset();
			}
			if (currentAnimation == &walkUp || currentAnimation == &pushUp) {
				currentAnimation = &walkUp;
				walkUp.Reset();
			}
			if (currentAnimation == &walkRight || currentAnimation == &pushRight) {
				currentAnimation = &walkRight;
				walkRight.Reset();
			}
		}

		collider->SetPos(position.x, position.y);

		colliderR->SetPos(position.x + 24 * zoom, position.y);
		colliderL->SetPos(position.x - 24 * zoom, position.y);
		colliderU->SetPos(position.x, position.y - 24 * zoom);
		colliderD->SetPos(position.x, position.y + 24 * zoom);

		currentAnimation->Update();
	}

	return Update_Status::UPDATE_CONTINUE;
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

}

