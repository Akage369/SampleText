#ifndef __WALL_OBJECT_H__
#define __WALL_OBJECT_H__

#include "Boxes.h"
#include "Path.h"

class Wall_Obj : public Box
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Wall_Obj(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	

	bool posInix = true;
	bool posIniy = true;

	
	


private:
	// The path that will define the position in the world
	Path wallpath;

	// Enemy animations
	Animation wallanim;
};

#endif // __WALL_OBJECT_H__

