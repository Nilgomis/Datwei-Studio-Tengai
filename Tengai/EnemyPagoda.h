#ifndef __ENEMYPAGODA_H__
#define __ENEMYPAGODA_H__

#include "Enemy.h"
#include "Path.h"

class EnemyPagoda : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation spin;

public:

	EnemyPagoda(int x, int y, float time);

	void Move();
};

#endif // __ENEMYPAGODA_H__