#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 10

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER,
		TOUCH,
		BOX,
		TOUCHB,
		BALL,
		UI,

		MAX
	};

	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__



