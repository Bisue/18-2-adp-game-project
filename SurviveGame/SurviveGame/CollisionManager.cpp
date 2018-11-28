#include "CollisionManager.h"

namespace jm
{
	bool CollisionManager::checkCircleCollision(const vec2& pos1, const float& rad1, const vec2& pos2, const float& rad2)
	{
		return circleToCircle(pos1, rad1, pos2, rad2);
	}
	bool CollisionManager::checkCircleCollision(const GameObject& go1, const GameObject& go2)
	{
		return circleToCircle(go1.getPos(), go1.getBodyRadius(), go2.getPos(), go2.getBodyRadius());
	}
	bool CollisionManager::checkCircleCollision(const GameObject* go1, const GameObject* go2)
	{
		return circleToCircle(go1->getPos(), go1->getBodyRadius(), go2->getPos(), go2->getBodyRadius());
	}
	bool CollisionManager::checkCircleCollision(const GameObject& go1, const GameObject* go2)
	{
		return circleToCircle(go1.getPos(), go1.getBodyRadius(), go2->getPos(), go2->getBodyRadius());
	}
	bool CollisionManager::checkCircleCollision(const GameObject* go1, const GameObject& go2)
	{
		return circleToCircle(go1->getPos(), go1->getBodyRadius(), go2.getPos(), go2.getBodyRadius());
	}

	CollisionManager* CollisionManager::instance = nullptr;
}