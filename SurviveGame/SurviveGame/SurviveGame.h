#pragma once
#include "Game2D.h"
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include <random>
#include <vector>
#include "Randomization.h"
#include "Item.h"
#include "CollisionManager.h"
#include "Delay.h"
#include "SoundManager.h"

namespace jm
{
	class SurviveGame : public Game2D
	{
		using CM = CollisionManager;
		using RD = Randomization;
		using SM = SoundManager;
	private:
		vec2 playerSpawnPoint = vec2(0.0f, 0.0f);
		Player* player = nullptr;
		std::vector<Bullet*> playerBullets;
		std::vector<Zombie*> zombies;
		std::vector<Item*> items;

		float screenBorder = 1.0f;

		int score = 0;

		int kill = 0;
		bool isItemGiven[4] = { false,false,false,false };

		bool gameover = false;

		Delay spawnDelay = Delay(1.5f);
		Delay spawnSpeedUpDelay = Delay(1.0f);
		float gameTime = 0.0f;

	public:
		SurviveGame()
			: Game2D("Survive Game", 960, 960, false)
		{
			SM::getInstance()->initSound("hit.wav", "zombieHit", false);
			SM::getInstance()->initSound("boom.wav", "zombieDie", false);
			SM::getInstance()->initSound("shine.wav", "itemGen", false);

			player = new Player(playerSpawnPoint, 1.0f);
		}
		void update() override
		{
			if (!gameover)
			{
				inputManage();
				spawnZombie();
				updateStuffs();
				bulletManage();
				zombieManage();
				giveItem();
				itemManage();
				gameoverManage();
				render();
				spawnSpeedUp();
				updateScore();
				//debug();
			}
			else
			{
				gameoverScreen();
			}
		}
		
