#include "BallObject.h"

#include "Application.h"
#include "ModuleCollisions.h"

///Provisional
#include "ModuleInput.h"
#include <stdio.h>
#include "SDL/include/SDL.h"
#include "ModuleBoxes.h"




Ball_Obj::Ball_Obj(int x, int y) : Box(x, y)
{

	//if (App->lvlManage->Getlvl() == 1) {
	//	zoom = 3;
	//}
	//else {
	//	zoom = 1;
	//}
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

	//wallanim.PushBack({ 1,1,24,24 });
	currentAnim = &ballanim;



	ballpath.PushBack({ 0.0f, 0.0f }, 1, &ballanim);

	collider = App->collisions->AddCollider({ 0, 0, 24 * zoom, 24 * zoom }, Collider::Type::BALL, (Module*)App->boxes);


}

void Ball_Obj::Update()
{

	ballpath.Update();
	position = spawnPos + ballpath.GetRelativePosition();
	currentAnim = ballpath.GetCurrentAnimation();

	
	Box::Update();

	collider->SetPos(position.x, position.y);
}
