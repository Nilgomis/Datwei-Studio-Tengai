#ifndef __ENEMYDEMONWHEEL_H__
#define __ENEMYDEMONWHEEL_H__

#include "Enemy.h"
#include "Path.h"

class EnemyDemonWheel : public Enemy
{
private:
	//float wave = -1.0f;
	//bool going_up = true;
	iPoint originalPosition;
	Path path;
	//int original_y = 0;
	Animation flyforward;
	Animation flybackward;

public:

	EnemyDemonWheel(int x, int y);
	~EnemyDemonWheel(){};

	void Move();
	//void onCollision(Collider* Collider);
	//bool Cleanup();
};

#endif