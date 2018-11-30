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
		Delay(const float& delay);
		//getter, setter
		float getDelay() const;
		void setDelay(const float& newDelay);
		//methods
		bool check();
	};
}