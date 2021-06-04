#include "BoxObject.h"

#include "Application.h"
#include "ModuleCollisions.h"

///Provisional
#include "ModuleInput.h"
#include <stdio.h>
#include "SDL/include/SDL.h"
#include "ModulePlayer.h"
#include "LevelManager.h"
#include "SceneLevel1.h"


Box_Obj::Box_Obj(int x, int y) : Box(x, y)
{
	switch (App->lvlManage->Getlvl()) {
	case 1:
		zoom = 5;
		break;
	case 2:
		zoom = 4;
		break;
	case 3:
		zoom = 3;
		break;
	case 4:
		zoom = 3;
		break;
	case 5:
		zoom = 3;
		break;
	case 6:
		zoom = 3;
		break;
	default:
		zoom = 1;
		break;
	}
	

	boxanim.PushBack({ 105,1,24,24 });
	boxready.PushBack({ 131,1,24,24 });

	currentAnim = &boxanim;
	countx = 0;
	county = 0;
	//boxpath.PushBack({ 0.0f, 0.0f }, 100, &boxanim);

	//boxready.PushBack({ 131,1,24,24 });
	//countx = 0;
	//county = 0;
	//boxpath.PushBack({ 0.0f, 0.0f },100, &boxready); 

	collider = App->collisions->AddCollider({ 0, 0, 24*zoom, 24 * zoom }, Collider::Type::BOX, (Module*)App->boxes);
	colliderBR = App->collisions->AddCollider({( position.x + 24)* zoom, position.y, 24 * zoom, 24 * zoom }, Collider::Type::TOUCHB, (Module*)App->boxes);
	colliderBL = App->collisions->AddCollider({ (position.x - 24) * zoom, position.y, 24 * zoom, 24 * zoom }, Collider::Type::TOUCHB, (Module*)App->boxes);
	colliderBU = App->collisions->AddCollider({ position.x * zoom, (position.y - 24) * zoom, 24 * zoom, 24 * zoom }, Collider::Type::TOUCHB, (Module*)App->boxes);
	colliderBD = App->collisions->AddCollider({ position.x * zoom, (position.y + 24) * zoom, 24 * zoom, 24 * zoom }, Collider::Type::TOUCHB, (Module*)App->boxes);

	canStart = false;

}

Collider* Box_Obj::GetLateralColliderBR(){
	return colliderBR;
}
Collider* Box_Obj::GetLateralColliderBL() {
	return colliderBL;
}
Collider* Box_Obj::GetLateralColliderBU() {
	return colliderBU;
}
Collider* Box_Obj::GetLateralColliderBD() {
	return colliderBD;
}

void Box_Obj::Update()
{

	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) || (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
		|| (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) || (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN))
	{
		canStart = true;
	}

	if (countx < movx) {
		countx += 1*zoom;

	}

	if (countx > movx) {
		countx -= 1 * zoom;

	}

	if (county < movy) {
		county += 1 * zoom;
	}

	if (county > movy) {
		county -= 1 * zoom;
	}


	if (!posInix) {
		position.x = countx;

	}
	if (!posIniy) {
		position.y = county;

	}


	if (inContactR==true|| inContactL== true || inContactU == true || inContactD == true ) {

		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)&& canStart==true)
		{

			if (inContactR==true && isStoppedL==false && App->sceneLevel_1->pause == false) {

				if (movy == county) {
					if (movx == countx) {
						movx = position.x - 24 * zoom;

					}
					
					if (posInix == true) {
						posInix = false;
					}
					countx = position.x;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE) && canStart == true)
		{
			if (inContactL == true && isStoppedR == false && App->sceneLevel_1->pause == false) {
				if (movy == county) {
					if (movx == countx) {
						movx = position.x + 24 * zoom;


					}
					
				
					if (posInix == true) {
						posInix = false;
					}
					countx = position.x;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE) && canStart == true)
		{
			if (inContactU == true && isStoppedD == false && App->sceneLevel_1->pause == false) {
				if (movx == countx) {
					if (movy == county) {
						movy = position.y + 24 * zoom;

					}
					
					if (posIniy == true) {
						posIniy = false;
					}
					county = position.y;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) && canStart == true)
		{
			if (inContactD == true && isStoppedU == false && App->sceneLevel_1->pause == false) {
				if (movx == countx) {
					if (movy == county) {
						movy = position.y - 24 * zoom;

					}
					
					if (posIniy == true) {
						posIniy = false;
					}
					county = position.y;
				}
			}

		}

		

		
	}

	if (isReady == false) {
		currentAnim = &boxanim;
	}
	else if (movx == countx && movy == county) {
		{
			currentAnim = &boxready;
		}
	}
	

	collider->SetPos(position.x, position.y);
	colliderBR->SetPos(position.x + 24 * zoom, position.y);
	colliderBL->SetPos(position.x - 24 * zoom, position.y);
	colliderBU->SetPos(position.x, position.y - 24 * zoom);
	colliderBD->SetPos(position.x, position.y + 24 * zoom);

	
Box::Update();

}







