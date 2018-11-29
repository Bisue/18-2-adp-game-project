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
#include "Constants.h"
#include "ObjectManager.h"

namespace jm
{
	//TODO: 벡터(Bullets, Monsters, Items)를 각각 감싸고 있는 Wrapper클래스 구현
	//
	class SurviveGame : public Game2D
	{
	private:
		CrossHair crossHair;

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
		}
		void update() override
		{
			if (!gameover)
			{
				inputManage();
				spawnZombie();
				updateStuffs();
				giveItem();
				OM::getInstance()->update();
				gameoverManage();
				spawnSpeedUp();
				updateScore();
				render();
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
			gameover = OM::getInstance()->gameoverManager();
		}
		void updateScore()
		{
			ScoreManager::getInstance()->setScore(ScoreManager::getInstance()->getKill()*5+int(RUNTIME));
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
			switch ((ScoreManager::getInstance()->getKill()))
			{
			case 1:
				if (!isItemGiven[0])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[0] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 45:
				if (!isItemGiven[1])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[1] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 75:
				if (!isItemGiven[2])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[2] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 110:
				if (!isItemGiven[3])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[3] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
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
			auto& player = OM::getInstance()->getPlayer();
			if (player->getPos().x <= -SCREENBORDER)
			{
				dir.x = 1.0f;
			}
			if (player->getPos().x >= SCREENBORDER)
			{
				dir.x = -1.0f;
			}
			if (player->getPos().y <= -SCREENBORDER)
			{
				dir.y = 1.0f;
			}
			if (player->getPos().y >= SCREENBORDER)
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
				player->shoot(mousePos);
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
				spawnPoint.x = RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER);
				spawnPoint.y = 1.2f;
				break;
			case 2:
				spawnPoint.x = -1.2f;
				spawnPoint.y = RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER);
				break;
			case 3:
				spawnPoint.x = RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER);
				spawnPoint.y = -1.2f;
				break;
			case 4:
				spawnPoint.x = 1.2f;
				spawnPoint.y = RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER);
				break;
			}
			if (spawnDelay.check())
			{
				OM::getInstance()->addZombie(Zombie(spawnPoint));
			}
		}
		void updateStuffs()
		{
			OM::getInstance()->updateStuffs();
		}
		void render()
		{
			OM::getInstance()->render();
			crossHair.render();
		}
		void debug()
		{
			std::cout << "curTime = " << RUNTIME << ", deltaTime = " << DELTATIME << std::endl;
		}
	};
}