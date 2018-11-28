#pragma once
#include "Timer.h"

namespace jm
{
	class Delay
	{
	private:
		Timer timer;
		float delay;

	public:
		//constructor
		Delay(const float& delay)
			: delay(delay)
		{
			timer.start();
		}
		//getter, setter
		float getDelay() const
		{
			return delay;
		}
		void setDelay(const float& newDelay)
		{
			delay = newDelay;
		}
		//methods
		bool check()
		{
			float temp = static_cast<float>(timer.stopAndGetElapsedMilli());
			if (temp >= delay*1000)
			{
				timer.reset();
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}