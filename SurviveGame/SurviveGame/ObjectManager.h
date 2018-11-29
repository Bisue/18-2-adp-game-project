#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Zombie.h"
#include "Item.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "ScoreManager.h"
#include "Constants.h"
#include <vector>
#include <memory>

namespace jm
{
	class ObjectManager
	{
	private:
		std::shared_ptr<Player> player;
		std::vector<std::shared_ptr<Bullet>> bullets;
		std::vector<std::shared_ptr<Monster>> monsters;
		std::vector<std::shared_ptr<Item>> items;

	public:
		//constructor (for init player)
		ObjectManager(const vec2& playerStartPoint, const float& playerSpeed)
		{
			player = std::make_shared<Player>(playerStartPoint, playerSpeed);
		}
		
		//add
		void addBullet(Bullet& bullet)
		{
			bullets.push_back(std::make_shared<Bullet>(bullet));
		}
		void addItem(Item& item)
		{
			items.push_back(std::make_shared<Item>(item));
		}
		template <class MobType>
		void addMonster(MobType& monster)
		{
			monsters.push_back(std::shared_ptr<MobType>(monster));
		}
		//update
		void update()
		{
			updateBullets();
			updateMonsters();
			updateItems();
		}
		void updateBullets()
		{
			for (auto iter = bullets.begin(); iter < bullets.end();)
			{
				auto bullet = *iter;
				if (!((bullet->getPos().x >= -SCREENBORDER && bullet->getPos().x <= SCREENBORDER) && (bullet->getPos().y >= -SCREENBORDER && bullet->getPos().y <= SCREENBORDER)))
				{
					iter = bullets.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
		void updateMonsters()
		{
			for (auto iterM = monsters.begin(); iterM < monsters.end(); iterM++)
			{
				auto monster = *iterM;
				for (auto iterB = bullets.begin(); iterB < bullets.end(); iterB++)
				{
					auto bullet = *iterB;
					if (CM::getInstance()->checkCircleCollision(monster.get(), bullet.get()))
					{
						SM::getInstance()->stopAndPlaySound("zombieHit");

						float damage = bullet->getDamage();
						iterB = bullets.erase(iterB) - 1;
						monster->hit(damage);
						if (monster->checkDie())
						{
							SM::getInstance()->stopAndPlaySound("zombieDie");
							
							iterM = monsters.erase(iterM) - 1;
							ScoreManager::getInstance()->addKill(1);
							break;
						}
					}
				}
			}
		}
		void updateItems()
		{
			for (auto iter = items.begin(); iter < items.end();iter++)
			{
				auto item = *iter;
				if (CM::getInstance()->checkCircleCollision(player.get(), item.get()))
				{
					iter = items.erase(iter) - 1;
					player->increasePower();
				}
			}
		}
	};
}