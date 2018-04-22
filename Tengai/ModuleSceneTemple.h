#ifndef __MODULESCENETemple_H__
#define __MODULESCENETemple_H__

#include "Module.h"
#include "ModuleAudio.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;


class ModuleSceneTemple : public Module
{
public:
	ModuleSceneTemple();
	~ModuleSceneTemple();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	SDL_Texture* background2 = nullptr;
	SDL_Texture* background3 = nullptr;
	SDL_Rect bg;
	float bgXpos = 0;
	float bgXpos2 = 256;
	float bgXpos3 = 512;
	//Mix_Music* scene_temple = nullptr;
};

#endif // __MODULESCENETemple_H__