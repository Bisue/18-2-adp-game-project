#include "GameTime.h"
#include <iostream>

namespace jm
{ 
	float GameTime::getDeltaTime()
	{
		return deltaTime;
	}
	void GameTime::setDeltaTime(float dt)
	{
		deltaTime = dt;
		runTime += dt;
	}
	float GameTime::getRunTime()
	{
		return runTime;
	}

	GameTime* GameTime::instance = nullptr;
}