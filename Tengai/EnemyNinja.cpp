#include "Application.h"
#include "EnemyNinja.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"

EnemyNinja::EnemyNinja(int x, int y) :Enemy(x, y, time)
{
	air.PushBack({ 19, 113, 30, 42 });

	recharging.PushBack({ 414, 65, 22, 34 });

	shoot.PushBack({ 458, 64, 41, 37 });

	raise.PushBack({ 159, 113, 30, 42 });
	raise.PushBack({ 65,113,30,42 });
	raise.PushBack({ 112,113,30,42 });
	raise.PushBack({ 158,113,30,42 });
	raise.speed = 0.2f;

	run.PushBack({ 206,14,43,34 });
	run.PushBack({ 253,14,48,34 });
	run.PushBack({ 312,14,27,34 });
	run.PushBack({ 362,14,36,34 });
	run.PushBack({ 414,8,37,39 });
	run.PushBack({ 206,66,43,34 });
	run.PushBack({ 253,66,27,35 });
	run.PushBack({ 312,67,43,34 });
	run.PushBack({ 253,66,27,35 });

	up.PushBack({ 362,68,27,33 });
	idle.PushBack({ 362,68,27,33 });

	move.PushBack({ 1.75f, 3.0f }, 8, &air);
	move.PushBack({ 1.75f, 3.0f }, 10, &recharging);
	move.PushBack({ 1.75f, 3.0f }, 40, &shoot);
	move.PushBack({ 1.0f, 0.0f }, 20, &raise);
	move.PushBack({ -1.5f, 0.0f }, 40, &run);
	move.PushBack({ 5.50f,-4.00f }, 80, &up);
	move.PushBack({ 0.0f,0.0f }, 10000, &idle);

	animation = &air;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY_NINJA, (Module*)App->enemies);

	originalpos.y = y;
	originalpos.x = x;
}