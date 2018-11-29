#include "ObjectManager.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Item.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "ScoreManager.h"
#include "Constants.h"

namespace jm
{
	ObjectManager* ObjectManager::getInstance()
	{
		if (instance = nullptr)
		{
			instance = new ObjectManager(vec2(0, 0), 5.0f);
		}
		return instance;
	}

	ObjectManager::ObjectManager(const vec2& playerStartPoint, const float& playerSpeed)
	{
		player = std::make_shared<Player>(playerStartPoint, playerSpeed);
	}
	void ObjectManager::addBullet(Bullet& bullet)
	{
		bullets.push_back(std::make_shared<Bullet>(bullet));
	}
	void ObjectManager::addItem(Item& item)
	{
		items.push_back(std::make_shared<Item>(item));
	}
	template <class MobType>
	void ObjectManager::addMonster(MobType& monster)
	{
		monsters.push_back(std::shared_ptr<MobType>(monster));
	}

	void ObjectManager::update()
	{
		updateBullets();
		updateMonsters();
		updateItems();
	}
	void ObjectManager::updateBullets()
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
	void ObjectManager::updateMonsters()
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
	void ObjectManager::updateItems()
	{
		for (auto iter = items.begin(); iter < items.end(); iter++)
		{
			auto item = *iter;
			if (CM::getInstance()->checkCircleCollision(player.get(), item.get()))
			{
				iter = items.erase(iter) - 1;
				player->increasePower();
			}
		}
	}

	ObjectManager* ObjectManager::instance = nullptr;
}