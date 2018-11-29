#pragma once
#include "GameObject.h"

namespace jm
{
	//singleton
	class CollisionManager
	{
	private:
		static CollisionManager* instance;
		CollisionManager()
		{ }
		CollisionManager(const CollisionManager& other)
		{ }

		bool circleToCircle(const vec2& pos1, const float& rad1, const vec2& pos2, const float& rad2);

	public:
		static CollisionManager* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new CollisionManager();
			}
			return instance;
		}
		bool checkCircleCollision(const vec2& pos1, const float& rad1, const vec2& pos2, const float& rad2);
		bool checkCircleCollision(const GameObject& go1, const GameObject& go2);
		bool checkCircleCollision(const GameObject* go1, const GameObject* go2);
		bool checkCircleCollision(const GameObject& go1, const GameObject* go2);
		bool checkCircleCollision(const GameObject* go1, const GameObject& go2);
	};
	using CM = CollisionManager;
}