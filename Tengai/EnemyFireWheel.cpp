#include "Application.h"
#include "EnemyFireWheel.h"
#include "ModuleCollision.h"
#include "Globals.h"

EnemyFireWheel::EnemyFireWheel(int x, int y) : Enemy(x, y)
{/*
	fly.PushBack({5,6,24,24});
	fly.PushBack({38, 6, 24, 24});
	fly.PushBack({71, 6, 24, 24});
	fly.PushBack({104, 6, 24, 24});
	fly.PushBack({137, 6, 24, 24});
	fly.PushBack({170, 6, 24, 24});
	fly.PushBack({203, 6, 24, 24});
	fly.PushBack({236, 6, 24, 24});
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({0, 0, 24, 24}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;*/
}

bool EnemyFireWheel::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	//enemy = App->textures->Load("Assets/Sprites/Characters/Sho/Sho spritesheet.png");
	return ret;
}

void EnemyFireWheel::Move()
{/*
	if(going_up)
	{
		if(wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if(wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = original_y + int(25.0f * sinf(wave));
	position.x -= 1;
	*/
}
