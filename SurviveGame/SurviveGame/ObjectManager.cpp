#include "ObjectManager.h"
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Runner.h"
#include "Tanker.h"
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
			instance = new ObjectManager(vec2(0, 0), 1.0f);
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
	void ObjectManager::addBullet(const Bullet& bullet)
	{
		bullets.push_back(std::make_shared<Bullet>(bullet));
	}
	void ObjectManager::addItem(const Item& item)
	{
		items.push_back(std::make_shared<Item>(item));
	}
	void ObjectManager::addZombie(const Zombie& zombie)
	{
		std::shared_ptr<Zombie> temp = std::make_shared<Zombie>(zombie);
		monsters.push_back(std::static_pointer_cast<std::shared_ptr<Monster>::element_type>(temp));
	}
	void ObjectManager::addRunner(const Runner& runner)
	{
		std::shared_ptr<Runner> temp = std::make_shared<Runner>(runner);
		monsters.push_back(std::static_pointer_cast<std::shared_ptr<Monster>::element_type>(temp));
	}
	void ObjectManager::addTanker(const Tanker& tanker)
	{
		std::shared_ptr<Tanker> temp = std::make_shared<Tanker>(tanker);
		monsters.push_back(std::static_pointer_cast<std::shared_ptr<Monster>::element_type>(temp));
	}

	void ObjectManager::update()
	{
		updateStuffs();
		updateBullets();
		updateMonsters();
		updateItems();
	}
	void ObjectManager::updateBullets()
	{
		for (int i = static_cast<int>(bullets.size())-1; i >= 0; i--)
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
		for (int iM = static_cast<int>(monsters.size())-1; iM >= 0; iM--)
		{
			auto& monster = monsters[iM];
			monster->moveTo(player->getPos());
			for (int iB = static_cast<int>(bullets.size())-1; iB >= 0; iB--)
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
		for (int i = static_cast<int>(items.size())-1; i >= 0; i--)
		{
			auto& item = items[i];
			if (CM::getInstance()->checkCircleCollision(player.get(), item.get()))
			{
				items.erase(items.begin() + i);
				player->enableGun();
				player->changeGun(player->getNextUnlockGunNum()-1);
			}
		}
	}
	void ObjectManager::updateStuffs()
	{
		player->update();
		for (int i = static_cast<int>(bullets.size())-1; i >= 0; i--)
		{
			auto& bullet = bullets[i];
			bullet->update();
		}
		for (int i = static_cast<int>(items.size()) - 1; i >= 0; i--)
		{
			auto& item = items[i];
			item->update();
		}
	}

	bool ObjectManager::gameoverManager()
	{
		for (int i = static_cast<int>(monsters.size())-1; i >= 0; i--)
		{
			auto& monster = monsters[i];
			if (CM::getInstance()->checkCircleCollision(player.get(), monster.get()))
			{
				SM::getInstance()->stopSound("defaultGunShoot");
				SM::getInstance()->stopSound("shotGunShoot");
				SM::getInstance()->stopSound("smgGunShoot");
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
		for (int i = static_cast<int>(items.size())-1; i >=0; i--)
		{
			auto& item = items[i];
			item->render();
		}
		for (int i = static_cast<int>(bullets.size())-1; i >= 0 ; i--)
		{
			auto& bullet = bullets[i];
			bullet->render();
		}
		for (int i = static_cast<int>(monsters.size())-1; i >= 0 ; i--)
		{
			auto& monster = monsters[i];
			monster->render();
		}
	}

	ObjectManager* ObjectManager::instance = nullptr;
}