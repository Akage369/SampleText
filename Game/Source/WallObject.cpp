#include "WallObject.h"

#include "Application.h"
#include "ModuleCollisions.h"


#include <stdio.h>
#include "SDL/include/SDL.h"
#include "ModuleBoxes.h"




Wall_Obj::Wall_Obj(int x, int y) : Box(x, y)
{

	
	switch (App->lvlManage->Getlvl()) {
	case 1:
		zoom = 3;
		break;
	case 2:
		zoom = 2;
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
	
	default:
		zoom = 1;
		break;
	}

	currentAnim = &wallanim;



	wallpath.PushBack({ 0.0f, 0.0f }, 1, &wallanim);

	collider = App->collisions->AddCollider({ 0, 0, 24*zoom, 24 * zoom }, Collider::Type::WALL, (Module*)App->boxes);
	

}

void Wall_Obj::Update()
{

	wallpath.Update();
	position = spawnPos + wallpath.GetRelativePosition();
	currentAnim = wallpath.GetCurrentAnimation();

	
	Box::Update();
	
	collider->SetPos(position.x, position.y);
}


