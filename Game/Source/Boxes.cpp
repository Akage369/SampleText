#include "Boxes.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"

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
	//if (collider != nullptr)
	//	collider->pendingToDelete = true;
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

void Box::Stop(char dir) {

}

void Box::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
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
		//sendBox = true;
	}
}

void Box::OnCollision(Collider* collider)
{
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	
	if(position.x > collider->rect.x && position.y == collider->rect.y ){//&& App->player->isPushingL==true){ //Caja a la derecha
		isStoppedL = true;
		isStoppedR = false;
		isStoppedD = false;
		isStoppedU = false;
	}

	if (position.x < collider->rect.x && position.y == collider->rect.y ){//&& App->player->isPushingR == true) { //Caja a la izquierda
		isStoppedR = true;
		isStoppedL = false;
		isStoppedD = false;
		isStoppedU = false;
	}
	
	if (position.x == collider->rect.x && position.y > collider->rect.y ){//&& App->player->isPushingU == true) { //Caja abajo
		isStoppedU = true;
		isStoppedD = false;
		isStoppedL = false;
		isStoppedR = false;
	}
	
	if (position.x == collider->rect.x && position.y < collider->rect.y){ //&& App->player->isPushingD == true) { //Caja arriba
		isStoppedD = true;
		isStoppedU = false;
		isStoppedL = false;
		isStoppedR = false;

	}
	
	/*switch (dir) {
	case 'R':
		isStoppedR = true;
		//isStoppedL = false;
		//isStoppedU = false;
		//isStoppedD = false;
		break;
	case 'L':
		//inContactR = false;
		isStoppedL = true;
		//inContactU = false;
		//inContactD = false;
		break;
	case 'U':
		//inContactR = false;
		//inContactL = false;
		isStoppedU = true;
		//inContactD = false;
		break;
	case 'D':
		//inContactR = false;
		//inContactL = false;
		//inContactU = false;
		isStoppedD = true;
		break;
	case'N':
		isStoppedR = false;
		isStoppedL = false;
		isStoppedU = false;
		isStoppedD = false;
		break;
		
	default:
		break;
	}
	*/
	//SetToDelete();

}

void Box::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}



void Box::changeContact(char dir) {
	/*switch (dir) {
	case 'R':
		this->inContactR = true;
		break;
	case 'L':
		this->inContactL = true;
		break;
	case 'U':
		this->inContactU = true;
		break;
	case 'D':
		this->inContactD = true;
		break;
	default:
		break;
	}
	*/
}