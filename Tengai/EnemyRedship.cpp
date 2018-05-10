#include "Application.h"
#include "EnemyREDSHIP.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleParticles.h"

EnemyREDSHIP::EnemyREDSHIP(int x, int y, float time) : Enemy(x, y,time)
{
	flyforward.PushBack({ 0, 96, 32, 32 });
	flyforward.PushBack({ 32, 96, 32, 32 });
	flyforward.PushBack({ 64, 96, 32, 32 });
	flyforward.PushBack({ 96, 96, 32, 32 });
	flyforward.PushBack({ 0, 96, 32, 32 });
	flyforward.PushBack({ 32, 96, 32, 32 });
	flyforward.PushBack({ 64, 96, 32, 32 });
	flyforward.PushBack({ 96, 96, 32, 32 });
	flyforward.PushBack({ 0, 96, 32, 32 });
	flyforward.PushBack({ 32, 96, 32, 32 });
	flyforward.PushBack({ 64, 96, 32, 32 });
	flyforward.PushBack({ 96, 96, 32, 32 });
	//attack
	flyforward.PushBack({ 0, 128, 32, 32 });
	flyforward.PushBack({ 32, 128, 32, 32 });
	flyforward.PushBack({ 64, 128, 32, 32 });
	flyforward.PushBack({ 96, 128, 32, 32 });
	flyforward.PushBack({ 0, 160, 32, 32 });
	flyforward.PushBack({ 32, 160, 32, 32 });

	flyforward.speed = 0.2f;

	animation = &flyforward;

	collider = App->collision->AddCollider({0, 0, 32, 32}, COLLIDER_TYPE::COLLIDER_ENEMY_REDSHIP, (Module*)App->enemies);

	originalPosition = { x,y };
	spawnTime = time;
}

void EnemyREDSHIP::Move()
{
	/*if(going_up)
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
	position.x -= 1;*/
	if (pathAssigned == false) {
		pathAssigned = true;
		if (position.y < 0) {
			path.PushBack({ 0, +1 }, 100, &flyforward);
			path.PushBack({ +1, 0 }, 5000, &flyforward);
		}
		if (position.y > 0 && position.y < 224) {
			path.PushBack({ -1.5f, 0 }, 100, &flyforward);
			path.PushBack({ +1, 0 }, 5000, &flyforward);
		}
		if (position.y >224) {
			path.PushBack({ 0, -1 }, 100, &flyforward);
			path.PushBack({ +1, 0 }, 5000, &flyforward);
		}
	}
	position = originalPosition + path.GetCurrentPosition(&animation);


	frameTime++;
	innerClock = frameTime / 60.000000000f;
	if (position.x > 0 && position.x < 304 && position.y > -16 && position.y < 240) {
		if (innerClock > 1.5f && shots == 0) {
			shots++;
			App->particles->AddParticle(App->particles->enemyshot, position.x + 13, position.y + 13, COLLIDER_ENEMY_SHOT);
		}
		if (innerClock > 3.0f && shots == 1) {
			shots++;
			App->particles->AddParticle(App->particles->enemyshot, position.x + 13, position.y + 13, COLLIDER_ENEMY_SHOT);
		}
		if (innerClock > 4.5f && shots == 2) {
			shots++;
			App->particles->AddParticle(App->particles->enemyshot, position.x + 13, position.y + 13, COLLIDER_ENEMY_SHOT);
		}
		if (innerClock > 6.0f && shots == 3) {
			shots++;
			App->particles->AddParticle(App->particles->enemyshot, position.x + 13, position.y + 13, COLLIDER_ENEMY_SHOT);
		}
	}
}
