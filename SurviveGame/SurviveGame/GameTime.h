#pragma once
#include <iostream>

//편의용 매크로들
#define DELTATIME (GameTime::getInstance()->getDeltaTime())
#define RUNTIME (GameTime::getInstance()->getRunTime())

namespace jm
{
	//싱글턴
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

		float getDeltaTime() const;
		void setDeltaTime(float dt);
		float getRunTime() const;
	};
}