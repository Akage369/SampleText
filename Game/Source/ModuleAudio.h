#ifndef __MODULE_AUDIO_H__
#define __MODULE_AUDIO_H__

#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 200

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ModuleAudio : public Module
{
public:
	//Constructor
	ModuleAudio();

	//Destructor
	~ModuleAudio();

	// Called on application start.
	// Initializes the SDL audio subsystem and SDL Mixer
	bool Init();

	// Called on application exit.
	// Frees the memory from all stored audio fx and music
	// Uninitializes the SDL_Mixer library
	bool CleanUp();

	// Plays a new music file from a file path
	// First loads the music file into the Mix_Music structure
	// Then plays the music indefinetely
	// Mix_Music* music is used for handling the current playing music
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Loads a sound fx (WAV) file in memory
	// Returns an index to the sound fx array
	// The index will be used to handle the effect (see PlayFx)
	uint LoadFx(const char* path);

	// Plays a previously loaded WAV
	// Receives an index from the sound fx array
	bool PlayFx(uint index, int repeat = 0);

private:
	// The current playing music
	Mix_Music* music = nullptr;

	// An array of all the loaded sound effects
	// Allows us to keep track of all sound fx and handle them through indices
	Mix_Chunk* soundFx[MAX_FX] = { nullptr };
};

#endif // __MODULE_AUDIO_H__
