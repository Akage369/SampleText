#ifndef __BALL_OBJECT_H__
#define __BALL_OBJECT_H__

#include "Boxes.h"
#include "Path.h"

class Ball_Obj : public Box
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Ball_Obj(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;






private:
	// The path that will define the position in the world
	Path ballpath;

	// Enemy animations
	Animation ballanim;
};

#endif // __BALL_OBJECT_H__


