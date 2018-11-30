#include "GameTime.h"
#include <iostream>

namespace jm
{ 
	GameTime* GameTime::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameTime();
		}
		return instance;
	}

	float GameTime::getDeltaTime() const
	{
		return deltaTime;
	}
	void GameTime::setDeltaTime(float dt)
	{
		deltaTime = dt;
		runTime += dt;
	}
	float GameTime::getRunTime() const
	{
		return runTime;
	}

	GameTime* GameTime::instance = nullptr;
}