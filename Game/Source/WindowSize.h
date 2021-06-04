#ifndef __WINDOW_SIZE_H__
#define __WINDOW_SIZE_H__

#include "Module.h"

class WinSize : public Module
{
public:

	WinSize(bool isEnabled);

	~WinSize();

	bool Start() override;

	Update_Status Update();
	
	int w = 0;
	int h = 0;
	
};



#endif // __WINDOW_SIZE_H__
