#ifndef __MODULESTARTSCREEN_H__
#define __MODULESTARTSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleStartScreen : public Module
{
private:

	int aux;
	bool print;


	float s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14;

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;

	SDL_Texture* background1 = nullptr;
	SDL_Texture* background2 = nullptr;
	SDL_Texture* background3 = nullptr;
	SDL_Texture* background4 = nullptr;
	SDL_Texture* background5 = nullptr;
	SDL_Texture* background6 = nullptr;
	SDL_Texture* background7 = nullptr;

	SDL_Rect title;
	SDL_Rect background;
	SDL_Rect psikyo1;
	SDL_Rect atlus1;
	SDL_Rect start_button;

	SDL_Rect bg1;
	SDL_Rect bg2;
	SDL_Rect bg3;
	SDL_Rect bg4;
	SDL_Rect bg5;
	SDL_Rect bg6;
	SDL_Rect bg7;

	_Mix_Music* music = nullptr;

public:

	update_status Update();
	bool Init();
	bool CleanUp();
	bool Start();


	ModuleStartScreen();
	~ModuleStartScreen();



	uint fx = 0;
};

#endif // __MODULESTARTSCREEN_H__