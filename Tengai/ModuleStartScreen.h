#ifndef __MODULESTARTSCREEN_H__
#define __MODULESTARTSCREEN_H__

#include "Module.h"

struct SDL_Texture;

class ModuleStartScreen : public Module
{
public:
	ModuleStartScreen();
	~ModuleStartScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	uint fx = 0;
};

#endif // __MODULESTARTSCREEN_H__