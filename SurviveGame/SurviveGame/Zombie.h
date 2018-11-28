#pragma once
#include "Monster.h"
#include "Delay.h"

namespace jm
{
	class Zombie : public Monster
	{
	private:

	public:
		Zombie(const vec2 position)
			: Monster(position, 0.4f, 0.05f, 200.0f, Delay(0.8f))
		{

		}

		void drawBody() const override
		{
			beginTransformation();
			{
				translate(position);
				beginTransformation();
				{
					drawFilledCircle(Colors::gray, bodyRadius);
				}
				endTransformation();
			}
			endTransformation();
		}
	};
}