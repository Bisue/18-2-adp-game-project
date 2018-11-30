#include "Delay.h"

namespace jm
{
	Delay::Delay(const float& delay)
		: delay(delay)
	{
		timer.start();
	}

	float Delay::getDelay() const
	{
		return delay;
	}
	void Delay::setDelay(const float& newDelay)
	{
		delay = newDelay;
	}

	bool Delay::check()
	{
		float temp = static_cast<float>(timer.stopAndGetElapsedMilli());
		if (temp >= delay * 1000)
		{
			timer.reset();
			return true;
		}
		else
		{
			return false;
		}
	}
}