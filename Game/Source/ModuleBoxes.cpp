#include "ModuleBoxes.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"


#include "Boxes.h"
#include "BoxObject.h"
#include "WallObject.h"
#include "OrangeObject.h"
#include "BallObject.h"

#include "Collider.h"
#include "ModulePlayer.h"
#include "ModuleBoxes.h"
#include "LevelManager.h"

#define SPAWN_MARGIN 50

ModuleBoxes::ModuleBoxes(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_BOXES; ++i)
		boxes[i] = nullptr;
}

ModuleBoxes::~ModuleBoxes()
{

}

bool ModuleBoxes::Start()
{
	texture = App->textures->Load("Assets/Textures/spritesheet_tiles.png");
	

	return true;
}


Update_Status ModuleBoxes::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (boxes[i] != nullptr && boxes[i]->pendingToDelete)
		{
			delete boxes[i];
			boxes[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleBoxes::Update()
{
	HandleBoxesSpawn();

	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (boxes[i] != nullptr)
			boxes[i]->Update();
	}

	HandleBoxesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleBoxes::PostUpdate()
{
	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (boxes[i] != nullptr) {
			boxes[i]->Draw();
			
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleBoxes::CleanUp()
{
	LOG("Freeing all boxes");

	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (boxes[i] != nullptr)
		{
			delete boxes[i];
			boxes[i] = nullptr;
		}
	}

	return true;
}

bool ModuleBoxes::AddBox(Box_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (spawnQueue[i].type == Box_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
			
		
	}
 
	return ret;
}

void ModuleBoxes::HandleBoxesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (spawnQueue[i].type != Box_Type::NO_TYPE)
		{
			
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnBox(spawnQueue[i]);
				spawnQueue[i].type = Box_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			
		}
	}
}

void ModuleBoxes::HandleBoxesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (boxes[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (boxes[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", boxes[i]->position.x * SCREEN_SIZE);

				boxes[i]->SetToDelete();
			}
		}
	}
}

void ModuleBoxes::SpawnBox(const BoxSpawnpoint& info)
{
	
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (boxes[i] == nullptr)
		{
			switch (info.type)
			{
			case Box_Type::BOX:
				boxes[i] = new Box_Obj(info.x, info.y);
				break;

			case Box_Type::WALL:
				boxes[i] = new Wall_Obj(info.x, info.y);
				break;
			case Box_Type::OR_FLOOR:
				boxes[i] = new Orange_Obj(info.x, info.y);
				break;
			case Box_Type::BALL:
				boxes[i] = new Ball_Obj(info.x, info.y);  
				break;


			}
		
			boxes[i]->texture = texture;
			break;
			
		}
	}
}

