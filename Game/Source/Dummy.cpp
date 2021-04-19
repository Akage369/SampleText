#include "Dummy.h"

bool ModuleDummy::Init()
{
	LOG("Dummy Init!\n");

	return true;
}

update_status ModuleDummy::PreUpdate()
{
	LOG("Dummy PreUpdate!\n");

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleDummy::Update()
{
	LOG("Dummy Update!\n");

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleDummy::PostUpdate()
{
	LOG("Dummy PostUpdate!\n");

	return update_status::UPDATE_CONTINUE;
}

bool ModuleDummy::CleanUp()
{
	LOG("Dummy CleanUp!\n");

	return true;
}