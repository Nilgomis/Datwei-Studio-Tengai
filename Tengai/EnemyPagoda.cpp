#include "Application.h"
#include "EnemyPagoda.h"
#include "ModuleCollision.h"
#include "Globals.h"

EnemyPagoda::EnemyPagoda(int x, int y, float time) : Enemy(x, y, time)
{
	spin.PushBack({ 14, 15 , 30, 30 });
	spin.PushBack({ 61, 16, 30, 30 });
	spin.PushBack({ 107, 16, 30, 30 });
	spin.PushBack({ 152, 16, 30, 30 });
	spin.speed = 0.2f;

	animation = &spin;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY_GREENSHIP, (Module*)App->enemies);

	original_y = y;
}

void EnemyPagoda::Move()
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
