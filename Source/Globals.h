#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <windows.h>

#define LOG(txt) OutputDebugString(txt)

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

enum class update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

#endif // __GLOBALS_H__