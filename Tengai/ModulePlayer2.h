#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"


struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* player2 = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	iPoint position;
	Collider* col;
	bool shooting;
	bool destroyed = false;
	float cooldown = 0.1f;
	int startx = 305;
	int starty = 126;
	Mix_Chunk* attack = nullptr;

	/*bool A2 = false;
	bool B2 = false;*/

};

#endif