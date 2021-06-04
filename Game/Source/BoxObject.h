#ifndef __BOX_OBJECT_H__
#define __BOX_OBJECT_H__

#include "Boxes.h"

class Box_Obj: public Box
{
public:
	
	Box_Obj(int x, int y);

	void Update() override;

	
	

	void walkx();
	void walky();
	
	Collider* GetLateralColliderBR() override;
	Collider* GetLateralColliderBL() override;
	Collider* GetLateralColliderBU() override;
	Collider* GetLateralColliderBD() override;
	
	signed int countx;
	signed int county;
	signed int movx;
	signed int movy;

	bool posInix = true;
	bool posIniy = true;

	Collider* colliderBR = nullptr;
	Collider* colliderBL = nullptr;
	Collider* colliderBU = nullptr;
	Collider* colliderBD = nullptr;

	bool canStart = false;
	

private:

	Animation boxanim;
	Animation boxready;

};

#endif // __BOX_OBJECT_H__
