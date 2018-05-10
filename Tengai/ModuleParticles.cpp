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

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	partsprite = App->textures->Load("Assets/Sprites/particles.png");
	
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

	tengaishot.anim.PushBack({ 390, 287, 31, 15 });
	tengaishot.anim.PushBack({ 433, 289, 31, 12 });

	tengaishot.anim.speed = 0.2f;
	tengaishot.speed.x = 10;
	tengaishot.life = 1000;

	junishot.anim.PushBack({ 11, 117, 31, 9 });
	junishot.anim.PushBack({ 11, 134, 31, 9 });
	junishot.anim.PushBack({ 50, 134, 31, 9 });

	junishot.anim.speed = 0.2f;
	junishot.speed.x = 10;
	junishot.life = 1000;

	enemyshot.anim.PushBack({ 0,16,6,6 });
	enemyshot.anim.PushBack({ 6,16,6,6 });
	enemyshot.anim.PushBack({ 12,16,6,6 });
	enemyshot.anim.PushBack({ 18,16,6,6 });
	enemyshot.anim.PushBack({ 24,16,6,6 });
	enemyshot.anim.PushBack({ 30,16,6,6 });
	enemyshot.anim.PushBack({ 36,16,6,6 });
	enemyshot.anim.PushBack({ 40,16,6,6 });
	enemyshot.anim.speed = 0.25f;
	enemyshot.speed.x = -2;
	enemyshot.life = 3000;


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(partsprite);


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
			//move colliders
			p->collider->SetPos(p->position.x, p->position.y);
			//draw particles
			App->render->Blit(partsprite, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

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
			p->position.y = y;
			if (collider_type != COLLIDER_NONE) {
				SDL_Rect colRect = { x,y,p->anim.GetCurrentFrame().w,p->anim.GetCurrentFrame().h };
				//p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				p->collider = App->collision->AddCollider(colRect, collider_type, this);
			}
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
			active[i]->collider->to_delete = true;
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