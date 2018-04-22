#ifndef __MODULESCENETemple_H__
#define __MODULESCENETemple_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneTemple : public Module
{
public:
	ModuleSceneTemple();
	~ModuleSceneTemple();

	bool Start();
	update_status Update();
	bool CleanUp();
	float Time();

public:

	SDL_Texture* background = nullptr;
	SDL_Rect bg;
	float bgXpos = 0;
	float bgXpos2 = 256;
	float bgXpos3 = 512;
	float timer = 0;
	float frameTime = 0;
	float t2;
};

#endif // __MODULESCENETemple_H__