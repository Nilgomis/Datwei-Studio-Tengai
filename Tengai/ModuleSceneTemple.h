#ifndef __MODULESCENETemple_H__
#define __MODULESCENETemple_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

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

	//SDL_Texture* background = nullptr;
	SDL_Texture* graphics	= nullptr;
	SDL_Texture* graphics1	= nullptr;
	SDL_Texture* graphics2	= nullptr;
	SDL_Texture* diagonal	= nullptr;
	SDL_Texture* fade1		= nullptr;
	SDL_Texture* fade2		= nullptr;
	SDL_Texture* end		= nullptr;
	SDL_Rect ground, gtrees, ggrass, grass, gtree1, gtree2,
			 gtree3, gate, gate2, temp, temp1, ftrees,
			 btrees, mtrees, ttrees, tree, toptree, rock,
			 bamboo, bamboo2, mount, sky, diagonal1, end1,
			 fader, midfade;

	//SDL_Rect bg;

	float x = 7000, 
		  y = -480, 
		  ygrass = 185;
	bool  fade = true;
	float alpha_mid = 0, 
		  alpha_mid1 = 255, 
		  alpha_graph2 = 255, 
		  alpha_graph1 = 0, 
		  alpha_end = 0;
	float speed = 11;
	float time = 0;
	float timer = 0;
	bool  gmod = false;

	float bgXpos = 0;
	float bgXpos2 = 256;
	float bgXpos3 = 512;
	float frameTime = 0;
	float t2;
};

#endif // __MODULESCENETemple_H__