#ifndef __LEVELMANAGER_H__ 
#define __LEVELMANAGER_H__ 

#include "Module.h"
#include "ModuleBoxes.h"

class LevelManager: public Module
{
private:
	
	int lvl = 0;

public:

	int boxes_lvl=0;
	bool boxes_done[3] = {false, false, false};

	LevelManager(bool isEnabled);

	~LevelManager();

	void lvlChange(int change, char op);

	void BoxesDone();
	
	void LevelComplete();
	
	int Getlvl();


	
	
};

#endif