#ifndef __MUSICMANAGER_H__ 
#define __MUSICMANAGER_H__ 

#include "Module.h"


class MusicManager : public Module
{
private:

	int lvl = 0;

public:

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;



	MusicManager(bool isEnabled);

	~MusicManager();

	void playMusic(const char*path);

	

	uint loseFX;

	bool playEffect = true;

};

#endif
