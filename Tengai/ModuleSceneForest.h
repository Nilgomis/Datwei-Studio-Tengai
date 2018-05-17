#ifndef __MODULESceneForest_H__
#define __MODULESceneForest_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleSceneForest : public Module
{
public:
	ModuleSceneForest();
	~ModuleSceneForest();

	bool Start();
	update_status Update();
	bool CleanUp();
	float Time();

public:
	Collider* leftCollider = nullptr;
	Collider* rightCollider = nullptr;
	Collider* topCollider = nullptr;
	Collider* botCollider = nullptr;
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
	float alpha_fade1 = 0, 
		  alpha_fade2 = 255, 
		  alpha_graph2 = 255, 
		  alpha_graph1 = 0, 
		  alpha_end = 0;
	float speed = 11;
	float time = 0;
	float timer = 0;
	

	/*float bgXpos = 0;
	float bgXpos2 = 256;
	float bgXpos3 = 512;*/
	float frameTime = 0;
	float t2;

	_Mix_Music* music = nullptr;
};

#endif // __MODULESceneForest_H__