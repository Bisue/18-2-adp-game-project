#pragma once
#include "Monster.h"
#include "Delay.h"

namespace jm
{
	class Runner : public Monster
	{
	private:

	public:
		Runner(const vec2 position)
			: Monster(position, 0.5f, 0.06f, 40.0f, Delay(5.0f), 100.0f)
		{

		}

		void drawBody() const override
		{
			beginTransformation();
			{
				drawFilledCircle(Colors::deepdarkred, bodyRadius);
				translate(bodyRadius*0.35f, 0);
				beginTransformation();
				{
					translate(0, bodyRadius);
					drawFilledCircle(Colors::darkred, bodyRadius*0.35f);
				}
				endTransformation();
				beginTransformation();
				{
					translate(0, -bodyRadius);
					drawFilledCircle(Colors::darkred, bodyRadius*0.35f);
				}
				endTransformation();
			}
			endTransformation();
		}
	};
}