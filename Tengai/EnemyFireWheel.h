#ifndef __ENEMYFIREWHEEL_H__
#define __ENEMYFIREWHEEL_H__

#include "Enemy.h"
#include "Path.h"

class EnemyFireWheel : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	EnemyFireWheel(int x, int y);
	bool Start();
	void Move();
};

#endif // __ENEMY_REDBIRD_H__