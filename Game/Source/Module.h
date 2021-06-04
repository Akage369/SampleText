#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

struct Collider;

class Module
{
public:
	Module(bool startEnabled);

	virtual bool Init();

	virtual bool Start();

	virtual Update_Status PreUpdate();

	virtual Update_Status Update();

	virtual Update_Status PostUpdate();

	virtual bool CleanUp();

	virtual void OnCollision(Collider* c1, Collider* c2);

	void Enable();

	void Disable();

	inline bool IsEnabled() const { return isEnabled; }

private:
	bool isEnabled = true;
};

#endif // __MODULE_H__