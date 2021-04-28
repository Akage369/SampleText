#include "OrangeObject.h"

#include "Application.h"
#include "ModuleCollisions.h"

///Provisional
#include "ModuleInput.h"
#include <stdio.h>
#include "SDL/include/SDL.h"


Orange_Obj::Orange_Obj(int x, int y) : Box(x, y)
{



	orangeanim.PushBack({ 53,1,24,24 });
	currentAnim = &orangeanim;



	orangepath.PushBack({ 0.0f, 0.0f }, 1, &orangeanim);
	


}

void Orange_Obj::Update()
{

	orangepath.Update();
	position = spawnPos + orangepath.GetRelativePosition();
	currentAnim = orangepath.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	///Movimiento player
	/*
	if (countx < movx) {
		countx += 1;

	}

	if (countx > movx) {
		countx -= 1;

	}

	if (county < movy) {
		county += 1;
	}

	if (county > movy) {
		county -= 1;
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
	*/
	Box::Update();

	//collider->SetPos(position.x, position.y);
}
