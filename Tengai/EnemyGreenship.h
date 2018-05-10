#ifndef __ENEMYGREENSHIP_H__
#define __ENEMYGREENSHIP_H__

#include "Enemy.h"
#include "Path.h"

class EnemyGREENSHIP : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	EnemyGREENSHIP(int x, int y, float time);

	void Move();
};

#endif // __ENEMYGREENSHIP_H__