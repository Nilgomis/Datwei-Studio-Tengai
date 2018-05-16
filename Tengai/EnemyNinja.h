#ifndef __ENEMY_NINJA_H__
#define __ENEMY_NINJA_H__

#include "Enemy.h"
#include "Path.h"

class EnemyNinja : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint originalpos;

	Animation air;
	Animation run;
	Animation raise;
	Animation recharging;
	Animation shoot;
	Animation idle;
	Animation up;
	Path move;

public:
	EnemyNinja(int x, int y);
	void Move();

};

#endif // __ENEMY_NINJA_H__
