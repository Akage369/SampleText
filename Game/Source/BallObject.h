#ifndef __BALL_OBJECT_H__
#define __BALL_OBJECT_H__

#include "Boxes.h"
#include "Path.h"

class Ball_Obj : public Box
{
public:
	
	Ball_Obj(int x, int y);

	
	void Update() override;







private:
	

	
	Animation ballanim;
};

#endif // __BALL_OBJECT_H__


