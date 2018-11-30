#pragma once
#include "Game2D.h"
#include <vector>
#include <memory>

namespace jm
{
	//singleton
	//#issues
	//1. vector ��ȯ���������� ���� �־���
	//- ����(���׳�): auto iter = xxx.begin() �� �̿��� for����
	//- ����: �ε����� ����
	//- �ذ�� ������ ����
	//2. std::shared_ptr������ ������ ����
	//- std::static_pointer_cast�� �ذ�� ������ ����
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