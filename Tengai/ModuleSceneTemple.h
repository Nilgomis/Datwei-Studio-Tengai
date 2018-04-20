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

public:

	SDL_Texture* background = nullptr;
	SDL_Texture* stars = nullptr;
};

#endif // __MODULESCENETemple_H__