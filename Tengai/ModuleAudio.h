#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

#define MAX_MUSICS 50
#define MAX_FX 50

struct Mix_Music;
struct Mix_Chunk;

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Music* const LoadMusic(const char* path);
	Mix_Chunk* const LoadEffect(const char* path);

	bool UnloadMusic(Mix_Music * mus);
	bool UnloadEffect(Mix_Chunk * fx);

public:
	Mix_Music* Musics[MAX_MUSICS];
	Mix_Chunk* Effect[MAX_FX];
};


#endif // __ModuleAudio_H_