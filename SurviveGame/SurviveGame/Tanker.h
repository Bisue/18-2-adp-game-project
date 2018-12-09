#pragma once
#include "Monster.h"
#include "Delay.h"

namespace jm
{
	class Tanker : public Monster
	{
	private:

	public:
		Tanker(const vec2 position)
			: Monster(position, 0.1f, 0.3f, 500.0f, Delay(1.0f), 2.0f)
		{

		}

		void drawBody() const override
		{
			beginTransformation();
			{
				//drawFilledCircle(Colors::deepdarkcrystal, bodyRadius);
				//translate(bodyRadius*0.35f, 0);
				//beginTransformation();
				//{
				//	translate(0, bodyRadius);
				//	drawFilledCircle(Colors::darkcrystal, bodyRadius*0.35f);
				//}
				//endTransformation();
				//beginTransformation();
				//{
				//	translate(0, -bodyRadius);
				//	drawFilledCircle(Colors::darkcrystal, bodyRadius*0.35f);
				//}
				//endTransformation();

				translate(bodyRadius*0.35f, 0);
				beginTransformation();
				{
					translate(0, bodyRadius);
					drawFilledCircle(Colors::darkcrystal, bodyRadius*0.35f);
				}
				endTransformation();
				beginTransformation();
				{
					translate(0, -bodyRadius);
					drawFilledCircle(Colors::darkcrystal, bodyRadius*0.35f);
				}
				endTransformation();
				translate(-bodyRadius*0.35f, 0);
				drawFilledCircle(Colors::deepdarkcrystal, bodyRadius);
			}
			endTransformation();
		}
	};
}