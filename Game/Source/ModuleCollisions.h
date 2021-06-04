#ifndef __MODULE_COLLISIONS_H__
#define __MODULE_COLLISIONS_H__

#define MAX_COLLIDERS 200

#include "Module.h"
#include "Collider.h"

class ModuleCollisions : public Module
{
public:
	
	ModuleCollisions(bool startEnabled);

	~ModuleCollisions();

	Update_Status PreUpdate();

	Update_Status Update();

	Update_Status PostUpdate();

	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr);

	void RemoveCollider(Collider* collider);

	void DebugDraw();

private:
	
	Collider* colliders[MAX_COLLIDERS] = { nullptr };

	bool matrix[Collider::Type::MAX][Collider::Type::MAX];

	bool debug = false;
};

#endif // __MODULE_COLLISIONS_H__