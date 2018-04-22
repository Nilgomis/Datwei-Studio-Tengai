#ifndef __ENEMYPEGTOP_H__
#define __ENEMYPEGTOP_H__

#include "Enemy.h"
#include "Path.h"

class EnemyPegTop : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	EnemyPegTop(int x, int y);

	void Move();
};

#endif // __ENEMYPEGTOP_H__