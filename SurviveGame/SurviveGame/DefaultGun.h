#pragma once
#include "Gun.h"

namespace jm
{
	class DefaultGun : public Gun
	{
	private:

	public:
		DefaultGun(const vec2& initPos,)
			: Gun(initPos, Delay(0.3f), 4.0f)
		{

		}

		void fire(const vec2& targetPos) override
		{

		}
	};
}