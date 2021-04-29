#ifndef __LEVELMANAGER_H__ 
#define __LEVELMANAGER_H__ 

#include "Module.h"
#include "ModuleBoxes.h"

class LevelManager: public Module
{
private:
	
	int lvl = 1;

public:

	int boxes_lvl=0;
	bool boxes_done[3] = {false, false, false};

	LevelManager(bool isEnabled);

	~LevelManager();

	void lvlChange(int change, char op);

	void Lose();
	
	void LevelComplete();
	
	int Getlvl();

	int steps = 0;
	
	int win =0;

	int max_steps = 0;
};

#endif
