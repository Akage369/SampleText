#ifndef __DUMMY_ESC_H__
#define __DUMMY_ESC_H__

// TODO 7: Create your new module "DummyESC".
// It should check if the player hits ESC key. Use _kbhit() and _getch().

#include "Module.h"

class ModuleDummyESC : public Module
{
public:

	update_status PreUpdate() override;
};

#endif // !__DUMMYESC_H__


