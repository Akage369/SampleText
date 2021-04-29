#ifndef __MODULE_BOXES_H__
#define __MODULE_BOXES_H__

#include "Module.h"
#include "LevelManager.h"
#include "Application.h"

#define MAX_BOXES 75

enum class Box_Type {
	NO_TYPE,
	BOX,
	WALL,
	OR_FLOOR,
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
	// Constructor
	ModuleBoxes(bool startEnabled);

	// Destructor
	~ModuleBoxes();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddBox(Box_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleBoxesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleBoxesDespawn();
	
	


private:
	// Spawns a new enemy using the data from the queue
	void SpawnBox(const BoxSpawnpoint& info);

private:
	// A queue with all spawn points information
	BoxSpawnpoint spawnQueue[MAX_BOXES];

	// All spawned enemies in the scene
	Box* boxes[MAX_BOXES] = { nullptr };
	
	///Box* boxeslvl[] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	

};

#endif // __MODULE_BOXES_H__
