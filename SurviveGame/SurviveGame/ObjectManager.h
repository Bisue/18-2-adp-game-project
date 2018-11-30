#pragma once
#include "Game2D.h"
#include <vector>
#include <memory>

namespace jm
{
	//singleton
	//#issues
	//1. vector 순환과정에서의 버그 있었음
	//- 기존(버그남): auto iter = xxx.begin() 을 이용해 for돌림
	//- 현재: 인덱스로 돌림
	//- 해결된 것으로 보임
	//2. std::shared_ptr에서의 다형성 문제
	//- std::static_pointer_cast로 해결된 것으로 보임
	class Player;
	class Bullet;
	class Monster;
	class Zombie;
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
		void addBullet(const Bullet& bullet);
		void addItem(const Item& item);
		void addZombie(const Zombie& zombie);
		//update
		void update();
		void updateBullets();
		void updateMonsters();
		void updateItems();
		void updateStuffs();
		//manage
		bool gameoverManager();
		//render
		void render();
	};
	using OM = ObjectManager;
}