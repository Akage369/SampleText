#ifndef __BOXES_H__
#define __BOXES_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Box
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Box(int x, int y);

	// Destructor
	virtual ~Box();

	// Returns the enemy's collider
	const Collider* GetCollider() const;
	///
	
	virtual Collider* GetLateralColliderBR();
	virtual Collider* GetLateralColliderBL();
	virtual Collider* GetLateralColliderBU();
	virtual Collider* GetLateralColliderBD();
	

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);
	

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	void changeContact(char dir);
	///
	virtual void Stop(char dir);
	

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	bool inContactR ;
	bool inContactL ;
	bool inContactU ;
	bool inContactD ;

	bool isStoppedR = false;
	bool isStoppedL = false;
	bool isStoppedU = false;
	bool isStoppedD = false;
	
protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

	

};

#endif // __BOXES_H__
