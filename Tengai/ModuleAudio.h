#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include "Module.h"
#include "Globals.h"

#define MAX_MUSICS 50
#define MAX_FX 50

struct _Mix_Music;
struct Mix_Chunk;

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	_Mix_Music* const LoadMusic(const char* path);
	Mix_Chunk* const LoadEffect(const char* path);

	bool UnloadMusic(_Mix_Music * mus);
	bool UnloadEffect(Mix_Chunk * fx);

public:
	_Mix_Music* Musics[MAX_MUSICS];
	Mix_Chunk* Effect[MAX_FX];
};


#endif 