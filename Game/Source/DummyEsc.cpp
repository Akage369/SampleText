#include "DummyEsc.h"

#include <conio.h>

update_status ModuleDummyESC::PreUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	if (_kbhit() && _getch() == 27)
		ret = update_status::UPDATE_STOP;

	return ret;
}