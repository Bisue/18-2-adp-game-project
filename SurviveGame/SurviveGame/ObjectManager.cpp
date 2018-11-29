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
		if (instance == nullptr)
		{
			instance = new ObjectManager(vec2(0, 0), 5.0f);
		}
		return instance;
	}

	std::shared_ptr<Player>& ObjectManager::getPlayer()
	{
		return player;
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
	void ObjectManager::addMonster(Monster& monster)
	{
		monsters.push_back(std::make_shared<Monster>(monster));
	}

	void ObjectManager::update()
	{
		updateBullets();
		updateMonsters();
		updateItems();
	}
	void ObjectManager::updateBullets()
	{
		for (int i = bullets.size()-1; i >= 0; i--)
		{
			auto& bullet = bullets[i];
			if (!((bullet->getPos().x >= -SCREENBORDER && bullet->getPos().x <= SCREENBORDER) && (bullet->getPos().y >= -SCREENBORDER && bullet->getPos().y <= SCREENBORDER)))
			{
				bullets.erase(bullets.begin() + i);
			}
		}
	}
	void ObjectManager::updateMonsters()
	{
		for (int iM = monsters.size()-1; iM >= 0; iM--)
		{
			auto& monster = monsters[iM];
			for (int iB = bullets.size()-1; iB >= 0; iB--)
			{
				auto& bullet = bullets[iB];
				if (CM::getInstance()->checkCircleCollision(monster.get(), bullet.get()))
				{
					SM::getInstance()->stopAndPlaySound("zombieHit");

					float damage = bullet->getDamage();
					bullets.erase(bullets.begin()+iB);
					monster->hit(damage);
					if (monster->checkDie())
					{
						SM::getInstance()->stopAndPlaySound("zombieDie");

						monsters.erase(monsters.begin() + iM);
						ScoreManager::getInstance()->addKill(1);
						break;
					}
				}
			}
		}
	}
	void ObjectManager::updateItems()
	{
		for (int i = items.size()-1; i >= 0; i--)
		{
			auto& item = items[i];
			if (CM::getInstance()->checkCircleCollision(player.get(), item.get()))
			{
				items.erase(items.begin() + i);
				player->increasePower();
			}
		}
	}

	bool ObjectManager::gameoverManager()
	{
		for (int i = monsters.size()-1; i >= 0; i--)
		{
			auto& monster = monsters[i];
			if (CM::getInstance()->checkCircleCollision(player.get(), monster.get()))
			{
				SM::getInstance()->stopSound("playerShoot");
				SM::getInstance()->stopSound("zombieHit");
				SM::getInstance()->stopSound("zombieDie");
				SM::getInstance()->stopSound("bgm");

				SM::getInstance()->playSound("gameover");
				return true;
			}
		}
		return false;
	}

	void ObjectManager::render()
	{
		player->render();
		for (int i = items.size()-1; i >=0; i--)
		{
			auto& item = items[i];
			item->render();
		}
		for (int i = bullets.size()-1; i >= 0 ; i--)
		{
			auto& bullet = bullets[i];
			bullet->render();
		}
		for (int i = monsters.size()-1; i >= 0 ; i--)
		{
			auto& monster = monsters[i];
			monster->render();
		}
	}

	ObjectManager* ObjectManager::instance = nullptr;
}