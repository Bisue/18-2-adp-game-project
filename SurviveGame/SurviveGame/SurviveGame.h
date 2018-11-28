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
#include "GameTime.h"
#include "CrossHair.h"
#include "ScoreManager.h"

namespace jm
{
	class SurviveGame : public Game2D
	{
		using CM = CollisionManager;
		using SM = SoundManager;
	private:
		vec2 playerSpawnPoint = vec2(0.0f, 0.0f);
		CrossHair crossHair;
		Player* player = nullptr;
		std::vector<Bullet*> playerBullets;
		std::vector<Zombie*> zombies;
		std::vector<Item*> items;

		float screenBorder = 1.0f;

		int kill = 0;
		bool isItemGiven[4] = { false,false,false,false };

		bool gameover = false;

		Delay spawnDelay = Delay(1.5f);
		Delay spawnSpeedUpDelay = Delay(1.0f);

	public:
		SurviveGame()
			: Game2D("Survive Game", 960, 960, false)
		{
			SM::getInstance()->initSound("horror_bgm.wav", "bgm", true);
			SM::getInstance()->initSound("single_shot.wav", "playerShoot", false);
			SM::getInstance()->initSound("zombie_hit.wav", "zombieHit", false);
			SM::getInstance()->initSound("zombie_die.wav", "zombieDie", false);
			SM::getInstance()->initSound("shine.wav", "itemGen", false);
			SM::getInstance()->initSound("gameover_scream.mp3", "gameover", false);

			//BGM
			SM::getInstance()->playSound("bgm");

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
					SM::getInstance()->stopSound("playerShoot");
					SM::getInstance()->stopSound("zombieHit");
					SM::getInstance()->stopSound("zombieDie");
					SM::getInstance()->stopSound("bgm");
					SM::getInstance()->playSound("gameover");
					gameover = true;
				}
			}
		}
		void updateScore()
		{
			ScoreManager::getInstance()->setScore(kill*5+int(RUNTIME));
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
			case 20:
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
			player->move(dir.nomalized());

			//getMousePos
			vec2 mousePos = getCursorPos();
			//mouseLookAt
			player->lookAt(mousePos);
			//shoot
			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				player->shoot(playerBullets, mousePos);
			}
			//crossHair 업데이트
			crossHair.updateMousePos(mousePos);
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
				zombies[i]->moveTo(player->getPos());
				for (int j = playerBullets.size()-1; j >= 0; j--)
				{
					if(CM::getInstance()->checkCircleCollision(zombies[i], playerBullets[j]))
					{
						SM::getInstance()->stopAndPlaySound("zombieHit");

						float damage = playerBullets[j]->getDamage();
						delete playerBullets[j];
						playerBullets[j] = nullptr;
						playerBullets.erase(playerBullets.begin() + j);
						zombies[i]->hit(damage);
						if (zombies[i]->checkDie())
						{
							SM::getInstance()->stopAndPlaySound("zombieDie");

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
			for (int i = 0; i < playerBullets.size(); i++)
			{
				playerBullets[i]->update();
			}
			for (int i = 0; i < items.size(); i++)
			{
				items[i]->update();
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
			crossHair.render();
		}
		void debug()
		{
			std::cout << "curTime = " << RUNTIME << ", deltaTime = " << DELTATIME << std::endl;
		}
	};
}