#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// Explosion particle
	/*explosion.anim.PushBack({ 274, 296, 33, 30 });
	explosion.anim.PushBack({ 313, 296, 33, 30 });
	explosion.anim.PushBack({ 346, 296, 33, 30 });
	explosion.anim.PushBack({ 382, 296, 33, 30 });
	explosion.anim.PushBack({ 419, 296, 33, 30 });
	explosion.anim.PushBack({ 457, 296, 33, 30 });
	//explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;*/

	// Shooting particle
	//shoot.anim.PushBack({ 73, 151, 27, 3 });
	shoot.anim.PushBack({ 148, 151, 32, 3 });
	shoot.anim.PushBack({ 107, 151, 32, 4 });
	/*shoot.anim.PushBack({ 97, 137, 11, 15 });
	shoot.anim.PushBack({ 121, 139, 11, 15 });
	shoot.anim.PushBack({ 144, 135, 11, 15 });
	shoot.anim.PushBack({ 168, 135, 11, 15 });
	shoot.anim.PushBack({ 192, 135, 11, 15 });
	shoot.anim.PushBack({ 216, 136, 11, 15 });
	shoot.anim.PushBack({ 240, 138, 11, 15 });
	shoot.anim.PushBack({ 264, 135, 11, 15 });
	shoot.anim.PushBack({ 288, 135, 11, 15 });
	shoot.anim.PushBack({ 313, 135, 11, 15 });
	shoot.anim.PushBack({ 337, 136, 11, 15 });
	shoot.anim.PushBack({ 360, 138, 11, 15 });*/

	shoot.anim.speed = 0.25f;
	shoot.speed.x = 10;
	shoot.life = 3000;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	playershot = App->textures->Load("Assets/Sprites/Characters/Sho/Sho_spritesheet.png");
	player2shot = App->textures->Load("Assets/Sprites/Characters/Sho/Sho_spritesheet.png");
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(playershot);
	App->textures->Unload(player2shot);


	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(playershot, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			App->render->Blit(player2shot, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play audio
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y+10;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}