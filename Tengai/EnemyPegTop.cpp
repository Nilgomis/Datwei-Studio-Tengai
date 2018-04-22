#include "Application.h"
#include "EnemyPegTop.h"
#include "ModuleCollision.h"
#include "Globals.h"

EnemyPegTop::EnemyPegTop(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 39, 10 , 42, 48 });
	fly.PushBack({ 83, 10, 42, 48 });
	fly.PushBack({ 128, 10, 42, 48 });
	fly.PushBack({ 172, 10, 42, 48 });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 42, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void EnemyPegTop::Move()
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
