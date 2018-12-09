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
			: Monster(position, 0.3f, 0.05f, 100.0f, Delay(1.0f), 0.5f)
		{

		}

		void drawBody() const override
		{
			beginTransformation();
			{
				//drawFilledCircle(Colors::deepdartgreen, bodyRadius);
				//translate(bodyRadius*0.35f, 0);
				//beginTransformation();
				//{
				//	translate(0, bodyRadius);
				//	drawFilledCircle(Colors::darkgreen, bodyRadius*0.35f);
				//}
				//endTransformation();
				//beginTransformation();
				//{
				//	translate(0, -bodyRadius);
				//	drawFilledCircle(Colors::darkgreen, bodyRadius*0.35f);
				//}
				//endTransformation();

				translate(bodyRadius*0.35f, 0);
				beginTransformation();
				{
					translate(0, bodyRadius);
					drawFilledCircle(Colors::darkgreen, bodyRadius*0.35f);
				}
				endTransformation();
				beginTransformation();
				{
					translate(0, -bodyRadius);
					drawFilledCircle(Colors::darkgreen, bodyRadius*0.35f);
				}
				endTransformation();
				translate(-bodyRadius*0.35f, 0);
				drawFilledCircle(Colors::deepdartgreen, bodyRadius);
			}
			endTransformation();
		}
	};
}