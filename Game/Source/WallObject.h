#ifndef __WALL_OBJECT_H__
#define __WALL_OBJECT_H__

#include "Boxes.h"
#include "Path.h"

class Wall_Obj : public Box
{
public:
	
	Wall_Obj(int x, int y);

	void Update() override;

	bool CleanUp();
	

	bool posInix = true;
	bool posIniy = true;

	
	


private:
	
	Path wallpath;

	
	Animation wallanim;
};

#endif // __WALL_OBJECT_H__

