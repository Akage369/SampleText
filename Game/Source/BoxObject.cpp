#include "BoxObject.h"

#include "Application.h"
#include "ModuleCollisions.h"

///Provisional
#include "ModuleInput.h"
#include <stdio.h>
#include "SDL/include/SDL.h"
#include "ModulePlayer.h"
#include "LevelManager.h"


Box_Obj::Box_Obj(int x, int y) : Box(x, y)
{
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

void Box_Obj::Stop(char dir) {
	/*
	switch (dir) {
	case'R':
		isStoppedR = true;
		break;
	case'L':
		isStoppedL= true;
		break;
	case'U':
		isStoppedU = true;
		break;
	case'D':
		isStoppedD = true;
		break;

	case'N':
		
		isStoppedR = false;
		isStoppedL = false;
		isStoppedU = false;
		isStoppedD = false;
		break;
	}
	*/
}

void Box_Obj::walkx() {
	if (posInix == true) {
		posInix = false;
	}
	countx = position.x;


}
void Box_Obj::walky() {
	if (posIniy == true) {
		posIniy = false;
	}
	county = position.y;


}



void Box_Obj::Update()
{

	if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) || (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
		|| (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) || (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN))
	{
		canStart = true;
	}

	//if (boxready == true) {
	//	currentAnim = &boxready;
		//boxpath.Update();
		//currentAnim = boxpath.GetCurrentAnimation();
	//}
	//else {
	//	currentAnim = &boxanim;
		//boxpath.Update();
		//currentAnim = boxpath.GetCurrentAnimation();

	//}
	///////////////el que va mejor

	/*
	if ( App->player->collider->rect.y == colliderBR->rect.y && (App->player->collider->rect.x == colliderBR->rect.x || App->player->collider->rect.x + zoom == colliderBR->rect.x ) ){
		
		inContactR = true;
		inContactL = false;
		inContactU = false;
		inContactD = false;
		
		
	}
	else if (App->player->collider->rect.y == colliderBL->rect.y && (App->player->collider->rect.x == colliderBL->rect.x || App->player->collider->rect.x == zoom + colliderBL->rect.x )) {

		inContactR = false;
		inContactL = true;
		inContactU = false;
		inContactD = false;

	}
	else if (App->player->collider->rect.x == colliderBU->rect.x && (App->player->collider->rect.y == colliderBU->rect.y || App->player->collider->rect.y  == zoom+colliderBU->rect.y)) {

		inContactR = false;
		inContactL = false;
		inContactU = true;
		inContactD = false;
	}
	else if (App->player->collider->rect.x == colliderBD->rect.x && (App->player->collider->rect.y  == colliderBD->rect.y || App->player->collider->rect.y + zoom == colliderBD->rect.y )) {
		inContactR = false;
		inContactL = false;
		inContactU = false;
		inContactD = true;
	}
	else {
		inContactR = false;
		inContactL = false;
		inContactU = false;
		inContactD = false;
	}
	*/
	/*
	if (App->player->collider->rect.y == colliderBR->rect.y && (App->player->collider->rect.x >= colliderBR->rect.x )) {

		inContactR = true;
		inContactL = false;
		inContactU = false;
		inContactD = false;


	}
	else if (App->player->collider->rect.y == colliderBL->rect.y && (App->player->collider->rect.x <= colliderBL->rect.x )) {

		inContactR = false;
		inContactL = true;
		inContactU = false;
		inContactD = false;

	}
	else if (App->player->collider->rect.x == colliderBU->rect.x && (App->player->collider->rect.y <= colliderBU->rect.y )) {

		inContactR = false;
		inContactL = false;
		inContactU = true;
		inContactD = false;
	}
	else if (App->player->collider->rect.x == colliderBD->rect.x && (App->player->collider->rect.y >= colliderBD->rect.y)) {
		inContactR = false;
		inContactL = false;
		inContactU = false;
		inContactD = true;
	}
	else {
		inContactR = false;
		inContactL = false;
		inContactU = false;
		inContactD = false;
	}
	*/

	/* ////////////Original de colisiones
	if ( App->player->collider->rect.y == colliderBR->rect.y && (App->player->collider->rect.x == colliderBR->rect.x || 
		App->player->collider->rect.x + 1 == colliderBR->rect.x ||  App->player->collider->rect.x  == 1+ colliderBR->rect.x||
		App->player->collider->rect.x + 2 == colliderBR->rect.x || App->player->collider->rect.x == 2 + colliderBR->rect.x) ){
		
		inContactR = true;
		inContactL = false;
		inContactU = false;
		inContactD = false;
		
		
	}
	else if (App->player->collider->rect.y == colliderBL->rect.y && (App->player->collider->rect.x == colliderBL->rect.x || 
		App->player->collider->rect.x + 1 == colliderBL->rect.x || App->player->collider->rect.x == 1 + colliderBL->rect.x ||
		App->player->collider->rect.x + 2 == colliderBL->rect.x || App->player->collider->rect.x == 2 + colliderBL->rect.x)) {

		inContactR = false;
		inContactL = true;
		inContactU = false;
		inContactD = false;

	}
	else if (App->player->collider->rect.x == colliderBU->rect.x && (App->player->collider->rect.y == colliderBU->rect.y || 
		App->player->collider->rect.y + 1 == colliderBU->rect.y || App->player->collider->rect.y == 1 + colliderBU->rect.y ||
		App->player->collider->rect.y + 2 == colliderBU->rect.y || App->player->collider->rect.y == 2 + colliderBU->rect.y)) {

		inContactR = false;
		inContactL = false;
		inContactU = true;
		inContactD = false;
	}
	else if (App->player->collider->rect.x == colliderBD->rect.x && (App->player->collider->rect.y + 1 == colliderBD->rect.y || 
		App->player->collider->rect.y + 1 == colliderBD->rect.y || App->player->collider->rect.y == 1 + colliderBD->rect.y ||
		App->player->collider->rect.y + 2 == colliderBD->rect.y || App->player->collider->rect.y == 2 + colliderBD->rect.y)) {
		inContactR = false;
		inContactL = false;
		inContactU = false;
		inContactD = true;
	}
	else {
		inContactR = false;
		inContactL = false;
		inContactU = false;
		inContactD = false;
	}
	*/
	
	/*
	if ( App->player->collider->rect.y == colliderBR->rect.y && App->player->collider->rect.x  == colliderBR->rect.x ){
		
		inContactR = true;
		inContactL = false;
		inContactU = false;
		inContactD = false;
		
		
	}
	else if (App->player->collider->rect.y == colliderBL->rect.y && App->player->collider->rect.x == colliderBL->rect.x) {

		inContactR = false;
		inContactL = true;
		inContactU = false;
		inContactD = false;

	}
	else if (App->player->collider->rect.y == colliderBU->rect.y && App->player->collider->rect.x == colliderBU->rect.x) {

		inContactR = false;
		inContactL = false;
		inContactU = true;
		inContactD = false;
	}
	else if (App->player->collider->rect.y == colliderBD->rect.y && App->player->collider->rect.x == colliderBD->rect.x) {
		inContactR = false;
		inContactL = false;
		inContactU = false;
		inContactD = true;
	}
	else {
		inContactR = false;
		inContactL = false;
		inContactU = false;
		inContactD = false;
	}*/
	/*
	else if (App->player->collider->rect.x == colliderBR->rect.x && App->player->collider->rect.y == colliderBR->rect.y) ||
		(App->player->collider->rect.x == colliderBL->rect.x && App->player->collider->rect.y == colliderBL->rect.y) ||
		(App->player->collider->rect.x == colliderBU->rect.x && App->player->collider->rect.y == colliderBU->rect.y) ||
		(App->player->collider->rect.x == colliderBD->rect.x && App->player->collider->rect.y == colliderBD->rect.y) {
		
			inContactR = App->player->isPushingL;
			inContactL = App->player->isPushingR;
			inContactU = App->player->isPushingD;
			inContactD = App->player->isPushingU;
			*/

	//boxpath.Update();
	//position = spawnPos + boxpath.GetRelativePosition();
	//currentAnim = boxpath.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	///Movimiento player
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

		

		//if (App->input->keys[SDL_SCANCODE_R] == Key_State::KEY_DOWN) {
		//	App->lvlManage->lvlChange(1,'+');
		//}


		// Moving the player with the camera scroll
		//App->player->position.x += 1;

		//position.x = count;
		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			&& (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)&& canStart==true)
		{

			if (inContactR==true && isStoppedL==false) {

				if (movy == county) {
					if (movx == countx) {
						movx = position.x - 24 * zoom;

					}
					else {
						if (countx - movx < 4) {
							movx -= 24 * zoom;
						}

					}

					///walkx();
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
			if (inContactL == true && isStoppedR == false) {
				if (movy == county) {
					if (movx == countx) {
						movx = position.x + 24 * zoom;


					}
					else {
						if (movx - countx < 4) {
							movx += 24 * zoom;
						}
					}
					///walkx();
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
			if (inContactU == true && isStoppedD == false) {
				if (movx == countx) {
					if (movy == county) {
						movy = position.y + 24 * zoom;

					}
					else {
						if (movy - county < 4) {
							movy += 24 * zoom;
						}

					}

					///walky();
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
			if (inContactD == true && isStoppedU == false) {
				if (movx == countx) {
					if (movy == county) {
						movy = position.y - 24 * zoom;

					}
					else {
						if (county - movy < 4) {
							movy -= 24 * zoom;
						}

					}
					///walky();
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

	//isStoppedR = false;
	//isStoppedL = false;
	//isStoppedU = false;
	//isStoppedD = false;

	
Box::Update();

}







