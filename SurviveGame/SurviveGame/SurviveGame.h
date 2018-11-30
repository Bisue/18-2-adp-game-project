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

		Delay spawnDelay = Delay(1.5f);
		Delay spawnSpeedUpDelay = Delay(1.0f);

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

			//youdied
			AlphaY y(vec2(-fontSize, fontSize), Colors::red, fontSize);
			youdied.push_back(y);
			AlphaO o(vec2(0, fontSize), Colors::red, fontSize);
			youdied.push_back(o);
			AlphaU u(vec2(fontSize, fontSize), Colors::red, fontSize);
			youdied.push_back(u);
			AlphaD d1(vec2(-1.5f*fontSize, 0), Colors::red, fontSize);
			youdied.push_back(d1);
			AlphaI i(vec2(-0.5f*fontSize, 0), Colors::red, fontSize);
			youdied.push_back(i);
			AlphaE e(vec2(0.5f*fontSize, 0), Colors::red, fontSize);
			youdied.push_back(e);
			AlphaD d2(vec2(1.5f*fontSize, 0), Colors::red, fontSize);
			youdied.push_back(d2);

			//enter esc to exit
			AlphaE e1(vec2(-4*fontSize1, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(e1);
			AlphaN n(vec2(-3*fontSize1, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(n);
			AlphaT t(vec2(-2*fontSize1, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(t);
			AlphaE e2(vec2(-fontSize1, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(e2);
			AlphaR r(vec2(0, -2 * fontSize1), Colors::black, fontSize1);
			enter.push_back(r);

			AlphaE e3(vec2(2* fontSize1, -2 * fontSize1), Colors::red, fontSize1);
			enter.push_back(e3);
			AlphaS s(vec2(3* fontSize1, -2 * fontSize1), Colors::red, fontSize1);
			enter.push_back(s);
			AlphaC c(vec2(4* fontSize1, -2 * fontSize1), Colors::red, fontSize1);
			enter.push_back(c);

			AlphaT t1(vec2(-3*fontSize1, -3 * fontSize1), Colors::red, fontSize1);
			enter.push_back(t1);
			AlphaO o1(vec2(-2*fontSize1, -3 * fontSize1), Colors::red, fontSize1);
			enter.push_back(o1);

			AlphaE e4(vec2(0, -3 * fontSize1), Colors::red, fontSize1);
			enter.push_back(e4);
			AlphaX x(vec2(1.5f*fontSize1, -3 * fontSize1), Colors::red, fontSize1);
			enter.push_back(x);
			AlphaI i1(vec2(1.5f*fontSize1, -3 * fontSize1), Colors::red, fontSize1);
			enter.push_back(i1);
			AlphaT t2(vec2(1.5f*fontSize1, -3 * fontSize1), Colors::red, fontSize1);
			enter.push_back(t2);


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
				std::cout << "Survive Time = " << RUNTIME <<"(s)" << std::endl;
				std::cout << "Kill = " << ScoreManager::getInstance()->getKill() << std::endl;
				std::cout << "Your Score = " << ScoreManager::getInstance()->getScore() << std::endl;
			}
		}
		void updateScore()
		{
			SCM::getInstance()->setScore(SCM::getInstance()->getKill()*5+int(RUNTIME));
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
			case 2:
				if (!isItemGiven[1])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[1] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 3:
				if (!isItemGiven[2])
				{
					OM::getInstance()->addItem(Item(vec2(RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER), RD::getInstance()->randomFloat(-SCREENBORDER, SCREENBORDER))));
					isItemGiven[2] = true;
					SM::getInstance()->playSound("itemGen");
				}
				break;
			case 4:
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
			if (spawnDelay.check())
			{
				OM::getInstance()->addZombie(Zombie(spawnPoint));
			}
		}
		void render()
		{
			OM::getInstance()->render();
			crossHair.render();
		}
	};
}