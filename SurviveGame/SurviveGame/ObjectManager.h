#pragma once
#include "Game2D.h"
#include <vector>
#include <memory>

namespace jm
{
	//[미사용:버그]
	//vector for도는과정에서 오류가 생김.

	class Player;
	class Bullet;
	class Monster;
	class Item;

	class ObjectManager
	{
	private:
		static ObjectManager* instance;

		std::shared_ptr<Player> player;
		std::vector<std::shared_ptr<Bullet>> bullets;
		std::vector<std::shared_ptr<Monster>> monsters;
		std::vector<std::shared_ptr<Item>> items;

		//constructor (for init player)
		ObjectManager(const vec2& playerStartPoint, const float& playerSpeed);

	public:
		static ObjectManager* getInstance();

		std::shared_ptr<Player>& getPlayer();
		//add
		void addBullet(Bullet& bullet);
		void addItem(Item& item);
		void addMonster(Monster& monster);
		//update
		void update();
		void updateBullets();
		void updateMonsters();
		void updateItems();
		//manage
		bool gameoverManager();
		//render
		void render();
	};
	using OM = ObjectManager;
}