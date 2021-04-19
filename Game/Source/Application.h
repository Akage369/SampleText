#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

// TODO 7: Create your new module "DummyESC".
#define NUM_MODULES 2

class Module;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:

	Module* modules[NUM_MODULES];

};

#endif // __APPLICATION_H__
