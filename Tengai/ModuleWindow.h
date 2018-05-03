#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__
/*#define SCREEN_SIZE 1
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 1*/

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;
};

#endif // __ModuleWindow_H__