		void gameoverScreen()
		{
			beginTransformation();
			drawFilledStar(Colors::red, 1.0f, 0.5f);
			endTransformation();
		}
		void gameoverManage()
		{
			for (int i = 0; i < zombies.size(); i++)
			{
				if (CM::getInstance()->checkCircleCollision(player, zombies[i]))
				{
					gameover = true;
				}
			}
		}
		void updateScore()
		{
			score = (kill * 15 + int(gameTime) * 5);
			gameTime += getTimeStep();
		}
		void spawnSpeedUp()
		{
			if (spawnDelay.getDelay() >= 0.1f)
			{
				if (spawnSpeedUpDelay.check())
				{
					spawnDelay.setDelay(spawnDelay.getDelay()*0.98f);
				}
			}
		}
		void giveItem()
		{
			switch (kill)
			{
			case 1:
				if (!isItemGiven[0])
				{
					items.push_back(new Item(vec2(RD::getInstance()->randomFloat(-screenBorder, screenBorder), RD::getInstance()->randomFloat(-screenBorder, screenBorder))));
					isItemGiven[0] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 45:
				if (!isItemGiven[1])
				{
					items.push_back(new Item(vec2(RD::getInstance()->randomFloat(-screenBorder, screenBorder), RD::getInstance()->randomFloat(-screenBorder, screenBorder))));
					isItemGiven[1] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 75:
				if (!isItemGiven[2])
				{
					items.push_back(new Item(vec2(RD::getInstance()->randomFloat(-screenBorder, screenBorder), RD::getInstance()->randomFloat(-screenBorder, screenBorder))));
					isItemGiven[2] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 110:
				if (!isItemGiven[3])
				{
					items.push_back(new Item(vec2(RD::getInstance()->randomFloat(-screenBorder, screenBorder), RD::getInstance()->randomFloat(-screenBorder, screenBorder))));
					isItemGiven[3] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			}
		}
		void itemManage()
		{
			for (auto iter = items.begin(); iter < items.end();)
			{
				if (CM::getInstance()->checkCircleCollision(player, *iter))
				{
					delete *iter;
					iter = items.erase(iter);
					player->increasePower();
				}
				else
				{
					iter++;
				}
			}
		}
		void inputManage()
		{
			//move
			vec2 dir(0.0f, 0.0f);
			if (isKeyPressed(GLFW_KEY_W))
			{
				dir.y += 1.0f;
			}
			if (isKeyPressed(GLFW_KEY_S))
			{
				dir.y -= 1.0f;
			}
			if (isKeyPressed(GLFW_KEY_A))
			{
				dir.x -= 1.0f;
			}
			if (isKeyPressed(GLFW_KEY_D))
			{
				dir.x += 1.0f;
			}
			if (player->getPos().x <= -screenBorder)
			{
				dir.x = 1.0f;
			}
			if (player->getPos().x >= screenBorder)
			{
				dir.x = -1.0f;
			}
			if (player->getPos().y <= -screenBorder)
			{
				dir.y = 1.0f;
			}
			if (player->getPos().y >= screenBorder)
			{
				dir.y = -1.0f;
			}

			player->move(dir, getTimeStep());

			//getMousePos
			vec2 mousePos = getCursorPos();
			//mouseLookAt
			player->lookAt(mousePos);
			//shoot
			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				player->shoot(playerBullets, mousePos);
			}
		}
		void spawnZombie()
		{
			int sideFlag = RD::getInstance()->randomInt(1, 4);
			vec2 spawnPoint;
			switch (sideFlag)
			{
			case 1:
				spawnPoint.x = RD::getInstance()->randomFloat(-screenBorder, screenBorder);
				spawnPoint.y = 1.2f;
				break;
			case 2:
				spawnPoint.x = -1.2f;
				spawnPoint.y = RD::getInstance()->randomFloat(-screenBorder, screenBorder);
				break;
			case 3:
				spawnPoint.x = RD::getInstance()->randomFloat(-screenBorder, screenBorder);
				spawnPoint.y = -1.2f;
				break;
			case 4:
				spawnPoint.x = 1.2f;
				spawnPoint.y = RD::getInstance()->randomFloat(-screenBorder, screenBorder);
				break;
			}
			if (spawnDelay.check())
			{
				zombies.push_back(new Zombie(spawnPoint));
			}
		}
		void bulletManage()
		{
			for (auto iter = playerBullets.begin(); iter<playerBullets.end();)
			{
				auto bullet = *iter;
				if (!((bullet->getPos().x >= -screenBorder&&bullet->getPos().x <= screenBorder) && (bullet->getPos().y >= -screenBorder &&bullet->getPos().y <= screenBorder)))
				{
					delete bullet;
					iter = playerBullets.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
		void zombieManage()
		{
			for (int i = zombies.size()-1; i >=0; i--)
			{
				zombies[i]->moveTo(player->getPos(), getTimeStep());
				for (int j = playerBullets.size()-1; j >= 0; j--)
				{
					if(CM::getInstance()->checkCircleCollision(zombies[i], playerBullets[j]))
					{
						SM::getInstance()->playSound("zombieHit");

						float damage = playerBullets[j]->getDamage();
						delete playerBullets[j];
						playerBullets[j] = nullptr;
						playerBullets.erase(playerBullets.begin() + j);
						zombies[i]->hit(damage);
						if (zombies[i]->checkDie())
						{
							SM::getInstance()->playSound("zombieDie");

							delete zombies[i];
							zombies[i] = nullptr;
							zombies.erase(zombies.begin() + i);

							kill++;
							break;
						}
					}
				}
			}
		}
		void updateStuffs()
		{
			float timeStep = getTimeStep();
			player->update(timeStep);
			for (int i = 0; i < playerBullets.size(); i++)
			{
				playerBullets[i]->update(timeStep);
			}
			for (int i = 0; i < items.size(); i++)
			{
				items[i]->update(timeStep);
			}
		}
		void render()
		{
			player->render();
			for (int i = 0; i < items.size(); i++)
			{
				items[i]->render();
			}
			for (int i = 0; i < playerBullets.size(); i++)
			{
				playerBullets[i]->render();
			}
			for (int i = 0; i < zombies.size(); i++)
			{
				zombies[i]->render();
			}
			
			//crosshair
			beginTransformation();
			translate(getCursorPos());
			drawFilledCircle(Colors::green, 0.01f);
			drawWiredCircle(Colors::green, 0.04f);
			endTransformation();
		}
		void debug()
		{
			std::cout << "randDir = " <<RD::getInstance()->randomDirVector()<< std::endl;
		}
	};
}