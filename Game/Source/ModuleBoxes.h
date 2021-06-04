#ifndef __MODULE_BOXES_H__
#define __MODULE_BOXES_H__

#include "Module.h"
#include "LevelManager.h"
#include "Application.h"

#define MAX_BOXES 300

enum class Box_Type {
	NO_TYPE,
	BOX,
	WALL,
	BALL,
};

struct BoxSpawnpoint
{
	Box_Type type = Box_Type::NO_TYPE;
	int x, y;
};

class Box;
struct SDL_Texture;

class ModuleBoxes : public Module
{
public:

	ModuleBoxes(bool startEnabled);

	~ModuleBoxes();

	bool Start() override;

	Update_Status PreUpdate() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	bool AddBox(Box_Type type, int x, int y);

	void HandleBoxesSpawn();

	void HandleBoxesDespawn();
	
	


private:
	void SpawnBox(const BoxSpawnpoint& info);

private:
	BoxSpawnpoint spawnQueue[MAX_BOXES];

	Box* boxes[MAX_BOXES] = { nullptr };
	
	SDL_Texture* texture = nullptr;

	

};

#endif // __MODULE_BOXES_H__
