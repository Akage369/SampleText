#ifndef __BOXES_H__
#define __BOXES_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Box
{
public:
	
	Box(int x, int y);


	virtual ~Box();

	const Collider* GetCollider() const;
	
	
	virtual Collider* GetLateralColliderBR();
	virtual Collider* GetLateralColliderBL();
	virtual Collider* GetLateralColliderBU();
	virtual Collider* GetLateralColliderBD();
	
	virtual void Update();

	virtual void Draw();

	virtual void OnCollision(Collider* collider);
	
	virtual void BoxesDone();
	virtual void BoxesQuit();

	virtual void SetToDelete();
	
public:
	iPoint position;

	SDL_Texture* texture = nullptr;

	bool pendingToDelete = false;

	bool inContactR ;
	bool inContactL ;
	bool inContactU ;
	bool inContactD ;

	bool isStoppedR = false;
	bool isStoppedL = false;
	bool isStoppedU = false;
	bool isStoppedD = false;

	bool sendBox = false;
	bool isReady = false;
	bool hasEntered = false;

	int zoom =1;
	
protected:
	
	Animation* currentAnim = nullptr;

	Collider* collider = nullptr;

	iPoint spawnPos;

};

#endif // __BOXES_H__
