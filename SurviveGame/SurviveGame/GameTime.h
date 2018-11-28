#pragma once
#include <iostream>

//���ǿ� ��ũ�ε�
#define DELTATIME (GameTime::getInstance()->getDeltaTime())
#define RUNTIME (GameTime::getInstance()->getRunTime())

namespace jm
{
	//singleton
	class GameTime
	{
	private:
		static GameTime* instance;

		float runTime = 0;
		float deltaTime = 0;

		GameTime()
		{ }
		GameTime(const GameTime& other)
		{ }

	public:
		static GameTime* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new GameTime();
			}
			return instance;
		}

		float getDeltaTime();
		void setDeltaTime(float dt);
		float getRunTime();
	};
}