#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::WALL][Collider::Type::TOUCH] = true;
	matrix[Collider::Type::WALL][Collider::Type::BOX] = false;
	matrix[Collider::Type::WALL][Collider::Type::TOUCHB] = true;
	matrix[Collider::Type::WALL][Collider::Type::BALL] = true;
	matrix[Collider::Type::WALL][Collider::Type::UI] = false;


	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::TOUCHB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::UI] = true;

	matrix[Collider::Type::TOUCH][Collider::Type::WALL] = true;
	matrix[Collider::Type::TOUCH][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::TOUCH][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::TOUCH][Collider::Type::BOX] = true;
	matrix[Collider::Type::TOUCH][Collider::Type::TOUCHB] = false;
	matrix[Collider::Type::TOUCH][Collider::Type::BALL] = false;
	matrix[Collider::Type::TOUCH][Collider::Type::UI] = false;

	matrix[Collider::Type::BOX][Collider::Type::WALL] = false;
	matrix[Collider::Type::BOX][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BOX][Collider::Type::TOUCH] = true;
	matrix[Collider::Type::BOX][Collider::Type::BOX] = false;
	matrix[Collider::Type::BOX][Collider::Type::TOUCHB] = true;
	matrix[Collider::Type::BOX][Collider::Type::BALL] = true;
	matrix[Collider::Type::BOX][Collider::Type::UI] = false;

	matrix[Collider::Type::TOUCHB][Collider::Type::WALL] = true;
	matrix[Collider::Type::TOUCHB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TOUCHB][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::TOUCHB][Collider::Type::BOX] = true;
	matrix[Collider::Type::TOUCHB][Collider::Type::TOUCHB] = false;
	matrix[Collider::Type::TOUCHB][Collider::Type::BALL] = false;
	matrix[Collider::Type::TOUCHB][Collider::Type::UI] = false;

	matrix[Collider::Type::BALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::BALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BALL][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::BALL][Collider::Type::BOX] = true;
	matrix[Collider::Type::BALL][Collider::Type::TOUCHB] = false;
	matrix[Collider::Type::BALL][Collider::Type::BALL] = false;
	matrix[Collider::Type::BALL][Collider::Type::UI] = false;

	matrix[Collider::Type::UI][Collider::Type::WALL] = false;
	matrix[Collider::Type::UI][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::UI][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::UI][Collider::Type::BOX] = false;
	matrix[Collider::Type::UI][Collider::Type::TOUCHB] = false;
	matrix[Collider::Type::UI][Collider::Type::BALL] = false;
	matrix[Collider::Type::UI][Collider::Type::UI] = false;




}

ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
	
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{

			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::TOUCH: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::BOX: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::TOUCHB: // celeste
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::BALL: // fuxia
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;

		case Collider::Type::UI: // salmon
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		}
	}
	
}

bool ModuleCollisions::CleanUp() 
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}