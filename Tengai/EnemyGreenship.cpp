#include "Application.h"
#include "EnemyGREENSHIP.h"
#include "ModuleCollision.h"
#include "Globals.h"

EnemyGREENSHIP::EnemyGREENSHIP(int x, int y, float time) : Enemy(x, y, time)
{
	fly.PushBack({ 14, 15 , 30, 30 });
	fly.PushBack({ 61, 16, 30, 30 });
	fly.PushBack({ 107, 16, 30, 30 });
	fly.PushBack({ 152, 16, 30, 30 });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY_GREENSHIP, (Module*)App->enemies);

	original_y = y;
}

void EnemyGREENSHIP::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = original_y + int(25.0f * sinf(wave));
	position.x -= 1;
}