void ModuleBoxes::OnCollision(Collider* c1, Collider* c2)
{
	
	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		//if (c1->type == Collider::Type::BOX && c2->type == Collider::Type::TOUCH){
		


		//	if (boxes[i] != nullptr && boxes[i]->GetCollider() == c1)
		//	{
		//		boxes[i]->OnCollision(c2,0); //Notify the enemy of a collision
		//		break;
		//	}
		//}
		if (c1->type == Collider::Type::WALL && c2->type == Collider::Type::TOUCH) {
			

				if (boxes[i] != nullptr && boxes[i]->GetCollider() == c1)
				{

					
					if (c2==App->player->colliderL) {
						App->player->isStopped('L'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderR) {
						App->player->isStopped('R'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderU) {
						App->player->isStopped('U'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderD) {
						App->player->isStopped('D'); //Notify the enemy of a collision
					}
						
					break;
				}
			
		
		}
		
		if (c1->type == Collider::Type::WALL && c2->type == Collider::Type::TOUCHB) {////////////////////////////////////FRENAR CAJAS
			//////////////////////METODO CLASSICO
			
			if (boxes[i] != nullptr && (boxes[i]->GetLateralColliderBR() == c2|| boxes[i]->GetLateralColliderBL() == c2 || 
				boxes[i]->GetLateralColliderBU() == c2 || boxes[i]->GetLateralColliderBD() == c2))
			{
				if (c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) {
					int zoom = boxes[i]->zoom;
					if (((c1->rect.x == 24*zoom + boxes[i]->position.x)) && ((c1->rect.y == boxes[i]->position.y))) {//Caja a la izquierda
						boxes[i]->isStoppedR = true;
						//boxes[i]->isStoppedL = false; 
					}
					if ((c1->rect.x + 24*zoom == boxes[i]->position.x) && ((c1->rect.y == boxes[i]->position.y))) {//Caja a la derecha
						boxes[i]->isStoppedL = true;
						//boxes[i]->isStoppedR = false;
					}
					if ((c1->rect.x == boxes[i]->position.x) && ((c1->rect.y +24*zoom ==  boxes[i]->position.y))) {//Caja abajo
						boxes[i]->isStoppedU = true;
						//boxes[i]->isStoppedD = false;
					}
					if ((c1->rect.x == boxes[i]->position.x) && ((c1->rect.y == 24*zoom + boxes[i]->position.y))) {//Caja arriba
						boxes[i]->isStoppedD = true;
						//boxes[i]->isStoppedU = false;
					}

					
					break;
				}
				else {
					//boxes[i]->Stop('N'); //Notify the enemy of a collision
					boxes[i]->OnCollision(c1); //Notify the enemy of a collision
				}
			}
			


		}

		if (c1->type == Collider::Type::BOX && c2->type == Collider::Type::TOUCHB) {////////////////////////////////////FRENAR CAJAS CON CAJAS

			  //////////////////METODO CLASSICO
			/*
			if (boxes[i] != nullptr && (boxes[i]->GetLateralColliderBR() == c2 || boxes[i]->GetLateralColliderBL() == c2 ||
				boxes[i]->GetLateralColliderBU() == c2 || boxes[i]->GetLateralColliderBD() == c2))
			{
				if (c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) {

					if ((c1->rect.x == 24 + boxes[i]->position.x) && ((c1->rect.y == boxes[i]->position.y))) {//Caja a la izquierda
						boxes[i]->isStoppedR = true;
						//boxes[i]->isStoppedL = false; 
					}
					if ((c1->rect.x + 24 == boxes[i]->position.x) && ((c1->rect.y == boxes[i]->position.y))) {//Caja a la derecha
						boxes[i]->isStoppedL = true;
						//boxes[i]->isStoppedR = false;
					}
					if ((c1->rect.x == boxes[i]->position.x) && ((c1->rect.y + 24 == boxes[i]->position.y))) {//Caja abajo
						boxes[i]->isStoppedU = true;
						//boxes[i]->isStoppedD = false;
					}
					if ((c1->rect.x == boxes[i]->position.x) && ((c1->rect.y == 24 + boxes[i]->position.y))) {//Caja arriba
						boxes[i]->isStoppedD = true;
						//boxes[i]->isStoppedU = false;
					}


					break;
				}
				else {
					//boxes[i]->Stop('N'); //Notify the enemy of a collision
					boxes[i]->OnCollision(c1); //Notify the enemy of a collision
				}
			}
			*/
			////////////METODO PARA QUE UNA CAJA DETECTE OTRA AL LADO PERO ESTA SE VAYA Y LA COLISION SE MANTENGA
			
			if (boxes[i] != nullptr && (boxes[i]->GetLateralColliderBR() == c2 || boxes[i]->GetLateralColliderBL() == c2 ||
				boxes[i]->GetLateralColliderBU() == c2 || boxes[i]->GetLateralColliderBD() == c2))
			{
				if (c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) {
					int zoom = boxes[i]->zoom;
					if ((c1->rect.x == 24*zoom + boxes[i]->position.x) && ((c1->rect.y == boxes[i]->position.y))) {//Caja a la izquierda
						boxes[i]->isStoppedR = true;
						//boxes[i]->isStoppedL = false; 
					}
					if ((c1->rect.x + 24*zoom == boxes[i]->position.x) && ((c1->rect.y == boxes[i]->position.y))) {//Caja a la derecha
						boxes[i]->isStoppedL = true;
						//boxes[i]->isStoppedR = false;
					}
					if ((c1->rect.x == boxes[i]->position.x) && ((c1->rect.y + 24*zoom == boxes[i]->position.y))) {//Caja abajo
						boxes[i]->isStoppedU = true;
						//boxes[i]->isStoppedD = false;
					}
					if ((c1->rect.x == boxes[i]->position.x) && ((c1->rect.y == 24*zoom + boxes[i]->position.y))) {//Caja arriba
						boxes[i]->isStoppedD = true;
						//boxes[i]->isStoppedU = false;
					}


					break;
				}
				else {
					if (boxes[i]->position.x > c1->rect.x && boxes[i]->position.y == c1->rect.y && App->player->isPushingL == true) { //Caja a la derecha
						boxes[i]->isStoppedL = true;
						boxes[i]->isStoppedR = false;
						boxes[i]->isStoppedD = false;
						boxes[i]->isStoppedU = false;
					}
					else if (boxes[i]->position.x < c1->rect.x && boxes[i]->position.y == c1->rect.y && App->player->isPushingR == true) { //Caja a la izquierda
						boxes[i]->isStoppedR = true;
						boxes[i]->isStoppedL = false;
						boxes[i]->isStoppedD = false;
						boxes[i]->isStoppedU = false;
					}
					else if (boxes[i]->position.x == c1->rect.x && boxes[i]->position.y > c1->rect.y && App->player->isPushingU == true) { //Caja abajo
						boxes[i]->isStoppedU = true;
						boxes[i]->isStoppedD = false;
						boxes[i]->isStoppedL = false;
						boxes[i]->isStoppedR = false;
					}
					else if (boxes[i]->position.x == c1->rect.x && boxes[i]->position.y < c1->rect.y && App->player->isPushingD == true) { //Caja arriba
						boxes[i]->isStoppedD = true;
						boxes[i]->isStoppedU = false;
						boxes[i]->isStoppedL = false;
						boxes[i]->isStoppedR = false;

					}
					else {
						boxes[i]->isStoppedD = false;
						boxes[i]->isStoppedU = false;
						boxes[i]->isStoppedL = false;
						boxes[i]->isStoppedR = false;
					}
				}
			}

		}

		
		else if (c1->type == Collider::Type::BOX && c2->type == Collider::Type::TOUCH) {
			if (boxes[i] != nullptr && boxes[i]->GetCollider() == c1)
			{
				//if (c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) {
				//if (c1->rect.x +6== c2->rect.x && c1->rect.y == c2->rect.y|| c1->rect.x  == 6 + c2->rect.x && c1->rect.y == c2->rect.y || c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y ||
				//	c1->rect.x == c2->rect.x && c1->rect.y + 6 == c2->rect.y || c1->rect.x == c2->rect.x && c1->rect.y == 6 + c2->rect.y) {


				///////CON MARGEN
				int zoom = boxes[i]->zoom;
				if ((c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y)|| (c1->rect.x+1*zoom == c2->rect.x && c1->rect.y == c2->rect.y) ||(c1->rect.x == 1 * zoom +c2->rect.x && c1->rect.y == c2->rect.y)
					||(c1->rect.x + 2 * zoom == c2->rect.x && c1->rect.y == c2->rect.y) || (c1->rect.x == 2 * zoom + c2->rect.x && c1->rect.y == c2->rect.y)||
					(c1->rect.x == c2->rect.x && c1->rect.y +1 * zoom == c2->rect.y) || (c1->rect.x ==  c2->rect.x && c1->rect.y == 1 * zoom + c2->rect.y)||
					(c1->rect.x == c2->rect.x && c1->rect.y + 2 * zoom == c2->rect.y) || (c1->rect.x == c2->rect.x && c1->rect.y == 2 * zoom + c2->rect.y)) {
					if (c2 == App->player->colliderL) {
						App->player->Push('L'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderR) {
						App->player->Push('R'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderU) {
						App->player->Push('U'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderD) {
						App->player->Push('D'); //Notify the enemy of a collision
					}


					if (boxes[i]->isStoppedR == true && c2 == App->player->colliderR) {
						App->player->isBlockedR = true;
					}
					if (boxes[i]->isStoppedL == true && c2 == App->player->colliderL) {
						App->player->isBlockedL = true;
					}
					if (boxes[i]->isStoppedU == true && c2 == App->player->colliderU) {
						App->player->isBlockedU = true;
					}
					if (boxes[i]->isStoppedD == true && c2==App->player->colliderD) {
						App->player->isBlockedD = true;
					}



					break;
				}
				else {
			
					
						App->player->Push('N'); //Notify the enemy of a collision
					
					break;
				}
				
				///////SIN TANTO MARGEN
				/*
				if ((c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) ||
					(c1->rect.x + 1 == c2->rect.x && c1->rect.y == c2->rect.y) || (c1->rect.x == 1 + c2->rect.x && c1->rect.y == c2->rect.y)||
					(c1->rect.x == c2->rect.x && c1->rect.y + 1 == c2->rect.y) || (c1->rect.x == c2->rect.x && c1->rect.y == 1 + c2->rect.y)) {
					if (c2 == App->player->colliderL) {
						App->player->Push('L'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderR) {
						App->player->Push('R'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderU) {
						App->player->Push('U'); //Notify the enemy of a collision
					}
					if (c2 == App->player->colliderD) {
						App->player->Push('D'); //Notify the enemy of a collision
					}


					if (boxes[i]->isStoppedR == true && c2 == App->player->colliderR) {
						App->player->isBlockedR = true;
					}
					if (boxes[i]->isStoppedL == true && c2 == App->player->colliderL) {
						App->player->isBlockedL = true;
					}
					if (boxes[i]->isStoppedU == true && c2 == App->player->colliderU) {
						App->player->isBlockedU = true;
					}
					if (boxes[i]->isStoppedD == true && c2 == App->player->colliderD) {
						App->player->isBlockedD = true;
					}



					break;
				}
				else {


					App->player->Push('N'); //Notify the enemy of a collision

					break;
				}
				*/
				
			}
		
		//else if (c1->type == Collider::Type::TOUCH && c2->type == Collider::Type::BOX) 
		//{////////////CHOQUE DEL PLAYER CON LAS CAJAS
			
//			if (boxes[i] != nullptr && boxes[i]->GetCollider() == c2)
//			{
//				if (c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) {

					
					




//					break;
//			}
//				else {


					//App->player->isBlockedR = false;
					//App->player->isBlockedL = false;
					//App->player->isBlockedU = false;
					//App->player->isBlockedD = false;

//					break;
//				}


//			}
			

		}


		///SOLO CON 1 CAJA 
		/*
		else if (c1->type == Collider::Type::TOUCHB && c2->type == Collider::Type::PLAYER) {

			if (boxes[i] != nullptr)// && c1->type== Collider::Type::TOUCHB)
			{
				if (c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) {

					
					/*if ((c2->rect.x ==24+ boxes[i]->GetCollider()->rect.x) &&((c2->rect.y == boxes[i]->GetCollider()->rect.y)) ) {//Player a la derecha

						boxes[i]->inContactR = true;
						boxes[i]->inContactL = false;
						boxes[i]->inContactU = false;
						boxes[i]->inContactD = false;
					}
					else {
						boxes[i]->inContactR = false;
					}


					if ((c2->rect.x +24== boxes[i]->GetCollider()->rect.x) && ((c2->rect.y == boxes[i]->GetCollider()->rect.y))) {//Player a la Izquierda
						boxes[i]->inContactR = false;
						boxes[i]->inContactL = true;
						boxes[i]->inContactU = false;
						boxes[i]->inContactD = false;
					}
					else {
						boxes[i]->inContactL = false;
					}

					if ((c2->rect.x == boxes[i]->GetCollider()->rect.x) && ((c2->rect.y +24== boxes[i]->GetCollider()->rect.y))) {//Player Arriba
						boxes[i]->inContactR = false;
						boxes[i]->inContactL = false;
						boxes[i]->inContactU = true;
						boxes[i]->inContactD = false;
					}
					else {
						boxes[i]->inContactU = false;
					}


					if ((c2->rect.x == boxes[i]->GetCollider()->rect.x) && ((c2->rect.y ==24+ boxes[i]->GetCollider()->rect.y))) {//Player Abajo
						boxes[i]->inContactR = false;
						boxes[i]->inContactL = false;
						boxes[i]->inContactU = false;
						boxes[i]->inContactD = true;
					}
					else {
						boxes[i]->inContactD = false;
					}
					*/


		/*
					if ((c2->rect.x == 24 + boxes[i]->GetCollider()->rect.x) && (c2->rect.y == boxes[i]->GetCollider()->rect.y)) {//Player a la derecha
						//boxes[i]->OnCollision(c1,'R');
						//boxes[i]->changeContact('R');
						boxes[i]->inContactR = true;
						boxes[i]->inContactL = false;
						boxes[i]->inContactU = false;
						boxes[i]->inContactD = false;
						boxes[i]->SetToDelete();
						break;

					}
					
					if ((c2->rect.x + 24 == boxes[i]->GetCollider()->rect.x) && (c2->rect.y == boxes[i]->GetCollider()->rect.y)) {//Player a la Izquierda
						//boxes[i]->OnCollision(c1, 'L');
						//boxes[i]->changeContact('L');
						boxes[i]->inContactR = false;
						boxes[i]->inContactL = true;
						boxes[i]->inContactU = false;
						boxes[i]->inContactD = false;
						boxes[i]->SetToDelete();
						break;
						
					}
					
					if ((c2->rect.x == boxes[i]->GetCollider()->rect.x) && (c2->rect.y + 24 == boxes[i]->GetCollider()->rect.y)) {//Player Arriba
						//boxes[i]->OnCollision(c1, 'U');
						//boxes[i]->changeContact('U');
						boxes[i]->inContactR = false;
						boxes[i]->inContactL = false;
						boxes[i]->inContactU = true;
						boxes[i]->inContactD = false;
						boxes[i]->SetToDelete();
						break;
					}
					
					if ((c2->rect.x == boxes[i]->GetCollider()->rect.x) && (c2->rect.y == 24 + boxes[i]->GetCollider()->rect.y)) {//Player Abajo
						//boxes[i]->OnCollision(c1, 'D');
						//boxes[i]->changeContact('D');
						boxes[i]->inContactR = false;
						boxes[i]->inContactL = false;
						boxes[i]->inContactU = false;
						boxes[i]->inContactD = true;
						boxes[i]->SetToDelete();
						break;
					}
				
					
		*/
		/*
					
					
				}
				else {
					boxes[i]->inContactR = false;
					boxes[i]->inContactL = false;
					boxes[i]->inContactU = false;
					boxes[i]->inContactD = false;
					break;
				}
				
				/*
				else {
					boxes[i]->inContactR = false;
					boxes[i]->inContactL = false;
					boxes[i]->inContactU = false;
					boxes[i]->inContactD = false;
				}+/
				
				/*
				else if(){
					boxes[i]->changeContact('L');
				}
				else if () {
					boxes[i]->changeContact('U');
				}
				else if () {
					boxes[i]->changeContact('D');
				}
				*/
/*break;

			}
		}
		*/
		else if (c1->type == Collider::Type::BOX && c2->type == Collider::Type::BALL) {
			if (boxes[i] != nullptr && boxes[i]->GetCollider() == c2) {

				
				
				if (c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) {

					boxes[i]->hasEntered = true;
					boxes[i]->BoxesDone();
					boxes[i]->sendBox = false;
					//App->lvlManage->BoxesDone(boxes[i]);
					boxes[i]->isReady = true;
					App->lvlManage->LevelComplete();
					
					
				}
				else {
					if (boxes[i]->hasEntered == true) {
						boxes[i]->BoxesQuit();
						
					}
					boxes[i]->sendBox = true;
					
				}
				//boxes[i]->sendBox = false;

				App->lvlManage->LevelComplete();

			}
			if (boxes[i] != nullptr && boxes[i]->GetCollider() == c1) {



				if (c1->rect.x == c2->rect.x && c1->rect.y == c2->rect.y) {
					boxes[i]->isReady = true;

				}
				else {
					boxes[i]->isReady = false;
				}


			}
			
		}
	}
	
	
}