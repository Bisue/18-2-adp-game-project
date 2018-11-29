#pragma once
#include "Bullet.h"
#include <vector>
#include <memory>
#include "Constants.h"

namespace jm
{
	class BulletManager
	{
	private:
		static BulletManager* instance;

		std::vector<std::shared_ptr<Bullet>> body;

	public:
		static BulletManager* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new BulletManager();
			}
			return instance;
		}

		void add(Bullet& element)
		{
			body.push_back(std::make_shared<Bullet>(element));
		}

		std::vector<std::shared_ptr<Bullet>>& getBody()
		{
			return body;
		}

		void update()
		{
			for (auto iter = body.begin(); iter < body.end();)
			{
				auto bullet = *iter;
				if (!((bullet->getPos().x >= -SCREENBORDER && bullet->getPos().x <= SCREENBORDER) && (bullet->getPos().y >= -SCREENBORDER && bullet->getPos().y <= SCREENBORDER)))
				{
					iter = body.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
	};
}