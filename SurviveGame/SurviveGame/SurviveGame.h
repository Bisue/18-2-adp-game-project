#pragma once
#include "Game2D.h"
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Runner.h"
#include "Tanker.h"
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
#include "Alphabets.h"

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

		Delay zombieSpawnDelay = Delay(1.5f);          //default = 1.5f;
		Delay zombieSpawnSpeedUpDelay = Delay(2.0f);   //default = 2.0f;
		Delay runnerSpawnDelay = Delay(3.5f);          //default = 3.5f;
		Delay runnerSpawnSpeedUpDelay = Delay(4.0f);   //default = 4.0f;
		Delay tankerSpawnDelay = Delay(15.0f);         //default = 15.0f;
		Delay tankerSpawnSpeedUpDelay = Delay(20.0f);  //default = 20.0f;

	public:
		SurviveGame()
			: Game2D("Survive Game", 960, 960, false)
		{
			SM::getInstance()->initSound("horror_bgm.wav", "bgm", true);
			SM::getInstance()->initSound("single_shot.wav", "defaultGunShoot", false);
			SM::getInstance()->initSound("multi_shot.wav", "shotGunShoot", false);
			SM::getInstance()->initSound("short_shot.wav", "smgGunShoot", false);
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
				giveItem();
				OM::getInstance()->update();
				gameoverManage();
				spawnSpeedUp();
				updateScore();
				render();
			}
			else
			{
				gameoverScreen();
			}
		}

		void gameoverScreen()
		{
			float fontSize = 0.2f;
			float fontSize1 = 0.1f;
			std::vector<std::reference_wrapper<Alphabet>> youdied;
			std::vector<std::reference_wrapper<Alphabet>> enter;

			//YOU DIED
			AlphaY a1(vec2(-fontSize, fontSize), Colors::red, fontSize);
			youdied.push_back(a1);
			AlphaO a2(vec2(0, fontSize), Colors::red, fontSize);
			youdied.push_back(a2);
			AlphaU a3(vec2(fontSize, fontSize), Colors::red, fontSize);
			youdied.push_back(a3);

			AlphaD a4(vec2(-1.5f*fontSize, 0), Colors::red, fontSize);
			youdied.push_back(a4);
			AlphaI a5(vec2(-0.5f*fontSize, 0), Colors::red, fontSize);
			youdied.push_back(a5);
			AlphaE a6(vec2(0.5f*fontSize, 0), Colors::red, fontSize);
			youdied.push_back(a6);
			AlphaD a7(vec2(1.5f*fontSize, 0), Colors::red, fontSize);
			youdied.push_back(a7);

			//PRESS ESC TO EXIT
			AlphaP b1(vec2(-4*fontSize1, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b1);
			AlphaR b2(vec2(-3*fontSize1, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b2);
			AlphaE b3(vec2(-2*fontSize1, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b3);
			AlphaS b4(vec2(-fontSize1, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b4);
			AlphaS b5(vec2(0, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b5);

			AlphaE b6(vec2(2* fontSize1, -2 * fontSize1), Colors::blue, fontSize1);
			enter.push_back(b6);
			AlphaS b7(vec2(3* fontSize1, -2 * fontSize1), Colors::blue, fontSize1);
			enter.push_back(b7);
			AlphaC b8(vec2(4* fontSize1, -2 * fontSize1), Colors::blue, fontSize1);
			enter.push_back(b8);

			AlphaT b9(vec2(-3*fontSize1, -3 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b9);
			AlphaO b10(vec2(-2*fontSize1, -3 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b10);

			AlphaE b11(vec2(0, -3 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b11);
			AlphaX b12(vec2(fontSize1, -3 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b12);
			AlphaI b13(vec2(2*fontSize1, -3 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b13);
			AlphaT b14(vec2(3*fontSize1, -3 * fontSize1), Colors::black, fontSize1);
			enter.push_back(b14);

			//render
			for (auto alpha : youdied)
			{
				alpha.get().render();
			}
			for (auto alpha : enter)
			{
				alpha.get().render();
			}
		}
		void gameoverManage()
		{
			gameover = OM::getInstance()->gameoverManager();
			if (gameover)
			{
				std::cout << "\n생존 시간 = " << RUNTIME <<"(초)" << std::endl;
				std::cout << "킬 수 = " << ScoreManager::getInstance()->getKill() << std::endl;
				std::cout << "총 점수 = " << ScoreManager::getInstance()->getScore() << std::endl;
			}
		}
		void updateScore()
		{
			SCM::getInstance()->setScore(SCM::getInstance()->getKill()*5+int(RUNTIME));
		}
		void spawnSpeedUp()
		{
			if (zombieSpawnDelay.getDelay() >= 0.65f)
			{
				if (zombieSpawnSpeedUpDelay.check())
				{
					zombieSpawnDelay.setDelay(zombieSpawnDelay.getDelay()*0.98f);
				}
			}
			if (runnerSpawnSpeedUpDelay.getDelay() >= 1.5f)
			{
				if (runnerSpawnSpeedUpDelay.check())
				{
					runnerSpawnDelay.setDelay(runnerSpawnDelay.getDelay()*0.98f);
				}
			}
			if (tankerSpawnSpeedUpDelay.getDelay() >= 8.0f)
			{
				if (tankerSpawnSpeedUpDelay.check())
				{
					tankerSpawnDelay.setDelay(tankerSpawnDelay.getDelay()*0.98f);
				}
			}
		}
		void giveItem()
		{
			switch ((ScoreManager::getInstance()->getKill()))
			{
			case 5:
				if (!isItemGiven[0])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[0] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 10:
				if (!isItemGiven[1])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[1] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 15:
				if (!isItemGiven[2])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[2] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 20:
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
			//이동
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

			//플레이어 무기교체
			if (isKeyPressedAndReleased(GLFW_KEY_1))
			{
				player->changeGun(1);
			}
			if (isKeyPressedAndReleased(GLFW_KEY_2))
			{
				player->changeGun(2);
			}
			if (isKeyPressedAndReleased(GLFW_KEY_3))
			{
				player->changeGun(3);
			}

			//마우스 입력관련
			vec2 mousePos = getCursorPos();
			//lookAt
			player->lookAt(mousePos);
			//발사
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
			if (zombieSpawnDelay.check())
			{
				OM::getInstance()->addZombie(Zombie(spawnPoint));
			}
			if (runnerSpawnDelay.check())
			{
				OM::getInstance()->addRunner(Runner(spawnPoint));
			}
			if (tankerSpawnDelay.check())
			{
				OM::getInstance()->addTanker(Tanker(spawnPoint));
			}
		}
		void render()
		{
			OM::getInstance()->render();
			crossHair.render();
		}
	};
}