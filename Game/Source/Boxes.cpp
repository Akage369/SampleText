#include "Boxes.h"

#include "Application.h"
#include "ModuleCollisions.h"

#include "ModuleRender.h"
#include "BoxObject.h"
#include "ModuleBoxes.h"
#include "ModulePlayer.h"

Box::Box(int x, int y) : position(x, y)
{
	spawnPos = position;
	
}
Box::~Box()
{
}


const Collider* Box::GetCollider() const
{
	return collider;
}


void Box::Update()
{

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
	}


	
}

void Box::Draw()
{
	if (currentAnim != nullptr) {
		
			App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()), 1.0f, true, zoom);
		
		
	}
	
}

Collider* Box::GetLateralColliderBR() 
{
	return collider;
}
Collider* Box::GetLateralColliderBL()
{
	return collider;
}
Collider* Box::GetLateralColliderBU()
{
	return collider;
}
Collider* Box::GetLateralColliderBD()
{
	return collider;
}

void Box::BoxesDone() {
	if (sendBox == true) {
		App->lvlManage->boxes_lvl++;
		sendBox = false;
	}
}

void Box::BoxesQuit() {
	if (sendBox == false) {
		App->lvlManage->boxes_lvl--;
	}
}

void Box::OnCollision(Collider* collisionWall)
{
	
	if (position.x > collisionWall->rect.x && position.y == collisionWall->rect.y) {//&& App->player->isPushingL==true){ //Caja a la derecha
		isStoppedL = true;
	}

	if (position.x < collisionWall->rect.x && position.y == collisionWall->rect.y) {//&& App->player->isPushingR == true) { //Caja a la izquierda
		isStoppedR = true;
	}

	if (position.x == collisionWall->rect.x && position.y > collisionWall->rect.y) {//&& App->player->isPushingU == true) { //Caja abajo
		isStoppedU = true;
	}

	if (position.x == collisionWall->rect.x && position.y < collisionWall->rect.y) { //&& App->player->isPushingD == true) { //Caja arriba
		isStoppedD = true;
	}
}

void Box::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;

}