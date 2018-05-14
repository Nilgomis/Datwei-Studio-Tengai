#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL.h"


#define MAX_KEYS 300
#define MAX_BUTTONS 10
#define MAX_GAMEPADS 2

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

/*enum BUTTON_STATE
{
	BUTTON_IDLE = 0,
	BUTTON_UP, 
	BUTTON_DOWN,
	BUTTON_REPEAT,
	
};*/

enum BUTTONS {
	BUTTON_A,
	BUTTON_B
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
	KEY_STATE controller[MAX_BUTTONS];
	KEY_STATE controller2[MAX_BUTTONS];

	SDL_Event event;
	bool controller_state[MAX_BUTTONS];
	SDL_GameController* gamepad [MAX_GAMEPADS] = { nullptr };
	SDL_GameController* gamepad2 [MAX_GAMEPADS] = { nullptr };

	struct ControlDir
	{
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		Sint16 X = 0;
		Sint16 Y = 0;
		int deadzone = 5000;
	};

	ControlDir GamepadDir[MAX_GAMEPADS];
};

#endif // __ModuleInput_H__