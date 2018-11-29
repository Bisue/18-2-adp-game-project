#pragma once
#include "Game2D.h"
#include <vector>
#include <memory>

namespace jm
{
	class Player;
	class Bullet;
	class Monster;
	class Item;

	class ObjectManager
	{
	private:
		std::shared_ptr<Player> player;
		std::vector<std::shared_ptr<Bullet>> bullets;
		std::vector<std::shared_ptr<Monster>> monsters;
		std::vector<std::shared_ptr<Item>> items;

	public:
		//constructor (for init player)
		ObjectManager(const vec2& playerStartPoint, const float& playerSpeed);
		
		//add
		void addBullet(Bullet& bullet);
		void addItem(Item& item);
		template <class MobType>
		void addMonster(MobType& monster);
		//update
		void update();
		void updateBullets();
		void updateMonsters();
		void updateItems();
	};
}