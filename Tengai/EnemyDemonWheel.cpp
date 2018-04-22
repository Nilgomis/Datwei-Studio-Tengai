#include "Application.h"
#include "EnemyDemonWheel.h"
#include "ModuleCollision.h"
#include "Globals.h"

EnemyDemonWheel::EnemyDemonWheel(int x, int y) : Enemy(x, y)
{
	flyforward.PushBack({ 1, 0, 30, 31 });
	flyforward.PushBack({ 33, 0, 30, 31 });
	flyforward.PushBack({ 65, 1, 30, 31 });
	flyforward.PushBack({ 97, 0, 30, 31 });
	flyforward.PushBack({ 0, 32, 30, 31 });
	flyforward.PushBack({ 32, 32, 30, 31 });
	flyforward.PushBack({ 64, 32, 30, 31 });
	flyforward.PushBack({ 97, 32, 30, 31 });
	flyforward.PushBack({ 1, 65, 30, 31 });
	flyforward.PushBack({ 32, 64, 30, 31 });
	flyforward.PushBack({ 64, 64, 30, 31 });
	flyforward.PushBack({ 96, 64, 30, 31 });

	path.PushBack({ -0.5f, 0 }, 500, &flyforward);
	flyforward.speed = 0.2f;

	animation = &flyforward;

	collider = App->collision->AddCollider({0, 0, 30, 31}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalPosition = { x,y };
}

void EnemyDemonWheel::Move()
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
	position = originalPosition + path.GetCurrentPosition(&animation);
}
