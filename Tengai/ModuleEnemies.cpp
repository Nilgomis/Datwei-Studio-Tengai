#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "EnemyPegTop.h"
#include "EnemyDemonWheel.h"
#include "ModuleSceneTemple.h"

//#define SPAWN_MARGIN 50
#define DESPAWN_TIME 20

ModuleEnemies::ModuleEnemies()
{
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Assets/Sprites/Enemies/spriteEnemies.png");
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	/*for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
	if(queue[i].type != ENEMY_TYPES::NO_TYPE)
	{
	if(queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
	{
	SpawnEnemy(queue[i]);
	queue[i].type = ENEMY_TYPES::NO_TYPE;
	}
	}
	}*/
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (App->scene_temple->Time() >= queue[i].time && App->scene_temple->Time() < queue[i].time + 1)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			//if(enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			if (App->scene_temple->Time() > enemies[i]->time + DESPAWN_TIME)
			{
				delete enemies[i];
				enemies[i] = nullptr;
				LOG("Despawned enemy: %i" + i);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, float time)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].time = time;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::DEMONWHEEL:
			enemies[i] = new EnemyDemonWheel(info.x, info.y, info.time);
			LOG("Spawned enemy: %i" + i);
			break;

			/*case ENEMY_TYPES::PEGTOP:
			enemies[i] = new EnemyPegTop(info.x, info.y, info.time);
			break;*/

		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}