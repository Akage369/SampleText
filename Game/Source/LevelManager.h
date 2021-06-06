#ifndef __LEVELMANAGER_H__ 
#define __LEVELMANAGER_H__ 

#include "Module.h"
#include "ModuleBoxes.h"


class LevelManager: public Module
{
private:
	
	int lvl = 0;

public:

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

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

	bool changeScene = true;

	bool godmode = false;

	int scoreFont = -1;

	uint loseFX;

	bool playEffect = true;
	void playMusicLose();

	unsigned int currentTime;

	unsigned int lastTime = 0;

	int delay = 700;

	void disableMusic(int delay);

	bool firstCaption = true;

	//Mix_Music* lvlmusic;
	

	
};

#endif
