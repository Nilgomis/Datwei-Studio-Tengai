#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


ModuleAudio::ModuleAudio() : Module()
{
	// Initialize music to nullptr
	for (int i = 0; i < MAX_MUSICS; i++) {
		Musics[i] = nullptr;
	}
	// Initialize fx nullptr
	for (int i = 0; i < MAX_FX; i++) {
		Effect[i] = nullptr;
	}
}

ModuleAudio::~ModuleAudio()
{}

// Called before audio is available
bool ModuleAudio::Init()
{
	LOG("Init Audios library");

	bool ret = true;

	// load support for the PNG image format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);
	Mix_OpenAudio(44100, AUDIO_S8, 2, 4096);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	for (int i = 0; i < MAX_MUSICS; ++i) {
		if (Musics[i] != nullptr) {
			Mix_PlayMusic(Musics[0], 1);
		}
		//if (Effect[i] != nullptr) {
			//Mix_PlayChannel(-1, sfx[0], 0);
		//}
	}

	return ret;

	Mix_VolumeMusic(MIX_MAX_VOLUME / 10);

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing music and fx library");

	// Free all music and fx
	for (int i = 0; i < MAX_MUSICS; i++) {
		Mix_FreeMusic(Musics[i]);
	}
	for (int i = 0; i < MAX_FX; i++) {
		Mix_FreeChunk(Effect[i]);
	}

	Mix_CloseAudio();
	return true;
}

// Load new music from file path
_Mix_Music * const ModuleAudio::LoadMusic(const char* path)
{
	// Load a music from a path (must be a ogg)
	// and check for errors
	_Mix_Music* music = Mix_LoadMUS(path);
	if (!music) {
		LOG("Mix_LoadMUS: %s\n", Mix_GetError());
		// handle error
	}
	else {

		bool room = false;
		for (int i = 0; i < MAX_MUSICS; ++i)
		{
			if (Musics[i] == nullptr)
			{
				Musics[i] = music;
				room = true;
				break;
			}
		}
		if (room == false)
			LOG("Music buffer overflow");
	}
	return music;
}

// Load new fx from file path
Mix_Chunk * const ModuleAudio::LoadEffect(const char* path)
{

	// Load a music from a path (must be a ogg)
	// and check for errors
	Mix_Chunk* fx = Mix_LoadWAV(path);

	if (!fx) {
		LOG("Mix_LoadWAV error: %s\n", Mix_GetError());
		// handle error
	}
	else {

		bool room = false;
		for (int i = 0; i < MAX_FX; ++i)
		{
			if (Effect[i] == nullptr)
			{
				Effect[i] = fx;
				room = true;
				break;
			}
		}
		if (room == false)
			LOG("SFX buffer overflow");
	}

	return fx;
}

bool ModuleAudio::UnloadMusic(_Mix_Music* mus) {

	bool ret = false;

	if (mus != nullptr)
	{
		for (int i = 0; i < MAX_MUSICS; ++i)
		{
			if (Musics[i] == mus)
			{
				Musics[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FreeMusic(mus);
	}

	return ret;
}


bool ModuleAudio::UnloadEffect(Mix_Chunk* _fx) {
	bool ret = false;

	if (_fx != nullptr)
	{
		for (int i = 0; i < MAX_FX; ++i)
		{
			if (Effect[i] == _fx)
			{
				Effect[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FreeChunk(_fx);
	}

	return ret;
}