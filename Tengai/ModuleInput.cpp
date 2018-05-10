#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// controller
	LOG("Init controller");
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("Gamecontroller could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	return ret;
}


// Calling every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	if (e.type == SDL_QUIT)
		return update_status::UPDATE_STOP;

	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	// gamepads

	if (gamepad == nullptr || gamepad2 == nullptr) {

		for (int i = 0; i < SDL_NumJoysticks(); ++i) {

			if (SDL_IsGameController(i)) {

				// Controller1
				gamepad = SDL_GameControllerOpen(i);

				if (gamepad != nullptr) {

					key1 = SDL_GameControllerMapping(gamepad);
				}

				// Controller2
				gamepad2 = SDL_GameControllerOpen(i);

				if (gamepad2 != nullptr) {

					key2 = SDL_GameControllerMapping(gamepad2);
				}
			}
		}
	}


	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}