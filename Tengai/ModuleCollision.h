#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 300

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_REDSHIP,
	COLLIDER_ENEMY_GREENSHIP,
	COLLIDER_ENEMY_NINJA,
	COLLIDER_ENEMY_SHOT,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		if (this != nullptr) {
			rect.x = x;
			rect.y = y;
		}
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void DebugDraw();

private:

	Collider * colliders[MAX_COLLIDERS] = { nullptr };
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__