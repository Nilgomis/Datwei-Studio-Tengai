#ifndef __ENEMYREDSHIP_H__
#define __ENEMYREDSHIP_H__

#include "Enemy.h"
#include "Path.h"

class EnemyREDSHIP : public Enemy
{
private:
	//float wave = -1.0f;
	//bool going_up = true;
	iPoint originalPosition;
	float spawnTime;
	Path path;
	//int original_y = 0;
	bool pathAssigned = false;
	float innerClock;
	float frameTime = 0;
	int shots = 0;
	Animation flyforward;
	Animation flybackward;

public:

	EnemyREDSHIP(int x, int y, float time);
	~EnemyREDSHIP(){};

	void Move();
	//void onCollision(Collider* Collider);
	//bool Cleanup();
};

#endif