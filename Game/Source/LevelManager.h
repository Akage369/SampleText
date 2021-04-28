#ifndef __LEVELMANAGER_H__ 
#define __LEVELMANAGER_H__ 

#include "Module.h"

class LevelManager: public Module
{
private:
	
	int lvl = 0;

public:

	LevelManager(bool isEnabled);

	~LevelManager();

	void lvlChange(int change, char op);
	
	int Getlvl();
	
	
};

#endif
