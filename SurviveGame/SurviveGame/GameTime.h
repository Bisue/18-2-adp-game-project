#pragma once
#include <iostream>

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