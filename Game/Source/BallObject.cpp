#include "BallObject.h"

#include "Application.h"
#include "ModuleCollisions.h"


#include "SDL/include/SDL.h"
#include "ModuleBoxes.h"




Ball_Obj::Ball_Obj(int x, int y) : Box(x, y)
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
	
	currentAnim = &ballanim;

	collider = App->collisions->AddCollider({ 0, 0, 24 * zoom, 24 * zoom }, Collider::Type::BALL, (Module*)App->boxes);

}

void Ball_Obj::Update()
{

	position = spawnPos;
	currentAnim = &ballanim;
	
	Box::Update();

	collider->SetPos(position.x, position.y);
}
