#ifndef __MODULEENDSCREEN_H__
#define __MODULEENDSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleEndScreen : public Module
{
private:
	
	SDL_Texture* screen_outro = nullptr;
	SDL_Rect outro;

	
public:

	ModuleEndScreen();
	~ModuleEndScreen();

	update_status Update();
	//bool Init();
	bool CleanUp();
	bool Start();


	
};

#endif
