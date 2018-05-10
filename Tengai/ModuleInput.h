#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL.h"


#define MAX_KEYS 300
#define MAX_BUTTONS 12

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	bool controller_state[MAX_BUTTONS];
	SDL_GameController* gamepad = { nullptr };
	SDL_GameController* gamepad2 = { nullptr };
	char *key1;		//gamepads assigned here
	char *key2;


};

#endif // __ModuleInput_H__