#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* player = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	iPoint position;
	Collider* col;
	bool shooting;
	bool destroyed = false;
	bool death = false;
	bool spawn = true;
	float cooldown = 0.1f;
	Mix_Chunk* attack = nullptr;

	/*bool A = false;
	bool B = false;*/

};

#endif