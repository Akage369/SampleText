#ifndef __BOX_OBJECT_H__
#define __BOX_OBJECT_H__

#include "Boxes.h"
#include "Path.h"

class Box_Obj: public Box
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Box_Obj(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step

	void Update() override;

	
	

	void walkx();
	void walky();
	
	Collider* GetLateralColliderBR() override;
	Collider* GetLateralColliderBL() override;
	Collider* GetLateralColliderBU() override;
	Collider* GetLateralColliderBD() override;

	void Stop(char dir) override;
	
	
	//bool isStoppedR=false;
	//bool isStoppedL = false;
	//bool isStoppedU = false;
	//bool isStoppedD = false;

	signed int countx;
	signed int county;
	signed int movx;
	signed int movy;

	bool posInix = true;
	bool posIniy = true;

	
	
	//Collider* colliders[4] = { nullptr ,nullptr ,nullptr ,nullptr };
	Collider* colliderBR = nullptr;
	Collider* colliderBL = nullptr;
	Collider* colliderBU = nullptr;
	Collider* colliderBD = nullptr;

	
	

private:
	// The path that will define the position in the world
	Path boxpath;

	// Enemy animations
	Animation boxanim;
};

#endif // __BOX_OBJECT_H__
